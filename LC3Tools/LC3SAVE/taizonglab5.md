    .ORIG x3000
    
;读入n
    LD R1,N_POS
    LD R2,N48
    INPUT_N
    GETC
    OUT
    ADD R0,R0,R2
    STR R0,R1,#0
    GETC
    OUT
    ADD R0,R0,#-10
    BRz INPUT_N_DIGIT ;是换行则是一位数
    ADD R0,R0,#10
    ADD R0,R0,R2
    ADD R0,R0,#10
    STR R0,R1,#0
    GETC
    OUT ;读入换行

;读入n组数
    INPUT_N_DIGIT
    LD R1,N_POS
    LDR R1,R1,#0
    LD R2,BOOK_POS
    LD R3,N32
    LD R4,N48
    LD R5,P32
    INPUT
;读入第一个数
    GETC
    OUT
    ADD R0,R0,R4
    STR R0,R2,#0
    GETC
    OUT
    ADD R0,R0,R3
    BRz NEXT_1 ;如果是空格则是一位数
    ADD R0,R0,R5
    ADD R0,R0,R4
    ADD R0,R0,#10
    STR R0,R2,#0
    GETC
    OUT ;读入空格
;读入第二个数
    NEXT_1
    ADD R2,R2,#1
    GETC
    OUT
    ADD R0,R0,R4
    STR R0,R2,#0
    GETC
    OUT
    ADD R0,R0,#-10
    BRz NEXT_2 ;如果是空格则是一位数
    ADD R0,R0,#10
    ADD R0,R0,R4
    ADD R0,R0,#10
    STR R0,R2,#0   
    GETC
    OUT ;读入换行
    NEXT_2
    ADD R2,R2,#1
    ADD R1,R1,#-1
    BRp INPUT
    
;预处理,处理2^x和2^n-1
    AND R0,R0,#0
    ADD R0,R0,#1
    LD R1,N_POS
    LDR R1,R1,#0
    LD R2,DIGIT_POS
    LOOP_1 STR R0,R2,#0
    ADD R0,R0,R0
    ADD R2,R2,#1
    ADD R1,R1,#-1
    BRp LOOP_1
    LD R2,JUDGE_POS
    ADD R0,R0,#-1
    STR R0,R2,#0
    LD R2,PAUSE_POS
    AND R3,R3,#0
    STR R3,R2,#0
;主
    LD R6,SP ;栈指针
    AND R1,R1,#0 ;形参m
    AND R0,R0,#0 ;形参now
    JSR DFS
    
    LD R1,ANSWER_POS
    LD R2,N_POS
    LDR R2,R2,#0
    LD R3,P48
    PRINT LDR R0,R1,#0
    ADD R0,R0,#-10
    BRn PRINT_1
    ADD R4,R0,#0
    ADD R0,R3,#1
    TRAP x21
    ADD R0,R4,#0
    BR PRINT_2
    PRINT_1 ADD R0,R0,#10
    PRINT_2 ADD R0,R0,R3
    TRAP x21
    LD R0,P32
    TRAP x21
    ADD R1,R1,#1
    ADD R2,R2,#-1
    BRp PRINT
    HALT
    
    
    
    DFS
    ADD R6,R6,#-1
    STR R7,R6,#0
    ADD R6,R6,#-1
    STR R1,R6,#0 ;now
    ADD R6,R6,#-1
    STR R0,R6,#0 ;m
;判断n==m
    LD R2,N_POS
    LDR R2,R2,#0
    NOT R2,R2
    ADD R2,R2,#1
    ADD R2,R0,R2
    BRn CONTINUE_1;如果为负则继续
;判断now==2^n-1
    LD R3,JUDGE_POS
    LDR R2,R3,#0
    NOT R2,R2
    ADD R2,R2,#1
    ADD R2,R1,R2
    BRnp CONTINUE_2;不为0则跳过
    LD R2,PAUSE_POS
    AND R3,R3,#0
    ADD R3,R3,#1
    STR R3,R2,#0
    BR CONTINUE_2
;向下递归
    CONTINUE_1
;判断是否已经有答案
    LD R3,PAUSE_POS
    LDR R3,R3,#0
    BRp CONTINUE_2
    LD R3,BOOK_POS
    LD R5,ANSWER_POS
    ADD R3,R3,R0
    ADD R3,R3,R0
    LDR R4,R3,#0 ;取出这组的第一个数
    ADD R5,R5,R0
    STR R4,R5,#0
    LD R3,DIGIT_POS
    ADD R3,R3,#-1
    ADD R3,R3,R4
    LDR R3,R3,#0 ;得到次数的2^(x-1)
    ADD R1,R1,R3
    ADD R0,R0,#1
    JSR DFS
    
    LDR R0,R6,#0
    LDR R1,R6,#1
    LD R3,PAUSE_POS
    LDR R3,R3,#0
    BRp CONTINUE_2
    LD R3,BOOK_POS
    LD R5,ANSWER_POS
    ADD R3,R3,R0
    ADD R3,R3,R0
    LDR R4,R3,#1 ;取出这组的第二个数
    ADD R5,R5,R0
    STR R4,R5,#0
    LD R3,DIGIT_POS
    ADD R3,R3,#-1
    ADD R3,R3,R4
    LDR R3,R3,#0 ;得到次数的2^(x-1)
    ADD R1,R1,R3
    ADD R0,R0,#1
    JSR DFS
    CONTINUE_2
    LDR R0,R6,#0
    ADD R6,R6,#1
    LDR R1,R6,#0
    ADD R6,R6,#1
    LDR R7,R6,#0
    ADD R6,R6,#1
    RET

    N32 .FILL x-0020;空格
    N48 .FILL x-0030;0
    P32 .FILL x0020
    P48 .FILL x0030
    N_POS .FILL x3FFF
    JUDGE_POS .FILL x4000
    DIGIT_POS .FILL x4001
    PAUSE_POS .FILL x5000
    ANSWER_POS .FILL x5001
    BOOK_POS .FILL x6000
    SP .FILL xFE00
    .END
;x3FFF 存放n
;x4000 存放2^n-1,用于判断
;x4001 存放2的次方
;x5000 标记是否已经存在答案
;x5001 存放答案
;x6000 存放n组书
;xFE00 sp 栈
;int n;
;dfs(0,0);
;void dfs(int m,int now){
;   if(m==n){
;       if(now==(1<<n)-1)Print();
;       return;
;   }
;   dfs(m+1,now+(1<<(A[2*m]-1)));
;   dfs(m+1,now+(1<<(A[2*m+1]-1)));
;}
