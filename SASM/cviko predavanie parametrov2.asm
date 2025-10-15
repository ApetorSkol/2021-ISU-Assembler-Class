%include "rw32-2018.inc"

section .data
    sNum db "1450",0

section .text

; int print_number(char* s_number)
print_number:
    enter 0,0
    
    ; int atoi (const char * str)
    CEXTERN atoi
    push dword[ebp+8]
    call atoi
    add esp,4
    
    call WriteInt32
    call WriteNewLine
    
    leave
    ret
_main:
    push ebp
    mov ebp, esp
    
    
    push sNum
    call print_number
    add esp, 4
    pop ebp
    ret