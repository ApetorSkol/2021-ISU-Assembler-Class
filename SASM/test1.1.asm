%include "rw32-2018.inc"

;--- Task 2 ---
;
; Create a function "task12" to evaluate the following expression using SIGNED integer arithmetic:
;
; q = (a*b + c - 32)/(7*d + e - 122) ... division quotient
; r = (a*b + c - 32)%(7*d + e - 122) ... division remainder 
;
; The arguments a, b, c, d and e are stored in the memory and are defined as follows:
;
;    [a] ...  8bit signed integer
;    [b] ... 32bit signed integer
;    [c] ... 16bit signed integer
;    [d] ... 16bit signed integer
;    [e] ... 16bit signed integer
;
; Store the result to the memory at the addresses q and r this way:
;
;    [q] ... lower 32 bits of the division quotient (32bit signed integer)
;    [r] ... division remainder (32bit signed integer)
;
; Important notes:
;  - do NOT take into account division by zero 
;  - the function does not have to preserve the original content of the registers
section .data
    a db -127
    b dd -2147483647
    c dw -32767
    d dw -32767
    e dw -32767
    
    q dd 12
    r dd 12

section .text
_main:
    push ebp
    mov ebp,esp
    
    
    
    mov al,[a]
    movsx eax,al

    imul dword[b]
        
    mov cx,[c]
    movsx ecx,cx
    sub ecx,32
    add eax,ecx
    
    
    
    mov ecx,eax
    mov ebx,edx
    
    xor eax,eax
    mov ax,[d]
    mov dx, 7
    imul dx
    sal edx,16
    add eax,edx
    sub eax,122
    mov dx,[e]
    movsx edx,dx
    add eax,edx
    
    

    xchg eax,ecx
    mov edx,ebx
    
    
    ;pri prida
    idiv ecx

            
    mov [q], eax
    mov [r], edx
    

    

    pop ebp
    ret