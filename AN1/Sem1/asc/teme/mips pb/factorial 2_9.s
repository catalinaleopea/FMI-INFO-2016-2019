.data
n: .word 5 #5!=120 in hexa=78
s: .word 1
.text
main:
intrare:
lw $t0,n
ble $t0,0,sfarsit
lw $t1,s
mult $t1,$t0
mflo $t1
sw $t1,s
subu $t0,1
sw $t0,n
j intrare

sfarsit:
lw $a0, s
li $v0, 1
syscall
la $v0,10
syscall