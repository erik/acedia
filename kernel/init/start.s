; Copyright (C) 2011 by Erik Price
; 
; Permission to use, copy, modify, and/or distribute this software for any
; purpose with or without fee is hereby granted, provided that the above
; copyright notice and this permission notice appear in all copies.
; 
; THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
; WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
; MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
; ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
; WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
; ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
; OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.


MBOOT_PAGE_ALIGN    equ 1<<0
MBOOT_MEM_INFO      equ 1<<1
MBOOT_HEADER_MAGIC  equ 0x1BADB002 ; Multiboot Magic value
MBOOT_HEADER_FLAGS  equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM      equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

[BITS 32]

[GLOBAL mboot]

section .mbheader
align 4
mboot:
  dd  MBOOT_HEADER_MAGIC                               
  dd  MBOOT_HEADER_FLAGS
  dd  MBOOT_CHECKSUM

section .text

STACKSIZE equ 0x4000  ; 16K for stack
        
[GLOBAL start]
[EXTERN kmain]

start:
  push    eax   ;; multiboot magic
  push    ebx   ;; load multiboot header location

  ; Execute the kernel:
  cli           ;; disable interrupts
  call kmain    ;; enter kernel
  cli           ;; disable interrupts 
  hlt           ;; halt cpu
  jmp $         ;; just in case

section .bss
align 4
stack:
   resb STACKSIZE ; setup 16k for stack space
