.text
.globl main
main:
    li $v0,4
	la $a0,var_1
	syscall

	li $v0,5
	syscall
	sw $v0,num_1

	move $t1,$v0

	li $v0,4
	la $a0,var_1
	syscall

	li $v0,5
	syscall
	sw $v0,num_2
	move $t2,$v0

	li $t0,0

Product:
    beq $t1,$0,end
	add $t0,$t0,$t2
	addi $t1,$t1,-1
	j Product

end:
    sw $t0,result
	li $v0,4
	la $a0,rslt
	syscall

	li $v0,1
	lw $a0,result
	syscall

	li $v0,12
	syscall
	move $t3,$v0

	li $v0,10
	syscall

.data
num_1:	.space	4
num_2:	.space	4
result:	.space	4

var_1:  .asciiz "\nPlease enter a value: "
rslt:  .asciiz	"The Product of the above number given is: "