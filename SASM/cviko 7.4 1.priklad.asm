%include "rw32-2018.inc"

section .data
    str1 db "Ahoj svete! 123a4b5c6",0
section .text
; char * toupper (const char *pStr){
;   char *pNewStr = (char*)malloc(strlen(strlen(pStr)+1))
;   for (int i = 0; i <= strlne(pStr); i++)
;     if (pStr[i] >= 'a' && pStr[i] <= 'z') 
;       pStr[i]-=32
;     else
;       pNewStr[i] = pStr[i]
;   return pNewStr
;}
toupper:
    enter 0,0

    mov esi,[ebp+8] 
    push esi
    call strlen
    add esp,4
    mov ecx,eax
    ;do ecx sa ulozila dlzka retazca
    
    push ecx
    CEXTERN malloc
    call malloc
    add esp,4
    mov ecx,eax
    
    inc ecx
    push ecx
    call malloc
    pop ecx
    mov edi,eax
.loop:
    lodsb
    cmp al,'a'
    jb .skip
    cmp al,'z'
    ja .skip
    sub al,32
.skip:
    stosb 
    loop .loop
    
    pop eax
    pop ecx
    pop esi
    
    
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