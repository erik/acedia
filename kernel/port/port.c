#include "port.h"
/* read / write data on ports */

/* write a byte on a port */
void koutportb(unsigned short port, unsigned char value) {
  asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

/* read a u8int from a port */
unsigned char kinportb(unsigned short port) {
  unsigned char ret;
  asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
  return ret;
}

/* read a u16int from a port */
unsigned short kinportw(unsigned short port) {
  unsigned short ret;
  asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
  return ret;
} 
