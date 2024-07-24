; Test_SRA
;
; Student Name: Iftekhar Rafi
; ID: B00871031
;
; ECED 3403 - Computer Architecture

    org    #1000

Main    ; 1. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #80,R0        ; R0 <- 0x0080 (128 in decimal, 0b10000000)
    
    ; 2. SRA: Shift R0 right arithmetically (should preserve the sign bit)
    sra    R0              ; R0 >> 1
    
    ; 3. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #01,R1        ; R1 <- 0x0001 (1 in decimal, 0b00000001)
    
    ; 4. MOVH: Load immediate value (higher byte) into R1
    movh    #FF01,R1       ; R1 <- 0xFF01 (-255 in decimal, 0b1111111100000001)
    
    ; 5. SRA: Shift R1 right arithmetically (should preserve the sign bit)
    sra    R1              ; R1 >> 1
    
    ; 6. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #01,R2        ; R2 <- 0x0001 (1 in decimal, 0b00000001)
    
    ; 7. MOVH: Load immediate value (higher byte) into R2
    movh    #7F01,R2       ; R2 <- 0x7F01 (32513 in decimal, 0b0111111100000001)
    
    ; 8. SRA: Shift R2 right arithmetically (should not preserve the sign bit)
    sra    R2              ; R2 >> 1
    
    ; 9. Halt program execution
    halt
    
    end    Main            ; End of program
