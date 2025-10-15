%include "rw32-2018.inc"

section .data
    ; segment == section
    ; zde budou vase data
    ; tu sa nachadzaju inicializovane data
    a db 6
    ; inicializoval som premennu 'a' s velkostou byte(db) a hodnotou 6
    ; assembeler vnima vsetky premenne ako pointre
    ptr_a db 6,4,5,5
    ; ptr_a ukazuje na 6
    ; dalej su za sestkou zapisane 4.5.5
    db 45,34,56,6
    db 43
    db -5
    ; tieto premenne su zapisane v pamati po ptr_a
    
    b db 'a','b','c','d'
    c db "abcdef"
    arr1 dd 1,2,3,4,10
    sum dd 0
section .text ; do section sa pise kod
_main:
mov ebp, esp
    push ebp
    mov ebp, esp ; mov d = s
    
    mov al,[ptr_a]
    mov al,[ptr_a + 1*1]
    ; tymto sa mozem pohybovat v poli
    ; 1*1 je i*size teda index krat velkost o ktoru sa mame posuvat
    
    mov al,[b]
    mov ecx,[c]
    
    mov eax,0
    add eax,[arr1 + 0*4]
    add eax,[arr1 + 1*4]
    add eax,[arr1 + 2*4]
    add eax,[arr1 + 3*4]
    add eax,[arr1 + 4*4]
    mov [sum],eax
    
    pop ebp
    ret