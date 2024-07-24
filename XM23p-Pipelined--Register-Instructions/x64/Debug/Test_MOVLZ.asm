; Test_MOVLZ.asm
;
; Student Name: Iftekhar Rafi
; ID: B00871031
;
; ECED 3403 - Computer Architecture

    org    #1000

Main    ; 1. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #0F,R0        ; R0 <- 0x000F
    
    ; 2. Halt program execution
    halt
    
    end    Main        ; End of program
