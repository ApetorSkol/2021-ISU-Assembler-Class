%include "rw32-2018.inc"

section .data
    ; zde budou vase data
    a db -50
    b dw 100 
    c dd -10000
    v dd 0
section .text
_main:
    mov ebp, esp
    push ebp
    mov ebp, esp
    
    mov al,[b]
    movsx eax,al
    imul dword[c]
    mov bl,[a]
    movsx ebx,bl
    add eax,ebx
    sub eax,10
    add ebx,100000
    
    cwd
    idiv ebx
    
    mov[v],eax
    
    pop ebp
    ret