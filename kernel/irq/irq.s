; IRQ handling

[EXTERN handle_irq]  

%macro IRQ 1
  [GLOBAL irq%1]
  irq%1:
    port%1 equ %1 + 32
    cli
    push byte 0
    push byte port%1
    jmp irq_common
%endmacro

IRQ 0
IRQ 1
IRQ 2
IRQ 3
IRQ 4
IRQ 5
IRQ 6
IRQ 7
IRQ 8
IRQ 9
IRQ 10
IRQ 11
IRQ 12
IRQ 13
IRQ 14
IRQ 15
    
irq_common:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, handle_irq
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret

%ifdef comment
   pusha

   mov ax, ds
   push eax

   mov ax, 0x10
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax

   call handle_irq

   pop ebx
   mov ds, bx
   mov es, bx
   mov fs, bx
   mov gs, bx

   popa
   add esp, 8
   sti
   iret
%endif
