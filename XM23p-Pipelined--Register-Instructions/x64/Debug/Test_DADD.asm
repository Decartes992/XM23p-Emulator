; Test_DADD_Carry
;
; Student Name: Iftekhar Rafi
; ID: B00871031
;
; ECED 3403 - Computer Architecture

    org    #1000

Main    ; 1. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #99,R0        ; R0 <- 0x0099
    
    ; 2. MOVL: Load immediate value (lower byte) into a register
    movl    #99,R1        ; R1 <- 0x0099
    
    ; 3. MOVH: Load immediate value (higher byte) into R0 and R1
    movh    #9900,R0      ; R0 <- 0x9999
    movh    #9900,R1      ; R1 <- 0x9999
    
    ; 4. DADD: Decimal Add R1 to R0 (should set carry bit)
    dadd    R1,R0         ; R0 <- R0 + R1
    ; Check PSW bits after DADD (Decimal addition with carry)
    
    ; 5. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #45,R2       ; R2 <- 0x0045
    
    ; 6. MOVL: Load immediate value (lower byte) into a register
    movl    #55,R3        ; R3 <- 0x0055
    
    ; 7. MOVH: Load immediate value (higher byte) into R2 and R3
    movh    #4500,R2      ; R2 <- 0x4545
    movh    #5500,R3      ; R3 <- 0x5555
    
    ; 8. DADD: Decimal Add R3 to R2 using the carry bit set by previous DADD
    dadd    R3,R2         ; R2 <- R2 + R3 + Carry
    ; Check PSW bits after DADD (Decimal addition with carry from previous DADD)
    
    ; 9. Halt program execution
    halt
    
    end    Main        ; End of program
