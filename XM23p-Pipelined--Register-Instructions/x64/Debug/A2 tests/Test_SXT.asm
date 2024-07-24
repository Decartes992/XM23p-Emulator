; Test_SXT
;
; Student Name: Iftekhar Rafi
; ID: B00871031
;
; ECED 3403 - Computer Architecture

    org    #1000

Main    ; 1. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #80,R0        ; R0 <- 0x0080 (-128 in decimal, signed byte)
    
    ; 2. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #7F,R1        ; R1 <- 0x007F (127 in decimal, signed byte)
    
    ; 3. SXT: Sign-extend byte to word
    sxt    R0         ; R0 <- Sign-extend R0 (R0 = 0xFF80)
    
    ; 4. SXT: Sign-extend byte to word
    sxt    R1         ; R1 <- Sign-extend R1 (R1 = 0x007F)
    
    ; 5. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #00,R2        ; R2 <- 0x0000 (0 in decimal, signed byte)
    
    ; 6. SXT: Sign-extend byte to word
    sxt    R2         ; R2 <- Sign-extend R2 (R2 = 0x0000)
    
    ; 7. Halt program execution
    halt
    
    end    Main        ; End of program
