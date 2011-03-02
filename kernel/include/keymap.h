#ifndef _KEYMAP_H_
#define _KEYMAP_H_

#include <stdint.h>

// mapping unused ascii values to keys
typedef enum Keys {
  KEY_F1 = '\x10',
  KEY_F2,
  KEY_F3,
  KEY_F4,
  KEY_F5,
  KEY_F6,
  KEY_F7,
  KEY_F8,
  KEY_F9,
  KEY_F10,

  KEY_LEFT = '\x1C',
  KEY_RIGHT,
  KEY_UP,
  KEY_DOWN,

} Keys_t;

extern uint8_t en_us_keymap[128];
extern uint8_t en_us_keymap_shift[128];

#endif /* _KEYMAP_H_ */
