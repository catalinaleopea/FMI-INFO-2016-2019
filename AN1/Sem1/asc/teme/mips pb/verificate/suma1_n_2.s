.data
n:.word 3
suma:.space 4
.text
main:

lw $t0,n
li $t1,2
div $t0,$t1
mflo $t2
addi $t3,$t2,1
li $t1,0
et1:

bgt $t3,$t0,et2
add $t1,$t1,$t2
add $t1,$t1,$t3
addi $t2,$t2,-1
addi $t3,$t3,1
b et1

et2:
sw $t1,suma
li $v0,10
syscall