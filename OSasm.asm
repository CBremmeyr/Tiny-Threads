; ============================================================================
;   OSasm.asm: low-level OS commands, written in assembly
;   Runs on MSP432
;   A very simple real time operating system with minimal features.
; ============================================================================

        .thumb
        .text
        .align 2


        .global  RunPt            		; currently running thread
        .global  OS_DisableInterrupts
        .global  OS_EnableInterrupts
        .global  StartOS
        .global  SysTick_Handler


OS_DisableInterrupts:  .asmfunc			; Complete this

    CPSID i  ;PRIMASK
    CPSID f  ;FAULTMASK
	BX LR

    .endasmfunc


OS_EnableInterrupts:  .asmfunc			; Complete this
        
	CPSIE i    ;PRIMASK
	CPSIE f    ;FAULTMASK
	BX LR
		
    .endasmfunc


RunPtAddr .field RunPt,32


SysTick_Handler:  .asmfunc     ; 1) Handler automatically saves R0-R3,R12,LR,PC,PSR on stack upon entry
							   ; 2) Disable interrupt mechanism to prevent interrupts from happening during switch
							   ; 3) Save remaining regs r4-11 on stack (of current thread)
							   ; 4) Load R0 with the address of RunPt, current thread
							   ; 5) Load R1 with the value of RunPt
							   ; 6) Save current SP into TCB structure
							   ; 7) Load R1 with the value of RunPt->next
							   ; 8) Store it in RunPt (so it points to next thread)
							   ; 9) Load new thread SP; SP = RunPt->sp;
							   ;10) Restore regs r4-11 (next thread)
							   ;11) Enable interrupt mechanism
							   ;12) Return to calling function (R0-R3,R12,LR,PC,PSR are automatically restored upon exit
    .endasmfunc


StartOS:  .asmfunc			   ; 1) Kickstarts the process with 1st thread
    ADR   R0, RunPtAddr 	   ; 2) Load R0 with the address of RunPt, current thread
	LDR	  R2, [R0]  	       ; 3) Load R2 with the value of RunPt
	MOV   SP, R2         	   ; 4) Load SP with new thread SP; SP = RunPt->stackPointer;
	POP   {R4-R11}			   ; 5) Restore regs r4-11
	POP   {R0-R3}			   ; 6) Restore regs r0-3
	POP   {R12}				   ; 7) Restore reg r12
	POP   {LR}    	           ; 8) Restore LR and discard LR from initial stack
	POP   {LR} 				   ; 9) Restore return address and store it in LR (start location)
	POP	  {R1}				   ;10) Restore XPSR into R1 and discard XPSR
	BL    OS_EnableInterrupts  ;11) Enable interrupt mechanism at processor level
	BX	  LR				   ;12) Return to calling function which would start the first thread

    .endasmfunc

    .end
