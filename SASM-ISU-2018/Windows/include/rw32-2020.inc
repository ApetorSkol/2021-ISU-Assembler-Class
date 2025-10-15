; Verze: 2020.05.01
; Autor: Filip Orsag (orsag@fit.vutbr.cz)
;
; Podpurna knihovna funkci "rw32-20XX.inc" pro predmet ISU.
; Pro svou cinnost vyuziva standardni knihovny jazyka C.
; Lze ji pouzit v OS Windows nebo Linux.
;
; Knihovnu vkladejte na zacatek vaseho programu: 
;
;	%include "rw32-20XX.inc"
;
; Preklad Windows:
;	nasm -f win32 -g -o helloworld.obj helloworld.asm
;	golink helloworld.obj /fo helloworld.exe /console /debug coff /entry:_main msvcrt.dll kernel32.dll
;
; Preklad Linux:
;	nasm -f elf32 -g -o helloworld.o helloworld.asm
;	gcc -m32 -o helloworld helloworld.o
;
;
; Dostupne funkce jsou nasledujici:
;
; Cteni z klavesnice:
;   (verze '_Silent' nevypisuji nic na obrazovku a v pripade chybne zadaneho cisla tuto skutecnost ignoruji)
;
;	ReadChar/ReadChar_Silent
;		Vstup:	nic.
;		Vystup:	AL = hodnota znaku.
;		Chovani: ceka na zadani znaku a na stisk klavesy ENTER (lze zadat i vice znaku, ale ty budou ignorovany, platny je pouze prvni znak).

;	ReadString/ReadString_Silent
;		Vstup:	EBX = maximalni pocet znaku, ktere mohou byt nacteny.
;				EDI = adresa, kam se retezec nacte (musi byt rezervovano alespon EBX+1 bytu).
;		Vystup:	EAX = pocet prectenych znaku
;				retezec znaku ulozeny na adrese EDI.
;		Chovani: nacita znaky z klavesnice, dokud neni stisknuta klavesa ENTER. Na adresu v EDI ulozi maximalne EBX znaku
;				 nebo mene (vsechny dalsi znaky budou ignorovany), skutecny pocet znaku vraci v registru EAX.

;	ReadInt8/ReadInt8_Silent
;		Vstup:	nic.
;		Vystup:	AL = cislo z intervalu <-128, 127>.
;		Chovani: cte cislo z klvesnice, umozni zadat jakykoliv znak, ale pouze znak '-','+' a cislice budou akceptovany,
;				 pokud neni zadana zadny znak a je stisknut ENTER, pak je vracena hodnota 0, pri prekroceni kterekoliv povolene
;				 meze je vraceno bud maximum nebo minimum daneho rozsahu.

;	ReadInt16/ReadInt16_Silent
;		Vstup:	nic.
;		Vystup:	AX = cislo z intervalu <-32768, 32767>.
;		Chovani: viz ReadInt8.

;	ReadInt32/ReadInt32_Silent
;		Vstup:	nic.
;		Vystup:	EAX = cislo z intervalu <-2^31, 2^31 - 1>.
;		Chovani: viz ReadInt8.

;	ReadUInt8/ReadUInt8_Silent
;		Vstup:	nic.
;		Vystup:	AL = cislo z intervalu <0, 255>.
;		Chovani: viz ReadInt8 s tim rozdilem, ze pri zadani znaku '-' bude cislo v doplnkovem kodu, ale interpretovano jako cislo bez znamenka.

;	ReadUInt16/ReadUInt16_Silent
;		Vstup:	nic.
;		Vystup:	AX = cislo z intervalu <0, 65535>.
;		Chovani: viz ReadUInt8.

;	ReadUInt32/ReadUInt32_Silent
;		Vstup:	nic.
;		Vystup:	EAX = cislo z intervalu <0, 2^32 - 1>.
;		Chovani: viz ReadUInt8.

;	ReadFloat/ReadFloat_Silent
;		Vstup:	nic.
;		Vystup:	EAX = 32bitove realne cislo v plovouci radove carce (v jazyce C typ float).
;		Chovani: viz ReadInt8, navic je dovoleno zadat znak '.' (desetinna carka) a exponent (e+N nebo e-N).

;	ReadDouble/ReadDouble_Silent
;		Vstup:	nic.
;		Vystup:	ST0 = 64bitove realne cislo v plovouci radove carce (v jazyce C typ double).
;		Chovani: viz ReadFloat.

; Vypis na obrazovku:
;	WriteChar
;		Vstup:	znak v AL.
;		Vystup:	vypise znak na obrazovku.

;	WriteNewLine
;		Vstup:	nic.
;		Vystup:	vypise konec radku ("\n").

;	WriteString
;		Vstup:	ESI = ukazatel na retezec zakonceny hodnotou 0, ktery bude vypsan.
;		Vystup:	vypise retezec na obrazovku.

;	WriteBin8
;		Vstup:	AL = cislo.
;		Vystup:	vypise cislo z AL na obrazovku v binarni podobe.

;	WriteBin16
;		Vstup:	AX = cislo
;		Vystup:	vypise cislo z AX na obrazovku v binarni podobe.

;	WriteBin32
;		Vstup:	EAX = cislo.
;		Vystup:	vypise cislo z EAX na obrazovku v binarni podobe.

