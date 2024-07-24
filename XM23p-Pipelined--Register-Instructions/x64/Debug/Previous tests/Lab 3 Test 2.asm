; Program to test SETCC and CLRCC instructions
; This program sets the carry bit, performs a DADD instruction, and then clears the carry bit.

	org	#1000
START  
        SETCC   C               ; Set Carry bit
        MOVLZ     $15,R1        ; Load R1 with 0x000F
        MOVLZ     $12,R0        ; Load R0 with 0x000C
        ADDC      R0,R1         ; R1 <--- R1 + R0 + CARRY
        CLRCC   C               ; Clear Carry bit
        SUBC      $1,R1         ; R1 <---- R1 - 1 - CARRY
        SETCC   CV              ; Set Carry and Overflow
        SUBC    R0,R1           ; R1 <---- R1 - R0
        CLRCC   C               ; Clear Carry bit
        SETCC   N
        HALT                    ; Halt the program

        END     START
