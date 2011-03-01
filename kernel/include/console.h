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


#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include <stdint.h>

#define VID_ROWS 25
#define VID_COLS 80

/* console colors */
typedef enum kConsoleColor {
  KBLACK = 0x0,
  KBLUE,
  KGREEN,
  KCYAN,
  KRED,
  KMAGENTA,
  KBROWN,
  
  /* light colors */
  KGREY_L,
  /* and dark grey for some reason... */
  KGREY,

  KBLUE_L,
  KGREEN_L,
  KCYAN_L,
  KRED_L,
  KMAGENTA_L,
  KBROWN_L
} kConsoleColor_t;


typedef struct cursor {
  uint32_t x;
  uint32_t y;
} cursor_t;

extern cursor_t g_csr;
extern int g_text_attrib;
extern uint16_t* g_textmem;

/* init text vide mode */
void kinit_video();

/* clear screen */
void kclear();

/* scroll screen if needed*/
void kscroll();

/* write character */
void kputc(uint8_t c);

/* write string */
void kputs(const char* c);

/* formatted print */
//void kprintf(char*f

/* update the cursor position */
void kupdatecursor();

/* set the fore/back ground color */
void ktextcolor(uint8_t fore, uint8_t back);

/* set the (x,y) coordinate of the cursor */
void ksetcursorxy(uint32_t x, uint32_t y);


#endif /* _CONSOLE_H_ */
