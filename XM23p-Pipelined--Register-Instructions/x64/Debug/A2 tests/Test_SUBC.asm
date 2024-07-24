; Test_SUBC
;
; Student Name: Iftekhar Rafi
; ID: B00871031
;
; ECED 3403 - Computer Architecture

    org    #1000

Main    ; 1. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #05,R0        ; R0 <- 0x0005
    
    ; 2. MOVL: Load immediate value (lower byte) into a register
    movl    #03,R1        ; R1 <- 0x0003
    
    ; 3. SUBC: Subtract R1 from R0 with carry
    subc    R1,R0        ; R0 <- R0 - R1 - Carry
    ; Check PSW bits after normal subtraction
    
    ; 4. SETCC: Set the carry bit
    setcc    C    ; Set CF
    
    ; 5. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #FF,R2        ; R2 <- 0x00FF (255 in decimal)
    
    ; 6. MOVL: Load immediate value (lower byte) into a register
    movl    #01,R3        ; R3 <- 0x0001
    
    ; 7. SUBC: Subtract R2 from R3 with carry
    subc    R2,R3        ; R3 <- R3 - R2 - Carry
    ; Check PSW bits after subtraction causing borrow
    
    ; 8. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #80,R4        ; R4 <- 0x0080 (-128 in decimal for signed overflow)
    
    ; 9. MOVL: Load immediate value (lower byte) into a register
    movl    #01,R5        ; R5 <- 0x0001
    
    ; 10. SUBC: Subtract R4 from R5 with carry
    subc    R4,R5        ; R5 <- R5 - R4 - Carry
    ; Check PSW bits after subtraction causing overflow
    
    ; 11. Halt program execution
    halt
    
    end    Main        ; End of program
