jmp start

number db 5 dup 0
cr dw 10, 13, "$"
temp dw 0
check dw 0

start:
    mov cx,0
    mov bx,0
input:
    mov ax, 0
    mov ah, 01h
    int 21h ;takes an input character
    mov dx, 0
    mov dl, al
    mov ax, cx ; cx gives the stored digits to ax, since input is read char by char and to have the whole number like 321, we store it.
    cmp dl, 0D ;if the character is newline jumps to lfin
    je lfin
    cmp dl, ' ' ;if the character is space character jumps to fin
    je fin
    jmp dummyjump ; go to dummy jump to prevent jump>128
fin:
    cmp check,0 ;this is to prevent pushing into stack whenever the space is after an operation character
    je input
    push cx; push the stored number into stack
    mov cx, 0 ;get rid of the stored number that we pushed
    jmp input
lfin:
    cmp cx,0 ; check the edge case that only one number input is given
    jne lfinonevalue
    pop ax ;after the operations are done pops the output to ax
    mov bx, offset number+4 ;stores the postition of the last character of the number array in the bx register
    mov b[bx],"$" ; end of the string
    dec bx 
    jmp convert_hexadecimal
lfinonevalue:
    
    mov ax,cx ;after the operations are done pops the output to ax
    mov bx, offset number+4 ;stores the postition of the last character of number in the bx register
    mov b[bx],"$" ; end of the string
    dec bx
    jmp convert_hexadecimal 
bdec:
    sub dx, '0' ;converts ascii code to the real value of the integer
    mov temp,dx
    mov ax, cx
    mov cx, 10h
    mul cx ;multiplies the previous value of cx with 16 before adding the current character
    add ax, temp
    mov cx, ax
    jmp input
letter: ;decreases the ascii code even more since letters' ascii value are not consecutive with digits'
    sub dx, 7d
    jmp bdec
lowercase: ;decreases the ascii code even more since lowercase letters' ascii value are not consecutive with digits'
    sub dx, 39d
    jmp bdec

dummyjump:
    mov check,0
    cmp dl, '+' ;if the character is plus jump to badd
    je badd
    cmp dl, '/' ;if the character is slash jump to bdiv
    je bdiv
    cmp dl, '*' ;if the character is asterisk jump to bmult
    je bmult
    cmp dl, '^' ;if the character is exponent operator jump to bxor
    je bxor
    cmp dl, '|' ;if the character is vertical bar jump to bor
    je bor
    cmp dl, '&' ;if the character is ampersand jump to band
    je band
    mov check,1
    cmp dl, 96d ;if the character's ascii code is bigger than 96 then it is a lowercase letter
    jg lowercase
    cmp dl, 64d ;if the character's ascii code is bigger than 64 then it is a uppercase letter
    jg letter
    jmp bdec ;else the character is a digit


badd: ;pops 2 number from stack adds them and pushes it back
    pop bx
    pop ax
    add ax, bx
    push ax
    jmp input
bdiv: ;pops 2 number from stack divides the first one to the second one and pushes the quotient back
    pop bx
    pop ax
    mov dx, 0
    div bx
    push ax
    jmp input
bmult: ;pops 2 number from stack multpilies them and pushes the result back
    pop bx
    pop ax
    mul bx
    push ax
    jmp input
bxor: ;pops 2 number from stack does the bitwise xor operation and pushes the result back
    pop bx
    pop ax
    xor ax, bx
    push ax
    jmp input
bor: ;pops 2 number from stack does the bitwise or operation and pushes the result back
    pop bx
    pop ax
    or ax, bx
    push ax
    jmp input
band: ;pops 2 number from stack does the bitwise and operation and pushes the result back
    pop bx
    pop ax
    and ax, bx
    push ax
    jmp input
convert_hexadecimal:
    mov dx, 0
    mov cx, 10h
    div cx ;takes the right most digit of the number by dividing it to 16
    cmp dx, 10 ;if the digit is bigger or equal to 10 it will be converted to letters
    jl adddec
    jmp addlet
adddec: ;converts the digit to character again and stores it in the memory
    add dx, 48d
    mov [bx], dl
    dec bx
    cmp ax, 00 ;if the number is 0 stops converting
    jnz convert_hexadecimal
    jmp printnl
addlet: ;converts the letter to character again and stores it in the memory
    add dx, 55d
    mov [bx], dl
    dec bx
    cmp ax, 00 ;if the number is 0 stops converting
    jnz convert_hexadecimal
printnl: ;prints a new line
    mov ah, 02h ; print a character
    mov dl, 0Dh ; move the cursor to start of the current row
    int 21h 
    mov dl, 0Ah ; move the cursor to the next line without changing the column, no need to change ah, it is already 02h.
    int 21h
    mov cx, offset number ;stores the first in the number array
    

print: ;prints 0's until cx equals to dx, since cx starts from first index of the number array and dx shows the start index of the number in number array 
    mov dx,bx
    inc dx ; we decreased one time excessively    
    cmp cx, dx ;if there is leading zeros jumps to printloop
    jne printloop
    mov ah, 09
    int 21h ;prints the output string
    jmp exit
printloop: ;prints leading zeros
   mov ah, 02
   mov dl, '0'
   int 21h
   inc cx
   jmp print
exit:
    mov ah, 04ch
    mov al, 00
    int 21h

