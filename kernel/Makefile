include ../project_make.config

# HOST holds path of cross-compiler
TARGET_DEST = ..# PLACE KERNEL IN OUTTERMOST FOLDER OF PROJECT
KERNEL_NAME = Xylo.elf
TARGET      = $(TARGET_DEST)/$(KERNEL_NAME)# TARGET PATH

CC          = $(HOST)-gcc
SYSROOT     = $(SYSROOT_PREFIX)/sysroot
SYS_HEADERS = /usr/include
SYSLIBS     = $(SYSROOT)/usr/lib
CFLAGS      =  -O2 -ffreestanding -g \
		       --sysroot=$(SYSROOT) -isystem=$(SYS_HEADERS) -Wall -Wextra -Werror -std=gnu11
LDFLAGS     = -T $(ARCH)/linker.ld -nostdlib -lgcc
			  # -T is a flag to attach linker scripts


# TODO build based on architecture

ARCH    = ./arch/$(TARGET_ARCH)
KER_SRC = ./src
HEADERS = ./include



# C Runtime objects
CRT_BEGIN := $(shell $(CC) -print-file-name=crtbegin.o) # Gets crtbegin and crtend from the cross-compiler
CRT_DIR   := $(dir $(CRT_BEGIN))# Extract directory names
CRT_OBJS   = crtbegin.o crtend.o


OBJECTS = start.o terminal.o gdt.o crti.o crtn.o $(CRT_OBJS)



# OBJECTS FOR MAIN BUILD
KERN_OBJS := $(OBJECTS) kernel.o


# Test variables
TEST_PATH = ./test
TEST_SUBDIRS= terminal_tests
TEST_OBJS := $(OBJECTS) test_printf.o test_kernel.o




.PHONY: clean install_headers test


all: $(TARGET)

$(TARGET): $(KERN_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -lk -o $(TARGET)



############################# SOURCE TARGETS ###################################
start.o: $(ARCH)/start.s
	$(CC) $(CFLAGS) -c $^ -o $@


kernel.o: $(KER_SRC)/kernel.c
	$(CC) $(CFLAGS) -c $^ -o $@


terminal.o: $(ARCH)/terminal.c
	$(CC) $(CFLAGS) -c $^ -o $@


gdt.o: $(ARCH)/gdt.c $(ARCH)/gdt.h
	$(CC) $(CFLAGS) -c $< -o $@



crti.o: $(ARCH)/crti.s
	$(CC) $(CFLAGS) -c $^ -o $@

crtn.o: $(ARCH)/crtn.s
	$(CC) $(CFLAGS) -c $^ -o $@

# For each target, copy the file from the cross-compiler directory to this directory
$(CRT_OBJS):# CRT_OBJS = crtbegin.o crtend.o
	cp $(CRT_DIR)$@ ./

################################################################################


test: $(TEST_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -lk -o $(TARGET)


test_printf.o: ./test/terminal_tests/test_printf.c ./test/terminal_tests/test_printf.h
	$(CC) $(CFLAGS) -c $< -o $@


test_kernel.o: ./test/test_kernel.c
	$(CC) $(CFLAGS) -c $^ -o $@




# HEADER TARGET
install_headers:
	mkdir -p $(SYSROOT)$(SYS_HEADERS)/kernel
	cp $(HEADERS)/* $(SYSROOT)$(SYS_HEADERS)/kernel



# UTILITY TARGETS
clean:
	rm -f $(KERN_OBJS) $(TEST_OBJS) $(TARGET)
