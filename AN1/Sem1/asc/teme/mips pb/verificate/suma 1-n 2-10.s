.data
n: .word 5
s: .word 0
i: .word 1
.text
main:
intrare:
lw $t0,n
ble $t0,0,sfarsit
lw $t1,i
bgt $t1,$t0,sfarsit
lw $t0,s
add $t0,$t0,$t1
sw $t0,s
addi $t1,$t1,1
sw $t1,i
j intrare

sfarsit:
li $v0,10
syscall