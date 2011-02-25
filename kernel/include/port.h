#ifndef _PORT_H_
#define _PORT_H_

void koutportb(unsigned short port, unsigned char val);
unsigned char kinportb(unsigned short port);
unsigned short kinportw(unsigned short port);

#endif /* _PORT_H_ */
