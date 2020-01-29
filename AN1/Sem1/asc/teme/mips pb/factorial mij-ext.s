.data
n: .word 5 #5!=120 in hexa=78
s: .word 1

.text
main:
lw $t0,n
li $t1,2
div $t0,$t1
mflo $t2
addi $t3,$t2,1

intrare:
ble $t2,$zero,sfarsit
lw $t1,s
mult $t1,$t2
mflo $t1
mult $t1,$t3
mflo $t1
sub $t2,$t2,1
addi $t3,$t3,1
sw $t1,s
j intrare

sfarsit:
mult $t1,$t3
mflo $t1
sw $t1,s
lw $a0, s
li $v0, 1

syscall
la $v0,10
syscall