;	WriteHex8
;		Vstup:	AL = cislo.
;		Vystup:	vypise cislo z AL na obrazovku v hexadecimalni podobe "0xXX".

;	WriteHex16
;		Vstup:	AX = cislo
;		Vystup:	vypise cislo z AX na obrazovku v hexadecimalni podobe "0xXXXX".

;	WriteHex32
;		Vstup:	EAX = cislo.
;		Vystup:	vypise cislo z EAX na obrazovku v hexadecimalni podobe "0xXXXXXXXX".

;	WriteInt8
;		Vstup:	AL = cislo.
;		Vystup:	vypise cislo z AL na obrazovku v dekadicke forme se znamenkem.

;	WriteInt16
;		Vstup:	AX = cislo.
;		Vystup:	vypise cislo z AX na obrazovku v dekadicke forme se znamenkem.

;	WriteInt32
;		Vstup:	EAX = cislo.
;		Vystup:	vypise cislo z EAX na obrazovku v dekadicke forme se znamenkem.

;	WriteUInt8
;		Vstup:	AL = cislo.
;		Vystup:	vypise cislo z AL na obrazovku v dekadicke forme bez znamenka.

;	WriteUInt16
;		Vstup:	AX = cislo.
;		Vystup:	vypise cislo z AX na obrazovku v dekadicke forme bez znamenka.

;	WriteUInt32
;		Vstup:	EAX = cislo.
;		Vystup:	vypise cislo z EAX na obrazovku v dekadicke forme bez znamenka.

;	WriteFlags
;		Vstup:	nic (aktualni stav priznakoveho registru).
;		Vystup:	vypise obsah registru priznaku EFLAGS na obrazovku.

;	WriteFloat
;		Vstup:	EAX = cislo (realne cislo s jednoduchou presnosti - float).
;		Vystup:	vypise cislo z EAX na obrazovku ve forme realneho cisla.

;	WriteDouble
;		Vstup:	ST0 = cislo (realne cislo v koprocesoru, vypisuje se cislo s dvojitou presnosti - double).
;		Vystup:	vypise cislo z ST0 na obrazovku ve forme realneho cisla.
;

;	WriteAllGPRegisters32
; 		Vstup: nic (aktualni stav jednotlivych registru)
;		Vystup: vypise obsah registru EAX, EBX, ECX, EDX, ESI, EDI, EBP, ESP
;

;	WriteTestGPRegisters32
; 		Vstup: nic (aktualni stav jednotlivych registru)
;		Vystup: vypise obsah registru EBX, ECX, EDX, ESI, EDI, EBP
;

;	WriteArrayInt8
; 		Vstup: ESI = ukazatel na pole 8bitovych cisel, 
;			   ECX = pocet prvku pole
;		Vystup: vypise pole 8bitovych cisel se znamenkem
;

;	WriteArrayInt16
; 		Vstup: ESI = ukazatel na pole 16bitovych cisel,
;			   ECX = pocet prvku pole
;		Vystup: vypise pole 16bitovych cisel se znamenkem
;

;	WriteArrayInt32
; 		Vstup: ESI = ukazatel na pole 32bitovych cisel,
;			   ECX = pocet prvku pole
;		Vystup: vypise pole 32bitovych cisel se znamenkem
;

;	WriteArrayUInt8
; 		Vstup: ESI = ukazatel na pole 8bitovych cisel, 
;			   ECX = pocet prvku pole
;		Vystup: vypise pole 8bitovych cisel bez znamenka
;

;	WriteArrayUInt16
; 		Vstup: ESI = ukazatel na pole 16bitovych cisel,
;			   ECX = pocet prvku pole
;		Vystup: vypise pole 16bitovych cisel bez znamenka
;

;	WriteArrayUInt32
; 		Vstup: ESI = ukazatel na pole 32bitovych cisel,
;			   ECX = pocet prvku pole
;		Vystup: vypise pole 32bitovych cisel bez znamenka
;

bits 32

%macro STRING 2+.nolist
    %1: DB %2
	endof.%1: DB 0
	lenof.%1 EQU endof.%1 - %1
	sizeof.%1 EQU endof.%1 - %1
%endmacro

%macro INVOKE 1.nolist
	call %1
%endmacro

CLIB EQU 1
NO_CLIB EQU 0

%macro CALL_CDECL 1-*
	%assign incStack 0
	%if %0 > 1
		%assign i 0		
		%rep %0-1
			%assign i i+1
			%rotate -1
			%ifstr %1
				section .data
					%%str %+ i: db %1, 0
				section .text
					push %%str %+ i
			%else
				push dword %1
			%endif
			%assign incStack incStack+4
		%endrep
		%rotate -1
	%endif
	call %1
	%if incStack > 0
		add esp,incStack
	%endif
%endmacro

%macro CALL_CLIB 1+
	push ecx
	push edx
	CALL_CDECL %1
	pop edx
	pop ecx
%endmacro

%macro PRINTF 1+
	push ecx
	push edx
	CALL_CDECL printf,%1
	push 0
	call fflush
	add esp,4
	pop edx
	pop ecx
%endmacro

%macro CALL_PASCAL 1-*.nolist
    %if %0 > 1
        %rep %0-1
            %rotate 1
            push dword %1
        %endrep
        %rotate 1
    %endif
    call %1
%endmacro

