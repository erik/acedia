#include <string.h>
#include <stdbool.h>

#include "kernel.h"
#include "port.h"
#include "console.h"
#include "gdt.h"

// kernel entry point

int kmain(struct multiboot *mboot_ptr) {

  init_gdt();
  kinit_video();

  kputs("Hello, world!\nnewline?\nCARRIAGE RETURN\rsomething else \n");

  int i;
  for(i = ' '; i < 256; i++) {
    ktextcolor(i % KBROWN_L, KBLACK);
    kputc((char)i);
    
  }

  return 0x0;
} 
