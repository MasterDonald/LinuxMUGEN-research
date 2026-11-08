# Diagrams

- `file-callgraph.mmd`: Mermaid flowchart of the 90 heaviest file-to-file
  call relations in the Elecbyte code (edge label = number of call sites).
  Generated from the reconstruction; see ../subsystem-analysis.md.
- `startup.mmd`: process startup and resource loading order (from strace
  and `_mangled_main`).
- `character-load.mmd`: character loading flow (from `PlayerDefLoad*`).
