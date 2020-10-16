# Xylo

An operating system that runs on the IA-32 architecture.

## Xylo Source Tree

* `kernel` - Architecture dependent Xylo kernel source code

* `libk` - Xylo kernel-specific implementation of C standard library

* `Makefile`- Operating system Makefile that creates the binary executable elf file


## Supported architectures

* i386 (IA-32)


## Building the Kernel

Create a file in the Xylo top-level directory named `project_make.config`.

Add the code below to `project_make.config` (Assuming a cross-compiler from host to target has been created).



`HOST = ~/opt/cross/bin/i686-elf # Or path prefix to compiler, excluding the compiler name. E.g gcc, g++, etc)
SYSROOT_PREFIX = PATH_TO_XYLO_DIRECTORY
TARGET_ARCH = SUPPORTED_ARCHITECTURE`
