# tree-sitter-fountain

[![CI][ci]](https://github.com/tree-sitter-grammars/tree-sitter-fountain/actions/workflows/ci.yml)
[![discord][discord]](https://discord.gg/w7nTvsVJhm)
[![matrix][matrix]](https://matrix.to/#/#tree-sitter-chat:matrix.org)
<!-- NOTE: uncomment these if you're publishing packages: -->
<!-- [![npm][npm]](https://www.npmjs.com/package/tree-sitter-fountain) -->
<!-- [![crates][crates]](https://crates.io/crates/tree-sitter-fountain) -->
<!-- [![pypi][pypi]](https://pypi.org/project/tree-sitter-fountain/) -->

A tree-sitter parser for [.fountain](https://fountain.io/) files with hierarchical parsing support for proper code outlining.

## Features

- **Complete Fountain Spec**: Full implementation of the Fountain 1.1 specification
- **Hierarchical AST**: Section blocks contain scene blocks, scene blocks contain dialogue/action
- **All Elements**: Scenes, sections, dialogue, action, transitions, notes, boneyard, synopses, lyrics, centered text, page breaks, title pages
- **Forced Elements**: Support for forced scene headings (`.HEADING`), transitions (`>TRANSITION`), character names (`@CHARACTER`), and action (`!ACTION`)
- **Dual Dialogue**: Character cues with `^` marker
- **Emphasis**: Bold, italic, underline, and bold-italic
- **Title Pages**: Multi-line fields with continuation support

## Editor Support

### Zed Editor

Install the [Fountain extension](https://github.com/trieloff/zed-fountain) from the Zed extensions gallery:

1. Open Zed
2. Go to Extensions (Cmd+Shift+X / Ctrl+Shift+X)
3. Search for "Fountain"
4. Click Install

Features include syntax highlighting, hierarchical outline view (sections → scenes → dialogue), smart indentation, and bracket matching.

## Testing

### Running Tests

Run the unit tests using Node.js built-in test runner:

```bash
npm test
```

This will run all fixture-based tests in `test/fixtures/`.

Alternatively, run the tree-sitter corpus tests:

```bash
npm run test:tree-sitter
```

### Creating New Tests

To add a new test:

1. Create a `.fountain` file in `test/fixtures/` with your test content
2. Generate the expected AST by running:

```bash
node test/generate-fixtures.js
```

This will create a `.json` file with the complete AST structure for each `.fountain` file.

Alternatively, you can manually create the JSON file with the expected AST structure:

```json
{
  "type": "document",
  "children": [
    {
      "type": "scene_heading",
      "children": [
        {"type": "scene_start", "children": []},
        {"type": "description", "children": []}
      ]
    },
    {
      "type": "action",
      "children": [
        {"type": "line", "children": []}
      ]
    }
  ]
}
```

The test runner will automatically discover and run your new test on the next `npm test` run. Tests perform deep AST comparison, verifying the complete tree structure.

## References

<!-- NOTE: add the grammar's references here -->

[ci]: https://img.shields.io/github/actions/workflow/status/tree-sitter-grammars/tree-sitter-fountain/ci.yml?logo=github&label=CI
[discord]: https://img.shields.io/discord/1063097320771698699?logo=discord&label=discord
[matrix]: https://img.shields.io/matrix/tree-sitter-chat%3Amatrix.org?logo=matrix&label=matrix
[npm]: https://img.shields.io/npm/v/tree-sitter-fountain?logo=npm
[crates]: https://img.shields.io/crates/v/tree-sitter-fountain?logo=rust
[pypi]: https://img.shields.io/pypi/v/tree-sitter-fountain?logo=pypi&logoColor=ffd242
