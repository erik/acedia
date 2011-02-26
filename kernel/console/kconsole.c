#include "console.h"
#include "port.h"

cursor_t g_csr;
int g_text_attrib;
unsigned short* g_textmem;

void kinit_video() {
  g_csr.x = g_csr.y = 0;

  g_textmem = (unsigned short*)0xB8000;

  ktextcolor(KGREY_L, KBLACK);
  kclear();
}

void kclear() {
  unsigned short c = ' ' | g_text_attrib << 8;

  int i;
  for(i = 0; i < VID_ROWS * VID_COLS; ++i) {
    g_textmem[i] = c;
  } 
}

void kscroll() {
  int i;
  unsigned short c = ' ' | g_text_attrib << 8;

  int max = VID_COLS * (VID_ROWS - 1);
  
  if(g_csr.y >= VID_ROWS) {
    
    for(i = 0; i < max; ++i) {
      g_textmem[i] = g_textmem[i + VID_COLS];
    }
    for(i = max; i < VID_ROWS * VID_COLS; ++i) {
      g_textmem[i] = c;
    }

    g_csr.y = VID_ROWS - 1;
    g_csr.x = 0;

  }
}

void kputc(unsigned char c) {
  unsigned short let = c | g_text_attrib << 8;
  
  if(g_csr.x >= VID_COLS) {
    g_csr.x = 0;
    g_csr.y++;
  }

  if(c == '\n') {
    g_csr.x = 0;
    g_csr.y++;
  } else if(c == '\r') {
    g_csr.x = 0;
  } else if(c >= ' ') {
    /* make sure c is a printable character */

    g_textmem[g_csr.y * VID_COLS + g_csr.x] = let;
    g_csr.x++;
  }
  
  kupdatecursor();
  kscroll();
}

void kputs(char* c) {
  char x;
  while((x = *c++) != '\0') {
    kputc(x);
  }
}

void kupdatecursor() {
  unsigned temp;

  temp = g_csr.y * VID_COLS + g_csr.x;

  koutportb(0x3D4, 14);
  koutportb(0x3D5, temp >> 8);
  koutportb(0x3D4, 15);
  koutportb(0x3D5, temp);
}

void ktextcolor(unsigned char fore, unsigned char back) {
  g_text_attrib = ((back << 4) | (fore & 0x0F));
}

void ksetcursorxy(int x, int y) {
  g_csr.x = x;
  g_csr.y = y;
  kupdatecursor();
}