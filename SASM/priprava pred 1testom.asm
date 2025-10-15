%include "rw32-2018.inc"

section .data
    pole_1 dw 1,2,3,-420,5,6,
    pole_2 dd 1,2,3,0,5,6
    
    a db 2
    b db 3
    c dw 6
    d dd 3
    x dd 0

section .text
_main:
    push ebp
    mov ebp, esp
    
    xor eax,eax
    xor edx,edx
    
    mov al,[a]
    add al,[b]
    cbw
    imul ax,[c]
    sub ax,42
    cwde
    cdq
    idiv dword [d]
    
    mov ax, [pole_1 +2*3]
    add ax, [pole_2 + 4*5]
    cwde
    mov [pole_2 + 4*3], eax

    xor ebx,ebx
    xor eax,eax
    
    mov ax, 9
    and ax,1
    add bx,ax
    
    mov ax, 9
    shr ax,1
    and ax,1
    add bx,ax
    
    mov ax, 9
    shr ax,2
    and ax,1
    add bx,ax
     
    mov ax, 9
    shr ax,3
    and ax,1
    add bx,ax
    
    
    pop ebp
    ret