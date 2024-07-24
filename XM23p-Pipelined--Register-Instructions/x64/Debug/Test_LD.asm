; Test_LD
;
; Student Name: Iftekhar Rafi
; ID: B00871031
;
; ECED 3403 - Computer Architecture

    org    #1000

Main    ; 1. Store immediate value into memory
    movlz   #12,R0        ; Load R0 with 0x0012 (address in memory)
    movlz   #78,R1        ; Load R1 with 0x0078 (data to store)
    str     R1,R0        ; Store R1 at the address in R0 (DMEM[0x0012] <- 0x0078)

    ; 2. Load value from memory into register
    movlz   #12,R2        ; Load R2 with 0x0012 (address in memory)
    ld      R3,R2        ; Load R3 with the value at the address in R2 (R3 <- DMEM[0x0012])

    ; 3. Halt program execution
    halt
    
    end    Main        ; End of program
