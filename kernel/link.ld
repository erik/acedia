ENTRY(start)

SECTIONS {
   
  . = 0x100000;
  _kernel_start = .;

  .mbheader : {
    *(.mbheader)
  }  
  
  .text : {
    code = .;
    *(.text)
    . = ALIGN(4096);
  }

  .data : {
     data = .;
     *(.data)
     *(.rodata)
     . = ALIGN(4096);
  }

  .bss : {
    bss = .;
    *(.bss)
    . = ALIGN(4096);
  }

  _kernel_end = .;
}


