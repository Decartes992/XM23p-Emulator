; Test_MOVL.asm
;
; Student Name: Iftekhar Rafi
; ID: B00871031
;
; ECED 3403 - Computer Architecture

    org    #1000

Main    ; 1. MOVL: Load immediate value (lower byte) into a register
    movl    #1A,R1        ; R1 <- 0x001A
    
    ; 2. Halt program execution
    halt
    
    end    Main        ; End of program
