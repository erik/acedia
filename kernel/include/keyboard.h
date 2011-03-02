#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <stdint.h>
#include <stdbool.h>

#include "idt.h"
#include "irq.h"
#include "port.h"
#include "keymap.h"

#define KEY_PORT 0x60

/* no way it could get this big, right? */
#define KEY_BUFFER_STACK_SIZE 0x1000

#define KEY_PRESSED(scan) (!((scan) & 0x80))
#define KEY_RELEASED(scan) ((scan) & 0x80)

#define SCAN_SHIFT_L 0x2A
#define SCAN_SHIFT_R 0x36
#define SCAN_CAPS    0xBA
#define SCAN_ALT     0x38
#define SCAN_CTRL    0x1D

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
