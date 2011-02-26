#include <string.h>

#include "kernel.h"
#include "port.h"
#include "console.h"

// kernel entry point

int kmain(struct multiboot *mboot_ptr)
{
  kinit_video();
  
  kputs("Hello, world!\nnewline?\nCARRIAGE RETURN\rsomething else \n");

  int i;
  for(i = ' '; i < 256; i++) {
    ktextcolor(i % KBROWN_L, KBLACK);
    kputc((char)i);
    
  }

  kputs("\n\n\n");

  
  char one[10] = {'o', 'n', 'e', '\0'};
  char two[10] = {'t', 'w', 'o', '\0'};
  
  strcat(one, two);

  kputs(one);

  return 0x0;
} 
