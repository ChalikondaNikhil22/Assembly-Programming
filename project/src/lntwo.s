.data
	format: .asciz  "%d\n"
.text

.global two
.global two_label1

two:
	cmp 	$1,	%rdi
	jle	two_label1
	pushq	%rdi
	pushq	$2
	xor	%rbx,	%rbx
	xor	%rdx,	%rdx
	xor	%rax,	%rax
	popq	%rbx
	popq	%rax
	idivq	%rbx
	pushq	%rax
	popq	%rdi
	call 	two_label1
	add	$1,	%rdi
	ret

two_label1:
	movq    $0,	%rdi
    ret
