	.file "tests_math.s"
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
main:
	pushq %rbp
	movq %rsp, %rbp
	addq $-96, %rsp

	movl $2, -8(%rbp)

	movl $2, -12(%rbp)

	movq -8(%rbp), %rax
	imul -12(%rbp), %rax
	movq %rax, -16(%rbp)

	movl $4, -20(%rbp)

	movq -16(%rbp), %rax
	add -20(%rbp), %rax
	movq %rax, -24(%rbp)

	movl -24(%rbp), %eax
	movl %eax, -4(%rbp)

	movl $8, -28(%rbp)

	movl -28(%rbp), %eax
	cmp -4(%rbp), %eax
	sete %al
	movzbl %al, %eax
	movl %eax, -32(%rbp)

	movl -32(%rbp), %eax
	movl %eax, -8(%rbp)

label_0_if:

	cmp $0, -8(%rbp)
	jz label_1_else

	movl $8, -36(%rbp)

	movl -36(%rbp), %eax
	cmp -4(%rbp), %eax
	sete %al
	movzbl %al, %eax
	movl %eax, -40(%rbp)

	cmp $0, -40(%rbp)
	jz label_bool_condition_of_print0
	movq $.BOOL_TRUE, %rdi
	jmp end_label_bool_condition_of_print0
label_bool_condition_of_print0:
	movq $.BOOL_FALSE, %rdi
end_label_bool_condition_of_print0:
	movq $0, %rax
	call printf

	movl $8, -44(%rbp)

	movl -44(%rbp), %eax
	cmp -4(%rbp), %eax
	setle %al
	movzbl %al, %eax
	movl %eax, -48(%rbp)

	cmp $0, -48(%rbp)
	jz label_bool_condition_of_print1
	movq $.BOOL_TRUE, %rdi
	jmp end_label_bool_condition_of_print1
label_bool_condition_of_print1:
	movq $.BOOL_FALSE, %rdi
end_label_bool_condition_of_print1:
	movq $0, %rax
	call printf

	movl $8, -52(%rbp)

	movl -52(%rbp), %eax
	cmp -4(%rbp), %eax
	setge %al
	movzbl %al, %eax
	movl %eax, -56(%rbp)

	cmp $0, -56(%rbp)
	jz label_bool_condition_of_print2
	movq $.BOOL_TRUE, %rdi
	jmp end_label_bool_condition_of_print2
label_bool_condition_of_print2:
	movq $.BOOL_FALSE, %rdi
end_label_bool_condition_of_print2:
	movq $0, %rax
	call printf

label_1_else:

label_3_if:

	cmpl $1, -8(%rbp)
	setne %al
	movzbl %al, %eax
	movl %eax, -60(%rbp)

	cmpl $1, -60(%rbp)
	setne %al
	movzbl %al, %eax
	movl %eax, -64(%rbp)

	cmp $0, -64(%rbp)
	jz label_4_else

	movl $8, -68(%rbp)

	movl -68(%rbp), %eax
	cmp -4(%rbp), %eax
	setne %al
	movzbl %al, %eax
	movl %eax, -72(%rbp)

	cmp $0, -72(%rbp)
	jz label_bool_condition_of_print3
	movq $.BOOL_TRUE, %rdi
	jmp end_label_bool_condition_of_print3
label_bool_condition_of_print3:
	movq $.BOOL_FALSE, %rdi
end_label_bool_condition_of_print3:
	movq $0, %rax
	call printf

	movl $8, -76(%rbp)

	movl -76(%rbp), %eax
	cmp -4(%rbp), %eax
	setl %al
	movzbl %al, %eax
	movl %eax, -80(%rbp)

	cmp $0, -80(%rbp)
	jz label_bool_condition_of_print4
	movq $.BOOL_TRUE, %rdi
	jmp end_label_bool_condition_of_print4
label_bool_condition_of_print4:
	movq $.BOOL_FALSE, %rdi
end_label_bool_condition_of_print4:
	movq $0, %rax
	call printf

	movl $8, -84(%rbp)

	movl -84(%rbp), %eax
	cmp -4(%rbp), %eax
	setg %al
	movzbl %al, %eax
	movl %eax, -88(%rbp)

	cmp $0, -88(%rbp)
	jz label_bool_condition_of_print5
	movq $.BOOL_TRUE, %rdi
	jmp end_label_bool_condition_of_print5
label_bool_condition_of_print5:
	movq $.BOOL_FALSE, %rdi
end_label_bool_condition_of_print5:
	movq $0, %rax
	call printf

label_4_else:

	movl $0, %eax
	leave
	ret

	.NEG_FLOAT:
		.long 2147483648
