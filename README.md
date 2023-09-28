# LiOS86

## Overview

A simple, toy x86 operating system written in C++.

![LiOS86 screenshot](docs/screenshot.png)

Features implemented in the current version (`1.0.0`):
- bootloader
- interrupt handling
- simple interactive shell
- crude dynamic memory allocation

Not yet implemented:
- virtual memory support
- disk access & filesystem support
- concurrency support

The provided `Makefile` supports compiling the operating system from source (using an i386 [cross-compiler](https://wiki.osdev.org/GCC_Cross-Compiler)), generating a disk image and running it in `qemu` emulator.

## Build details
The OS was cross-built and tested using:
- NASM version 2.15.05
- Binutils version 2.40 (`i386-elf` target)
- GCC version 12.2.0 (`i386-elf` target)
- QEMU version 6.2.0

GCC cross-compiler was configured and built with `--enable-languages=c,c++ --without-headers --with-newlib --disable-hosted-libstdcxx --disable-libstdcxx-verbose` flags.

## Useful resources

- [OS Dev wiki](https://wiki.osdev.org/Main_Page)
