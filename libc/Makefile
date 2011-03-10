SOURCES := $(patsubst %.c,%.o,$(shell find . -name "*.c"))
SOURCES += $(patsubst %.s,%.o,$(shell find . -name "*.s"))

HEADERS := $(shell find . -name "*.h")

STATIC := libc.a

SUBDIR := libc

CFLAGS += -I$(BUILDDIR)/include

all: headers $(STATIC)
	@ echo "  CP $(STATIC) => build/lib"
	@ cp $(STATIC) $(BUILDDIR)/lib

headers: $(HEADERS)
	@ echo "  CP headers => build/$(SUBDIR)"
$(HEADERS):
	@ cp $@ $(BUILDDIR)/include

$(STATIC): $(SOURCES)
	@ echo "  AR" $(SUBDIR)/$<
	@ $(AR) $(ARFLAGS) $(STATIC)  $(SOURCES) 

%.o: %.s
	@ echo "  AS" $(SUBDIR)/$<
	@ $(AS) $(ASFLAGS) $< -o $@

%.o: %.c
	@ echo "  CC" $(SUBDIR)/$<
	@ $(CC) $(CFLAGS) -c $< -o $@


.PHONY: $(HEADERS)

