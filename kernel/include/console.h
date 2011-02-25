#ifndef _CONSOLE_H_
#define _CONSOLE_H_

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

extern int g_csr_x;
extern int g_csr_y;
extern int g_text_attrib;
extern unsigned short* g_textmem;

/* init text vide mode */
void kinit_video();

/* clear screen */
void kclear();

/* write character */
void kputc(char c);

/* write string */
void kputs(char* c);

/* update the cursor position */
void kupdatecursor();

/* set the fore/back ground color */
void ktextcolor(unsigned char fore, unsigned char back);

/* set the (x,y) coordinate of the cursor */
void ksetcursorxy(int x, int y);


#endif /* _CONSOLE_H_ */
