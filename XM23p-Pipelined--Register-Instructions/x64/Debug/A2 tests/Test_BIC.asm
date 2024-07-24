; Test_BIC
;
; Student Name: Iftekhar Rafi
; ID: B00871031
;
; ECED 3403 - Computer Architecture

    org    #1000

Main    ; 1. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #FF,R0        ; R0 <- 0x00FF
    
    ; 2. MOVL: Load immediate value (lower byte) into a register
    movl    #F0,R1        ; R1 <- 0x00F0
    
    ; 3. BIC: Clear bits of R0 in R1 (should clear lower nibble)
    bic    R1,R0        ; R0 <- R0 & ~R1
    
    ; 4. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #0F,R2        ; R2 <- 0x000F
    
    ; 5. MOVL: Load immediate value (lower byte) into a register
    movl    #F0,R3        ; R3 <- 0x00F0
    
    ; 6. BIC: Clear bits of R2 in R3 (should clear upper nibble)
    bic    R2,R3        ; R3 <- R3 & ~R2
    
    ; 7. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #80,R4        ; R4 <- 0x0080
    
    ; 8. BIC: Clear bits of R4 in R0 (should clear bit 7)
    bic    R4,R0        ; R0 <- R0 & ~R4
    
    ; 9. Halt program execution
    halt
    
    end    Main        ; End of program
