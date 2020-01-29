#subiect 23
.data
c: .byte 'a'
n: .word 5
k: .byte 0
i: .word 1
.text
main:

intrare:
lw $t0,n
ble $t0,0,sfarsit # n<=0
lw $t1,i
bgt $t1,$t0,push #folosim un contor i,i>=n
lw $t0,c
addi $sp,$sp,-4 #decrementeaza pointerul catre stiva cu 4
sw $t0, 0($sp) #salveaza caracterul din $t0 in stiva
addi $t1,$t1,1 #incrementeaza contorul
sw $t1,i
j intrare

push:
addi $sp,$sp,-4 #decrementeaza pointerul catre stiva cu 4
lw $t0,k
sw $t0, 0($sp) #adaugam 0 la sfarsit

sfarsit:
li $v0,10
syscall