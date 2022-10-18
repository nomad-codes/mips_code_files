.text
.globl  main
main:
.text
    li $v0, 4
    la $a0, var_1
    syscall

    li $v0, 5
    syscall
    move $t0, $v0

    li $v0, 4
    la $a0, var_2
    syscall

    li $v0, 5
    syscall
    move $t1, $v0

    slt $s0, $t0, $t1
    bne $s0, $zero, res
    move $t1, $t0

res:
    li $v0, 4
    la $a0, var_4
    syscall

    li $v0, 1
    move $a0, $t1
    syscall

    .data
var_1: .asciiz "First Number -:  "
var_2: .asciiz "Second Number -:  "
var_4: .asciiz "Resulting Larger Number -:  "
newline: .asciiz "\n"