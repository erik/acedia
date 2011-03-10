#include "page.h"

// mostly copied from James Molloy's tutorial, after rage-quitting several times

extern unsigned int placement ;

unsigned int* frames = 0;
unsigned int num_frames = 0;
unsigned int end_mem;


#define INDEX_FROM_BIT(a) (a/(8*4))
#define OFFSET_FROM_BIT(a) (a%(8*4))

#define COMMON_STUB \
  uint32_t frame = frame_addr/0x1000;             \
  uint32_t idx = INDEX_FROM_BIT(frame);           \
  uint32_t off = OFFSET_FROM_BIT(frame)

// Static function to set a bit in the frames bitset
static void set_frame(uint32_t frame_addr) {
  COMMON_STUB;
  frames[idx] |= (0x1 << off);
}

// Static function to clear a bit in the frames bitset
static void clear_frame(uint32_t frame_addr) {
  COMMON_STUB;
  frames[idx] &= ~(0x1 << off);
}

// Static function to test if a bit is set.
static uint32_t test_frame(uint32_t frame_addr) {
  COMMON_STUB;
  return (frames[idx] & (0x1 << off));
}

// find the first available frame
static uint32_t first_frame() {
  uint32_t i, j;
  for (i = 0; i < INDEX_FROM_BIT(num_frames); i++) {
    if (frames[i] != 0xFFFFFFFF) {
      for (j = 0; j < 32; j++) {
        uint32_t toTest = 0x1 << j;
        if (!(frames[i] & toTest)) {
          return i*4*8+j;
        }
      }
    }
  }
  return (unsigned)-1;
}

void alloc_frame(page_t *page, int is_kernel, int is_writeable) {
  // return if frame already allocated
  if (page->frame != 0) {
    return;
  }
  else {
    uint32_t idx = first_frame(); // idx is now the index of the first free frame.
    if (idx == (uint32_t)-1) {
      kpanic("No free frames!");
    }
    set_frame(idx * 0x1000);            // this frame is now ours!
    page->present = 1;                  // Mark it as present.
    page->rw = (is_writeable) ? 1 : 0;  // Should the page be writeable?
    page->user = (is_kernel) ? 0 : 1;   // Should the page be user-mode?
    page->frame = idx;
  }
}

// Function to deallocate a frame.
void free_frame(page_t *page) {
  uint32_t frame;
  if (!(frame=page->frame)) {
    return; // The given page didn't actually have an allocated frame!
  }
  else {
    clear_frame(frame); // Frame is now free again.
    page->frame = 0x0; // Page now doesn't have a frame.
  }
} 


page_t *get_page(uint32_t address, int make, page_directory_t *dir)
{
  // Turn the address into an index.
  address /= 0x1000;
  // Find the page table containing this address.
  uint32_t table_idx = address / 1024;
  if (dir->tables[table_idx]) {
    return &dir->tables[table_idx]->pages[address%1024];
  }
  else if(make) {
    uint32_t tmp;
    dir->tables[table_idx] = (page_table_t*)_kmalloc(sizeof(page_table_t), 1, &tmp);
    memset(dir->tables[table_idx], 0, 0x1000);
    dir->tables_phys[table_idx] = tmp | 0x7; // PRESENT, RW, US.
    return &dir->tables[table_idx]->pages[address%1024];
  }
  else {
    return 0;
  }
} 



void kinit_paging() {
  end_mem = multiboot_ptr->mem_upper * 1024;

  frames = (unsigned int*) kmalloc(end_mem / 0x1000, 0);
  memset(frames, 0, end_mem / 0x1000 / 8);
  
  num_frames = end_mem / 0x1000;
  frames = (unsigned*)kmalloc(INDEX_FROM_BIT(num_frames), 0);
  memset(frames, 0, INDEX_FROM_BIT(num_frames));
  
  // create page directory
  kernel_directory = (page_directory_t*)kmalloc(sizeof(page_directory_t), 1);
  memset(kernel_directory, 0, sizeof(page_directory_t));
  current_directory = kernel_directory;
  
  unsigned int i = 0;
  while (i <= (unsigned int)&_kernel_end) {
    // set kernel code to unwritable
    alloc_frame(get_page(i, 1, kernel_directory), 0, 0);
    i += 0x1000;
  }
  
  // register paeg_fault handler
  install_isr(14, page_fault);

  // set page directory
  __asm__ volatile("mov %0, %%cr3":: "r"(&kernel_directory->tables_phys));
  uint32_t cr0;
  __asm__ volatile("mov %%cr0, %0": "=r"(cr0));
  cr0 |= 0x80000000;
  __asm__ volatile("mov %0, %%cr0":: "r"(cr0));
}

void page_fault(regs_t* regs) {
  // A page fault has occurred.
  // The faulting address is stored in the CR2 register.
  uint32_t faulting_address;
  __asm__ volatile("mov %%cr2, %0" : "=r" (faulting_address));
  
  // The error code gives us details of what happened.
  int present   = !(regs->err_code & 0x1); // Page not present
  int rw = regs->err_code & 0x2;           // Write operation?
  int us = regs->err_code & 0x4;           // Processor was in user-mode?
  int reserved = regs->err_code & 0x8;     // Overwritten CPU-reserved bits of page entry?
  //  int id = regs->err_code & 0x10;          // Caused by an instruction fetch?

  // Output an error message.
  kputs("Page fault! (");
  if(present) {
    kputs("P");
  }
  if(rw) {
    kputs("R");
  } else {
    kputs("W");
  }
  if (us) {
    kputs("U");
  } else {
    kputs("K");
  }
  if(reserved) {
    kputs("Res");
  }
  kputs(") at ");
  kputhex((int)faulting_address);
  kputs("\n");
  __asm__ ("hlt");
} 
