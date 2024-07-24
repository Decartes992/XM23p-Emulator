; Test_SWPB
;
; Student Name: Iftekhar Rafi
; ID: B00871031
;
; ECED 3403 - Computer Architecture

    org    #1000

Main
    ; 1. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #12,R0        ; R0 <- 0x0012
    
    ; 2. MOVH: Load immediate value (higher byte) into a register
    movh    #3400,R0       ; R0 <- 0x3412
    
    ; 3. SWPB: Swap bytes in R0
    swpb    R0             ; R0 <- 0x1234
    
    ; 4. MOVLZ: Load immediate value (lower byte) into a register
    movlz    #56,R1        ; R1 <- 0x0056
    
    ; 5. MOVH: Load immediate value (higher byte) into a register
    movh    #7800,R1       ; R1 <- 0x7856
    
    ; 6. SWPB: Swap bytes in R1
    swpb    R1             ; R1 <- 0x3878
    
    ; 7. Halt program execution
    halt
    
    end    Main            ; End of program
