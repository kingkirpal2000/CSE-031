	.data
n:	.word 25
str1:	.asciiz "Less than\n"
str2:	.asciiz "Less than or equal to\n"
str3:	.asciiz "Greater than\n"
str4:	.asciiz "Greater than or equal to\n"

	.text
main:	la $t0, n
	lw $t0, 0($t0)
	li $v0, 5
	syscall
	move $t1, $v0
	
 	sgt  $t2, $t1, $t0 
	beq  $t2, $0, ls_or_eq

gr_than:	li $v0, 4
		la $a0, str3
		syscall
		j finish

ls_or_eq:	li $v0, 4
		la $a0, str2
		syscall
		j finish

#gr_or_eq: 	li $v0, 4
#		la $a0, str4
#		syscall
#		j finish
#
#less_than:	li $v0, 4
#		la $a0, str1
#		syscall
#		j finish

	
finish: li $v0, 10
	syscall
