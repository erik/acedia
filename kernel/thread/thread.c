#include "thread.h"

#include "console.h"

// current thread
unsigned thread_index = 1;

thread_t* threads[MAX_THREADS] = {NULL};

inline void save_registers(volatile struct registers* regs) { 
  /*// use pusha, pop each off stack instead?
  __asm__ volatile("mov %%eax, %0" : "=r"(regs->eax));

  __asm__ volatile("mov %%ebx, %0" : "=r"(regs->ebx));
  __asm__ volatile("mov %%ecx, %0" : "=r"(regs->ecx));
  __asm__ volatile("mov %%edx, %0" : "=r"(regs->edx));

  __asm__ volatile("mov %%esi, %0" : "=r"(regs->esi));
  __asm__ volatile("mov %%edi, %0" : "=r"(regs->edi));
  __asm__ volatile("mov %%ebp, %0" : "=r"(regs->ebp));
  __asm__ volatile("mov %%esp, %0" : "=r"(regs->esp));

  __asm__ volatile("mov %%cs, %0" : "=r"(regs->cs));
  __asm__ volatile("mov %%ds, %0" : "=r"(regs->ds));
  __asm__ volatile("mov %%es, %0" : "=r"(regs->es));
  __asm__ volatile("mov %%fs, %0" : "=r"(regs->fs));
  __asm__ volatile("mov %%gs, %0" : "=r"(regs->gs));
  __asm__ volatile("mov %%ss, %0" : "=r"(regs->ss));

  __asm__ volatile("pushf; pop %%eax; mov %%eax, %0" : "=r"(regs->eflags));*/
}

inline void load_registers(volatile struct regs* regs) {
  __asm__ volatile("mov %0, %%ds" : : "r"(regs->ds));
  __asm__ volatile("mov %0, %%es" : : "r"(regs->es));
  __asm__ volatile("mov %0, %%fs" : : "r"(regs->fs));
  __asm__ volatile("mov %0, %%gs" : : "r"(regs->gs));
  __asm__ volatile("mov %0, %%ss" : : "r"(regs->ss));

  __asm__ volatile("push %0; popf" : : "r"(regs->eflags));

  // popa expects "push eax, ecx, edx, ebx, esp, ebp, esi, edi"
  __asm__ volatile("push %0" : : "r"(regs->eax));
  __asm__ volatile("push %0" : : "r"(regs->ecx));
  __asm__ volatile("push %0" : : "r"(regs->edx));
  __asm__ volatile("push %0" : : "r"(regs->ebx));

  __asm__ volatile("push %0" : : "r"(regs->esp));
  __asm__ volatile("push %0" : : "r"(regs->ebp));
  __asm__ volatile("push %0" : : "r" (regs->esi));
  __asm__ volatile("push %0" : : "r"(regs->edi));

  __asm__ volatile("popa");

}

void init_threading() {
  thread_index = 0;
  install_time_handler(thread_swap);
}

static int called = 0;

void thread_swap(struct regs* r, unsigned ticks) {
  if(!called++) {
    __asm__ volatile("sti; jmp *%0" : : "r" (threads[0]->fcn));
    return;
  }
  disableInterrupts();
  unsigned i;
  thread_t* t;

  t = threads[thread_index];
  //  save_registers(&t->regs);
  thread_index = ++thread_index % 2;
  //  kputhex(thread_index);

  //  t->regs.cs = r->cs;
  //t->regs.esp = r->esp;
  //t->regs.eip = r->eip;
  //t->regs.ebp = r->ebp;
  //  t->regs.ebp = r->ebp;
  
  t = threads[thread_index];

  __asm__ volatile("mov %0, %%esp" : : "r"(t->regs.esp));
  __asm__ volatile("mov %0, %%ebp" : : "r"(t->regs.esp));

  __asm__ volatile("sti; jmp *%0" : : "r" (t->fcn));

  t->fcn(0);  
}

void add_thread(thread_t* thread) {
  unsigned i;
  for(i = 0; threads[i]; ++i);
  threads[i] = thread;
  //save_registers(&thread->regs);
}
