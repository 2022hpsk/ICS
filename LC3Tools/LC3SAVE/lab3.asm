        .ORIG x3000
        AND R4,R4,0 ;;R4 <- 0 to judge if queue is empty
        LD R5,HEAD  ;;R5 <- x5000
        LD R6,TAIL  ;;R6 <- x5000
        LD R7,OUTS  ;;R7 <- x6000
INPUT   TRAP x20    ;;GETC
        TRAP x21    ;;ECHO
        
        ADD R1,R0,#-10  ;;R1 <- R0 - 10
        BRz ENDIN       ;;ENDIN if R1 == 0
GET-    LD R1,ASC-      ;;R1 <- -45
        ADD R1,R0,R1    ;;R1 <- R0 - 45
        BRz POPL
GET]    LD R1,ASC]      ;;R1 <- -93
        ADD R1,R0,R1    ;;R1 <- R0 - 93
        BRz POPR
GET+    LD R1,ASC+      ;;R1 <- -43
        ADD R1,R0,R1    ;;R1 <- R0 - 43
        BRz PUSHL
GET[    LD R1,ASC[      ;;R1 <- -91
        ADD R1,R0,R1    ;;R1 <- R0 - 91
        BRz PUSHR        
        
POPL    ADD R4,R4,0     ;;setcc : R4    
        BRz EMPTYPO
        ADD R2,R4,#-1   ;;R2 <- R4 - 1
        BRz ONEPOP
        ADD R7,R7,#1    ;;R7 <- R7 + 1 OUTS pointer ++
        LDR R2,R5,#0    ;;R2 <- MEM[R5]
        STR R2,R7,#0    ;;MEM[R7] <- R2
        ADD R5,R5,#1    ;;R5 <- R5 + 1 head pointer ++
        ADD R4,R4,#-1   ;;R4 <- R4 - 1 counter --
        BRnzp INPUT     ;;STEP DONE ,NEXT INPUT  
        
POPR    ADD R4,R4,0     ;;setcc : R4    
        BRz EMPTYPO
        ADD R2,R4,#-1   ;;R2 <- R4 - 1
        BRz ONEPOP
        ADD R7,R7,#1    ;;R7 <- R7 + 1 OUTS pointer ++
        LDR R2,R6,#0    ;;R2 <- MEM[R6]
        STR R2,R7,#0    ;;MEM[R7] <- R2
        ADD R6,R6,#-1   ;;R6 <- R6 - 1 TAIL pointer --
        ADD R4,R4,#-1   ;;R4 <- R4 - 1 counter --    
        BRnzp INPUT     ;;STEP DONE ,NEXT INPUT
        
PUSHL   TRAP x20    ;;GETC
        TRAP x21    ;;ECHO
        ADD R4,R4,0     ;;setcc : R4    
        BRz EMPTYPU
        ADD R5,R5,#-1   ;;R5 <- R5 - 1
        STR R0,R5,0     ;;MEM[R5] <- R0
        ADD R4,R4,#1    ;;R4 <- R4 + 1
        BRnzp INPUT
PUSHR   TRAP x20    ;;GETC
        TRAP x21    ;;ECHO
        ADD R4,R4,0     ;;setcc : R4    
        BRz EMPTYPU
        ADD R6,R6,#1    ;;R6 <- R6 + 1
        STR R0,R6,0     ;;MEM[R6] <- R0
        ADD R4,R4,#1    ;;R4 <- R4 + 1
        BRnzp INPUT
        
EMPTYPO ADD R7,R7,#1    ;;R7 <- R7 + 1
        LD R2,ASC_      ;;R2 <- 95
        STR R2,R7,0     ;;MEM[R7] <- R2 ('_')
        BRnzp   INPUT
        
EMPTYPU STR R0,R6,0     ;;MEM[R6] <- R0
        ADD R4,R4,#1    ;;R4 <- R4 + 1
        BRnzp INPUT
        
ONEPOP  ADD R7,R7,#1    ;;R7 <- R7 + 1 OUTS pointer ++
        LDR R2,R6,#0    ;;R2 <- MEM[R6]
        STR R2,R7,#0    ;;MEM[R7] <- R2
        ADD R4,R4,#-1   ;;R4 <- R4 - 1 counter --    
        BRnzp INPUT     ;;STEP DONE ,NEXT INPUT 
        
ENDIN   AND R2,R2,0     ;;R2 <- 0
        ADD R7,R7,#1    ;;R7 <- R7 + 1
        STR R2,R7,0     ;;MEM[R7] <- 0
        LD  R0,OUTSTA   ;;R0 <- x6001    
        TRAP x22        ;;PUTS    
        HALT
        
HEAD    .FILL x5000
TAIL    .FILL x5000     
OUTS    .FILL x6000
OUTSTA  .FILL x6001
ASC+    .FILL xFFD5     ;;(-43)
ASC-    .FILL xFFD3     ;;(-45)
ASC]    .FILL xFFA3     ;;(-93)
ASC[    .FILL xFFA5     ;;(-91)
ASC_    .FILL x005F     ;;(+95)
        .END
   