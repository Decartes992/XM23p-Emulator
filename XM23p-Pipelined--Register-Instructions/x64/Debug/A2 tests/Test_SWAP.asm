; Test_SWAP
;
; Student Name: Iftekhar Rafi
; ID: B00871031
;
; ECED 3403 - Computer Architecture

    org    #1000

Main    ; 1. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #12,R0        ; R0 <- 0x0012 (18 in decimal)
    
    ; 2. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #34,R1        ; R1 <- 0x0022 (52 in decimal)
    
    ; 3. SWAP: Swap values between R0 and R1
    swap    R0,R1         ; R0 <-> R1
    
    ; 4. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #56,R2        ; R2 <- 0x0038 (86 in decimal)
    
    ; 5. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #78,R3        ; R3 <- 0x004E (126 in decimal)
    
    ; 6. SWAP: Swap values between R2 and R3
    swap    R2,R3         ; R2 <-> R3
    
    ; 7. Halt program execution
    halt
    
    end    Main        ; End of program
