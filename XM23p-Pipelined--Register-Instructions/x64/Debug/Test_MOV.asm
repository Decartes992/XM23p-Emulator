; Test_MOV.asm
;
; Student Name: Iftekhar Rafi
; ID: B00871031
;
; ECED 3403 - Computer Architecture

    org    #1000

Main    ; 1. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #AA,R0        ; R0 <- 0x00AA
    
    ; 2. MOV: Move R0 to R1
    mov    R0,R1        ; R1 <- R0
    
    ; 3. Halt program execution
    halt
    
    end    Main        ; End of program
