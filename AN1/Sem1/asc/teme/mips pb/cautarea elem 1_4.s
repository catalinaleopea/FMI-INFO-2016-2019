.data
v: .word 2, 1, 3, 5, 4 #vectorul
n: .word 5
i: .word 0
x: .word 3
y: .word 0

.text
main:
intrare:
lw $t2,x
lw $t0, i
lw $t1,n
bge $t0,$t1,iesire
add $t0,$t0,$t0
add $t0,$t0,$t0 
lw $t0,v($t0)
lw $t3,y
beq $t0,$t2,et #daca v[i]=x
lw $t0,i
addi $t0,$t0,1 #i=i+1
sw $t0, i
j intrare

et:
li $t3,1
sw $t3,y

iesire:
li $v0,10
syscall
