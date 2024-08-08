; Test_CEX_Branch.asm

V1    equ    $10
V2    equ    $7
LR    equ    R5
PC    equ    R7

CODE
    org    #1000
Main
    movlz    V1,R1        ; R1 <- 10
    movlz    V2,R2        ; R2 <- 7
    setcc    Z            ; Set condition code Z (Zero)
    cex     eq,$2,$2      ; Conditional execution: 2 instructions if Z=0, 2 if Z=1
    movlz   #FF,R0
    beq     Subr1         ; Branch to Subr1 if Z=0
    add     R2,R1         ; R1 <- R1 + R2 if Z=0
    beq     Subr2         ; Branch to Subr2 if Z=1
    sub     $2,R1         ; R1 <- R1 - 2 if Z=1
    movls   #02,R3        ; R3 <- 2
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
