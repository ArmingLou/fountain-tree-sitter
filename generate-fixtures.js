#!/usr/bin/env node
const fs = require('fs');
const path = require('path');
const { exec } = require('node:child_process');
const { promisify } = require('node:util');

const execAsync = promisify(exec);

/**
 * Parse tree-sitter CLI output into a JSON AST structure with text content
 */
function parseTreeSitterOutput(output, sourceText) {
  const lines = output.split('\n');
  const astStartIdx = lines.findIndex(line => line.trim().startsWith('(document'));
  if (astStartIdx === -1) {
    throw new Error('Could not find AST in output');
  }

  let astEndIdx = astStartIdx;
  let parenCount = 0;
  for (let i = astStartIdx; i < lines.length; i++) {
    const line = lines[i];
    if (line.includes('.fountain')) break;

    for (const char of line) {
      if (char === '(') parenCount++;
      if (char === ')') parenCount--;
    }
    astEndIdx = i;
    if (parenCount === 0) break;
  }

  const cleanOutput = lines.slice(astStartIdx, astEndIdx + 1).join('\n').trim();
  const sourceLines = sourceText.split('\n');

  const stack = [];
  let current = null;
  let i = 0;

  while (i < cleanOutput.length) {
    if (cleanOutput[i] === '(') {
      i++;
      let nodeType = '';
      while (i < cleanOutput.length && cleanOutput[i] !== ' ' && cleanOutput[i] !== ')' && cleanOutput[i] !== '\n') {
        nodeType += cleanOutput[i];
        i++;
      }

      const node = { type: nodeType, children: [] };

      if (current) {
        stack.push(current);
      }
      current = node;

      if (cleanOutput[i] === ' ' && cleanOutput[i + 1] === '[') {
        i += 2;
        let posStr = '';
        while (i < cleanOutput.length && cleanOutput[i] !== ']') {
          posStr += cleanOutput[i];
          i++;
        }
        const [startRow, startCol] = posStr.split(',').map(s => parseInt(s.trim()));

        i++;
        while (i < cleanOutput.length && cleanOutput[i] === ' ') i++;
        if (cleanOutput[i] === '-') {
          i++;
          while (i < cleanOutput.length && cleanOutput[i] === ' ') i++;
          if (cleanOutput[i] === '[') {
            i++;
            posStr = '';
            while (i < cleanOutput.length && cleanOutput[i] !== ']') {
              posStr += cleanOutput[i];
              i++;
            }
            const [endRow, endCol] = posStr.split(',').map(s => parseInt(s.trim()));

            if (startRow === endRow) {
              node.text = sourceLines[startRow]?.substring(startCol, endCol);
            } else {
              let text = sourceLines[startRow]?.substring(startCol) || '';
              for (let r = startRow + 1; r < endRow; r++) {
                text += '\n' + (sourceLines[r] || '');
              }
              if (endRow < sourceLines.length) {
                text += '\n' + (sourceLines[endRow]?.substring(0, endCol) || '');
              }
              node.text = text;
            }

            i++;
          }
        }
      }

      while (i < cleanOutput.length && cleanOutput[i] !== '\n' && cleanOutput[i] !== '(' && cleanOutput[i] !== ')') {
        i++;
      }
    } else if (cleanOutput[i] === ')') {
      if (stack.length > 0) {
        const parent = stack.pop();
        parent.children.push(current);
        current = parent;
      }
      i++;
    } else if (cleanOutput[i] === '\n' || cleanOutput[i] === ' ') {
      i++;
    } else {
      i++;
    }
  }

  return current;
}

async function generateFixture(fountainFile) {
  const baseName = path.basename(fountainFile, '.fountain');
  const fountainPath = path.join(__dirname, 'test', 'fixtures', `${baseName}.fountain`);
  const jsonPath = path.join(__dirname, 'test', 'fixtures', `${baseName}.json`);

  console.log(`Generating fixture for ${baseName}...`);

  const sourceText = fs.readFileSync(fountainPath, 'utf8');
  const { stdout } = await execAsync(`npx --yes tree-sitter parse "${fountainPath}" 2>&1`);
  const ast = parseTreeSitterOutput(stdout, sourceText);

  fs.writeFileSync(jsonPath, JSON.stringify(ast, null, 2));
  console.log(`✓ Generated ${baseName}.json`);
}

// Get fixture names from command line or generate for all new ones
const args = process.argv.slice(2);
if (args.length === 0) {
  console.log('Usage: node generate-fixtures.js <fixture-name> [<fixture-name>...]');
  console.log('Example: node generate-fixtures.js test-title-page-simple');
  process.exit(1);
}

(async () => {
  for (const name of args) {
    await generateFixture(name);
  }
})();
