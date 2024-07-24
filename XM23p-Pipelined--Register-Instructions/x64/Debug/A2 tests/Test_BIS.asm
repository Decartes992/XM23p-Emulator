; Test_BIS
;
; Student Name: Iftekhar Rafi
; ID: B00871031
;
; ECED 3403 - Computer Architecture

    org    #1000

Main    ; 1. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #00,R0        ; R0 <- 0x0000
    
    ; 2. MOVL: Load immediate value (lower byte) into a register
    movl    #F0,R1        ; R1 <- 0x00F0
    
    ; 3. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #01,R5       ; R5 <- 0x0001 (bit position 0)
    bis     R5,R0         ; R0 <- R0 | (1 << R5) (R0 = 0x0001)
    
    ; 4. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #80,R2        ; R2 <- 0x0080 (128 in decimal)
    
    ; 5. MOVL: Load immediate value (lower byte) into a register
    movl    #01,R3        ; R3 <- 0x0001
    
    ; 6. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #07,R5       ; R5 <- 0x0007 (bit position 7)
    bis     R5,R3         ; R3 <- R3 | (1 << R5) (R3 = 0x0081)
    
    ; 7. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #0F,R5       ; R5 <- 0x000F (bit position 15)
    movl    #00,R4        ; R4 <- 0x0000
    bis     R5,R4         ; R4 <- R4 | (1 << R5) (R4 = 0x8000)
    
    ; 8. Halt program execution
    halt
    
    end    Main        ; End of program
