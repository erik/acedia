BUILDDIR := $(PWD)/build

CC := gcc -m32
LD := ld
AS := nasm

CFLAGS := -Wall -Werror -Wextra -m32
CFLAGS += -nostdlib -fno-builtin -fno-stack-protector 
CFLAGS += -Wno-unused-parameter -Wno-unused-function

LDFLAGS := -T$(BUILDDIR)/include/link.ld -static
LDFLAGS += -nostdlib -melf_i386

BIN_DIRS := kernel

export BUILDDIR CC LD AS CFLAGS LDFLAGS

all: mkdirs $(BIN_DIRS)

$(BIN_DIRS):
	@echo "make" $@
	@make -s -C $@

clean:
	rm $(shell find . -name "*.o")

distclean: clean
	rm -rf $(BUILDDIR)

mkdirs:
	@ mkdir -p $(BUILDDIR)/include
	@ mkdir -p $(BUILDDIR)/bin

.PHONY: $(BIN_DIRS) clean distclean mkdirs
