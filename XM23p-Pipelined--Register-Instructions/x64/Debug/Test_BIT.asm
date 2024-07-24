; Test_BIT
;
; Student Name: Iftekhar Rafi
; ID: B00871031
;
; ECED 3403 - Computer Architecture

    org    #1000

Main    ; 1. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #F0,R0        ; R0 <- 0x00F0 (240 in decimal)
    
    ; 2. MOVL: Load immediate value (lower byte) into a register
    movl    #01,R1        ; R1 <- 0x0001 (1 in decimal)
    
    ; 3. BIT: Test bit 0 in R0 (no common bits, should set ZF)
    bit    R1,R0        ; Test bit 0 in R0
    
    ; 4. Halt program execution
    halt
    
    end    Main        ; End of program
