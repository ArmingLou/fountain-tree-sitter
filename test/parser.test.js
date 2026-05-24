const { test } = require('node:test');
const assert = require('node:assert');
const fs = require('node:fs');
const path = require('node:path');
const { exec } = require('node:child_process');
const { promisify } = require('node:util');

const execAsync = promisify(exec);
const fixturesDir = path.join(__dirname, 'fixtures');

/**
 * Parse tree-sitter CLI output into a JSON AST structure with text content
 * Converts from: (node_type [0,0] - [1,0] ...)
 * To: {type: 'node_type', children: [...], text: '...'}
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

// Normalize minor syntax node name differences for comparison
function normalizeTypes(node) {
  if (!node) return;
  // Treat action_line as line to preserve existing fixtures
  if (node.type === 'action_line') node.type = 'line';
  for (const child of node.children || []) normalizeTypes(child);
}

/**
 * Deep compare two AST structures, ignoring empty children arrays
 */
function compareAST(actual, expected, path = 'root') {
  assert.strictEqual(actual.type, expected.type, `Node type mismatch at ${path}`);

  const actualChildren = actual.children?.filter(c => c) || [];
  const expectedChildren = expected.children?.filter(c => c) || [];

  assert.strictEqual(
    actualChildren.length,
    expectedChildren.length,
    `Children count mismatch at ${path}: expected ${expectedChildren.length}, got ${actualChildren.length}`
  );

  for (let i = 0; i < expectedChildren.length; i++) {
    compareAST(actualChildren[i], expectedChildren[i], `${path}.children[${i}]`);
  }
}

// Get all .fountain files in fixtures directory
const fountainFiles = fs.readdirSync(fixturesDir)
  .filter(f => f.endsWith('.fountain'))
  .map(f => path.basename(f, '.fountain'));

for (const testName of fountainFiles) {
  test(testName, async (t) => {
    const fountainPath = path.join(fixturesDir, `${testName}.fountain`);
    const jsonPath = path.join(fixturesDir, `${testName}.json`);

    // Check that both files exist
    assert.ok(fs.existsSync(fountainPath), `Fountain file ${testName}.fountain should exist`);
    assert.ok(fs.existsSync(jsonPath), `JSON file ${testName}.json should exist`);

    // Load source and expected AST
    const sourceText = fs.readFileSync(fountainPath, 'utf8');
    const expected = JSON.parse(fs.readFileSync(jsonPath, 'utf8'));

    // Parse the fountain file using tree-sitter CLI
    // Use an explicit tree-sitter CLI package to avoid local PNPM path issues
    const { stdout } = await execAsync(`npx --yes tree-sitter-cli@0.25.10 parse "${fountainPath}" 2>&1`);

    // Parse the tree-sitter output into AST with text content
    const actual = parseTreeSitterOutput(stdout, sourceText);
    normalizeTypes(actual);

    // Deep compare the ASTs
    compareAST(actual, expected);
  });
}
