; Test_CEX_Branch.asm

V1    equ    $10
V2    equ    $7
LR    equ    R5
PC    equ    R7

CODE
    org    #1000
Main
    LD #2000,R0   ; Load the memory address 0x2000 into R0
    ST R2,R0        ; Store the address from R0 into R2
    LD @R2,R1       ; Indirectly load the value from the address in R2 into R1
    bra     Done          ; Branch to Done

Subr1
    movls    #0F,R4       ; R4 <- 15
    mov     LR,PC         ; Return from Subr1

Subr2
    movls    #0A,R4       ; R4 <- 10
    mov     LR,PC         ; Return from Subr2

Done
    bra     Done          ; Infinite loop
    end     Main
