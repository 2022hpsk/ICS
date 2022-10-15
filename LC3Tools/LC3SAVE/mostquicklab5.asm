            .ORIG x3000
            LD R4,STACK1    ;;R5 <- x4000 
            LD R5,STACK2    ;;R5 <- x5000
            LD R6,RETSTACK  ;;R6 <- xFDFF
            AND R1,R1,0     ;;(R1 <- 0)
            STI R1,BITCONST ;;MEM[x6004] <- 0
            STR R1,R6,0     ;;MEM[xFDFF] <- 0( ORIGINAL BITNUMBER)
            BR READN        ;;(;;Decimal Input N -> R1 :N)
NEXT        STI R1,COUNTER  ;;MEM[x6001] <- R1
            STI R1,CONSTNUM ;;MEM[x6002] <- R1
            JSR NUMBERTOBIT ;;MEM[x6004] <- R1(BIT VERSION)
            BR READ
            
READDONE    LDI R0,CONSTNUM ;;R0 <- MEM[x6002]            
            STI R0,COUNTER  ;;MEM[x6001] <- R1            
            LD R4,STACK1    ;;R5 <- x4000 
            LD R5,STACK2    ;;R5 <- x5000 
            LD R3,LIST      ;;R3 <- x7000
            JSR SEARCH
            
            HALT
            
            
SEARCH      ADD R6,R6,#-1   ;;R6 <- R6 - 1
            STR R7,R6,0     ;;MEM[R6] <- R7
            ADD R6,R6,#-1   ;;R6 <- R6 - 1
            ADD R4,R4,#-1   ;;R4 <- R4 - 1
            ADD R5,R5,#-1   ;;R5 <- R5 - 1
            ADD R3,R3,#1    ;;R3 <- R3 + 1
            
            BR  Choose1     ;;choose stack1
Choose1back JSR SEARCH      ;;go deeper
            BR  Choose2     ;;in Choose2 ,one more thing:judge if it is deepest.
Choose2back JSR SEARCH      ;;go deeper
Deepest     BR  Judge
Continue    ADD R3,R3,#-1   ;;R3 <- R3 - 1
            ADD R4,R4,#1    ;;R4 <- R4 + 1
            ADD R5,R5,#1    ;;R5 <- R5 + 1
            ADD R6,R6,#1    ;;R6 <- R6 + 1
            LDR R7,R6,0     ;;R7 <- MEM[R6]
            ADD R6,R6,#1    ;;R6 <- R6 + 1
            
SEARCHRET   RET
            
Judge       LDR R0,R6,0
            LDI R1,BITCONST
            AND R0,R0,R1        ;;R0 <- R0 & R1      
            NOT R0,R0
            ADD R0,R0,#1        ;;R0 <- -R0
            ADD R0,R1,R0        ;;R0 <- R1 - R0
            BRz FINISH
            BR  Continue 
            
Choose1     LDI R0,CONSTNUM     ;;R0 <- MEM[x6002] (counter)
            LD  R1,STACK1       ;;R1 <- x4000
            ADD R0,R0,R4        ;;R0 <- R0(n) + R4(stack now)
            NOT R0,R0
            ADD R0,R0,#1        ;;R0 <- -R0
            ADD R0,R1,R0        ;;R0 <- R1(x4000) - R0(stack + counter n)
            BRp Deepest
            
            LDR R0,R4,0         ;;R0 <- MEM[R4]
            STR R0,R3,0         ;;MEM[R3] <- R0
            JSR MAPTOBIT
            BR  Choose1back
            
Choose2     LDI R0,CONSTNUM     ;;R0 <- MEM[x6002] (counter)
            LD  R1,STACK2       ;;R1 <- x5000
            ADD R0,R0,R5        ;;R0 <- R0(n) + R5(stack now)
            NOT R0,R0
            ADD R0,R0,#1        ;;R0 <- -R0
            ADD R0,R1,R0        ;;R0 <- R1(x5000) - R0(stack + counter n)
            BRp Deepest
            
            LDR R0,R5,0         ;;R0 <- MEM[R5]
            STR R0,R3,0         ;;MEM[R3] <- R0
            JSR MAPTOBIT
            BR  Choose2back

MAPTOBIT    LDR R2,R6,#2       ;;R2 <- MEM[R6] (BITNUMBER)
            
            
            
            LDR R1,R3,0         ;;R1 <- MEM[R3] (counter) (;;R0 <- BIT[R1]:1)
            AND R0,R0,0         ;;R0 <- 0
            ADD R0,R0,#1        ;;R0 <- R0 + 1
