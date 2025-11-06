# 🖥️ Dateldi Os - Custom Operating System

<p align="center">
  <img src="https://img.shields.io/badge/License-MIT-blue.svg" alt="License">
  <img src="https://img.shields.io/badge/Platform-x86_64-lightgrey.svg" alt="Platform">
  <img src="https://img.shields.io/badge/Bootloader-GRUB-red.svg" alt="Bootloader">
  <img src="https://img.shields.io/badge/Build-Make-green.svg" alt="Build System">
</p>

<p align="center">
  <strong>A custom x86-64 operating system</strong>
</p>

---

- **Boot Process**: Uses GRUB as the bootloader for reliable system initialization
- **Cross-Platform Development**: Can be built and tested on various host systems

## 🛠️ Build and Requirements

### Host System Requirements
- **GNU Make** (build system)
- **GCC Cross-Compiler** (x86_64-elf-gcc, x86_64-elf-g++)
- **NASM** or **GAS** (assembler)
- **GRUB** (bootloader tools)
- **QEMU** (for emulation/testing)

### Build

```bash
make
