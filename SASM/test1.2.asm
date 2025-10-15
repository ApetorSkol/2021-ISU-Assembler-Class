%include "rw32-2018.inc"

section .data
    ; zde budou vase data

section .text
;
;--- Task 1 ---
;
; Create a function "task11" to swap bytes X1, X2, X3, X4 within the register EAX this way:
;
; original value: EAX = X4 X3 X2 X1
; result        : EAX = X1 X3 X2 X4 
;
; The argument to the function is passed in the register EAX and it returns the result 
; in the register EAX. The least significant byte is X1, the most significant byte is X4.
;
; Arguments:
;    - EAX = 32bit value
;
; Result:
;    - EAX = result
;    - the function does not have to preserve content of any register
task11:
    
    rol eax,8
    ror ax,8
    ror eax,8    

    pop ebp
    ret