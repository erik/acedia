;; Setting up all the ISRs

; in isr.c
[EXTERN handle_isr]

; Macro the ISR creation, since it's incredibly repetetive

; No error code
%macro ISRN 1
  [GLOBAL isr%1]        ; %1 accesses the first parameter.
  isr%1:
    cli
    push byte 0
    push byte %1
    jmp isr_common_stub
%endmacro

; Error code
%macro ISRE 1
  [GLOBAL isr%1]
  isr%1:
    cli
    push byte %1
    jmp isr_common_stub
%endmacro 


ISRN  0         ; Division by zero exception
ISRN  1         ; Debug exception
ISRN  2         ; Non maskable interrupt
ISRN  3         ; Breakpoint exception
ISRN  4         ; 'Into detected overflow'
ISRN  5         ; Out of bounds exception
ISRN  6         ; Invalid opcode exception
ISRN  7         ; No coprocessor exception

ISRE  8         ; Double fault (pushes an error code)

ISRN 9          ; Coprocessor segment overrun

ISRE 10         ; Bad TSS (pushes an error code)
ISRE 11         ; Segment not present (pushes an error code)
ISRE 12         ; Stack fault (pushes an error code)
ISRE 13         ; General protection fault (pushes an error code)
ISRE 14         ; Page fault (pushes an error code)

ISRN 15         ; Unknown interrupt exception
ISRN 16         ; Coprocessor fault
ISRN 17         ; Alignment check exception
ISRN 18         ; Machine check exception

; Reserved
ISRN 19
ISRN 20
ISRN 21
ISRN 22
ISRN 23
ISRN 24
ISRN 25
ISRN 26
ISRN 27
ISRN 28
ISRN 29
ISRN 30
ISRN 31



; Common ISR code
isr_common_stub:
  pusha                    ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

  mov ax, ds               ; Lower 16-bits of eax = ds.
  push eax                 ; save the data segment descriptor

  mov ax, 0x10  ; load the kernel data segment descriptor
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  call handle_isr

  pop eax        ; reload the original data segment descriptor
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  popa                     ; Pops edi,esi,ebp...
  add esp, 8     ; Cleans up the pushed error code and pushed ISR number
  sti
  iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP
