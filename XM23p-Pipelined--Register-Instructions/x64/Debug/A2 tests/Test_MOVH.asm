; Test_MOVH.asm
;
; Student Name: Iftekhar Rafi
; ID: B00871031
;
; ECED 3403 - Computer Architecture

    org    #1000

Main    ; 1. MOVH: Load immediate value (higher byte) into a register
    movh    #3C00,R3        ; R3 <- 0x3C00
    
    ; 2. Halt program execution
    halt
    
    end    Main        ; End of program
