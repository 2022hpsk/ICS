# lab1-report

郑浩博 3210105321

## Algorithm Explanation

​	First, we start at the location 0x3000. Then we set R2=0, which will show the result: 1 for yes and 0 for no. Set R1=4, which is a counter to see if test-number is F-word. R0's value is the value at location 0x3100, namely our test number. Now cc =R0.

​	Then we construct a Loop as below , and break when R0 ==0,which means every bits of test number have been tested.

```
0000 010 000001010    ;; if R0 == 0 break  (BRz)
...
0000 111  111110101   ;; return if   (BR)
```

​	Then we judge the highest bit of R0(test-number), by the 2's complement, the highest bit is 1if it's negative.

​	<u>**The core of my algorithm is that if the highest bit is 1,then R1 = R1 - 1; if is 0,then R1 = 4. Bitwise left shift after every judgement until R0(test-numbe) is 0 or R1 is 0**</u>

​	Thus if R0<0, we do as below:

```
0001 001 001 1 11111  ;; R1 = R1 - 1    (ADD)
0001 000 000 0 00 000 ;; R0 = R0 + R0   (ADD)
```

​	otherwise，we do as below:

```
0101 001 001 1 00000  ;;R1 <- 0  (AND)
0001 001 001 1 00100  ;;R1 = R1 + 4  (ADD)

0001 000 000 0 00 000 ;; R0 = R0 + R0   (ADD)
```

​	What's more, if R1 is 0, we need break:

```
0001 001 001 1 00000  ;; R1 = R1 + 0, setcc (ADD)
0000 010 000000010    ;; if R1 == 0 ,break (BR)
0001 000 000 1 00000  ;; R0 = R0 + 0, setcc (ADD)
```

​	Finally, after the loop is stop, we need to check if R1 is 0 or not. If R1 is 0, test number have 4 continuous 1 and is a F-words, we need to set R2 = 1. Otherwise R2 =0:

```
0001 001 001 1 00000  ;; R1 = R1 + 0 , setcc (BRp)
0000 001 000000001    ;; if R1 > 0 ,jump one step (BR)
0001 010 010 1 00001  ;; R2 = R2 + 1 (ADD)
```

## Questions And Answers

​	1.briefly describe the algorithm.

​		answer:The core of my algorithm is that if the highest bit is 1,then R1 = R1 - 1; if is 0,then R1 = 4. Bitwise left shift after every judgement until R0(test-numbe) is 0 or R1 is 0

​	2.why your last line is x3100.

​		answer：To use the LDI instruction. Then we can Load the value at location x3100.

## Code

```
;; Check the F-words
0011 0000 0000 0000   ;;put the code to 0x3000
0101 010 010 1 00000  ;;R2 <- 0 ,(show the result: 1 for yes and 0 for no)
0101 001 001 1 00000  ;;R1 <- 0 ,  (use R1 to judge if it is F-words)  (AND)
0001 001 001 1 00100  ;;R1 = R1 + 4 , (use R1 to judge if it is F-words) (ADD)
1010 000 000001111    ;;R0<-M[x3100], setcc  (put the test number to R0) (LDI)

0000 010 000001010    ;; if R0 == 0 break  (BRz)
0000 100 000000011    ;; if R0 < 0 ,jump three step  (BRn)

0101 001 001 1 00000  ;;R1 <- 0  (AND)
0001 001 001 1 00100  ;;R1 = R1 + 4  (ADD)
0000 111 000000001    ;;jump one step (BR)

0001 001 001 1 11111  ;; R1 = R1 - 1    (ADD)
0001 000 000 0 00 000 ;; R0 = R0 + R0   (ADD)
0001 001 001 1 00000  ;; R1 = R1 + 0, setcc (ADD)
0000 010 000000010    ;; if R1 == 0 ,break (BR)
0001 000 000 1 00000  ;; R0 = R0 + 0, setcc (ADD)
0000 111  111110101   ;; return if   (BR)

0001 001 001 1 00000  ;; R1 = R1 + 0 , setcc (BRp)
0000 001 000000001    ;; if R1 > 0 ,jump one step (BR)
0001 010 010 1 00001  ;; R2 = R2 + 1 (ADD)

1111 0000 0010 0101   ;; HALT (trap 25)
0011 0001 0000 0000   ;;0X3100
```

## 
