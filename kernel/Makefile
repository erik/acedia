# kernel Makefile

SOURCES := $(patsubst %.c,%.o,$(shell find . -name "*.c"))
SOURCES += $(patsubst %.s,%.s.o,$(shell find . -name "*.s"))

HEADERS := $(shell find . -name "*.h")

SUBDIR := kernel

CFLAGS += -Iinclude/ -Idriver/include -I$(BUILDDIR)/$(SUBDIR)/include
LDFLAGS := -Tlink.ld -melf_i386 $(BUILDDIR)/lib/libc.a
ASFLAGS := -felf

all: kernel $(HEADERS)

kernel: $(SOURCES)
	@ $(LD) -o kernel $(SOURCES) $(LDFLAGS)
	@ mv kernel $(BUILDDIR)/bin

$(HEADERS):
	@ echo "  CP $(SUBDIR)/$@ => build/$@"
	@ cp $@ $(BUILDDIR)/include

%.s.o: %.s
	echo "  AS" $(SUBDIR)/$<
	@ $(AS) $(ASFLAGS) $< -o $@

%.o: %.c
	echo "  CC" $(SUBDIR)/$<
	$(CC) $(CFLAGS) -c $< -o $@

clean:


.PHONY: $(HEADERS)
