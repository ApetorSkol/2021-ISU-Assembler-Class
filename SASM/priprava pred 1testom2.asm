%include "rw32-2018.inc"

section .data
    a db 250
    b db 200

section .text
_main:
    push ebp
    mov ebp, esp
    
    mov al,[a]
    mul al
    mov bx,ax
    mov al,[b]
    cbw 
    add bx,[b]
    mov ax,bx
    mul ax
    call WriteInt8
    
    sal edx,16
    mov dx,ax
    mov edx,eax

    pop ebp
    ret