;;  Actually write the IDT

[GLOBAL idt_flush]    ; Allows the C code to call idt_flush().
[EXTERN idt_ptr]

idt_flush:
   lidt [idt_ptr]        ; Load the IDT pointer.
   ret
