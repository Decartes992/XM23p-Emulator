LR    EQU   R5
PC    EQU   R7

        ORG   #1000

CoR1
        MOVLZ   #0,R1
        BL      CoR2
        ADD     #1,R1
        SWAP    LR,PC

CoR1_X
        BRA     CoR1_X

        ORG   #2000

CoR2
        ADD     #1,R1
        SWAP    LR,PC
        ADD     #2,R1
        SWAP    LR,PC

CoR2_X
        BRA     CoR2_X

        END   CoR1
