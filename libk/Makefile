include ../project_make.config
# $(HOST) holds path to cross-compiler
# $(SYSROOT_PREFIX) holds the full path to the outtermost folder in the project

TARGET_LIBS = libk.a
CC       = $(HOST)-gcc#Call architecture dependent compiler executable
AR       = $(HOST)-ar#Call architecture dependent archiver executable
AR_FLAGS = rcs


SYSROOT  = $(SYSROOT_PREFIX)/sysroot
SYSLIBS  = $(SYSROOT)/usr/lib
SYS_HEADERS  = /usr/include
CFLAGS   =  -O2 -ffreestanding -g -Wall -Wextra -Werror \
		   --sysroot=$(SYSROOT) -isystem=$(SYS_HEADERS) -std=gnu11 \
		   -D __is_libk
LDFLAGS  = -T $(ARCH)/linker.ld



##################### Library paths, files and objects #########################

# string.h files
STRING_PATH = string
STRING_SRC := $(shell find $(STRING_PATH) -name '*.c')
STRING_OBJECTS = $(STRING_SRC:.c=.o)

# stdio.h files
STDIO_PATH = stdio
STDIO_SRC := $(shell find $(STDIO_PATH) -name '*.c')
STDIO_OBJECTS = $(STDIO_SRC:.c=.o)

# stdlib.h files
STDLIB_PATH = stdlib
STDLIB_SRC := $(shell find $(STDLIB_PATH) -name '*.c')
STDLIB_OBJECTS = $(STDLIB_SRC:.c=.o)

################################################################################



HEADERS  = ./include
OBJECTS := $(STRING_OBJECTS) $(STDIO_OBJECTS) $(STDLIB_OBJECTS)


.Phony: clean install_headers install_libraries
.Suffixes: .o .c



######################### BUILD RULES #########################################
all: | $(TARGET_LIBS) install_libraries

$(TARGET_LIBS): $(OBJECTS)
	$(AR) $(AR_FLAGS) $@ $(OBJECTS)

# compile c files to object files
%.o: %.c
	$(CC) -MD -c $< -o $@ $(CFLAGS)

###############################################################################





########################### Installation rules ################################
install_headers:
	mkdir -p $(SYSROOT)$(SYS_HEADERS)
	cp -rf $(HEADERS)/* $(SYSROOT)$(SYS_HEADERS)

# Creates SYSROOT/usr/lib and copies libk.a to it
install_libraries:
	mkdir -p $(SYSLIBS)
	cp $(TARGET_LIBS) $(SYSLIBS)

################################################################################





########################### Misc rules ################################

clean:
	rm -f $(OBJECTS) $(TARGET_LIBS) $(OBJECTS:.o=.d)
