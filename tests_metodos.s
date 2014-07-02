	.file "tests_metodos.s"
	.global main
	.type main, @function
.INT:
	.string "Print. El valor entero es: %d \n"
.FLOAT:
	.string "Print. El valor flotante es: %f \n"
.BOOL_TRUE:
	.string "Print. El valor booleano es: True \n"
.BOOL_FALSE:
	.string "Print. El valor booleano es: False \n"
alo:
	pushq %rbp
	movq %rsp, %rbp
	addq $-16, %rsp

	movl $1, -4(%rbp)

	movq 20(%rbp), %rax
	add -4(%rbp), %rax
	movq %rax, -8(%rbp)

	movl -8(%rbp), %eax
	movl %eax, 20(%rbp)

	movq 20(%rbp), %rsi
	movq $.INT, %rdi
	movq $0, %rax
	call printf

	movl $0, %eax
	leave
	ret

alo2:
	pushq %rbp
	movq %rsp, %rbp
	addq $-20, %rsp

	movl $1, -4(%rbp)

	movq 24(%rbp), %rax
	add -4(%rbp), %rax
	movq %rax, -8(%rbp)

	movl -8(%rbp), %eax
	movl %eax, 24(%rbp)

	movq 24(%rbp), %rax
	movq %rax, 4(%rsp)

	call alo

	movq 24(%rbp), %rsi
	movq $.INT, %rdi
	movq $0, %rax
	call printf

	movl 24(%rbp), %eax
	leave
	ret

main:
	pushq %rbp
	movq %rsp, %rbp
	addq $-36, %rsp

	movl $7, -8(%rbp)

	movl %eax, -4(%rbp)

	movl $8, -12(%rbp)

	movl %eax, -8(%rbp)

	movq -4(%rbp), %rsi
	movq $.INT, %rdi
	movq $0, %rax
	call printf

	movq -4(%rbp), %rax
	movq %rax, 8(%rsp)

	call alo2

	movl %eax, -16(%rbp)

	movl %eax, -4(%rbp)

	movq -4(%rbp), %rsi
	movq $.INT, %rdi
	movq $0, %rax
	call printf

	movl $3, -20(%rbp)

	movq -20(%rbp), %rax
	imul -4(%rbp), %rax
	movq %rax, -24(%rbp)

	movq -24(%rbp), %rax
	movq %rax, 12(%rsp)

	call alo2

	movl %eax, -28(%rbp)

	movl %eax, -4(%rbp)

	movq -4(%rbp), %rsi
	movq $.INT, %rdi
	movq $0, %rax
	call printf

	movl $0, %eax
	leave
	ret

	.NEG_FLOAT:
		.long 2147483648
