; Test_RRC
;
; Student Name: Iftekhar Rafi
; ID: B00871031
;
; ECED 3403 - Computer Architecture

    org    #1000

Main
    ; 1. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #80,R0        ; R0 <- 0x0080
    
    ; 2. RRC: Rotate right through carry
    rrc     R0             ; R0 <- R0 rotated right through carry
    
    ; 3. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #01,R1        ; R1 <- 0x0001
    
    ; 4. MOVH: Load immediate value (higher byte) into a register
    movh     #FF01,R1      ; R1 <- 0xFF01
    
    ; 5. RRC: Rotate right through carry
    rrc     R1             ; R1 <- R1 rotated right through carry
    
    ; 6. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #01,R2        ; R2 <- 0x0001
    
    ; 7. MOVH: Load immediate value (higher byte) into a register
    movh     #7F01,R2      ; R2 <- 0x7F01
    
    ; 8. RRC: Rotate right through carry
    rrc     R2             ; R2 <- R2 rotated right through carry
    
    ; 9. Halt program execution
    halt
    
    end    Main            ; End of program
