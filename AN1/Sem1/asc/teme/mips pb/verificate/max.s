.data
a:.word 3
d:.word 1
c:.word 2
max:.space 4

.text
main:
lw $t0, a
lw $t1, d
bge $t0,$t1,else
lw $t0,d
lw $t1,c
bge $t0,$t1,iesire
lw $t0,c
b iesire

else:
lw $t1,c
bge $t0,$t1,iesire
lw $t0,c

iesire:
sw $t0,max
li $v0,10
syscall