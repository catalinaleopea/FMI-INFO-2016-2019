.data
x: .word 4
y: .word 0
v: .word 2, 4, 1, 5, 3
n: .word 5

.text
main:
li $t2,0
lw $t3,n
li $t1,0
li $t0,2
addi $t3,$t3,-1
add $t3,$t3,$t3
add $t3,$t3,$t3
lw $t4,x

ciclu:
bgt $t2,$t3,out
lw $t0,v($t2)
beq $t4,$t0,gasit
lw $t0,v($t3)
beq $t4,$t0,gasit
addi $t2,$t2,4
addi $t3,$t3,-4
j ciclu

gasit:
li $t0,1
sw $t0,y

out:
li $v0,10
syscall