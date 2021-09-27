	.text
main: add $t0, $t0, $s0
	subi $t1, $t0, 1
	subi $t2, $t1, 2
	subi $t3, $t2, 3
	subi $t4, $t3, 4
	subi $t5, $t4, 5
	subi $t6, $t5, 6
	subi $t7, $t6, 7
	

finish:
	li $v0, 10
	syscall
	
#In other words, for each register from $t1 to $t7, you program should
#storethe difference of the previous $tXregister value 
#and an incremental constant. The $s0 register contains the initial value. 
