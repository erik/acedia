#include "irq.h"
#include "console.h"

static irq_handle irq_handles[16] = {
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

void remap_irq() {
  koutportb(0x20, 0x11);
  koutportb(0xA0, 0x11);
  koutportb(0x21, 0x20);
  koutportb(0xA1, 0x28);
  koutportb(0x21, 0x04);
  koutportb(0xA1, 0x02);
  koutportb(0x21, 0x01);
  koutportb(0xA1, 0x01);
  koutportb(0x21, 0x0);
  koutportb(0xA1, 0x0);
}


void init_irq() {
  remap_irq();

  idt_set_gate(32, (unsigned)irq0, 0x08, 0x8E);
  idt_set_gate(33, (unsigned)irq1, 0x08, 0x8E);
  idt_set_gate(34, (unsigned)irq2, 0x08, 0x8E);
  idt_set_gate(35, (unsigned)irq3, 0x08, 0x8E);
  idt_set_gate(36, (unsigned)irq4, 0x08, 0x8E);
  idt_set_gate(37, (unsigned)irq5, 0x08, 0x8E);
  idt_set_gate(38, (unsigned)irq6, 0x08, 0x8E);
  idt_set_gate(39, (unsigned)irq7, 0x08, 0x8E);
  idt_set_gate(40, (unsigned)irq8, 0x08, 0x8E);
  idt_set_gate(41, (unsigned)irq9, 0x08, 0x8E);
  idt_set_gate(42, (unsigned)irq10, 0x08, 0x8E);
  idt_set_gate(43, (unsigned)irq11, 0x08, 0x8E);
  idt_set_gate(44, (unsigned)irq12, 0x08, 0x8E);
  idt_set_gate(45, (unsigned)irq13, 0x08, 0x8E);
  idt_set_gate(46, (unsigned)irq14, 0x08, 0x8E);
  idt_set_gate(47, (unsigned)irq15, 0x08, 0x8E);
}


void install_irq_handle(int port, irq_handle fcn) {
  irq_handles[port] = fcn;
}

void uninstall_irq_handler(int port) {
  irq_handles[port] = NULL;
}


void handle_irq(regs_t* regs) {
  int port = regs->int_no - 32;
  irq_handle handle = irq_handles[port];
  
  /* send EOI to slave if necessary */
  if(port > 7) {
    koutportb(0xA0, 0x20);
  }

  /* send EOI to master */
  koutportb(0x20, 0x20);

  // if a handle for specific port exists, call it
  if(handle != NULL) {
    kputs("calling handle...\n");
    handle(regs);
    kputs("done.\n");
  }

}
