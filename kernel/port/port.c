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



#include "port.h"
/* read / write data on ports */

/* write a byte on a port */
void koutportb(unsigned short port, unsigned char value) {
  __asm__ volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

/* read a u8int from a port */
unsigned char kinportb(unsigned short port) {
  unsigned char ret;
  __asm__ volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
  return ret;
}

/* read a u16int from a port */
unsigned short kinportw(unsigned short port) {
  unsigned short ret;
  __asm__ volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
  return ret;
} 
