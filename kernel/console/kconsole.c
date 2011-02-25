#include "console.h"
#include "port.h"

int g_csr_x, g_csr_y;
int g_text_attrib;
unsigned short* g_textmem;

void kinit_video() {
  g_csr_x = g_csr_y = 0;
  g_textmem = (unsigned short*)0xB8000;

  ktextcolor(KGREY_L, KBLACK);
  kclear();
}

void kclear() {
  char b = ' ';
  unsigned short c = b | g_text_attrib << 8;

  int i;
  for(i = 0; i < 80 * 25; ++i) {
    g_textmem[i]  = c;
  } 
}

void kputc(char c) {
  unsigned short let = c | g_text_attrib << 8;
  
  if(c == '\n') {
    g_csr_x = 0;
    g_csr_y++;
  } else if(c == '\r') {
    g_csr_x = 0;
  } else if(c >= ' ') {
    /* make sure c is a printable character */

    g_textmem[g_csr_y * 80 + g_csr_x] = let;
    g_csr_x++;
  }
  
  kupdatecursor();
}

void kputs(char* c) {
  char x;
  while((x = *c++) != '\0') {
    kputc(x);
  }
}

void kupdatecursor() {
  unsigned temp;

  temp = g_csr_y * 80 + g_csr_x;

  koutportb(0x3D4, 14);
  koutportb(0x3D5, temp >> 8);
  koutportb(0x3D4, 15);
  koutportb(0x3D5, temp);
}

void ktextcolor(unsigned char fore, unsigned char back) {
  g_text_attrib = ((back << 4) | (fore & 0x0F));
}

void ksetcursorxy(int x, int y) {
  g_csr_x = x;
  g_csr_y = y;
  kupdatecursor();
}
