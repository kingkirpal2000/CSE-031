        .data
str:	.asciiz "Please enter an integer: "
        .text
main: 		addi $sp, $sp, -4	# Moving stack pointer to make room for storing local variables (push the stack frame)
		la	$a0, str
		addi	$v0, $zero, 4
		syscall
	
		addi	$v0, $zero, 5
		syscall
		move	$a0, $v0

		jal recursion	# Call recursion(x)
		
		add $v0, $v0, $s0
		move $a0, $v0
		li $v0, 1
		syscall
		j end		# Jump to end of program


# Implementing recursion
recursion:	addi $sp, $sp, -12	# Push stack frame for local storage
		
		sw $ra, 0($sp)
		sw $a0, 4($sp)
				
		li $t0, 10
		bne $a0, $t0, not_ten
		
		li $v0, 2
		
		j end_recur
			
not_ten:	li $t2, 11
		bne $a0, $t2, not_eleven

		
		li $v0, 1
		
		j end_recur		

not_eleven:	sw $a0, 4($sp) 	
		add $s0, $s0, $a0
		addi $a0, $a0, 2
		
		
		jal recursion	
		
	
		sw $v0, 8($sp)
		
		
		lw $a0, 4($sp)
		addi $a0, $a0, 1
		
		jal recursion	
		
		
		lw $t0, 8($sp)
		add $v0, $v0, $t0
		
		j end_recur
		

# End of recursion function	
end_recur:	# TPS 2 #15 
		lw $ra, 0($sp)
		addi $sp, $sp, 12	# Pop stack frame 
		jr $ra

# Terminating the program
end:	addi $sp, $sp 4	# Moving stack pointer back (pop the stack frame)
		li $v0, 10 
		syscall
