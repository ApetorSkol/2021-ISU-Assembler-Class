%include "rw32-2018.inc"

section .data
    ; zde budou vase data

section .text

;int sum(int a, int b , int c) (return a+b+c;)
;eax = a
;ebx = b
;ecx = c
;edx = d

sum:
    mov eax,[esp + 4]
    add eax,[esp + 8]
    add eax,[esp + 12]
    add eax,[esp + 16]
    ret


_main:
    mov ebp , esp
    push ebp
    mov ebp, esp
    ; predavanie parametrov pre funkciu
    
    push dword 1
    push dword 2
    push dword 3
    push dword 4
    call sum

    call WriteInt32
    
    pop ebx
    pop ebx
    pop ebx
    pop ebx
    
    pop ebp
    ret