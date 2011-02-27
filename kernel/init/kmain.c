#include <string.h>
#include <stdbool.h>

#include "kernel.h"
#include "port.h"
#include "console.h"
#include "gdt.h"
#include "idt.h"

// kernel entry point

int kmain(struct multiboot *mboot_ptr) {
  panicking = false;

  init_gdt();
  init_idt();
  kinit_video(); 
  
  kputs("Hello, world!\nnewline?\nCARRIAGE RETURN\rsomething else \n");

  int i;
  for(i = ' '; i < 256; i++) {
    ktextcolor(i % KBROWN_L, KBLACK);
    kputc((char)i);
    
  }

  return 0x0;
} 


void _khalt(int reason, const char* msg, const char* fcn, const char* file, const char* line) {
  // recursive panic
  if(panicking) {
    __KHALT;
  }
  panicking = true;

  ktextcolor(KBLACK, KRED);
  kclear();
  
  kputs("\n\n\n" STOP_MSG "\n\n");

  /* this is why I need printf :( */

  if(reason == UNHANDLED_EXCEPTION) {
    kputs("KERNEL PANIC: ");
    kputs(msg);
    kputs("\n  Called from "); kputs(fcn); kputs(" ("); kputs(file); kputs(":"); kputs(line); kputs(")\n");
  } else if(reason == ASSERTION_FAILED) {
    kputs("ASSERTION FAILED: ");
    kputs(msg);
    kputs("\n  in "); kputs(fcn); kputs(" ("); kputs(file); kputs(":"); kputs(line); kputs(")\n");
  } else if(reason == UNKNOWN_FAILURE) {
    kputs("UNKNOWN FAILURE: ");
    kputs(msg);
  }

  __KHALT;

}
