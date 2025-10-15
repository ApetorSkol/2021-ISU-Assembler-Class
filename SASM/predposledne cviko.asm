%include "rw32-2020.inc"

section .data
    a dd 1.5
    b dq 5.7

section .text
_main:
    push ebp
    mov ebp, esp
    
    sub esp,16
    
    ;finit
    fld dword [a]
    fld qword [b]
    fld st1
    
    ; ulozi desatinne cislo na zasobnik
    push __float32__(1000.75)
    fld dword [esp]
    add esp, 4
    
    ; do st3 da st0. necykli zasobnik
    fst st3
    
    ;prida do st1=st1+st0
    fadd st1,st0
    
    ; st1= st1-st0
    fsub st1,st0
    
    pop ebp
    ret