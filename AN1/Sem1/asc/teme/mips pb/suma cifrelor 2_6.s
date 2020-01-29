.data
x: .word 1235
suma: .word 0

.text
main:
lw $t0,x
intrare:
ble $t0,0,sfarsit
li $t1,10
div $t0,$t1
mflo $t0
sw $t0,x
mfhi $t1
lw $t2,suma
bge $t2,0,et
sw $t1,suma

et:
add $t2,$t2,$t1
sw $t2,suma
b intrare

sfarsit:
li $v0,10
syscall