; Test_CLRCC.asm
;
; Student Name: Iftekhar Rafi
; ID: B00871031
;
; ECED 3403 - Computer Architecture

    org    #1000

Main    ; 1. CLRCC: Clear condition codes
    clrcc    1,1,0,1,1    ; Clear CF, OF, SF, ZF
    
    ; 2. Halt program execution
    halt
    
    end    Main        ; End of program
