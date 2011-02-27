#ifndef _KERNEL_H_
#define _KERNEL_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct multiboot {
  uint32_t flags;
  uint32_t mem_lower;
  uint32_t mem_upper;
  uint32_t boot_device;
  uint32_t cmdline;
  uint32_t mods_count;
  uint32_t mods_addr;
  uint32_t num;
  uint32_t size;
  uint32_t addr;
  uint32_t shndx;
  uint32_t mmap_length;
  uint32_t mmap_addr;
  uint32_t drives_length;
  uint32_t drives_addr;
  uint32_t config_table;
  uint32_t boot_loader_name;
  uint32_t apm_table;
  uint32_t vbe_control_info;
  uint32_t vbe_mode_info;
  uint32_t vbe_mode;
  uint32_t vbe_interface_seg;
  uint32_t vbe_interface_off;
  uint32_t vbe_interface_len;
} __attribute__((packed)) multiboot_t;

int kmain(struct multiboot*);

// kernel panic handling

#define STOP_MSG "Acedia has detected an error and must shutdown."

#define UNHANDLED_EXCEPTION  0x0 // unhandled exception
#define ASSERTION_FAILED     0x1 // failed assertion
#define UNKNOWN_FAILURE      0x3 // something else

#define __KHALT __asm__("cli; hlt")

// make sure a recursive panic doesn't happen
bool panicking;

// stop the kernel entirely
void _khalt(int reason, const char* msg, const char* fcn, const char *file, const char* line);

#define STRING_(x) #x
#define STRING(x) STRING_(x)

#define kpanic(msg) _khalt(UNHANDLED_EXCEPTION, msg, __FUNCTION__, __FILE__, STRING(__LINE__))
#define kassert(cond) if(!cond) { _khalt(ASSERTION_FAILED, #cond,  \
                                         __FUNCTION__, __FILE__, STRING(__LINE__)); }

#endif /* _KERNEL_H_ */

