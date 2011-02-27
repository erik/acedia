#ifndef _GDT_H_
#define _GDT_H_

#include <stdint.h>

/*
 * <http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html>
 * <http://www.osdever.net/bkerndev/Docs/gdt.htm>
 */

typedef struct gdt_entry {
  uint16_t limit_low;           // The lower 16 bits of the limit.
  uint16_t base_low;            // The lower 16 bits of the base.
  uint8_t  base_middle;         // The next 8 bits of the base.
  uint8_t  access;              // Access flags, which ring is segment in?.
  uint8_t  granularity;         // 1 byte, or 1K?
  uint8_t  base_high;           // The last 8 bits of the base.
} __attribute__((packed)) gdt_entry_t;

typedef struct gdt_ptr {
   uint16_t limit;               // The upper 16 bits of all selector limits.
   uint32_t base;                // The address of the first gdt_entry_t struct.
} __attribute__((packed)) gdt_ptr_t;

// in gdt.s
extern void gdt_flush(uint32_t);

void init_gdt();
void gdt_set_gate(int32_t, uint32_t, uint32_t, uint8_t, uint8_t);


gdt_entry_t gdt_entries[5]; // NULL, Code, Data, User Code, User Data
gdt_ptr_t   gdt_ptr;

#endif /* _GDT_H_ */