%macro CALL_STD 1-*.nolist
    %if %0 > 1
        %rep %0-1
            %rotate -1
            push dword %1
        %endrep
    %rotate -1
    %endif
    call %1
%endmacro

%define PAR_CDECL(i,N) EBP + 4 + i*4
%define PAR_STD(i,N) EBP + 4 + i*4
%define PAR_PASCAL(i,N) EBP + 4 + N*4 - (i - 1)*4

%define RET_CDECL(N) RET
%define RET_STD(N) RET N*4
%define RET_PASCAL(N) RET N*4

;%macro PRINTF 1-*.nolist
	;push ecx
	;push edx
	;CALL_CDECL %1
	;push 0
	;call fflush
	;add esp,4
	;pop edx
	;pop ecx
;%endmacro

%imacro MOVSTR 2+
	section .data
		%%str: db %2, 0
	section .text			
		mov %1,%%str
%endmacro

%macro FN_BEGIN_PUSHA 1-2 0
    %1:
        enter %2,0
        pushfd
        pushad
%endmacro

%define RET_EAX 1

%macro FN_END_POPA 0-1 0
	%if %1 = RET_EAX
		mov [tmpEAX],eax
	%endif
        popad
	%if %1 = RET_EAX
		mov eax,[tmpEAX]
	%endif		
        popfd
        leave
        ret
%endmacro

; Funkce standardni knihovny jazyka C (C Run-Time libraray)

%ifidn __OUTPUT_FORMAT__, win32
	%macro CEXTERN 1.nolist
		%ifndef CEXTERN_%1  
			extern _%1
			%xdefine CEXTERN_%1
			%xdefine %1 _%1			
		%endif
	%endmacro

    CEXTERN __iob_func
    
	%define stdin dword [rw_stdin]

    %macro INIT_STDIN 0
        cmp dword [rw_stdin],-1
        jnz %%stdinOK
		push eax
		CALL_CLIB __iob_func,0
        mov [rw_stdin],eax
        pop eax
    %%stdinOK:
        ;push dword [rw_stdin]          
    %endmacro

    ;nase vstupni funkce se bude jmenovat _main
    %define CMAIN _main
 
    %macro SIG_HANDLER 3
        %1:
            cmp dword [silent_exception],1
            jz %%exit
            mov esi,%3
            call WriteString
        %%exit:
			SIGNAL(%2, %1)
            mov eax,%2
			fnclex
            jmp dword far [recovery_dest]            
    %endmacro
    
    %macro SIG_HANDLERw 3
        %1:
            cmp dword [silent_exception],1
            jz %%checkRecovery
            mov esi,%3
            call WriteString    
        %%checkRecovery:
            cmp dword [recovery_initialised],1
            jnz %%exit
        	CALL_CDECL longjmp,recovery_record,%2
        %%exit:
            ret
    %endmacro

    %macro SET_EXCEPTION_CATCH 0
        mov dword [recovery_initialised],0
        xor eax,eax
        mov dword [recovery_initialised],1
;        push 0
;        push recovery_record
;        call _setjmp
;        add esp,8
    %endmacro
    
%elifidn __OUTPUT_FORMAT__, elf32

    %macro CEXTERN 1.nolist
        extern %1
    %endmacro
   
    CEXTERN stdin

    %macro INIT_STDIN 0
        ;push dword [stdin]
    %endmacro

    ;nase vstupni funkce se bude jmenovat main
    %define CMAIN main
    
    %macro SIG_HANDLER 3
        %1:
            cmp dword [silent_exception],1
            jz %%checkRecovery

            pushad
            mov esi,%3
            call WriteString
            popad
    
        %%checkRecovery:
            cmp dword [recovery_initialised],1
            jnz %%exit
			LONGJMP(recovery_record, %2)
        %%exit:
            ret
    %endmacro
    
    %macro SET_EXCEPTION_CATCH 0
        mov dword [recovery_initialised],1
        push 0
        push recovery_record
        call setjmp
        add esp,8
    %endmacro
%else
    %error "Formát -f" %+ __OUTPUT_FORMAT__ %+ " není podporován knihovnou RW32."
%endif

CEXTERN signal
%define SIGNAL(num, handler) CALL_CLIB signal, num, handler
CEXTERN longjmp
%define LONGJMP(record, num) CALL_CDECL longjmp, record, num
CEXTERN _setjmp

%define SET_SILENT_EXCEPTION(x) mov dword [silent_exception],x

%macro INIT_RECOVERY_SYSTEM 0
    ;CALL_CLIBsignal,SIGFPE,SIGFPEHandler
	SIGNAL(SIGFPE, SIGFPEHandler)
    ;CALL_CLIBsignal,SIGSEGV,SIGSEGVHandler
	SIGNAL(SIGSEGV, SIGSEGVHandler)
    CALL_CLIB printf,msg_ISU
%endmacro


%macro _E_TRY 0
	%push try_catch
	    pushad                          ;;Save Current State		
		push ebp
		push 0
		push 0
		push %$try_catch_no_exception
	    push %$try_catch_handler                        ;;Save Old Exception Handler
	    push dword [fs:0]           ;;Install New Handler
	    mov [fs:0], esp
%endmacro

