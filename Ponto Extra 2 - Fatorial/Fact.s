.data
  prompt: .asciiz   "\n"
  
########################################################  
.text
.globl main
main:
	li $v0, 5
	syscall
	move $a0, $v0

	
	jal fact
	move $a0, $v0
	
	li $v0, 1
	syscall
	
	li $v0, 10
	syscall
	
	fact: slti   $t0, $a0, 2
		  beq    $t0, $0, else
		  li     $v0, 1
		  jr     $ra
	else: addiu  $sp, $sp, -8
		  sw     $a0, 4($sp)
		  sw 	 $ra, 0($sp)
		  addiu  $a0, $a0, -1
		  jal fact
		  lw 	 $a0, 4($sp)
		  lw 	 $ra, 0($sp)
		  mul 	 $v0, $a0, $v0
		  addiu	 $sp, $sp, 8
		  jr 	 $ra
		  