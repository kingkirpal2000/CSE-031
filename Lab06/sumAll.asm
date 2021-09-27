	.data
qP: 	.asciiz "Please enter a number: "
eN:	.asciiz "Sum of even numbers is: "
oN:	.asciiz "Sum of odd numbers is: "
nL:	.asciiz "\n"
	.text
main:	la $a0, qP
	li $v0, 4
	syscall #printing qP
	
	li $v0, 5
	syscall # taking user input 
	beq $v0, $zero, finish
	move $t0, $v0
	
	srl $t1, $t0, 1
	sll $t1, $t1, 1
	
	beq $t1, $t0, evenSum
	j oddSum

evenSum:	add $s0, $s0, $t0
		j main
oddSum:		add $s1, $s1, $t0
		j main	

finish: la $a0, nL #printing new line
	li $v0, 4
	syscall 
	
	la $a0, eN #printing even number string
	li $v0, 4
	syscall
	move $a0, $s0
	li $v0, 1
	syscall
	la $a0, nL
	li $v0, 4
	syscall
	
	la $a0, oN #printing odd number string
	li $v0, 4
	syscall
	move $a0, $s1
	li $v0, 1
	syscall
	la $a0, nL
	li $v0, 4
	syscall
	
	li $v0, 10
	syscall
	