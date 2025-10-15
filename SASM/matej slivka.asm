%include "rw32-2018.inc"

section .data
    ; zde budou vase data

section .text
_main:
    mov ebp, esp
    push ebp
    mov ebp, esp
    
    mov eax,0xFE_56_11_47
    or eax,1000000010000001
    and eax,01111111111111110111111101111111
    mov ebx, eax
    ;1001
    shl ebx,3
    add eax,ebx
    shr eax,4
    ror ax,8
    ror eax,16
    ror ax,8
    rol eax,8 
    


    pop ebp
    ret