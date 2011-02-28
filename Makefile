BUILDDIR := $(PWD)/build

CC := clang
LD := ld
AS := nasm
AR := ar

ARFLAGS := rcs

CFLAGS := -Wall -Werror -Wextra -pedantic -std=c99 -O3
CFLAGS +=  -nostdinc -fno-builtin -fno-stack-protector -m32 -ffreestanding
CFLAGS += -Wno-unused-parameter -Wno-unused-function
CFLAGS += -I$(BUILDDIR)/include

LDFLAGS := -T$(BUILDDIR)/include/link.ld -static
LDFLAGS += -nostdlib -melf_i386

BIN_DIRS := kernel
LIB_DIRS := libc
TEST_DIRS := test

export BUILDDIR CC LD AS CFLAGS LDFLAGS AR ARFLAGS

all: mkdirs $(LIB_DIRS) $(BIN_DIRS)

$(LIB_DIRS):
	@echo "make" $@
	@make -s -C $@

$(BIN_DIRS):
	@echo "make" $@
	@make -s -C $@

clean:
	rm $(shell find . -name "*.o")

distclean: clean
	rm -rf $(BUILDDIR)

iso: $(BIN_DIRS)
	@genisoimage -graft-points -R 				\
		-b boot/grub/stage2_eltorito 			\
		-no-emul-boot 					\
		-boot-load-size 4 -boot-info-table 		\
		-o $(BUILDDIR)/iso/acedia.iso 			\
		boot/kernel=$(BUILDDIR)/bin/kernel		\
		boot/grub/menu.lst=boot/grub/menu.lst		\
		boot/grub/stage2_eltorito=boot/grub/stage2_eltorito

qemu: all iso
	@qemu -serial stdio -cdrom build/iso/acedia.iso

bochs: all iso
	@bochs -q

mkdirs:
	@ mkdir -p $(BUILDDIR)/include
	@ mkdir -p $(BUILDDIR)/bin
	@ mkdir -p $(BUILDDIR)/lib
	@ mkdir -p $(BUILDDIR)/iso

.PHONY: $(BIN_DIRS) $(LIB_DIRS) clean distclean mkdirs qemu bochs iso
