; Test_OR
;
; Student Name: Iftekhar Rafi
; ID: B00871031
;
; ECED 3403 - Computer Architecture

    org    #1000

Main    ; 1. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #00,R0        ; R0 <- 0x0000
    
    ; 2. MOVL: Load immediate value (lower byte) into a register
    movl    #00,R1        ; R1 <- 0x0000
    
    ; 3. OR: OR R1 with R0 (should set ZF since the result is zero)
    or    R1,R0        ; R0 <- R0 | R1
    ; Check PSW bits after OR
    
    ; 4. MOVH: Load immediate value (higher byte) into a register
    movh    #8000,R2        ; R2 <- 0x8000
    
    ; 5. OR: OR R2 with R0 (should set SF since the result has a high bit set)
    or    R2,R0        ; R0 <- R0 | R2
    ; Check PSW bits after OR
    
    ; 6. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #7F,R3        ; R3 <- 0x007F
    
    ; 7. OR: OR R3 with R0 (should keep SF set)
    or    R3,R0        ; R0 <- R0 | R3
    ; Check PSW bits after OR
    
    ; 8. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #00,R4        ; R4 <- 0x0000
    
    ; 9. OR: OR R4 with R0 (should keep SF set)
    or    R4,R0        ; R0 <- R0 | R4
    ; Check PSW bits after OR
    
    ; 10. Halt program execution
    halt
    
    end    Main        ; End of program
