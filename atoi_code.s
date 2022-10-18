.globl main
.text
main:
    li $v0, 8
	la $a0, string
	#li $a1, 2
	syscall

    la $a0, string
    move $t0, $v0
    jal atoi

    move $a0, $v0
    li $v0, 1
    syscall
exit:
    li $v0, 10
    syscall
atoi:
    sub $sp, $sp,4
    sw $ra, 0($sp)

    move $t0, $a0

    li $v0, 0

next:
    lb $t1, ($t0)

    blt $t1, 48, endloop
    bgt $t1, 57, endloop

    mul $v0, $v0, 10
    add $v0, $v0, $t1
    sub $v0, $v0, 48

    add $t0, $t0, 1

    b next
endloop:
    lw $ra, 0($sp)
    add $sp, $sp, 4
    jr $ra

    .data
string: .space 1024
