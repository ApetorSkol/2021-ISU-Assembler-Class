%include "rw32-2018.inc"

section .data
    ; zde budou vase data
    x dd -3
section .text
; int sum4_pascal(int a, char b, short c, int *pd)
; {return a+b+c+*pd }
; 8pd je pointer

; pd...ebp+8
; c....ebp+12
; b....ebp+16
; a ...ebp+20
sum4_pascal:
    enter 0,0
    ; push ebp
    ; mov ebp,esp
    ; sub esp,0
    mov edi,[ebp+20]
    ;+a
    movsx eax, byte [ebp+16]
    add edi,eax
    ;+a+b
    movsx eax,word [ebp+12]
    add edi,eax
    ;+a+b+c
    mov eax,[ebp+8]
    add edi,[eax]
    
    mov eax,edi
    
    leave
    ; mov esp,ebp
    ; pop ebp
    ret 16
_main:
    push ebp
    mov ebp, esp
    
    ; int x = -3
    ; WriteInt332(sum4_pascal(20, -6, -1, &x))
    push 20
    push -6
    push -1
    push x
    call sum4_pascal
    
    pop ebp
    ret