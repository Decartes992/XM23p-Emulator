; Program to test SETCC and CLRCC instructions
; This program sets the carry bit, performs a DADD instruction, and then clears the carry bit.

	org	#1000
START  
        CLRCC   VNZC
        SETCC   C               ; Set Carry bit
        CLRCC   C               ; Clear Carry bit
        SETCC   V               ; Set Overflow bit
        CLRCC   V               ; Clear Overflow bit
        SETCC   N               ; Set Negative bit
        CLRCC   N               ; Clear Negative bit
        SETCC   Z               ; Set Zero bit
        CLRCC   Z               ; Clear Zero bit
        SETCC   ZNVC            ; Set all bits
        CLRCC   ZNVC            ; Clear all bits
        HALT                    ; Halt the program

        END     START
