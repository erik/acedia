	.file	"thread.c"
	.comm	idt_entries,2048,32
	.comm	idt_ptr,6,1
	.text
.globl kputhex
	.type	kputhex, @function
kputhex:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	$16, %esi
	movl	%eax, %edi
	call	kputnum
	leave
	ret
	.cfi_endproc
.LFE0:
	.size	kputhex, .-kputhex
.globl kputdec
	.type	kputdec, @function
kputdec:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	$10, %esi
	movl	%eax, %edi
	call	kputnum
	leave
	ret
	.cfi_endproc
.LFE1:
	.size	kputdec, .-kputdec
.globl enableInterrupts
	.type	enableInterrupts, @function
enableInterrupts:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
#APP
# 32 "build/include/kernel.h" 1
	sti
# 0 "" 2
#NO_APP
	leave
	ret
	.cfi_endproc
.LFE2:
	.size	enableInterrupts, .-enableInterrupts
.globl disableInterrupts
	.type	disableInterrupts, @function
disableInterrupts:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
#APP
# 36 "build/include/kernel.h" 1
	cli
# 0 "" 2
#NO_APP
	leave
	ret
	.cfi_endproc
.LFE3:
	.size	disableInterrupts, .-disableInterrupts
	.comm	multiboot_ptr,8,8
.globl thread_index
	.data
	.align 4
	.type	thread_index, @object
	.size	thread_index, 4
thread_index:
	.long	1
.globl threads
	.bss
	.align 32
	.type	threads, @object
	.size	threads, 8192
threads:
	.zero	8192
	.text
.globl save_registers
	.type	save_registers, @function
save_registers:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
#APP
# 12 "kernel/thread/thread.c" 1
	mov %eax, %edx
# 0 "" 2
#NO_APP
	movq	-8(%rbp), %rax
	movl	%edx, (%rax)
#APP
# 14 "kernel/thread/thread.c" 1
	mov %ebx, %edx
# 0 "" 2
#NO_APP
	movq	-8(%rbp), %rax
	movl	%edx, 4(%rax)
#APP
# 15 "kernel/thread/thread.c" 1
	mov %ecx, %edx
# 0 "" 2
#NO_APP
	movq	-8(%rbp), %rax
	movl	%edx, 8(%rax)
#APP
# 16 "kernel/thread/thread.c" 1
	mov %edx, %edx
# 0 "" 2
#NO_APP
	movq	-8(%rbp), %rax
	movl	%edx, 12(%rax)
#APP
# 18 "kernel/thread/thread.c" 1
	mov %esi, %edx
# 0 "" 2
#NO_APP
	movq	-8(%rbp), %rax
	movl	%edx, 28(%rax)
#APP
# 19 "kernel/thread/thread.c" 1
	mov %edi, %edx
# 0 "" 2
#NO_APP
	movq	-8(%rbp), %rax
	movl	%edx, 32(%rax)
#APP
# 20 "kernel/thread/thread.c" 1
	mov %ebp, %edx
# 0 "" 2
#NO_APP
	movq	-8(%rbp), %rax
	movl	%edx, 36(%rax)
#APP
# 21 "kernel/thread/thread.c" 1
	mov %esp, %edx
# 0 "" 2
#NO_APP
	movq	-8(%rbp), %rax
	movl	%edx, 44(%rax)
#APP
# 23 "kernel/thread/thread.c" 1
	mov %cs, %dx
# 0 "" 2
#NO_APP
	movq	-8(%rbp), %rax
	movw	%dx, 16(%rax)
#APP
# 24 "kernel/thread/thread.c" 1
	mov %ds, %dx
# 0 "" 2
#NO_APP
	movq	-8(%rbp), %rax
	movw	%dx, 18(%rax)
#APP
# 25 "kernel/thread/thread.c" 1
	mov %es, %dx
# 0 "" 2
#NO_APP
	movq	-8(%rbp), %rax
	movw	%dx, 20(%rax)
