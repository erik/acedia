#include "time.h"

static unsigned timer_ticks = 0;

static time_handle handles[NUM_TIME_HANDLES];
static int handle_index = -1;

void set_phase(unsigned hz) {
  unsigned divisor = 1193180 / hz;       /* Calculate our divisor */
  outb(0x43, 0x36);                      /* Set our command byte 0x36 */
  outb(0x40, divisor & 0xFF);            /* Set low byte of divisor */
  outb(0x40, (uint8_t)(divisor >> 8));   /* Set high byte of divisor */
}

void timer_handler(struct regs *r) {
  timer_ticks++;
  unsigned i;
  for(i = 0; i < NUM_TIME_HANDLES; ++i) {
    time_handle fcn = handles[i];
    // break if no function present
    if(!fcn) {
      break;
    }
    fcn(r, timer_ticks); 
  }
}

void init_time() {
  // 1 millisecond timing
  set_phase(TICKS_PER_SEC);

  install_irq_handle(0, timer_handler);
}

int install_time_handler(time_handle fcn) {
  int index = ++handle_index;
  // out of space
  if(index >= NUM_TIME_HANDLES) {
    return -1;
  }

  handles[index] = fcn;
  return index;
}

void uninstall_time_handler(int index) {
  handles[index] = NULL;
}
