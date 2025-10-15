%include "rw32-2020.inc"

section .data
    a dd 1,2,3,5,6,2

section .text
_main:
    push ebp
    mov ebp, esp
   
    
    push __float32__(1.0)

    
    push __float32__(2.0)
    
    fld dword [esp + 4 ]
    push __float32__(4.250)
    fld dword[esp]
    fadd 
    fsqrt
    
    fld dword [esp + 4]
    fldpi
    fmul 
    
    fsubr dword [esp + 8]
    
    fsin
    
    fmul
    
    
    push __float32__(4.0)
    
    fld dword [esp+8]
    fld dword [esp]
    
    fmul
    
    fsubr dword [esp + 12]
    
    fabs
    
    fdiv
    
    pop eax
    pop eax
    
    
    add esp,8

    pop ebp
    ret
    