Loop        ADD R0,R0,R0        ;;R0 << 1
            ADD R1,R1,#-1       ;;R1 <- R1 - 1 (counter --)
            BRp Loop
            
            ADD R1,R2,0         ;;R1 <- R2(BITNUMBER)
            NOT R0,R0
            NOT R1,R1
            AND R0,R0,R1
            NOT R0,R0           ;;R0 <- R0 | R1
            
            ADD R2,R0,0         ;;R2(BITNUMBER) <- R0
            
            STR R2,R6,0         ;;MEM[R6] <- R2

            
            RET
            
            
FINISH      LDI R1,CONSTNUM     ;;R1 <- N
            LD R2,LIST          ;;R2 <- x7000
            ADD R1,R2,R1        ;;R1 <- R1 + R2
            ADD R1,R1,#1        ;;R1 <- R1 + 1
            AND R0,R0,0         ;;R0 <- 0
            STR R0,R1,0         ;;MEM[R1] <-0           (The end hint :0)
            LD R1,LIST          ;;R1 <- x7000
Nextout     ADD R1,R1,#1        ;;R1 <- R1 + 1
            LDR R2,R1,0         ;;R2 <- MEM[R1](R2 : Decimal number)
            BRz Outover
            ADD R0,R2,#-9       ;;R0 <- R2(Decimal number) -9  
            BRp Twooutput
            LD  R0,ASC0         ;;R0 <- 48
            ADD R0,R2,R0        ;;R0 <- R2 + 48
            TRAP x21
            LD R0,ASCSP
            TRAP x21
            BR Nextout

Twooutput   LD R0,ASC1          ;;R0 <- ASC1
            TRAP x21
            ADD R0,R2,#-9       ;;R0 <- R2(Decimal number) -9
            ADD R0,R0,#-1       ;;R0 <- R0 - 1
            LD  R2,ASC0         ;;R2 <- 48
            ADD R0,R0,R2        ;;R0 <- R0 + 48
            TRAP x21
            LD R0,ASCSP
            TRAP x21
            BR  Nextout
            
Outover     HALT
            
;;Decimal Input N -> R1
READN       TRAP x20
            TRAP x21
            ADD R2,R0,#-10  ;;(R2 <- R0ASC - 10)
            BRz NEXT
            JSR Multi10     ;;(R1 = R1 * 10)
            LD  R3,ASC-48   ;;(R3 <- -48)
            ADD R0,R0,R3    ;;(R0 = R0 - 48)
            ADD R1,R1,R0    ;;(R1 = R1 + R0)
            BRnzp   READN
            
;;;;Decimal Input i -> R1
READ        AND R1,R1,0     ;;R1 <- 0
READLOOP    TRAP x20
            TRAP x21
            ADD R2,R0,#-10  ;;(R2 <- R0ASC - 10)
            BRz Newline
            LD  R3,ASC-32   ;;(R3 <- -32)  
            ADD R2,R0,R3  ;;(R2 <- R0ASC - 32)
            BRz Read2
            JSR Multi10     ;;(R1 = R1 * 10)
            LD  R3,ASC-48   ;;(R3 <- -48)
            ADD R0,R0,R3    ;;(R0 = R0 - 48)
            ADD R1,R1,R0    ;;(R1 = R1 + R0)
            BRnzp   READLOOP

Read2       ADD R4,R4,#-1
            STR R1,R4,0
            BR  READ
Newline     ADD R5,R5,#-1
            STR R1,R5,0
            LDI R3,COUNTER
            ADD R3,R3,#-1
            STI R3,COUNTER
            BRp READ
            BR  READDONE
            
;;MEM[x6004] <- R1(BIT VERSION)             
NUMBERTOBIT AND R0,R0,0     ;;R0 <- 0
Bitloop     ADD R0,R0,#1    ;;R0 <- R0 + 1
            ADD R0,R0,R0    ;;R0 << 1
            ADD R1,R1,#-1   ;;R1 <- R1 - 1(counter --)
            BRp Bitloop
            STI R0,BITCONST ;;MEM[x6004] <- R0
            RET


            
;;Multi10 : R1 = R1 * 10, R2 = 0, R3 = 0
Multi10     AND R3,R3,#0    ;;(Multi10 : R1 = R1 * 10, R2 = 0, R3 = 0)
            AND R2,R2,#0    ;;(detail :  R3 = R1 +...  , R1 <- R3)
            ADD R2,R2,#10
MulLoop     BRz Back
            ADD R3,R3,R1
            ADD R2,R2,#-1
            BRnzp  MulLoop   
Back        ADD R1,R3,#0
            AND R3,R3,#0
            RET 
            

STACK1      .FILL x4000    
STACK2      .FILL x5000
RETSTACK    .FILL xFDFF
LIST        .FILL x7000
ASC-48      .FILL x-30
ASC-32      .FILL x-20
COUNTER     .FILL x6001
CONSTNUM    .FILL x6002
BITNUMBER   .FILL x6003
BITCONST    .FILL x6004
NegASC9     .FILL x-39
ASC1        .FILL x31
ASC0        .FILL x30
ASCSP       .FILL X20
            .END