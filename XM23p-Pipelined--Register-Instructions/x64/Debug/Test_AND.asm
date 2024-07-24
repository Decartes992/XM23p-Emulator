; Test_AND
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
    
    ; 3. AND: AND R0 with R1 (should result in 0x0000)
    and    R1,R0        ; R0 <- R0 & R1
    
    ; 4. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #FF,R2        ; R2 <- 0x00FF
    
    ; 5. MOVL: Load immediate value (lower byte) into a register
    movl    #0F,R3        ; R3 <- 0x000F
    
    ; 6. AND: AND R2 with R3 (should result in 0x000F)
    and    R3,R2        ; R2 <- R2 & R3
    
    ; 7. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #AA,R4        ; R4 <- 0x00AA
    
    ; 8. MOVL: Load immediate value (lower byte) into a register
    movl    #55,R5        ; R5 <- 0x0055
    
    ; 9. AND: AND R4 with R5 (should result in 0x0000)
    and    R5,R4        ; R4 <- R4 & R5
    
    ; 10. Halt program execution
    halt
    
    end    Main        ; End of program
