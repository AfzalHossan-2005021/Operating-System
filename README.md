# 🖥️ Operating System Labs & Projects

<div align="center">

[![License](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20WSL-brightgreen.svg)]()
[![Made with](https://img.shields.io/badge/Made%20with-C%2B%2B%20%7C%20Bash%20%7C%20Patch-red.svg)]()

**A comprehensive collection of operating systems coursework, xv6 labs, and systems programming assignments from BUET CSE313 & CSE314**

[📂 Explore Structure](#-project-structure) • [🚀 Quick Start](#-quick-start-guide) • [📖 Documentation](#-modules--documentation) • [🔧 Usage](#-usage--examples)

</div>

---

## 📋 Table of Contents

- [Overview](#-overview)
- [Key Features](#-key-features)
- [Project Structure](#-project-structure)
- [Modules & Documentation](#-modules--documentation)
- [Quick Start Guide](#-quick-start-guide)
- [Usage & Examples](#-usage--examples)
- [Technologies](#-technologies-used)
- [Installation Requirements](#-installation-requirements)
- [Contributing](#-contributing)
- [Author & Credits](#-author--credits)
- [License](#-license)

---

## 📚 Overview

This repository contains comprehensive solutions, patches, and example programs for operating systems coursework, with a focus on **xv6 RISC-V kernel modifications** and **systems-level programming**. The collection demonstrates core OS concepts including:

| Concept | Implementation | Location |
|---------|---|---|
| **Process Scheduling** | Single/Multi-CPU scheduling patches | [Scheduling/](Scheduling/) |
| **Inter-Process Communication** | Threaded IPC with pipes, signals | [Inter-Process-Communication/](Inter-Process-Communication/) |
| **System Calls** | Custom syscall implementation | [System-call/](System-call/) |
| **Threading** | User-level threading in xv6 | [Threading/](Threading/) |
| **Shell Scripting** | System automation & utilities | [Bash-Scripting/](Bash-Scripting/) |

---

## ⭐ Key Features

- ✅ **Production-Ready Patches** — Well-tested xv6 kernel modifications
- ✅ **Modular Design** — Independent labs cleanly separated
- ✅ **Complete Documentation** — Step-by-step guides for each module
- ✅ **Test Cases Included** — Comprehensive test suites
- ✅ **Multi-Level Learning** — From basic scripting to kernel development
- ✅ **Linux & WSL Compatible** — Works on most Unix-like systems

---

## 📁 Project Structure

```
Operating-System/
│
├── 🔵 Bash-Scripting/              # Shell scripting assignments
│   ├── Offline/                     # Assessment labs
│   │   ├── 2005021.sh              # Main solution
│   │   ├── Makefile                # Build/run configuration
│   │   └── test-cases.zip          # Test suite
│   └── Online/                      # Additional assignments
│       ├── A1/ - A2/               # Task groups A1-A2
│       └── B1/ - B2/               # Task groups B1-B2
│
├── 🟣 Inter-Process-Communication/ # IPC & threading concepts
│   ├── Offline/                     # Main IPC lab
│   │   ├── 2005021.cpp             # C++ IPC solution
│   │   ├── in.txt / out.txt        # Sample I/O files
│   │   └── README.md               # Detailed instructions
│   └── Online/                      # Additional IPC exercises
│       └── 2005021.cpp             # Extended solution
│
├── 🟠 Scheduling/                  # CPU scheduling in xv6
│   ├── Offline/                     # Comprehensive scheduling lab
│   │   ├── 2005021_singlecpu.patch # Single-CPU scheduler
│   │   ├── 2005021_multicpu.patch  # Multi-CPU scheduler
│   │   └── README.md               # Lab guide
│   └── Online/                      # Additional scheduling tasks
│       └── 2005021.patch
│
├── 🟡 System-call/                 # Custom syscall implementation
│   ├── Offline/                     # Syscall lab
│   │   ├── 2005021.patch           # Patch implementation
│   │   └── README.md               # Instructions
│   └── Online/                      # Extended syscall tasks
│       └── 2005021.patch
│
├── 🔴 Threading/                   # User-level threading
│   ├── 2005021.patch               # Threading patch
│   ├── Offline_5_Threading.pdf     # Lab specification
│   └── README.md                   # Setup & testing guide
│
├── xv6-riscv/                      # xv6 kernel source (submodule)
│   └── [Kernel source tree]
│
├── LICENSE                         # MIT License
└── README.md                       # This file
```

---

## 📖 Modules & Documentation

### 🔵 **Bash-Scripting**
**Shell scripting and system automation**

| Component | Description |
|-----------|---|
| **Offline** | Core shell scripting assignment with automated testing |
| **Online** | Multi-part scripting challenges (A1, A2, B1, B2) |
| **Build System** | Makefile-driven execution |

[→ View Bash-Scripting Docs](Bash-Scripting/Offline/README.md)

---

### 🟣 **Inter-Process Communication (IPC)**
**Threaded IPC, signals, and concurrent programming**

| Component | Description |
|-----------|---|
| **Offline** | Multi-threaded IPC implementation in C++ |
| **Online** | Extended IPC exercises and patterns |
| **Features** | Mutex locks, condition variables, pipes |

[→ View IPC Docs](Inter-Process-Communication/Offline/README.md)

---

### 🟠 **Scheduling**
**CPU scheduling algorithms in xv6 kernel**

| Component | Description |
|-----------|---|
| **Single-CPU** | Uniprocessor scheduling patches |
| **Multi-CPU** | SMP (symmetric multiprocessing) support |
| **Algorithms** | Round-robin, priority-based scheduling |

[→ View Scheduling Docs](Scheduling/Offline/README.md)

---

### 🟡 **System Calls**
**Custom system call implementation in xv6**

| Component | Description |
|-----------|---|
| **Offline** | Primary syscall development |
| **Online** | Extended syscall exercises |
| **Scope** | Implementation + kernel integration |

[→ View System Call Docs](System-call/Offline/README.md)

---

### 🔴 **Threading**
**User-level threading library for xv6**

| Component | Description |
|-----------|---|
| **Patch** | Threading implementation |
| **Features** | Thread creation, synchronization, scheduling |

[→ View Threading Docs](Threading/README.md)

---

## 🚀 Quick Start Guide

### Prerequisites

```bash
# Linux/WSL with development tools
sudo apt-get update
sudo apt-get install build-essential gcc g++ make git
```

### 1️⃣ Clone the Repository

```bash
git clone https://github.com/AfzalHossan-2005021/Operating-System.git
cd Operating-System
```

### 2️⃣ Initialize xv6 Submodule

```bash
git submodule update --init --recursive
```

### 3️⃣ Run Bash Scripts

```bash
cd Bash-Scripting/Offline
make run-script
```

### 4️⃣ Compile IPC Program

```bash
cd Inter-Process-Communication/Offline
g++ 2005021.cpp -o 2005021 -lpthread
./2005021 in.txt out.txt
```

### 5️⃣ Apply xv6 Patches & Build

```bash
cd xv6-riscv
git clean -fdx && git reset --hard

# Apply a scheduling patch (example)
git apply --whitespace=fix ../Scheduling/Offline/2005021_singlecpu.patch

# Build and run xv6
make qemu
```

---

## 🔧 Usage & Examples

### Bash Scripting
```bash
# Run the main shell script solution
cd Bash-Scripting/Offline
./2005021.sh [options]

# Or use Makefile
make run-script
```

### Inter-Process Communication
```bash
# Compile with threading support
g++ 2005021.cpp -o 2005021 -lpthread -std=c++11

# Execute with input/output files
./2005021 input.txt output.txt
```

### xv6 with Patches

```bash
# Navigate to xv6
cd xv6-riscv

# Apply desired patch
git apply --whitespace=fix ../Scheduling/Offline/2005021_singlecpu.patch

# Build kernel
make

# Boot in QEMU
make qemu

# Inside xv6 shell, test features:
# - threads (for threading lab)
# - trace (for tracing syscalls)
# - showlog (for show log functionality)
```

---

## 🛠️ Technologies Used

```
┌─────────────────────────────────────────────┐
│  Core Technologies & Languages              │
├─────────────────────────────────────────────┤
│ • C/C++        → System programming         │
│ • Bash/Shell   → Scripting & automation     │
│ • Git Patches  → Kernel modifications       │
│ • xv6-RISC-V   → Educational OS kernel      │
│ • QEMU         → System emulation           │
│ • Make         → Build automation           │
└─────────────────────────────────────────────┘
```

---

## 📦 Installation Requirements

| Requirement | Purpose | Install |
|-----------|---------|---------|
| **GCC/G++** | C/C++ compilation | `apt install build-essential` |
| **Make** | Build automation | `apt install make` |
| **Git** | Version control | `apt install git` |
| **QEMU** | xv6 emulation | `apt install qemu-system-riscv64` |
| **RISC-V Toolchain** | xv6 compilation | `apt install gcc-riscv64-linux-gnu` |

### Full Setup (Ubuntu/Debian):

```bash
sudo apt-get update && sudo apt-get install -y \
  build-essential \
  gcc \
  g++ \
  make \
  git \
  qemu-system-riscv64 \
  gcc-riscv64-linux-gnu
```

---

## 🤝 Contributing

Contributions are welcome! Please feel free to:

1. 🔀 **Fork** this repository
2. 🌿 **Create** a feature branch (`git checkout -b feature/improvement`)
3. ✏️ **Make** your changes with clear commit messages
4. 📤 **Push** to the branch (`git push origin feature/improvement`)
5. 📥 **Submit** a pull request

---

## 👤 Author & Credits

<div align="center">

**Maintainer:** Afzal Hossan (2005021)

**Coursework:** BUET CSE313 & CSE314  
**Institution:** Bangladesh University of Engineering & Technology  
**Level:** 3, Term II

Built with ❤️ for systems programming excellence

</div>

---

## 📄 License

This repository is licensed under the **MIT License** — see the [LICENSE](LICENSE) file for details.

```
MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software...
```

---

<div align="center">

### 📫 Questions or Feedback?

Feel free to open an issue or reach out with suggestions!

**[Back to Top](#-operating-system-labs--projects)** ⬆️

</div>
