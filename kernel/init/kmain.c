#include "kernel.h"
#include "port.h"
#include "console.h"

// kernel entry point

int kmain(struct multiboot *mboot_ptr)
{
  kinit_video();
  
  kputs("Hello, world!\nnewline?\nCARRIAGE RETURN\rsomething else");

  return 0x0;
} 
