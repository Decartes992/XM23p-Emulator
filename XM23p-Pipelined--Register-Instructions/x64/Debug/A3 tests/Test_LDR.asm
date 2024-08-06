; Test program for LDR and STR instructions

    org    #1000

Main
    ; Setup: Initialize some registers and memory
     movlz    #34,R1     ; R1 <- 0034
     movh     #1200,R1     ; R1 <- 1234 (full 16-bit value)
     movlz    #78,R2     ; R2 <- 5678
     movh     #5600,R2
     movlz    #CD,R3     ; R3 <- ABCD
     movh     #AB00,R3
     movh     #1000,R0

    ; Store values using STR
    str      R1,R0,$4     ; [R0 + 4] <- R1 (Store 1234 at [R0 + 4])
    str      R2,R0,$8     ; [R0 + 8] <- R2 (Store 5678 at [R0 + 8])

    ; Load values using LDR
    ldr      R0,$4,R4     ; R4 <- [R0 + 4] (Load value from [R0 + 4] into R4)
    ldr      R0,$8,R5     ; R5 <- [R0 + 8] (Load value from [R0 + 8] into R5)

    ; More STR examples
    str      R3,R0,$12    ; [R0 + 12] <- R3 (Store ABCD at [R0 + 12])
    str      R2,R0,$-2    ; [R0 - 2] <- R2 (Store 5678 at [R0 - 2])

    ; More LDR examples
    ldr      R0,$-2,R6    ; R6 <- [R0 - 2] (Load value from [R0 - 2] into R6)
    ldr      R0,$12,R7    ; R7 <- [R0 + 12] (Load value from [R0 + 12] into R7)

    halt                  ; Halt the program

    end     Main          ; End of program
