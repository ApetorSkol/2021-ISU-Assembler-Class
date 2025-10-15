%include "rw32-2018.inc"

section .data
    s1 db "ahoj",0
    s2 db "-----------",0

section .text
;cdecl int cpy(cahr* s1, char *s2)
;   (s1==null || s2 == null) return -1
;   strcpy(s1,s2)
cpy:
    enter 0,0
    
    mov eax,-1
    mov esi,[ebp+8]
    test esi,esi
    jz chyba
    push edi
    push esi
    
    CEXTERN strcpy
    call strcpy
    add esp,8
    xor eax,eax
    leave
    ret
    
    
chyba:
    mov eax,-1
    call WriteInt32
    leave
    ret
_main:
    ;char * strcpy( char* destination, const char * source); )
    push ebp
    mov ebp, esp
    
    push s2
    push s1
    call cpy
    add esp,8
    call WriteInt32
    call WriteNewLine
    

    pop ebp
    ret