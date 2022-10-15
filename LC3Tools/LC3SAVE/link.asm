        .ORIG x3000
        
        AND R0,R0,0
        LD R0,HEAD
        
LOOP    AND R1,R1,0
        LDR R1,R0,#1    ;;(R1 <- MEM[R0 + 1])
        ADD R2,R1,R2
        LDR R1,R0,0     ;;(if mem[R0]==0 done)
        BRz DONE
        LDR R0,R0,0
        BR  LOOP
    
    
DONE    TRAP x25    ;;halt
HEAD    .FILL   x4000
        .END
        
        
.orig x4000
.FILL x4002
.FILL x1111
.FILL x4006
.FILL x2222
.FILL x4010
.FILL x3333
.FILL x4004
.FILL x4444
.BLKW 8
.FILL x0
.FILL x5555
.end