            .ORIG x200
            LD R0,OS_SP         ;;R0 <- x3000
    
            LD R0,USER_PSR      ;;R0 <- x8002
            ADD R6,R6,#-1       ;;R6 <- R6 - 1
            STR R0,R6,#0        ;;MEM[R6] <- R0
    
            LD R0,USER_PC       ;;R0 <- x3000
            ADD R6,R6,#-1       ;;R6 <- R6 - 1
            STR R0,R6,#0        ;;MEM[R6] <- R0
    
            LD R0,KBSR_NUM      ;;R0 <- x4000
            STI R0,KBSR         ;;MEM[xFE00] <- R0   (let KBSR[14] be 1)
    
            LD R0,INTV_FC       ;;R0 <- x2000
            STI R0,INTV         ;;MEM[x0180] <- R0 (let INTVx0180 be x2000)
            RTI

OS_SP       .FILL x3000
USER_PSR    .FILL x8002
USER_PC     .FILL x3000
KBSR        .FILL xFE00
KBSR_NUM    .FILL x4000
INTV        .FILL x0180
INTV_FC     .FILL x2000
            .END

            .ORIG x2000
            ADD R6,R6,#-2       ;;R6 <- R6 - 2
            STR R0,R6,#0        ;;MEM[R6] <- R0 (Save R0)
            STR R1,R6,#1        ;;MEM[R6 + 1] <- R1 (Save R1)
            LDI R0,KBDR         ;;R0 <- MEM[xFE02]
            LD R1,Neg9          ;;R1 <- ASC (-'9')
            ADD R1,R1,R0        ;;R1 <- R0 - '9'
            BRnz Changepos          
            STI R0,Char         ;;MEM[x4000] <- R0  (Changechar)
            BR ENDDING             
Changepos   ADD R1,R1,#9        ;;R1 <- R1 + 9
            LDI R0,Pos          ;;R0 <- MEM[x4001]
            ADD R0,R0,R1        ;;R0 <- R0 + R1
            ADD R1,R0,#-16      ;;R1 <- R0 - 16
            BRnz Storepos
            LD R0,max_width     ;;R0 <- 17
Storepos    STI R0,Pos          ;;MEM[x4001] <- R0
ENDDING     LDR R0,R6,#0        ;;R0 <- MEM[R6]
            LDR R1,R6,#1        ;;R1 <- MEM[R6 + 1]
            ADD R6,R6,#2        ;;R6 <- R6 + 2
            RTI
    
KBDR        .FILL xFE02
Neg9        .FILL x-39
Char        .FILL x4000
Pos         .FILL x4001
max_width   .FILL #17
            .END

            .ORIG x3000
            LD R0,Initchar      ;;R0 <- x61
            STI R0,Charuser     ;;MEM[x4000] <- R0
            LD R1,Initpos       ;;R1 <- x5
            STI R1,Posuser      ;;MEM[x4001] <- R1
            
Loop        LDI R1,Posuser      ;;R1 <- MEM[x4001](Position)
            ADD R2,R1,#0        ;;R2 <- R1
            LD R0,Dot           ;;R0 <- ASC DOT(x2e)
            
Dothead     ADD R2,R2,#-1       ;;R2 <- R2 - 1 (Dot counter --)
            BRn Putchar      
            OUT                 ;;OUTPUT: DOT
            BR Dothead
            
Putchar     LDI R0,Charuser     ;;R0 <- MEM[x4000](Char)
            OUT                 ;;OUTPUT: Char
            OUT
            OUT
            NOT R2,R1
            ADD R2,R2,#9
            ADD R2,R2,#9        ;;R2 <- 17 - R1 (Restore Dot counter)
            LD R0,Dot           ;;R0 <- ASC DOT(x2e)
            
Dottail     ADD R2,R2,#-1       ;;R2 <- R2 - 1 (Dot counter --)
            BRn Newlineout
            OUT                 ;;OUTPUT: DOT
            BR Dottail
            
Newlineout  LD R0,Newline
            OUT
            LDI R1,Posuser      ;;R1 <- MEM[x4001](Position)
            BRz Delaycycle
            ADD R1,R1,#-1       ;;R1 <- R1 - 1  (Position --)
            STI R1,Posuser      ;;MEM[x4001] <- R1  (Store position)
            
Delaycycle  LD R2,Delaytime     ;;R2 <- x1000
Delay       ADD R2,R2,#-1
            BRp Delay
            BR Loop
    
Charuser    .FILL x4000
Posuser     .FILL x4001
Dot         .FILL x2e
Newline     .FILL xa
Initchar    .FILL x61
Initpos     .FILL x5
Delaytime   .FILL x1000
            .END