; Test_SETCC.asm
;
; Student Name: Iftekhar Rafi
; ID: B00871031
;
; ECED 3403 - Computer Architecture

    org    #1000

Main    ; 1. SETCC: Set condition codes
    setcc    1,1,0,1,1    ; Set CF, OF, SF, ZF
    
    ; 2. Halt program execution
    halt
    
    end    Main        ; End of program
