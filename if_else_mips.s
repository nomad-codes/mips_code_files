.data
.text
.globl main
main:
li $t0, 2;
li $t1, 3;

bne $t0, $t1, Label1
and $t4, $t0, $t1
j end_program

Label1: or $t4, $t0, $t1

end_program:
    li $v0, 1
    move $a0, $t4
    syscall
    li $v0, 10
    syscall