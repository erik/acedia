#ifndef _THREAD_H_
#define _THREAD_H_

#include <stddef.h>

#include "idt.h"
#include "time.h"
#include "port.h"

#define MAX_THREADS 0x400

struct registers {
  unsigned  eax, ebx, ecx, edx;
  unsigned short cs, ds, es, fs, gs, ss;
  unsigned int esi, edi, ebp, eip, esp;
  unsigned eflags;
};

enum thread_state {
  thread_sleep,
  thread_run,
  thread_exit
};

typedef void (*thread_fcn)(void* msg);

typedef struct thread {
  volatile struct registers regs;
  enum thread_state state;
  thread_fcn fcn;
  unsigned pid;
  unsigned tickets;
} thread_t;

void init_threading();
void thread_swap(struct regs* r, unsigned ticks);
void add_thread(thread_t* thread);

#endif /* _THREAD_H_ */
