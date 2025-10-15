%include "rw32-2020.inc"
CEXTERN malloc
section .data
    arr1 dw -5,1,0,10,-4,8,7
    arr1_len dd 7
    pArr2 dd 0

section .text
; int filter(const short* pA, short** ppB, int N)
;   short *pNewArray = (short*)malloc(N*sizeof(short));
;   for (int i = 0, j = 0; i <N; i++)
;       if (pA[i] >= 0 && even(pA[i])) pNewArray[j++] = pA[i]
;   *ppB = pNewArray
;   return j

filter:
    enter 0,0
    
    mov ecx,[ebp+16] ;ulozim si do ecx dlzku
    shl ecx,1
    push ecx
    call malloc
    add esp,4
    mov edi,eax
    mov esi,[ebp+12]
    mov [esi],eax
    
    mov ecx,[ebp+16]
    mov esi,[ebp+8]
    xor ebx,ebx
.next:
    lodsw
    ; mov ax,[esi]  toto je lodsw
    ; add esi,2     aj toto
    cmp ax,0 ;porovnavam s nulou
    jl .skip
    test ax,1
    jnz .skip ;sudost
    stosw
    inc ebx
.skip:
    loop .next
    
    mov eax,ebx
    
    leave
    ret
_main:
    push ebp
    mov ebp, esp
    
    mov ecx,[arr1_len]
    mov esi,arr1
    call WriteArrayInt16
    call WriteNewLine
    
    push dword [arr1_len]
    push pArr2
    push arr1
    call filter
    add esp,12
    
    mov ecx,eax
    mov esi,[pArr2]
    call WriteArrayInt16
    call WriteNewLine
    
    pop ebp
    ret