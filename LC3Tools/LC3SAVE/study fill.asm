    .ORIG x3000
    AND R0,R0,0;;将用到的寄存器清零,r0用来记录要检验的数据
    AND R1,R1,0;;r1只有一位是1
    AND R2,R2,0;;r2储存结果
    AND R3,R3,0;;用来记录已经出现了几个1
    AND R4,R4,0;;用来储存每一位的检验结果，为1则r0这一位是1
    AND R5,R5,0;;用来帮助br跳转
    AND R6,R6,0;;记录循环次数16
    ;;初始化寄存器，r1=1，r6=16
    LDI R0,22
    
    ADD R1,R1,1
    ADD R6,R6,7
    ADD R6,R6,7
    ADD R6,R6,2

LOOP
    AND R5,R5,0;;判断是否连续出现了四个一，即r3=4
    ADD R5,R3,-4
    BRZ ISFNUMBER
    AND R4,R0,R1;;检验r0的每一位是否为1
    BRNP NOTZERO
    BRZ ISZERO
CONTINE;;为下一次循环做准备
    ADD R1,R1,R1
    ADD R6,R6,-1
    BRP LOOP
    ;;运行到此处默认不是f数
    ADD R2,R2,0
    BRNZP BREAK
    
NOTZERO
    ADD R3,R3,1
    BRNZP CONTINE

ISZERO;;若某一位是0，则直接将r3清空
    AND R3,R3,0
    BRNZP CONTINE
    
ISFNUMBER;;是f数
    ADD R2,R2,1
    BRNZP BREAK
    
BREAK
    HALT
.FILL b0011000100000000
.END

