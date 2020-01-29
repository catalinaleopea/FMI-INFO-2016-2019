.data
a:.word 3
d:.word 2
c:.word 1
max:.space 4

.text
main:
lw $t0, a
lw $t1, d
lw $t2, c
bge $t0,$t1,else
sw $t1,max
bge $t1,$t2,iesire
j else2

else:
sw $t0,max
bge $t0,$t2,iesire
j else2

else2:
sw $t2,max
b iesire

iesire:
li $v0,10
syscall
