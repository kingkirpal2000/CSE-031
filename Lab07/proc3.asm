	.data

	.text
main:	addi $s0, $s0, 5
	addi $s1, $s1, 10
	addi $s2, $s2, 15
	move $a0, $s0
	move $a1, $s1
	move $a2, $s2
	add  $s2, $s2, $s1
	add  $s2, $s2, $s0
	jal sum
	add  $s2, $s2, $v0
	j exit
	
sum:	addi $sp, $sp, -12
	sw   $a0, 12($sp)
	sw   $a1, 8($sp)
	sw   $a2, 4($sp)
	sw   $ra, 0($sp)
	add  $a0, $a0, $a1
	add  $a1, $a1, $a2
	add  $a2, $a2, $s0
	jal sub
	move $s0, $v0
	lw   $a0, 12($sp)
	lw   $a1, 8($sp)
	lw   $a2, 4($sp)
	sub  $t0, $a0, $a2
	sub  $t1, $a1, $a0
	add  $t2, $a1, $a1
	move $a0, $t0
	move $a1, $t1
	move $a2, $t2
	jal sub
	move $s1, $v0
	add  $v0, $s0, $s1
	lw   $ra, 0($sp)
	addi $sp, $sp, 12
	jr   $ra
	
sub:	add $v0, $v0, $zero
	sub $v0, $a2, $a0
	sllv $v0, $v0, $a1
	jr $ra
	
	
exit: 	move $a0, $s2
	li $v0, 1
	syscall
	li $v0, 10
	syscall
