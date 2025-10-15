%include "rw32-2018.inc"

section .data
    str1 db "Ahoj svete! 123a4b5c6",0
section .text
; void toupper (char *pStr){
; for (int i = 0; i < strlne(pStr); i++)
; if (pStr[i] >= 'a' && pStr[i] <= 'z') pStr[i]-=32
;}
toupper:
    enter 0,0

    mov esi,[ebp+8]
    push esi
    call strlen
    add esp,4
    mov ecx,eax
    
.loop:
    mov al,[esi + ecx*1 - 1]
    cmp al,'a'
    jb .skip
    cmp al,'z'
    ja .skip
    sub al,32
    mov [esi + ecx*1 - 1],al
.skip:
    loop .loop
    
    leave
    ret
_main:
    push ebp
    mov ebp, esp
    
    mov esi,str1
    call WriteString
    call WriteNewLine
    
    push str1
    call toupper
    add esp,4

    mov esi,str1
    call WriteString
    call WriteNewLine

    pop ebp
    ret