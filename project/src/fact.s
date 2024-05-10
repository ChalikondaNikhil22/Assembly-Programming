.data
	format: .asciz  "%d\n"
.text

.global fact
.global fact_end


fact:
	movq	$1,	%rbx
	cmp 	%rbx,	%rdi
	jle		fact_end
	pushq	%rdi
	dec		%rdi
	call	fact
	popq	%rdi
	imulq	%rdi,	%rbp
	ret
fact_end:
	movq    $1,	%rbp
    ret
