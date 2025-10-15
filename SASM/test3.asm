%include "rw32-2020.inc"

section .data
    a dd 1,2,3,5,6,2

section .text
_main:
    push ebp
    mov ebp, esp
   
    
    push __float32__(0.0)

    
    push __float32__(0.0)
    
    fld dword [esp + 4 ]
    push __float32__(8.450)
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
    
    push __float32__(0.0)
    fld dword [esp]
    fcomp st0
    je delenie_nulou
    pop eax
    
    fdiv
    
    pop eax
    pop eax
    
    
    pop eax
    pop eax

    pop ebp
    ret
    
delenie_nulou:
    push 0xffffffff
    
    fld dword [esp]
    
    pop eax
    ret