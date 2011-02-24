#ifndef _PORT_H_
#define _PORT_H_

void k_outbyte(unsigned short port, unsigned char val);
unsigned char k_inbyte(unsigned short port);
unsigned short k_inword(unsigned short port);

#endif /* _PORT_H_ */