%macro _E_CATCH 0
	    jmp %$try_catch_no_exception ;Handler         ;;No Exception Occured, so jump over
	%$try_catch_handler:
	    mov esp, [esp + 8]              ;;Exception Occured, Get old ESP
	    pop dword [fs:0]            ;;Restore Old Exception Handler
	    add esp, 4                      ;;ESP value before SEH was set
	    popad                           ;;Restore Old State
%endmacro

%macro _E_END 0
	    jmp %$try_catch_exception_handled    ;;Exception was handled by @TRY_EXCEPT
	%$try_catch_no_exception:                ;;No Exception Occured
	    pop dword [fs:0]            ;;Restore Old Exception Handler
	    add esp, 32 + 20                 ;;ESP value before SEH was set. 32 for pushad and ...
	%$try_catch_exception_handled:           ;;...4 for push offset Handler. (No Restore State)
	%pop
%endmacro

global CMAIN
CEXTERN printf
CEXTERN scanf
CEXTERN sscanf
CEXTERN fgets
CEXTERN feof
CEXTERN getchar
CEXTERN strlen
CEXTERN fflush

; Konstanty

%define KB_ENTER 0x0D
%define KB_NEWLINE 0x0A
%define KB_BACKSPACE 0x08
%define EOL KB_NEWLINE
%define EOF -1
%define MAX_UBYTE 0xFF
%define MAX_UWORD 0xFFFF
%define MAX_UDWORD 0xFFFFFFFF
%define MAX_SBYTE 0x0000007F
%define MAX_SWORD 0x00007FFF
%define MAX_SDWORD 0x7FFFFFFF
%define MIN_SBYTE 0xFFFFFF80
%define MIN_SWORD 0xFFFF8000
%define MIN_SDWORD 0x80000000
%define MAX_STRING_LENGTH 1024

%define SIGSEGV 11
%define SIGFPE 8

section .data align=4

    STRING msg_ISU, '[ISU] Inicializovano, spoustim ISU_MAIN...',EOL
    STRING msg_EOL, `\n`
    STRING msg_EnterChar, 'Zadejte znak: '
    STRING msg_EnterUInt, 'Zadejte cele cislo bez znamenka z intervalu <%u,%u>: '
    STRING msg_EnterSInt, 'Zadejte cele cislo se znamenkem z intervalu <%d,%d>: '
    STRING msg_EnterFloat, 'Zadejte realne cislo (napr. 1.5): '
    STRING msg_EnterText, 'Zadejte text (akceptovano bude maximalne %d znaku): '
    STRING msg_NumberTooBig, `Cislo je prilis velke, vracim maximalni moznou hodnotu.\n`
    STRING msg_NumberTooLow, `Cislo je prilis male, vracim minimalni moznou hodnotu.\n`
    STRING msg_WrongNumber, 'Zadana hodnota neni rozpoznatelne cislo. Zadejte nove CISLO: '
    STRING msg_NoRegChanges, 'REG CHECK OK'
    STRING msg_regChanges, 'REG CHECK FAILED'
    STRING s_EAX, 'EAX'
    STRING s_EBX, 'EBX'
    STRING s_ECX, 'ECX'
    STRING s_EDX, 'EDX'
    STRING s_ESI, 'ESI'                        
    STRING s_EDI, 'EDI'        
    STRING s_EBP, 'EBP'        
    STRING s_ESP, 'ESP'

    msg_Flags        db 'Flags: xxxx|OF|DF|IF|TF|SF|ZF|xx|AF|xx|PF|xx|CF|',EOL,'       xxxx| '
    msg_FlagValues   db              'x| x| x| x| x| x| x| x| x| x| x| x|',EOL
        endof_msg_Flags db 0
        lenof_msg_Flags EQU endof_msg_Flags - msg_Flags
    rw_stdin         dd -1
    number_in        dq 0.0
    tmp              dd 0
    tmpEAX           dd 0
    reg_dump_b       dd 0,0,0,0,0,0,0,0
    reg_dump         dd 0
    msg_ExceptionFPE  db 'SIGFPE: Chyba aritmetiky (x/0, sqrt(-x), ...).',EOL,0
    msg_ExceptionFPEDetailed:
                      db 'SIGFPE: Chyba aritmetiky',EOL
                      db '   * FDIV: deleni nulou',EOL
                      db '   * FSQRT: odmocnina ze zaporneho cisla',EOL
                      db '   * FCOM: porovnavani dvou registru, ale k dispozici je jen jeden nebo zadny',EOL
                      db '   * FLD: nacteni SNaN (Signaling NaN)',EOL
                      db '   * FLD: nacteni hodnoty do plneho FPU',EOL
                      db '   * ___P: pokus o vyprazdneni (Pop) prazdneho zasobniku',EOL
                      db 0
    msg_ExceptionSEGV db 'SIGSEGV: Segmentation fault (�ten�/z�pis z/do pam�ti mimo povolenou oblast).',EOL,0
    msg_ExceptionSEGVDetailed:
                      db 'SIGSEGV: Segmentation fault',EOL
                      db '   * MOV [adresa],_ : zapis na zakazanou adresu',EOL
                      db '   * MOV _,[adresa] : cteni ze zakazane adresy',EOL
                      db '   * RET N: chybna hodnota N (Patri tam vubec?)',EOL
                      db '   * PUSH/POP: spatny pocet PUSH-POP',EOL
                      db '   * ESP/EBP: spatna prace se zasobnikem',EOL
                      db 0
    recovery_initialised dd 0
    silent_exception dd 0
    recovery_dest dd 0,0
    ioBuffer times MAX_STRING_LENGTH db '!'
                     db 0

