; locations x3FFF(BASE) through x3FFB (MAX). 
; R6 is the stack pointer. 
; R3 contains the size of the stack element. 
; R4 is a pointer specifying the location of the element to PUSH from or the space to POP to

POP	    ST	R2, Save2  
        ST	R1, Save1
        ST	R0, Save0
        LD	R1, BASE ; BASE : -x3FFF. 
        ADD	R1, R1, #-1 ; R1 <-  -x4000.
        ADD	R2, R6, R1 ; Compare stack pointer to x4000 
        BRz	fail_exit ; Branch if stack is empty.
        ADD	R0, R4, #0  ;;(R0 <- R4 :origin pointer)
        ADD	R1, R3, #0  ;;(R1 <- R3 :size counter )
        ADD	R5, R6, R3  ;;(R5 <- R6 + R3)
        ADD	R5, R5, #-1 ;;(R5 <- R5 - 1  :pointer that POP to)
        ADD	R6, R6, R3  ;;(R6 <- R6 + R3)
 
pop_loop	LDR	R2, R5, #0  ;;(R2 <- MEM[R5])
            STR R2, R0, #0  ;;(MEM[R0] <- R2)
	        ADD	R0, R0, #1  ;;(R0 = R0 + 1)
        	ADD	R5, R5, #-1 ;;(R5 = R5 - 1)
	        ADD R1, R1, #-1 ;;(R1 = R1 - 1 : size counter --)
            BRp pop_loop
            BRnzp success_exit	

PUSH	    ST	R2, Save2 
	        ST	R1, Save1 
	        ST	R0, Save0
	        LD	R1,MAX ; MAX :-x3FFB
	        ADD R2,R6,R1 ; Compare stack pointer to -x3FFB 
            BRz fail_exit ; Branch if stack is full.
            ADD R0, R4, #0  ;;(R0 <- R4 :origin pointer)
            ADD R1, R3, #0  ;;(R1 <- R3 :size counter)
            ADD	R5, R6, #-1 ;;(R5 <- R6 - 1)
	        NOT	R2, R3
    	    ADD	R2, R2, #1  ;;(R2 <- -R3)
	        ADD	R6, R6, R2  ;;(R6 <- R6 + R2)
	        
push_loop	LDR	R2, R0, #0  ;;(R2 <- MEM[R0])
	        STR	R2, R5, #0  ;;(MEM[R5] <- R2)
	        ADD	R0, R0, #1  ;;(R0 <- R0 + 1)
	        ADD	R5, R5, #-1 ;;(R5 <- R5 - 1)
	        ADD R1, R1, #-1 ;;(R1 <- R1 - 1)
            BRp	push_loop

success_exit	LD	R0, Save0
	            LD	R1, Save1 ; Restore original
	            LD	R2, Save2 ; register values.
                AND R5, R5, #0 ; R5 <-- success.
                RET

fail_exit	    LD	R0, Save0
                LD	R1, Save1 ; Restore original
	            LD	R2, Save2 ; register values.
	            AND	R5, R5, #0
                ADD R5, R5, #1 ; R5 <-- failure.
                RET
BASE	.FILL	xC001 ;;-x3FFF
MAX	    .FILL	xC005 ;;-x3FFB
Save0	.FILL	x0000
Save1	.FILL	x0000
Save2	.FILL	x0000
