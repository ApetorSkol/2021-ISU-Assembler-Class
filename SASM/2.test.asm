%include "rw32-2020.inc"

section .data
    ; zde budou vase data

;
;--- Úkol 2 ---
;
; Naprogramujte funkci: int task22(const int *pA, int N), která v poli 32bitových èísel se znaménkem pA 
; nalezne minimum a vrátí jeho hodnotu v registru EAX. Délka pole je dána parametrem N.
; Funkce dostává parametry, uklízí zásobník a vrací výsledek podle konvence CDECL.
;
; Parametry funkce:
;   pA: ukazatel na zaèátek pole 32bitových prvkù se znaménkem
;    N: poèet prvkù pole pA (32bitové èíslo se znaménkem)
;
; Návratová hodnota:
;   EAX = 0x80000000, když je pA neplatný ukazatel (pA == 0) nebo N <= 0
;   EAX = hodnota 32bitového minima se znaménkem.
;
; Dùležité:
;   Funkce musí zachovat obsah všech registrù, kromì registru EAX a pøíznakového registru.
;

pA dd 1,2,3,4,0
N dd 5
section .text
_main:
    push ebp

    push dword [N]
    push pA


    call task22

    add esp,8

    pop ebp
    ret
task22:
    
    push ebp
    mov ebp, esp

    push ecx
    push esi

    mov esi, [ebp + 8] 
    mov ecx, [ebp + 12] 

    cmp ecx, 0
    jle error
    cmp esi, 0
    je error

    mov eax, [esi]
    for:
        dec ecx
        cmp eax, [esi+ecx*4]
        jl forend
        mov eax, [esi+ecx*4]
    forend:
        cmp ecx, 0
        je end
        jmp for
 
error:
    mov eax, 0x80000000 
end:

    pop esi
    pop ecx

    pop ebp
    ret 8
