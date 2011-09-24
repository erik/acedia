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

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "kernel.h"
#include "multiboot.h"
#include "console.h"
#include "gdt.h"
#include "idt.h"
#include "irq.h"
#include "keyboard.h"
#include "page.h"
#include "time.h"
#include "thread.h"
#include "pong.h"

// kernel entry point

int kmain(struct multiboot *mboot_ptr, uint32_t magic) { 
  kassertmsg(magic == MULTIBOOT_BOOTLOADER_MAGIC, "Bad bootloader");
  multiboot_ptr = mboot_ptr;

  kinit();

  kputs("Press any key to begin Pong game...\n");
  wait_key();

  // fuck yeah, pong
  pong();

  return 0x0;
} 

void keyhandle(struct regs* regs) {
  uint8_t scancode = inb(0x60);
  kputdec(scancode);
}

// initialize everything needed for the kernel
void kinit() {
  disableInterrupts();
  
  init_gdt();
  init_idt();
  init_paging();
  init_memory();
  init_time();
  //  init_threading();

  enableInterrupts();  

  kinit_video();
  kinit_keyboard();  

  kputs(STARTUP_MSG);
}