section .bss    
    recovery_record resb 1024
    
section .text

SIG_HANDLER SIGFPEHandler,SIGFPE,msg_ExceptionFPEDetailed
SIG_HANDLER SIGSEGVHandler,SIGSEGV,msg_ExceptionSEGVDetailed

%ifidn __OUTPUT_FORMAT__, win32    
    %ifndef SASM
        ; Nektere dalsi funkce Win32 API
        extern ExitProcess

        section .text

            global start
        start:
            CALL_CLIB signal, SIGFPE, SIGFPEHandler
            CALL_CLIB signal, SIGSEGV, SIGSEGVHandler
            PRINTF msg_ISU
            call CMAIN
            CALL_STD ExitProcess,0
    %endif
%endif

;----------------
; Funkce ReadString/ReadString_Silent
;
%macro READ_STRING 1-2
	FN_BEGIN_PUSHA %1,0
%if %0 > 1
	CALL_CLIB printf, %2, ebx
%endif
	mov [edi], byte 0
	test ebx,ebx
	jz .return

	INIT_STDIN	
	CALL_CLIB fgets, ioBuffer, MAX_STRING_LENGTH, stdin
	test eax,eax
	jz .return

	mov [ioBuffer + ebx], byte 0
	CALL_CLIB strlen, ioBuffer
	mov ecx,eax

	cmp [ioBuffer + ecx - 1], byte 10
	je .is_new_line
	inc ecx
.is_new_line:
	mov [ioBuffer + ecx - 1], byte 0
	mov esi,ioBuffer
	rep movsb

.return:
	FN_END_POPA RET_EAX
%endmacro

;----------------
; Funkce ReadString_Silent
;    
READ_STRING ReadString_Silent

;----------------
; Funkce ReadString
;
READ_STRING ReadString, msg_EnterText

;----------------
; Funkce ReadChar_Silent
;
FN_BEGIN_PUSHA ReadChar_Silent
	jmp ReadChar.skipMsg
;----------------
; Funkce ReadChar
;
FN_BEGIN_PUSHA ReadChar
	mov esi,msg_EnterChar
	call WriteString
.skipMsg:
	INIT_STDIN
	CALL_CLIB fgets, ioBuffer, MAX_STRING_LENGTH, stdin
	test eax,eax
	jnz .exit
	mov byte [ioBuffer],0
.exit:
	xor eax,eax
	movzx eax,byte [ioBuffer]
FN_END_POPA RET_EAX

;----------------
; Funkce ReadNumber/ReadNumber_Silent
; Cte cislo ze standardniho vstupu dle formatovaciho retezce odpovidajiciho formatu scanf.
; Ukazatel na formatovaci retezec je ulozen v registru EBX.
;
%macro READ_NUMBER 1-2
	FN_BEGIN_PUSHA %1
	INIT_STDIN
.again:
	mov [number_in], dword 0
	mov [number_in + 4], dword 0

	CALL_CLIB fgets, ioBuffer, MAX_STRING_LENGTH, stdin
	test eax,eax
	jz .checkEOF

	CALL_CLIB sscanf, ioBuffer, ebx, number_in
	test eax,eax
	jnz .ok

.checkEOF:
	CALL_CLIB feof, stdin
	test eax,eax
	jnz .ok

%if %0 > 1
	CALL_CLIB printf, "%s", %2
	jmp .again
%endif
.ok:
	mov eax, [number_in]

	FN_END_POPA RET_EAX
%endmacro

;----------------
; Funkce ReadNumber_Silent
;    
READ_NUMBER ReadNumber_Silent

;----------------
; Funkce ReadNumber
;
READ_NUMBER ReadNumber, msg_WrongNumber

%macro CREATE_READNUMBER_PROLOGUE 5-6
FN_BEGIN_PUSHA %1
	mov edi,%2
	mov ebx,%3
	%if %0 > 5	
		CALL_CLIB printf, %6, edi, ebx
		push ebx
		MOVSTR ebx,%5
		call ReadNumber
		pop ebx
		jmp %4
	%else	
		push ebx
		MOVSTR ebx,%5
		call ReadNumber_Silent
		pop ebx
		jmp %4
	%endif
%endmacro

;----------------
; Funkce ReadIntX (8,16,32) {ReadInt8,ReadInt16,ReadInt32}
; Precte 8-, 16-, 32-bitovou celociselnou hodnotu se znamenkem z klavesnice
; Chovani funkci je dano chovanim funkce SSCANF. Veskere namitky se netykaji autora.
;
CREATE_READNUMBER_PROLOGUE ReadInt8,MIN_SBYTE,MAX_SBYTE,ReadInt,"%d",msg_EnterSInt
CREATE_READNUMBER_PROLOGUE ReadInt16,MIN_SWORD,MAX_SWORD,ReadInt,"%d",msg_EnterSInt
CREATE_READNUMBER_PROLOGUE ReadInt32,MIN_SDWORD,MAX_SDWORD,ReadInt,"%d",msg_EnterSInt
CREATE_READNUMBER_PROLOGUE ReadInt8_Silent,MIN_SBYTE,MAX_SBYTE,ReadInt,"%d"
CREATE_READNUMBER_PROLOGUE ReadInt16_Silent,MIN_SWORD,MAX_SWORD,ReadInt,"%d"
CREATE_READNUMBER_PROLOGUE ReadInt32_Silent,MIN_SDWORD,MAX_SDWORD,ReadInt,"%d"

