#include "keyboard.h"

#include "console.h"

static int32_t stack_ptr = -1;
static uint8_t key_buffer[KEY_BUFFER_STACK_SIZE] = {0};
static uint8_t *keymap, *keymap_shift;
static struct key_mods {
  bool l_shift;
  bool r_shift;

  bool caps;

  bool ctrl;

  bool alt;
} mods;

void kinit_keyboard() {
  install_irq_handle(0x1, key_interrupt_handle);
  
  // use default keymaps
  keymap = en_us_keymap;
  keymap_shift = en_us_keymap_shift;
  
  // ew.
  mods.l_shift = mods.r_shift = mods.caps = mods.ctrl = mods.alt = false;

}

#define SCANCODE(x) ((scan == x) || (scan == x + 0x80))
#define IS_SHIFTED ((mods.l_shift || mods.r_shift || mods.caps))

void key_interrupt_handle(struct regs* regs) {
  uint8_t scan = inb(KEY_PORT);
  uint8_t key = 0x0;

  if (SCANCODE(SCAN_SHIFT_L)) {
    mods.l_shift =  !mods.l_shift;
  } else if (SCANCODE(SCAN_SHIFT_R)) {
    mods.r_shift = !mods.r_shift;
  } else if (SCANCODE(SCAN_CAPS)) {
    mods.caps = !mods.caps;
  } else if (SCANCODE(SCAN_ALT)) {
    mods.alt = !mods.alt;
  } else if (SCANCODE(SCAN_CTRL)) {
    mods.ctrl = !mods.ctrl;
  }

  // don't worry about key released events just yet
  if(KEY_PRESSED(scan)) {
    if(IS_SHIFTED) {
      key = keymap_shift[scan];
    } else {
      key = keymap[scan];
    }
  } else {
    return;
  }

  // if key isn't mapped to anything, just return
  if(!key) {
    return;
  }

  if(stack_ptr >= KEY_BUFFER_STACK_SIZE) {
    // I GAVE YOU 0x1000 CHANCES, AND YOU JUST STOOD ME UP. FUCK YOUR STACK.
    stack_ptr = -1;
  } else {
    key_buffer[stack_ptr == -1 ? ++stack_ptr : stack_ptr++] = key;
  }
}

uint8_t wait_key() {
  while(stack_ptr < 0) __asm__ ("hlt");
  return poll_key();
}

uint8_t poll_key() {
  if(stack_ptr != -1) {
    uint8_t c = key_buffer[stack_ptr--];
    return c;
  } else {
    return 0x0;
  }
}

