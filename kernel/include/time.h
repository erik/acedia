#ifndef _TIME_H_
#define _TIME_H_

#include "irq.h"
#include "port.h"

#include "heap.h"

#define TICKS_PER_SEC 1000
#define NUM_TIME_HANDLES 0x100

typedef void (*time_handle)(struct regs* r, unsigned ticks);

void set_phase(unsigned hz);
void init_time();

// return the index of the function, -1 on fail
int install_time_handler(time_handle fcn);
void uninstall_time_handler(int index);

#endif /* _TIME_H_ */