#APP
# 26 "kernel/thread/thread.c" 1
	mov %fs, %dx
# 0 "" 2
#NO_APP
	movq	-8(%rbp), %rax
	movw	%dx, 22(%rax)
#APP
# 27 "kernel/thread/thread.c" 1
	mov %gs, %dx
# 0 "" 2
#NO_APP
	movq	-8(%rbp), %rax
	movw	%dx, 24(%rax)
#APP
# 28 "kernel/thread/thread.c" 1
	mov %ss, %dx
# 0 "" 2
#NO_APP
	movq	-8(%rbp), %rax
	movw	%dx, 26(%rax)
#APP
# 30 "kernel/thread/thread.c" 1
	pushf; pop %eax; mov %eax, %edx
# 0 "" 2
#NO_APP
	movq	-8(%rbp), %rax
	movl	%edx, 48(%rax)
	leave
	ret
	.cfi_endproc
.LFE4:
	.size	save_registers, .-save_registers
.globl load_registers
	.type	load_registers, @function
load_registers:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movzwl	18(%rax), %eax
#APP
# 34 "kernel/thread/thread.c" 1
	mov %ax, %ds
# 0 "" 2
#NO_APP
	movq	-8(%rbp), %rax
	movzwl	20(%rax), %eax
#APP
# 35 "kernel/thread/thread.c" 1
	mov %ax, %es
# 0 "" 2
#NO_APP
	movq	-8(%rbp), %rax
	movzwl	22(%rax), %eax
#APP
# 36 "kernel/thread/thread.c" 1
	mov %ax, %fs
# 0 "" 2
#NO_APP
	movq	-8(%rbp), %rax
	movzwl	24(%rax), %eax
#APP
# 37 "kernel/thread/thread.c" 1
	mov %ax, %gs
# 0 "" 2
#NO_APP
	movq	-8(%rbp), %rax
	movzwl	26(%rax), %eax
#APP
# 38 "kernel/thread/thread.c" 1
	mov %ax, %ss
# 0 "" 2
#NO_APP
	movq	-8(%rbp), %rax
	movl	48(%rax), %eax
#APP
# 40 "kernel/thread/thread.c" 1
	push %eax; popf
# 0 "" 2
#NO_APP
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
#APP
# 43 "kernel/thread/thread.c" 1
	push %eax
# 0 "" 2
#NO_APP
	movq	-8(%rbp), %rax
	movl	8(%rax), %eax
#APP
# 44 "kernel/thread/thread.c" 1
	push %eax
# 0 "" 2
#NO_APP
	movq	-8(%rbp), %rax
	movl	12(%rax), %eax
#APP
# 45 "kernel/thread/thread.c" 1
	push %eax
# 0 "" 2
#NO_APP
	movq	-8(%rbp), %rax
	movl	4(%rax), %eax
#APP
# 46 "kernel/thread/thread.c" 1
	push %eax
# 0 "" 2
#NO_APP
	movq	-8(%rbp), %rax
	movl	44(%rax), %eax
#APP
# 48 "kernel/thread/thread.c" 1
	push %eax
# 0 "" 2
#NO_APP
	movq	-8(%rbp), %rax
	movl	36(%rax), %eax
#APP
# 49 "kernel/thread/thread.c" 1
	push %eax
# 0 "" 2
#NO_APP
	movq	-8(%rbp), %rax
	movl	28(%rax), %eax
#APP
# 50 "kernel/thread/thread.c" 1
	push %eax
# 0 "" 2
#NO_APP
	movq	-8(%rbp), %rax
	movl	32(%rax), %eax
#APP
# 51 "kernel/thread/thread.c" 1
	push %eax
# 0 "" 2
# 53 "kernel/thread/thread.c" 1
	popa
# 0 "" 2
#NO_APP
	leave
	ret
	.cfi_endproc
.LFE5:
	.size	load_registers, .-load_registers
.globl init_threading
	.type	init_threading, @function
