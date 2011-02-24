# kernel Makefile

SOURCES := $(patsubst %.c,%.o,$(shell find . -name "*.c"))
SOURCES += $(patsubst %.s,%.o,$(shell find . -name "*.s"))

SUBDIR := kernel

CFLAGS := -Iinclude/ -I$(BUILDDIR)/$(SUBDIR)/include $(CFLAGS)
LDFLAGS := -Tlink.ld -melf_i386
ASFLAGS := -felf

all: kernel

kernel: $(SOURCES)
	$(LD) -o kernel $(SOURCES) $(LDFLAGS)
	mv kernel $(BUILDDIR)/bin

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

%.o: %.c
	echo "  CC" $(SUBDIR)/$<
	$(CC) $(CFLAGS) -c $< -o $@

clean:
