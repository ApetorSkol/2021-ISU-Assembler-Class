%include "rw32-2018.inc"

; Naprogramujte funkci "task11", který zamìní poøadí slabik (bytù) X1, X2, X3, X4 v registru EAX takto:
;
; pùvodní hodnota:  EAX = X4 X3 X2 X1
; výsledná hodnota: EAX = X3 X1 X4 X2 
;
; Funkci je hodnota pøedána v resgistru EAX a výsledek vrací také v registru EAX. Nejnižší významová
; slabika (byte) je X1, nejvyšší významová slabika (byte) je X4.
;
; Vstup:
;    - EAX = 32bitová hodnota
;
; Výstup:
;    - EAX = výsledek
;    - funkce nemusí zachovat obsah registrù
;
section .data

	; moje data
 
section .text
 
CMAIN:
        push ebp
        mov ebp,esp
        
        task11:
        
        ; zde zadejte kód funkce task11
        ret
 
        pop ebp	
	ret