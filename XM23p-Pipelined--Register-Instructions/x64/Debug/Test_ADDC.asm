; Test_ADDC.asm
;
; Student Name: Iftekhar Rafi
; ID: B00871031
;
; ECED 3403 - Computer Architecture

    org    #1000

Main    ; 1. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #FF,R0        ; R0 <- 0x00FF
    
    ; 2. MOVH: Load immediate value (higher byte) into a register
    movh    #FF00,R0        ; R0 <- 0xFFFF
    

    ; 3. MOVL: Load immediate value (lower byte) into a register
    movl    #01,R1        ; R1 <- 0x0001
    
    ; 4. ADD: Add R0 to R1 to set the carry bit
    add    R0,R1        ; R1 <- R1 + R0
    
    ; 5. ADDC: Add with carry R0 to R2
    addc    R1,R2        ; R2 <- R2 + R1 + Carry

    
    ; 4. Halt program execution
    halt
    
    end    Main        ; End of program
