.data
s: .word 0
v: .word 2, 4, 1, 5, 3
n: .word 4

.text
main:
li $t2,0
lw $t3,n
li $t1,0
li $t0,2
div $t3,$t0
mfhi $t4
addi $t3,$t3,-1
add $t3,$t3,$t3
add $t3,$t3,$t3

ciclu:
bgt $t2,$t3,out
lw $t0,v($t2)
add $t1,$t0,$t1
lw $t0,v($t3)
add $t1,$t0,$t1
addi $t2,$t2,4
addi $t3,$t3,-4
j ciclu

out:
mult $t0,$t4
mflo $t0
sub $t1,$t1,$t0
sw $t1,s
li $v0,10
syscall