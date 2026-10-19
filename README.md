# Operating Systems Assignment 8

This submission implements memory-management extensions for x86 xv6:

- Virtual-to-physical address translation (`va2pa`)
- Physical-memory statistics (`getmeminfo`)
- Hierarchical page-table printing (`vmprint`)
- Lazy heap allocation with page-fault handling

## Structure

- `source/kernel/` - modified kernel files
- `source/user/` - user test programs
- `screenshot/` - test output screenshots
- `report.pdf` - implementation report

## Tests

The included programs are `vatest`, `memtest`, `vmprinttest`, and `lazytest`.
Copy the files from `source/` into an x86 xv6 source tree, build with `make`, and run the tests from the xv6 shell.
