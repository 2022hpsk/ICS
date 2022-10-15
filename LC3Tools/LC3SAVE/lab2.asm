    
            .ORIG x3000
            LD R6,ASCbase
            AND R0,R0,0
            AND R2,R2,0
            AND R1,R1,#0 
            AND R4,R4,#0        ;;(R4 = 0)
;;Decimal Input -> R1
ENTER       TRAP x20       
            ADD R2,R0,#-10  ;;(R2 <- R0ASC - 10)
            BRz Next
            JSR Multi10     ;;(R1 = R1 * 10)
            ADD R0,R0,R6  ;;(R0 = R0 - 48)
            ADD R1,R1,R0    ;;(R1 = R1 + R0)
            BRnzp   ENTER
            
;;4 bits Binary to Decimal -> R2    
Next        AND R2,R2,#0    ;;(R2 = 0)
            AND R3,R3,#0    ;;(R3 = 0)
            ADD R3,R3,#4    ;;(R3 = R3 + 4)
Transform   BRz Store       ;;(if R3 == 4 - 4 == 0, break)
            ADD R1,R1,#0    ;;(R1 = R1 + 0)
            BRn Neg         ;;(if R1 < 0, goto Neg)
            ADD R2,R2,R2    ;;(R2 = R2 * 2)
            ADD R1,R1,R1    ;;(R1 << 1)
            ADD R3,R3,#-1   ;;(R3 = R3 - 1)
            BRnzp Transform
Neg         ADD R2,R2,R2    ;;(R2 = R2 * 2)
            ADD R2,R2,#1    ;;(R2 = R2 + 1)
            ADD R1,R1,R1    ;;(R1 << 1)
            ADD R3,R3,#-1   ;;(R3 = R3 - 1)
            BRnzp  Transform

;;Store: R2 -> x4000,x4001,x4002,x4003            
Store       ADD R2,R2,#-10  ;;(R2 = R2 - 10)
            BRzp Char      ;;(R2 >= 0)
Number      ADD R2,R2,#10   ;;(R2 = R2 + 10)
            ADD R2,R2,#12   ;;(R2 = R2 + 12)
            ADD R2,R2,#12   ;;(R2 = R2 + 12)
            ADD R2,R2,#12   ;;(R2 = R2 + 12)
            ADD R2,R2,#12   ;;(R2 = R2 + 12)
            BRnzp   Sto
Char        ADD R2,R2,#10   ;;(R2 = R2 + 10)
            ADD R2,R2,#11   ;;(R2 = R2 + 11)
            ADD R2,R2,#11   ;;(R2 = R2 + 11)
            ADD R2,R2,#11   ;;(R2 = R2 + 11)
            ADD R2,R2,#11   ;;(R2 = R2 + 11)
            ADD R2,R2,#11   ;;(R2 = R2 + 11)
Sto         ADD R4,R4,#0    ;;(R4 = R4 + 0)
            BRz Store0
            ADD R4,R4,#-1   ;;(R4 = R4 - 1)
            BRz Store1
            ADD R4,R4,#-1   ;;(R4 = R4 - 1)
            BRz Store2
            ADD R4,R4,#-1   ;;(R4 = R4 - 1)
            BRz Store3 
            
Store0      STI R2,loc0     ;;(Mem[x4000] <- R2)          
            ADD R4,R4,#1    ;;(R4 = R4 + 1)
            BRnzp Next
            
Store1      ADD R4,R4,#1    ;;(R4 = R4 + 1)
            STI R2,loc1     ;;(Mem[x4000] <- R2)          
            ADD R4,R4,#1    ;;(R4 = R4 + 1)
            BRnzp Next
            
Store2      ADD R4,R4,#2    ;;(R4 = R4 + 2)
            STI R2,loc2     ;;(Mem[x4000] <- R2)          
            ADD R4,R4,#1    ;;(R4 = R4 + 1)
            BRnzp Next
            
Store3      ADD R4,R4,#3    ;;(R4 = R4 + 3)
            STI R2,loc3     ;;(Mem[x4000] <- R2)          
            ADD R4,R4,#1    ;;(R4 = R4 + 1)
            BRnzp Output
            
Output      AND R2,R2,#0    ;;(R2 = 0)
            STI R2,loc4     ;;(Mem[x4004] <- 0)   
            LD R0,loc0     ;;(R0 <- x4000)
            TRAP x22        ;;(PUTS)
            
FINISH      HALT
    
    
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
        
        
ASCbase     .FILL   xffd0
loc0        .FILL   x4000
loc1        .FILL   x4001
loc2        .FILL   x4002
loc3        .FILL   x4003
loc4        .FILL   x4004
            .END