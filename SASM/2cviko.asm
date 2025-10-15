%include "rw32-2018.inc"

section .data
    ; zde budou vase data
    a db -100
    b dw 257
    c dd 1000000
    v dd 0
section .text
_main:
    push ebp
    mov ebp, esp
    
    ; add = je funkcia ktora prida do registru/pamati hodnotu
    ; sub = -------||------- odobere od ----------||---------
    ; CF-carry flag - nastavi sa pre preteceni
    mov al,1
    add al,255
    mov al,[a]
    adc al,100 ;prida do al 100 a hodnotu carry flag
    ;mul s8 ;nasobenie. vysledok sa vzdy ulozi do ax=s8*AL
    ;mul s16 
         ; vysledok sa ulozi do DX a AX
         ; DX:AX = s16*AX
         ; v DX je horna cast hodnoty
         ; v AX je dolna cast hodnoty
    ;mul s32 ; EDX:EAX = s32*EAX  
    ;imul ;nasobenie so znamienkom
    mov ax,32768
    mov dx,2
    mul dx
    ;div s8  ;delenie AL= AX/s8 AH= AX % s8
    ;idiv src ;delenie so znamienkom
    

    
    pop ebp
    ret