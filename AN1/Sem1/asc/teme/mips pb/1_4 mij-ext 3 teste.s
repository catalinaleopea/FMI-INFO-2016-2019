.data
x: .word 3
y: .word 0
v: .word 2, 4, 1, 5, 3
n: .word 5

.text
main:
lw $t3,n
li $t1,0
li $t0,2
div $t3,$t0
mflo $t2
move $t3,$t2
li $t4,4
mult $t2,$t4
mflo $t2
mult $t3,$t4
mflo $t3

ciclu:
li $t4,0 
blt $t2,$t4,out
lw $t0,v($t2)
lw $t4,x
beq $t4,$t0,gasit
lw $t0,v($t3)
beq $t4,$t0,gasit
addi $t3,$t3,4
addi $t2,$t2,-4
j ciclu

gasit:
li $t4,1
sw $t4,y

out:
li $v0,10
syscall