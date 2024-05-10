.data
	format: .asciz  "%d\n"
.text

.global gcd
.global gcd_label1
.global gcd_label2
.global two_label1
.global gcd_loop


gcd:
	cmp		%rsi,	%rdi
	je		gcd_loop
	jg		gcd_label1
	sub		%rdi,	%rsi
	jmp		gcd_label2
gcd_label1:
	movq 	%rdi, 	%rax   
	movq 	%rsi, 	%rdi   
	movq 	%rax, 	%rsi   
	sub		%rdi,	%rsi
	jmp		gcd_label2
gcd_label2:
	jmp		gcd
gcd_loop:
	movq 	%rdi,  %rbp
	ret

