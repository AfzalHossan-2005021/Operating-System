# Operating-System 📚

**A collection of operating systems labs and projects (BUET CSE313 & CSE314 — Level 3, Term II)**

---

## Overview ✨

This repository contains solutions, patches, and example programs for operating systems coursework. It primarily targets xv6-based labs (patches and tests) and includes standalone assignments implemented in C/C++ and shell scripting.

## Repository Structure 🔍

- [Bash-Scripting/Offline](Bash-Scripting/Offline/README.md) — Shell scripting assignments & Makefile (run via `make run-script`).
- [Inter-Process-Communication/Offline](Inter-Process-Communication/Offline/README.md) & [Inter-Process-Communication/Online](Inter-Process-Communication/Online/README.md) — IPC exercises with source code and sample IO files.
- [Scheduling/Offline](Scheduling/Offline/README.md) & [Scheduling/Online](Scheduling/Online/README.md) — xv6 scheduling labs (single- and multi-CPU patches for `xv6-riscv`).
- [System-call/Offline](System-call/Offline/README.md) & [System-call/Online](System-call/Online/README.md) — xv6 system call labs with traces and examples.
- [Threading/README.md](Threading/README.md) — xv6 threading lab; contains a patch and testing instructions.
- [xv6-riscv/](xv6-riscv/) — xv6 source tree (submodule) used as the base for applying patches.
- `LICENSE` — Project license.

> Each folder contains a detailed `README.md` with step-by-step setup and test commands. Click any link above to jump to the relevant instructions.

## Quick Start 🚀

1. Clone the repository:

```bash
git clone https://github.com/AfzalHossan-2005021/Operating-System.git
cd Operating-System
```

2. Initialize submodules (required for xv6):

```bash
git submodule update --init --recursive
```

3. Apply a patch for an xv6 lab (example):

```bash
cd xv6-riscv
# reset tree to avoid conflicts
git clean -fdx
git reset --hard
# apply patch (path to patch depends on the lab)
git apply --whitespace=fix ../Scheduling/Offline/2005021_singlecpu.patch
```

4. Build and run xv6 (from `xv6-riscv`):

```bash
make qemu
# inside xv6, use provided commands (see folder READMEs)
```

Notes:

- Many scripts and xv6 experiments were developed on Linux. On Windows, use WSL or a Linux VM to build and run xv6 and run shell scripts.

## Usage & Examples ⚙️

- Bash scripts: `cd Bash-Scripting/Offline && make run-script`
- IPC (Offline): compile and run `g++ 2005021.cpp -o 2005021 -lpthread` then `./2005021 in.txt out.txt`
- xv6 experiments: after applying the patch and starting `qemu`, follow the test commands in each lab README (e.g., `threads`, `trace`, `showlog`).

## Contributing 🤝

Contributions and improvements are welcome. Please open an issue or submit a pull request with a clear description of the change and related tests or usage notes.

## Author & Credits 👤

Maintainer: Afzal Hossan (2005021)

## License 📄

This repository is distributed under the terms in the `LICENSE` file.

---
