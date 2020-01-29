.data
 n:.word 0
 t:.space 4
.text
main:
 lw $v0, n
 lw $t1, n
 li $s0, 2
 div $v0, $s0
 mflo $v0
 mfhi $s0
 li $v1, 0
 add $v0, $v0, $s0
 li $s1, 0
 add $t1, $t1, $s0
Loop:
 ble $v0, $v1 end
 add $s1, $s1, $v0
 sub $s2, $t1, $v0
 addu $s2, $s2, 1
 add $s1, $s1, $s2
 subu $v0, $v0, 1
 j Loop
end:
 mul $v1, $s0, $t1
 sub $s1, $s1, $v1
 sw $s1, t
 li $v0, 10
 syscall