; Test_SUB
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
    
    ; 3. SUB: Subtract R1 from R0 (Normal subtraction)
    sub    R1,R0        ; R0 <- R0 - R1
    ; Check PSW bits after normal subtraction
    
    ; 4. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #FF,R2        ; R2 <- 0x00FF (255 in decimal)
    
    ; 5. MOVL: Load immediate value (lower byte) into a register
    movl    #01,R3        ; R3 <- 0x0001
    
    ; 6. SUB: Subtract R3 from R2 (Subtraction causing borrow)
    sub    R2,R3        ; R3 <- R3 - R2
    ; Check PSW bits after subtraction causing borrow
    
    ; 7. Halt program execution
    halt
    
    end    Main        ; End of program
