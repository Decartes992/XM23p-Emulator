; Test_LD
;
; Student Name: Iftekhar Rafi
; ID: B00871031
;
; ECED 3403 - Computer Architecture

    org    #1000

Main    ; 1. Setup: Initialize memory with a known value
    movlz    #20,R0      ; R0 <- 0x0020
    movl     #1234,R1    ; R1 <- 0x1234 (dummy value)
    movh     #1234,R1
    movl     #1,R2       ; R2 <- 0x0001 (dummy value)
    movl     #1,R3       ; R3 <- 0x0001 (dummy value)
    
    ; 2. Store known value to memory (at DMEM[0x0020])
    st        R1,R0      ; DMEM[R0] <- R1
    
    ; 3. Clear R1 to ensure we load the correct value
    ;movl      #0,R1      ; Clear R1
    
    ; 4. Test: Load the value from memory into R1
    ld        R0,R1      ; R1 <- DMEM[R0]

    ; 5. Halt: Stop the program
    halt

    end    Main        ; End of program
