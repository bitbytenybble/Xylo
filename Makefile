include project_make.config
# Test comment

CC      = $(HOST)-gcc
KERNEL_NAME = Xylo.elf
SYSROOT = $(SYSROOT_PREFIX)/sysroot
SYSLIBS = /usr/include
CFLAGS  =  -O2 -ffreestanding -g -Wall -Wextra -Werror \
		   --sysroot=$(SYSROOT) -isystem=$(SYSLIBS)
LDFLAGS = -T $(ARCH)/linker.ld

TARGET_FOLDERS = kernel libk

# todo build based on architecture
ARCH    = ./arch/$(TARGET_ARCH)
KER_SRC = ./src
HEADERS = ./include
OBJECTS = start.o kernel.o terminal.o


.PHONY: clean file_system kernel libk kernel_h libk_h



all: | file_system kernel_h libk_h libk kernel

test: | file_system kernel_h libk_h libk kernel_test


kernel_h:
	cd kernel && $(MAKE) install_headers

libk_h:
	cd libk && $(MAKE) install_headers

kernel:
	cd kernel && $(MAKE) all

kernel_test:
	cd kernel && $(MAKE) test


libk:
	cd libk && $(MAKE) all



# Create file system
file_system:
	mkdir -p $(SYSROOT)$(SYSLIBS)



# UTILITY TARGETS
run: all
	qemu-system-i386 -kernel $(KERNEL_NAME) -m size=2048k

trun: test
	qemu-system-i386 -kernel $(KERNEL_NAME) -m size=16M


clean:
	cd kernel && $(MAKE) clean
	cd libk && $(MAKE) clean
	rm -rf $(SYSROOT) $(KERNEL_NAME)
