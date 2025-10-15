%include "rw32-2020.inc"
CEXTERN malloc
section .data
    arr1 dw -5,1,0,10,-4,8,7
    arr1_len dd 7
    pArr2 dd 0

section .text

; int filter(const short* pA, short** ppB, int N) {
;   if (pA == NULL || ppB == NULL || N < 0) return -1;
;   short *pNewArray = (short*)malloc(N*sizoef(short));
;   if (pNewArray == NULL) return -1;
;   *ppB = pNewArray;
;   for(int i = 0, j = 0; i < N; i++)
;     if (pA[i] >= 0 && even(pA[i])) 
;       pNewArray[j++] = pA[i]
;   return j;
; }
filter:
    enter 0,0
    push ebx
    push ecx
    push esi
    push edi

;   short *pNewArray = (short*)malloc(N*sizoef(short));
    mov ecx,[ebp+16]    
    shl ecx,1
    push ecx
    call malloc 
    add esp,4
    mov edi,eax         ; EDI ~ pNewArray
;   *ppB = pNewArray;
    mov esi,[ebp+12]
    mov [esi],eax    
    
    mov ecx,[ebp+16]    ; ECX ~ N - i
    mov esi,[ebp+8]     ; ESI ~ pA[i]
    xor ebx,ebx         ; EBX ~ j
;   for(int i = 0, j = 0; i < N; i++)    
    cld
.next:
;    lodsw
    mov ax,[esi]
    add esi,2
;     if (pA[i] >= 0 && even(pA[i]))     
    cmp ax,0
    jl .skip
    test ax,1
    jnz .skip
;       pNewArray[j++] = pA[i]    
;    stosw
    mov [edi],ax
    add edi,2
    inc ebx
.skip:    
    loop .next
    
    mov eax,ebx

    pop edi
    pop esi    
    pop ecx
    pop ebx

    leave
    ret

CMAIN:
    push ebp
    mov ebp, esp
    
    mov ecx,[arr1_len]
;    xor ecx,ecx
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

    xor eax,eax
    pop ebp
    ret