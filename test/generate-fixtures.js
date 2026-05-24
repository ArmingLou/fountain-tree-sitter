const { execSync } = require('child_process');
const fs = require('fs');
const path = require('path');

const fixturesDir = path.join(__dirname, 'fixtures');

/**
 * Parse tree-sitter CLI output into a JSON AST structure with text content
 */
function parseTreeSitterOutput(output, sourceText) {
  // Remove warning and debug lines, extract only the AST portion
  const lines = output.split('\n');

  // Find the start of the AST (first line starting with '(document')
  const astStartIdx = lines.findIndex(line => line.trim().startsWith('(document'));
  if (astStartIdx === -1) {
    throw new Error('Could not find AST in output');
  }

  // Find the end of the AST (last ')' before any file path lines)
  let astEndIdx = astStartIdx;
  let parenCount = 0;
  for (let i = astStartIdx; i < lines.length; i++) {
    const line = lines[i];
    // Stop if we hit a line with file path (contains .fountain)
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
      // Start of a node
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

      // Extract position info [startRow,startCol] - [endRow,endCol]
      if (cleanOutput[i] === ' ' && cleanOutput[i + 1] === '[') {
        i += 2; // skip ' ['
        let posStr = '';
        while (i < cleanOutput.length && cleanOutput[i] !== ']') {
          posStr += cleanOutput[i];
          i++;
        }
        const [startRow, startCol] = posStr.split(',').map(s => parseInt(s.trim()));

        i++; // skip ']'
        while (i < cleanOutput.length && cleanOutput[i] === ' ') i++;
        if (cleanOutput[i] === '-') {
          i++; // skip '-'
          while (i < cleanOutput.length && cleanOutput[i] === ' ') i++;
          if (cleanOutput[i] === '[') {
            i++; // skip '['
            posStr = '';
            while (i < cleanOutput.length && cleanOutput[i] !== ']') {
              posStr += cleanOutput[i];
              i++;
            }
            const [endRow, endCol] = posStr.split(',').map(s => parseInt(s.trim()));

            // Extract text from source
            if (startRow === endRow) {
              node.text = sourceLines[startRow]?.substring(startCol, endCol);
            } else {
              // Multi-line node
              let text = sourceLines[startRow]?.substring(startCol) || '';
              for (let r = startRow + 1; r < endRow; r++) {
                text += '\n' + (sourceLines[r] || '');
              }
              if (endRow < sourceLines.length) {
                text += '\n' + (sourceLines[endRow]?.substring(0, endCol) || '');
              }
              node.text = text;
            }

            i++; // skip ']'
          }
        }
      }

      // Skip rest of line until newline or paren
      while (i < cleanOutput.length && cleanOutput[i] !== '\n' && cleanOutput[i] !== '(' && cleanOutput[i] !== ')') {
        i++;
      }
    } else if (cleanOutput[i] === ')') {
      // End of a node
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

// Get all .fountain files in fixtures directory
const fountainFiles = fs.readdirSync(fixturesDir)
  .filter(f => f.endsWith('.fountain'));

for (const file of fountainFiles) {
  const fountainPath = path.join(fixturesDir, file);
  const jsonPath = path.join(fixturesDir, file.replace('.fountain', '.json'));

  // Read source file
  const sourceText = fs.readFileSync(fountainPath, 'utf8');

  // Parse using tree-sitter CLI (ignore exit code as it may fail on parse errors)
  let output;
  try {
    output = execSync(`npx --yes tree-sitter parse "${fountainPath}" 2>&1`, { encoding: 'utf8' });
  } catch (err) {
    output = err.stdout || err.output?.join('') || '';
  }

  // Convert to JSON AST with text content
  const ast = parseTreeSitterOutput(output, sourceText);

  // Write to file
  fs.writeFileSync(jsonPath, JSON.stringify(ast, null, 2));
  console.log(`Generated ${jsonPath}`);
}
