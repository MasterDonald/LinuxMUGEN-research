# Provenance

## Received material

A directory `LINUX MUGEN 14.04.2002/` with 112 files in 9 directories
(VERIFIED). The directory mtimes of `data/`, `docs/`, `font/` and `stages/`
are 2020-05-13, and `chars/` shows 1901-12-13 (a zero or negative
timestamp). So the folder went through at least one re-archiving step after
2002 (STRONGLY INFERRED). File mtimes inside are 2000-2002 and consistent
with the release.

## Original distribution

| Fact | Class |
|---|---|
| Publisher: Elecbyte, "http://mugen.elecbyte.com", contact page "http://www.elecbyte.com/contact.html" | VERIFIED (readme) |
| Info screen: "MUGEN betas are available from www.elecbyte.com" | VERIFIED (screenshot) |
| Original archive name and format (tar.gz? zip?) | UNKNOWN. The readme thanks "SFX Maker" for the self-extracting archive, which is a DOS-era leftover |
| Whether this directory is complete versus the original archive | STRONGLY INFERRED complete: the readme references `mugenfaq.txt` (only `docs/mugenfaq.html` exists) and `sprmaker` (not included), but these are documentation inconsistencies; every file the executable opens at startup exists (experiments T3) |

## Integrity

- The executable carries a valid UPX 1.20 stub and decompresses without
  error. The unpacked ELF is self-consistent: all sections are present,
  the symbol table is intact and `.comment` is uniform (VERIFIED).
- No signs of later patching: all 778 objects carry the same compiler ident,
  and the code and data ranges match the symbol table (VERIFIED).
- SHA-256 of every file: [../artifacts/inventory.tsv](../artifacts/inventory.tsv).

## Duplicates in the archive (VERIFIED, same SHA-256)

- `readme.txt` = `docs/readme.txt`
- `updates.txt` = `docs/updates.txt`
- `data/select.def` = `data/kfm/select.def`
