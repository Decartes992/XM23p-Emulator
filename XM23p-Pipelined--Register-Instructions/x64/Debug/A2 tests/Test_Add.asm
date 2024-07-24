; Test_ADD
;
; Student Name: Iftekhar Rafi
; ID: B00871031
;
; ECED 3403 - Computer Architecture

    org    #1000

Main    ; 1. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #03,R0        ; R0 <- 0x0003
    
    ; 2. MOVL: Load immediate value (lower byte) into a register
    movl    #02,R1        ; R1 <- 0x0002
    
    ; 3. ADD: Add R0 to R1
    add    R0,R1        ; R1 <- R1 + R0
    
    ; 4. Halt program execution
    halt
    
    end    Main        ; End of program