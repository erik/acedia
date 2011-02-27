#ifndef _IDT_H_
#define _IDT_H_

#include "isr.h"

#include <stdint.h>
#include <string.h>

/*
 * <http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html>
 * <http://www.osdever.net/bkerndev/Docs/isrs.htm>
 */

typedef struct idt_entry {
  uint16_t base_lo;             // The lower 16 bits of the address to jump to when this interrupt fires.
  uint16_t sel;                 // Kernel segment selector.
  uint8_t  always0;             // This must always be zero.
  uint8_t  flags;               // More flags. See documentation.
  uint16_t base_hi;             // The upper 16 bits of the address to jump to.
} __attribute__((packed)) idt_entry_t;


// this struct is given to lidt
typedef struct idt_ptr {
  uint16_t limit;
  uint32_t base;                // The address of the first element in our idt_entry_t array.
} __attribute__((packed)) idt_ptr_t;

// in idt.s
extern void idt_flush();

void init_idt();
void idt_set_gate(uint8_t, uint32_t, uint16_t, uint8_t);


idt_entry_t idt_entries[256];
idt_ptr_t   idt_ptr;


#endif /* _IDT_H_ */
