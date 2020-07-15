; ============================================================================
;   ThreadLocks.asm: low-level OS commands, written in assembly
;   Runs on MSP432
; ============================================================================

        .thumb
        .text
        .align 2

        .global  RGB_Lock 		;Resource Lock on the RGB LED
        .global  Lock_Acquire
        .global  Lock_Release
        .global  Lock_Init

Lock_Acquire:  .asmfunc

	MOV		R1, #1			;Grab a lock (1)
	LDREX	R2, [R0]		;Load the door Value
	CMP		R2, R1			;Is the door open(0)?

	ITT		NE				;If Not Equal = Door is open

	;If door was open
	STREXNE	R2, R1, [R0]	;Try to Lock the Door. Returns 0 if successfull, 1 if failed
	CMPNE	R2, #1			;Was the Lock Successfull?

	;If Door was not open OR Lock was unsuccessfull
	BEQ		lf

	MOV		R0, #1			;Success, Door was locked
	BX 		LR

lf:							;local "lock failed" branch
	CLREX					;Return the lock
	MOV		R0, #0			;Return 0 - Door was already locked

    .endasmfunc

Lock_Init:  .asmfunc

	MOV		R1, #0x0    ;Init to 0
    STR		R1, [R0]    ;Store 0 in Var
	BX 		LR

    .endasmfunc

Lock_Release:  .asmfunc

	MOV		R1, #0		;0 means available
	STR		R1, [R0]	;Store 0 in Var Passed
	BX 		LR


    .endasmfunc