ReadInt:
	cmp eax,ebx
	jng .test_min

;	mov esi,msg_NumberTooBig
;	call WriteString
	mov eax,ebx
	jmp .return

.test_min:
	cmp eax,edi
	jnl .return

;	mov esi,msg_NumberTooLow
;	call WriteString
	mov eax,edi

.return:
FN_END_POPA RET_EAX

;----------------
; Funkce ReadUIntX (8,16,32) {ReadUInt8,ReadUInt16,ReadUInt32}
; Precte 8-, 16-, 32-bitovou celociselnou hodnotu bez znamenka z klavesnice
; Chovani funkci je dano chovanim funkce SSCANF. Veskere namitky se netykaji autora.
;
CREATE_READNUMBER_PROLOGUE ReadUInt8,0,MAX_UBYTE,ReadUInt,"%u",msg_EnterUInt
CREATE_READNUMBER_PROLOGUE ReadUInt16,0,MAX_UWORD,ReadUInt,"%u",msg_EnterUInt
CREATE_READNUMBER_PROLOGUE ReadUInt32,0,MAX_UDWORD,ReadUInt,"%u",msg_EnterUInt
CREATE_READNUMBER_PROLOGUE ReadUInt8_Silent,0,MAX_UBYTE,ReadUInt,"%u"
CREATE_READNUMBER_PROLOGUE ReadUInt16_Silent,0,MAX_UWORD,ReadUInt,"%u"
CREATE_READNUMBER_PROLOGUE ReadUInt32_Silent,0,MAX_UDWORD,ReadUInt,"%u"

ReadUInt:
	cmp eax,ebx
	jna .return

;	mov esi,msg_NumberTooBig
;	call WriteString
	mov eax,ebx

.return:
FN_END_POPA RET_EAX

;----------------
; Funkce ReadFloat
; Precte 32bitove realne cislo z klavesnice
; Chovani funkci je dano chovanim funkce SSCANF. Veskere namitky se netykaji autora.
;
FN_BEGIN_PUSHA ReadFloat
	mov esi,msg_EnterFloat
	call WriteString
	MOVSTR ebx,"%lf"
	call ReadNumber
	fld qword [number_in]
	sub esp,4
	fstp dword [esp]
	pop eax
FN_END_POPA RET_EAX

FN_BEGIN_PUSHA ReadFloat_Silent
	MOVSTR ebx,"%lf"
	call ReadNumber_Silent
	fld qword [number_in]
	sub esp,4
	fstp dword [esp]
	pop eax
FN_END_POPA RET_EAX
;----------------
; Funkce ReadDouble
; Precte 64bitove realne cislo z klavesnice
; Chovani funkci je dano chovanim funkce SSCANF. Veskere namitky se netykaji autora.
;
FN_BEGIN_PUSHA ReadDouble
	mov esi,msg_EnterFloat
	call WriteString
	MOVSTR ebx,"%lf"
	call ReadNumber
	fld qword [number_in]
FN_END_POPA RET_EAX

FN_BEGIN_PUSHA ReadDouble_Silent
	MOVSTR ebx,"%lf"
	call ReadNumber_Silent
	fld qword [number_in]
FN_END_POPA RET_EAX
;----------------
; WriteChar
; Vypise znak ulozeny v registru AL
;
WriteChar:
	pushfd
	push eax
	CALL_CLIB printf, "%c", eax
	pop eax
	popfd
	ret

;----------------
; WriteNewLine
; Vypise "End Of Line", tedy ASCII hodnoty CR, LF ve Windows (13, 10) a LF v Linuxu (10)
;
WriteNewLine:
	pushfd
	push eax
	CALL_CLIB printf,"%s",msg_EOL
	pop eax
	popfd
	ret

;----------------
; Funkce WriteBinX (8, 16, 32) {WriteBin8, WriteBin16, WriteBin32}
; Vypise 8,16,32 bitu z registru AL, AX, EAX
;
WriteBin8:
	pushfd
	pushad

	mov ecx,8
	rcl eax,24
	jmp WriteBin

WriteBin16:
	pushfd
	pushad

	mov ecx,16
	rcl eax,16
	jmp WriteBin

WriteBin32:
	pushfd
	pushad

	mov ecx,32

WriteBin:
	cld
	mov edi,ioBuffer
	mov ebx,eax

.next_bit:
	rcl ebx,1
	setc al
	add al,'0'
	stosb
	loop .next_bit

	mov [edi], byte 0
	mov esi,ioBuffer
	call WriteString

	popad
	popfd
	ret

;----------------
; WriteString
; Vypise retezce ukonceneho 0 (ASCIIZ), jehoz adresa je ulozena v registru ESI
;
WriteString:
	pushfd
	push eax
	CALL_CLIB printf,"%s", esi
	pop eax
	popfd
	ret

;----------------
; WriteFlags
; Vypise stav registru priznaku
;
WriteFlags:
	pushfd
	pushad

	pushfd
	pop ebx
	shl ebx,20

	mov ecx,12
	mov edi,msg_FlagValues

