; Test_CMP
;
; Student Name: Iftekhar Rafi
; ID: B00871031
;
; ECED 3403 - Computer Architecture

    org    #1000

Main    ; 1. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #05,R0        ; R0 <- 0x0005
    
    ; 2. MOVL: Load immediate value (lower byte) into a register
    movl    #05,R1        ; R1 <- 0x0005
    
    ; 3. CMP: Compare R0 with R1 (should be equal, Z flag set)
    cmp    R1,R0        ; Compare R0 with R1
    
    ; 4. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #FF,R2        ; R2 <- 0x00FF (255 in decimal)
    
    ; 5. MOVL: Load immediate value (lower byte) into a register
    movl    #01,R3        ; R3 <- 0x0001
    
    ; 6. CMP: Compare R2 with R3 (R2 > R3, N flag set)
    cmp    R2,R3        ; Compare R2 with R3
    
    ; 7. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #01,R4        ; R4 <- 0x0001
    
    ; 8. MOVL: Load immediate value (lower byte) into a register
    movl    #02,R5        ; R5 <- 0x0002
    
    ; 9. CMP: Compare R4 with R5 (R4 < R5, no flags set)
    cmp    R4,R5        ; Compare R4 with R5
    
    ; 10. Halt program execution
    halt
    
    end    Main        ; End of program
