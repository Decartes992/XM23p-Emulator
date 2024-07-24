; Test_MOVLS.asm
;
; Student Name: Iftekhar Rafi
; ID: B00871031
;
; ECED 3403 - Computer Architecture

    org    #1000

Main    ; 1. MOVLS: Load immediate value (lower byte) into a register (shifted left)
    movls    #2B,R2        ; R2 <- 0x2B00
    
    ; 2. Halt program execution
    halt
    
    end    Main        ; End of program
