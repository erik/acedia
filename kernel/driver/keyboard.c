#include "keyboard.h"

#include "console.h"

static int32_t stack_ptr = -1;
static uint8_t key_buffer[KEY_BUFFER_STACK_SIZE] = {0};

void kinit_keyboard() {
  install_irq_handle(0x1, key_interrupt_handle);
}

void key_interrupt_handle(struct regs* regs) {
  uint8_t key = inb(KEY_PORT);

  // TODO: Scancodes and such
  
  kputs("Looks like you hit: ");
  kputdec(key);
  kputs(" current stack size: ");
  kputdec(stack_ptr);
  kputs("\n");
  

  if(stack_ptr >= KEY_BUFFER_STACK_SIZE) {
    kputs("TODO: Keybuffer filled!\n");
  } else {
    key_buffer[stack_ptr == -1 ? ++stack_ptr : stack_ptr++] = key;
  }
}

uint8_t wait_key() {
  while(stack_ptr < 0) __asm__ ("hlt");
  return poll_key();
}

uint8_t poll_key() {
  if(stack_ptr != -1) {
    uint8_t c = key_buffer[stack_ptr--];
    return c;
  } else {
    return 0x0;
  }
}

