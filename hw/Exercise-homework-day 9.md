# Exercise-homework-day 9

## 9.1 

(a) A device register is a register (or memory location) that is used for data transfer to/from an input/output device. It provides a means of communication between the processor and the input/output device. The processor can poll this register to find out whether it has received an input or it can send an output from/to the specific device that the device register belongs to. In memory mapped I/O device registers are dedicated memory locations for each I/O device. There may be more than one device register (dedicated memory location) for one device.

 (b) A device data register is a device register (a dedicated memory location in memory- mapped I/O) that holds the data that is to be input/output.  ( For example ：KBDR DDR)

 (c) A device status register is a device register (a dedicated memory location in memory- mapped I/O) that indicates the status of the input/output. It allows for the processor to know whether or not input/output of the value in the device data register has occurred. Basically it is an important step to achieve synchronization in an asynchronous I/O system.  ( For example ：KBSR DSR)

## 9.2 

​	Because the processor will know exactly when the data will arrive and when it will be taken away (input and output).It will do input and/or output at regular intervals,and it will be guaranteed that during those intervals the input data is taken by the computer and the output data goes to the output device.

## 9.9 

​	If KBSR[15] is 1, the data contained in the KBDR has not been read by the processor. Thus, if the keyboard hardware does not check the KBSR before writing to the KBDR, user input could be lost.

## 9.10 

​	The display device is an output device and can't write to the DDR.

## 9.14

​	The address control logic controls this. It accesses the KBDR if the address is xFE02.
From our user's view,this access to KBDR looks like a normal load instruction.