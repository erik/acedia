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
	@qemu -cdrom build/iso/acedia.iso

bochs: all iso
	@bochs -q

mkdirs:
	@ mkdir -p $(BUILDDIR)/include
	@ mkdir -p $(BUILDDIR)/bin
	@ mkdir -p $(BUILDDIR)/iso

.PHONY: $(BIN_DIRS) clean distclean mkdirs
