#include "kernel.h"
#include "port.h"

// kernel entry point

int kmain(struct multiboot *mboot_ptr)
{
  // All our initialisation calls will go in here.
  return 0xDEADBABA;
} 
