%include "rw32-2020.inc"

section .data
    ; zde budou vase data

section .text
_main:
    CEXTERN qsort
    enter 0, 0
    
    pushad
    
    cmp esi,0
    je .zero
    cmp ecx,0
    jle .zero
    
    pop ebx
    leave
    popad
    ret
.zero:
    
    ret