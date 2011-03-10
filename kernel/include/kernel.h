/*
* Copyright (C) 2011 by Erik Price
* 
* Permission to use, copy, modify, and/or distribute this software for any
* purpose with or without fee is hereby granted, provided that the above
* copyright notice and this permission notice appear in all copies.
* 
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
* ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
* ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
* OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#ifndef _KERNEL_H_
#define _KERNEL_H_

#include <stdint.h>
#include <stdbool.h>

#include "multiboot.h"
#include "panic.h"

extern unsigned int _kernel_start;
extern unsigned int _kernel_end;

#define STARTUP_MSG "Acedia version 0.01, compiled on " __DATE__ " at " __TIME__ "\n"

inline void enableInterrupts() {
  __asm__ volatile("sti");
}

inline void disableInterrupts() { 
  __asm__ volatile("cli");
}

void kinit();

int kmain(struct multiboot*, uint32_t);

struct multiboot* multiboot_ptr;

#endif /* _KERNEL_H_ */
