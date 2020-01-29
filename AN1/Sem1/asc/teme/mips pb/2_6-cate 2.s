.data
n: .word 12345
s: .space 4

.text

main:
lw $t0,n
li $t1,0
li $t2,10

ciclu:
beq $t0,$zero,iesire 
div $t0,$t2
mfhi $t3
add $t1,$t1,$t3
mflo $t0
div $t0,$t2
mfhi $t3
add $t1,$t1,$t3
mflo $t0
j ciclu

iesire:
sw $t1,s
syscall
