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

#include "kernel.h"
#include "port.h"
#include "console.h"
#include "gdt.h"
#include "idt.h"
#include "irq.h"

// kernel entry point

int kmain(struct multiboot *mboot_ptr) {
  panicking = false;

  init_gdt();
  init_idt();

  kinit_video(); 

  kputs(STARTUP_MSG);
  
  kputs("Hello, world!\nnewline?\nCARRIAGE RETURN\rsomething else \n");

  int i;
  for(i = ' '; i < 256; i++) {
    ktextcolor((uint8_t)(i % KBROWN_L), KBLACK);
    kputc((uint8_t)i);
    
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
  
#define TEN "          "
#define TWENTY TEN TEN
#define THIRTY TEN TWENTY
#define FIFTY TWENTY THIRTY

  /* RED SCREEN OF CERTAIN DOOM */
  kputs("Despite your violent" " behavior, the only " TEN "  ####   ####       \n"
        "thing you've managed" " to break so far is " TEN " ###### ######      \n"
        "my heart.           " THIRTY                     " #############      \n"
                                               FIFTY      "  ###########       \n"
                                               FIFTY      "   #########        \n"
                                               FIFTY      "    #######         \n"
                                               FIFTY      "     #####          \n"
                                               FIFTY      "      ###           \n"
                                               FIFTY      "       #            \n");
#undef TEN
#undef TWENTY
#undef THIRTY
#undef FIFTY

  kputs(STOP_MSG "\n\n");

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
