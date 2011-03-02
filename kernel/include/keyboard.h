#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <stdint.h>
#include <stdbool.h>

#include "idt.h"
#include "irq.h"
#include "port.h"

#define KEY_PORT 0x60

/* no way it could get this big, right? */
#define KEY_BUFFER_STACK_SIZE 0x1000

/* initialize keyboard */
void kinit_keyboard();

void key_interrupt_handle(struct regs* regs);

/* blocking wait for character input */
uint8_t wait_key();

/* non-blocking character input */
uint8_t poll_key();

/* return the entire character buffer */
uint8_t* get_string();

#endif /* _KEYBOARD_H_ */
