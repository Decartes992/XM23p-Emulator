; Test_XOR
;
; Student Name: Iftekhar Rafi
; ID: B00871031
;
; ECED 3403 - Computer Architecture

    org    #1000

Main    ; 1. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #0F,R0        ; R0 <- 0x000F
    
    ; 2. MOVL: Load immediate value (lower byte) into a register
    movl    #F0,R1        ; R1 <- 0x00F0
    
    ; 3. XOR: XOR R0 and R1 (should result in 0x00FF, no flags set)
    xor    R0,R1        ; R1 <- R0 ^ R1
    
    ; 4. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #AA,R2       ; R2 <- 0x00AA
    
    ; 5. XOR: XOR R2 with itself (should result in 0x0000, Z flag set)
    xor    R2,R2        ; R2 <- R2 ^ R2
    
    ; 6. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #55,R3       ; R3 <- 0x0055
    
    ; 7. MOVL: Load immediate value (lower byte) into a register
    movl    #AA,R4       ; R4 <- 0x00AA
    
    ; 8. XOR: XOR R3 with R4 (should result in 0x00FF, no flags set)
    xor    R3,R4        ; R4 <- R3 ^ R4
    
    ; 9. Halt program execution
    halt
    
    end    Main        ; End of program