.cycle:
	rcl ebx,1
	setc al
	add al,'0'
	mov [edi],al
	add edi,3
	loop .cycle

	mov esi,msg_Flags
	call WriteString

	popad
	popfd
	ret

;----------------
; Funkce WriteIntX (8,16,32) {WriteInt8,WriteInt16,WriteInt32}
; Vypise 8-, 16-, 32-bitovou celociselnou hodnotu se znamenkem z registru AL, AX, EAX
;
;----------------
; Funkce WriteUIntX (8,16,32) {WriteUInt8,WriteUInt16,WriteUInt32}
; Vypise 8-, 16-, 32-bitovou celociselnou hodnotu bez znamenka z registru AL, AX, EAX
;
; Chovani funkci je dano chovanim funkce PRINTF a prislusnym formatovacim retezcem.
;

WriteInt8:
	pushfd
	push eax
	movsx eax,al
	jmp WriteInt

WriteUInt8:
	pushfd
	push eax
	movzx eax,al
	jmp WriteUInt

WriteInt16:
	pushfd
	push eax
	movsx eax,ax
	jmp WriteInt 

WriteUInt16:
	pushfd
	push eax
	movzx eax,ax
	jmp WriteUInt

WriteInt32:
	pushfd
	push eax

WriteInt:
	CALL_CLIB printf, "%d", eax

	pop eax
	popfd
	ret

WriteUInt32:
	pushfd
	push eax

WriteUInt:
	CALL_CLIB printf, "%u", eax

	pop eax
	popfd
	ret

;----------------
; Funkce WriteHexX (8,16,32) {WriteHex8,WriteHex16,WriteHex32}
; Vypise hexadecimalne 8-, 16-, 32-bitovou celociselnou hodnotu bez znamenka z registru AL, AX, EAX
;
; Chovani funkci je dano chovanim funkce PRINTF a prislusnym formatovacim retezcem.
;

WriteHex8:
	pushfd
	push eax
	push esi
	movzx eax,al
	MOVSTR esi,"0x%02X"
	jmp WriteHex

WriteHex16:
	pushfd
	push eax
	push esi
	movzx eax,ax
	MOVSTR esi,"0x%04X"
	jmp WriteHex

WriteHex32:
	pushfd
	push eax
	push esi	
	MOVSTR esi,"0x%08X"

WriteHex:
	CALL_CLIB printf, esi, eax

	pop esi
	pop eax
	popfd
	ret

;----------------
; Funkce WriteFloat
; Vypise 32-bitove realne cislo z registru EAX
;
WriteFloat:
	pushad
	pushfd
	push eax
	fld dword [esp]
	call WriteDouble
	add esp,4
	popfd
	popad
	ret

;----------------
; Funkce WriteFloat
; Vypise 32-bitove realne cislo z registru EAX
;
WriteFloatP1:
	enter 8,0
	pushfd
	push eax
	mov [ebp-4], eax
	fld dword [ebp-4]
	fstp qword [ebp-8]
	CALL_CLIB printf, "%.1f", [ebp-8], [ebp-4]			; printf vyzaduje vzdy double!
	pop eax
	popfd
	leave
	ret

;----------------
; Funkce WriteDouble
; Vypise 64-bitove realne cislo z registru koprocesoru ST0
;
WriteDouble:
	enter 8,0
	pushfd
	push eax
	fst qword [ebp-8]
	CALL_CLIB printf, "%lf", [ebp-8], [ebp-4]
	pop eax
	popfd
	leave
	ret

;----------------
; Funkce WriteAllGPRegisters32
; Vypise pole cisel, ukazatel na pole je v ESI, pocet cisel je v ECX
;
WriteAllGPRegisters32:
	pushfd
	pushad
	CALL_CLIB printf, `EAX=0x%08X,EBX=0x%08X,ECX=0x%08X,EDX=0x%08X,ESI=0x%08X,EDI=0x%08X,EBP=0x%08X,ESP=0x%08X\n`, eax, ebx, ecx, edx, esi, edi, ebp, esp
	popad
	popfd
	ret

;----------------
; Funkce WriteTestGPRegisters32
; Vypise pole cisel, ukazatel na pole je v ESI, pocet cisel je v ECX
;
WriteTestGPRegisters32:
	pushfd
	pushad
	CALL_CLIB printf, `EBX=0x%08X,ECX=0x%08X,EDX=0x%08X,ESI=0x%08X,EDI=0x%08X,EBP=0x%08X\n`, ebx, ecx, edx, esi, edi, ebp
	popad
	popfd
	ret

RegDump:
    mov [tmp],esp
    mov esp,reg_dump+4
    pushad
    mov esp,[tmp]
    mov [reg_dump - 16],esp
    ret  

;----------------
; Funkce WriteDiffTestGPRegisters32
; Vypise pole cisel, ukazatel na pole je v ESI, pocet cisel je v ECX
;
WriteDiffTestGPRegisters32:
;EAX ~ ESP + 28 (-0)
;ECX ~ ESP + 24 (-4)
;EDX ~ ESP + 20 (-8)
;EBX ~ ESP + 16 (-12)
;old ESP ~ ESP + 12 (-16)
;EBP ~ ESP + 8 (-20)
;ESI ~ ESP + 4 (-24)
;EDI ~ ESP + 0 (-28)

    mov [tmp],esp
    pushfd
    pushad
    mov ebp,esp