init_threading:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	movl	$0, thread_index(%rip)
	movl	$thread_swap, %edi
	call	install_time_handler
	leave
	ret
	.cfi_endproc
.LFE6:
	.size	init_threading, .-init_threading
.globl thread_swap
	.type	thread_swap, @function
thread_swap:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	$32, %esi
	movl	$32, %edi
	call	outb
	movl	thread_index(%rip), %eax
	mov	%eax, %eax
	movq	threads(,%rax,8), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	save_registers
	movl	thread_index(%rip), %eax
	addl	$1, %eax
	movl	%eax, thread_index(%rip)
	movl	thread_index(%rip), %eax
	andl	$1, %eax
	movl	%eax, thread_index(%rip)
	movl	thread_index(%rip), %eax
	mov	%eax, %eax
	movq	threads(,%rax,8), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	load_registers
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
#APP
# 76 "kernel/thread/thread.c" 1
	push %eax
# 0 "" 2
#NO_APP
	movq	-16(%rbp), %rax
	movl	8(%rax), %eax
#APP
# 77 "kernel/thread/thread.c" 1
	push %eax
# 0 "" 2
#NO_APP
	movq	-16(%rbp), %rax
	movl	12(%rax), %eax
#APP
# 78 "kernel/thread/thread.c" 1
	push %eax
# 0 "" 2
#NO_APP
	movq	-16(%rbp), %rax
	movl	4(%rax), %eax
#APP
# 79 "kernel/thread/thread.c" 1
	push %eax
# 0 "" 2
#NO_APP
	movq	-16(%rbp), %rax
	movl	44(%rax), %eax
#APP
# 81 "kernel/thread/thread.c" 1
	push %eax
# 0 "" 2
#NO_APP
	movq	-16(%rbp), %rax
	movl	36(%rax), %eax
#APP
# 82 "kernel/thread/thread.c" 1
	push %eax
# 0 "" 2
#NO_APP
	movq	-16(%rbp), %rax
	movl	28(%rax), %eax
#APP
# 83 "kernel/thread/thread.c" 1
	push %eax
# 0 "" 2
#NO_APP
	movq	-16(%rbp), %rax
	movl	32(%rax), %eax
#APP
# 84 "kernel/thread/thread.c" 1
	push %eax
# 0 "" 2
# 86 "kernel/thread/thread.c" 1
	popa
# 0 "" 2
#NO_APP
	movq	-16(%rbp), %rax
	movl	44(%rax), %eax
#APP
# 88 "kernel/thread/thread.c" 1
	mov %eax, %esp
# 0 "" 2
#NO_APP
	movq	-16(%rbp), %rax
	movl	36(%rax), %eax
#APP
# 89 "kernel/thread/thread.c" 1
	mov %eax, %ebp
# 0 "" 2
#NO_APP
	movq	-16(%rbp), %rax
	movq	56(%rax), %rax
#APP
# 93 "kernel/thread/thread.c" 1
	sti; jmp *%rax
# 0 "" 2
#NO_APP
	leave
	ret
	.cfi_endproc
.LFE7:
	.size	thread_swap, .-thread_swap
.globl add_thread
	.type	add_thread, @function
add_thread:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	subq	$24, %rsp
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L18
.L19:
	addl	$1, -4(%rbp)
.L18:
	movl	-4(%rbp), %eax
	mov	%eax, %eax
	movq	threads(,%rax,8), %rax
	testq	%rax, %rax
	jne	.L19
	movl	-4(%rbp), %eax
	mov	%eax, %eax
	movq	-24(%rbp), %rdx
	movq	%rdx, threads(,%rax,8)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	save_registers
	leave
	ret
	.cfi_endproc
.LFE8:
	.size	add_thread, .-add_thread
	.ident	"GCC: (Ubuntu/Linaro 4.4.4-14ubuntu5) 4.4.5"
	.section	.note.GNU-stack,"",@progbits
