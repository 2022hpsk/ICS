# Exercise-homework-day 6

## 6.3

x3000	1010000000001110	(LDI R0, A)
x3001	1010001000001110	(LDI R1, B)
x3002	0101010010100000	(AND R2, R2,#0)
x3003	0001010010100001	(ADD R2, R2,#1)
x3004	0001001001111111	(L	ADD R1, R1,#-1)
x3005	0000100000000010	(BRn S)
x3006	0001010010000010	(ADD R2, R2, R2)
x3007	0000111111111100	(BRnzp L)
x3008	0001001010100000	(S ADD R1, R2, #0)
x3009	1001000000111111	(N0T R0, R0)
x300a	1001001001111111	(N0T R1, R1)
x300b	0101000000000001	(AND R0, R0, R1)
x300c	1001000000111111	(N0T R0, R0)
x300d	1011000000000001	(STI R0, A)
x300e	1111000000100101	(TRAP x25)
x300e	0100000000000001	(A .FILL x4001)
x300f	0100000000000000	(B .FILL x4000)

The core of algorithm is that Make A into only one bit is 1 corresponding with the machine. And the OR(A,B), namely  NOT ( AND(not A, not B) ) 

## 7.4

Test : x301F

FINISH :x3027

SAVE3 : x3029

SAVE2 : x302A

## 7.18

(a) LDR R3, R1, #0

(b) NOT R3, R3

(c) ADD R3, R3, #1

## 7.20

Difference: program a will store x0015 into location x4000 at run time, but program b will store x0015 when the module is loaded into memory.