;        cmp eax,[reg_dump - 0]
;        jz .ebx
;        push s_EAX
;.ebx:        
    cmp ebx,[reg_dump - 12]
    jz .ecx
    push s_EBX
.ecx:        
    cmp ecx,[reg_dump - 4]
    jz .edx
    push s_ECX
.edx:
    cmp edx,[reg_dump - 8]
    jz .esi
    push s_EDX
.esi:
    cmp esi,[reg_dump - 24]
    jz .edi
    push s_ESI
.edi:
    cmp edi,[reg_dump - 28]
    jz .ebp
    push s_EDI
.ebp:        
    mov eax,[ebp + 8]
    cmp eax,[reg_dump - 20]
    jz .esp
    push s_EBP
.esp:
    mov eax,[tmp]
    cmp eax,[reg_dump - 16]
    jz .write
    push s_ESP
.write:
    mov ecx,ebp
    sub ecx,esp
    shr ecx,2
    cmp ecx,0
    jz .no_changes
    mov esi,msg_regChanges
    call WriteString
.write_next:        
    pop esi
;        call WriteString
    cmp ecx,1
    jz .skip_comma
    mov al,','
;        call WriteChar
.skip_comma:
    loop .write_next
    jmp .exit
.no_changes:        
    mov esi,msg_NoRegChanges
    call WriteString
.exit:
        ;call WriteNewLine
    popad
    popfd
    ret

;----------------
; Funkce WriteDiffTestGPRegisters32
; Vypise pole cisel, ukazatel na pole je v ESI, pocet cisel je v ECX
;
HaveGPRegisters32Changed:
;EAX ~ ESP + 28 (-0)
;ECX ~ ESP + 24 (-4)
;EDX ~ ESP + 20 (-8)
;EBX ~ ESP + 16 (-12)
;old ESP ~ ESP + 12 (-16)
;EBP ~ ESP + 8 (-20)
;ESI ~ ESP + 4 (-24)
;EDI ~ ESP + 0 (-28)
	mov [tmp],esp	
	pushfd
	pushad
	cmp ebx,[reg_dump - 12]
	jnz .changed
	cmp ecx,[reg_dump - 4]
	jnz .changed
	cmp edx,[reg_dump - 8]
	jnz .changed
	cmp esi,[reg_dump - 24]
	jnz .changed        
	cmp edi,[reg_dump - 28]
	jnz .changed
	mov eax,[esp + 8]
	cmp eax,[reg_dump - 20]
	jnz .changed
	mov eax,[tmp]
	cmp eax,[reg_dump - 16]
	jnz .changed
	mov [tmpEAX],dword 0
	jmp .exit
.changed:
	mov [tmpEAX],dword 1
.exit:
	popad
	popfd
	mov eax,[tmpEAX]
	ret

%macro CREATE_WRITE_ARRAY 2.nolist
; datovy typ (b,w,d), funkce pro vypis z RW32
WriteArray%2:
	pushfd
	push esi
	push eax

    test esi,esi
    jnz %%ptr_ok
	CALL_CLIB printf, 'NULL'
	jmp %%exit
%%ptr_ok:	
	mov al,'['
   	call WriteChar
    cmp ecx,0
    jle %%end
%%writeElement:
  	lods%1
   	call Write%2
   	cmp ecx,1
   	jbe %%skipComma
   	mov al,','
   	call WriteChar
	mov al,' '
   	call WriteChar
%%skipComma:
   	loop %%writeElement
%%end:
    mov al,']'
   	call WriteChar
   	;call WriteNewLine
%%exit:   
   	pop eax
   	pop esi
	popfd
	ret
%endmacro

;----------------
; Funkce WriteArrayInt8
; Vypise pole cisel, ukazatel na pole je v ESI, pocet cisel je v ECX
;
CREATE_WRITE_ARRAY b, Int8

;----------------
; Funkce WriteArrayInt16
; Vypise pole cisel, ukazatel na pole je v ESI, pocet cisel je v ECX
;
CREATE_WRITE_ARRAY w, Int16

;----------------
; Funkce WriteArrayInt32
; Vypise pole cisel, ukazatel na pole je v ESI, pocet cisel je v ECX
;
CREATE_WRITE_ARRAY d, Int32

;----------------
; Funkce WriteArrayUInt8
; Vypise pole cisel, ukazatel na pole je v ESI, pocet cisel je v ECX
;
CREATE_WRITE_ARRAY b, UInt8

;----------------
; Funkce WriteArrayUInt16
; Vypise pole cisel, ukazatel na pole je v ESI, pocet cisel je v ECX
;
CREATE_WRITE_ARRAY w, UInt16

;----------------
; Funkce WriteArrayUInt32
; Vypise pole cisel, ukazatel na pole je v ESI, pocet cisel je v ECX
;
CREATE_WRITE_ARRAY d, UInt32

;----------------
; Funkce WriteArrayFloat
; Vypise pole cisel, ukazatel na pole je v ESI, pocet cisel je v ECX
;
CREATE_WRITE_ARRAY d, Float

;----------------
; Funkce WriteArrayFloatP1
; Vypise pole cisel, ukazatel na pole je v ESI, pocet cisel je v ECX
;
CREATE_WRITE_ARRAY d, FloatP1

