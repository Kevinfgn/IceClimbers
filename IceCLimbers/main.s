	.file	"main.c"
	.text
	.section	.rodata
	.align 8
.LC0:
	.string	"failed to initialize allegro!\n"
.LC1:
	.string	"failed to create display!\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB20:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	$0, -24(%rbp)
	movq	atexit@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movl	$84018433, %edi
	call	al_install_system@PLT
	xorl	$1, %eax
	testb	%al, %al
	je	.L2
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$30, %edx
	movl	$1, %esi
	leaq	.LC0(%rip), %rdi
	call	fwrite@PLT
	movl	$-1, %eax
	jmp	.L3
.L2:
	movl	$480, %esi
	movl	$640, %edi
	call	al_create_display@PLT
	movq	%rax, -24(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L4
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$26, %edx
	movl	$1, %esi
	leaq	.LC1(%rip), %rdi
	call	fwrite@PLT
	movl	$-1, %eax
	jmp	.L3
.L4:
	movl	$0, %edx
	movl	$0, %esi
	movl	$0, %edi
	call	al_map_rgb@PLT
	movq	%xmm0, %rax
	movq	%xmm1, %rcx
	movq	%rcx, %rdx
	movq	%rax, %rcx
	movq	%rdx, %rbx
	movq	%rdx, %rax
	movq	%rcx, -40(%rbp)
	movq	-40(%rbp), %xmm0
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %xmm1
	call	al_clear_to_color@PLT
	call	al_flip_display@PLT
	movq	.LC2(%rip), %rax
	movq	%rax, -40(%rbp)
	movsd	-40(%rbp), %xmm0
	call	al_rest@PLT
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	al_destroy_display@PLT
	movl	$0, %eax
.L3:
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE20:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC2:
	.long	0
	.long	1076101120
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
