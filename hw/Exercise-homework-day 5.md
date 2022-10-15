# Exercise-homework-day 5

## 5.15 

R1 = 0x3121 = 0011 0001 0010 0001

R2 = Mem[0x3122] = 0x4566 = 0100 0101 0110 0110

R3 : =Mem[Mem[0x3123]] = 0xabcd = 1010 1011 1100 1101

R4: =Mem[R2 + 0x1] = 0xabcd = 1010 1011 1100 1101

## 5.16 

a. PC_relative mode : it has 9 bits signed offset.

b. Indirect mode : we can load value from any address by indirect mode

c. Base + offset mode: because we want to load an array of sequential addresses

## 5.37 

LDI :  Memory, MDR, MAR, IR, PC, Reg File, the SEXT unit connected to IR[8:0], ADDR2MUX, ADDR1MUX , alongwith the ADDER they connect to, and MARMUX and GateMARMUX implement the LDI instruction, alongwith NZP and the logic .

(More than LEA : Memory, MDR, MAR)

## 5.39 

LEA : IR, PC, Reg File, the SEXT unit connected to IR[8:0], ADDR2MUX, ADDR1MUX , alongwith the ADDER they connect to, and MARMUX and GateMARMUX implement the LEA instruction, alongwith NZP and the logic .

## 5.50 

The Conditional Branch : put the result back to the PC

The Load Effective Address : put the result directly to the R7 directly.

The LD Instruction : put the result to MAR to find the value at that location.

## 6.9 

x3100 	0010	000	0	0101	1010 (   LD R0, x5A(Z) )

x3101 	0010	001	0	0110	0100 (  LD R1, #100  )

x3102 	1111	0000	0010	0001 ( LOOP TRAP x21  )

x3103 	0001	001 	001	1	11111	(	ADD R1, R1, #-1 ) 

x3104 	0000	0011	1111	1101	(	BRp LOOP	) 

x3105 	1111	0000	0010	0101	(	TRAP x25	)



## 6.10

x3100  0101 000 010  0 00001 (AND R0, R2, #1)

x3101  0000 101 000001110 (BRnp ODD)

x3102  0000 010 000001110 (BRz EVEN)

If R2 is odd,it will branch to x3110, else it will branch to x3111.

