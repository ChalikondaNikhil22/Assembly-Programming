.data
	format: .asciz  "%d\n"
.text

.global cmpi
.global sub_opr
.global add_opr
.global mul_opr
.global div_opr
.global negetive_number

cmpi:
	cmp		%r9,	%rdi          
	ret                           

sub_opr:
	sub		%rbx,	%rax       
	movq  	%rax,	%rdx                          
	ret                         

add_opr:
	add		%rax,	%rbx
	movq  	%rbx,	%rdx                                    
	ret                           

mul_opr:
	imulq	%rax,	%rbx	               
	movq  	%rbx,	%rdx                          
	ret                           

div_opr:
	xor		%rdx,	%rdx          
	idivq	%rbx                            
	movq  	%rax,	%rdx                         
	ret                          

negetive_number: 
	neg		%r9                         
	popq  	%r9
	ret                      

