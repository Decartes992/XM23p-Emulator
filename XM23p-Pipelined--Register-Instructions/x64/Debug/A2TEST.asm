; XM23P Assembly Code Example
;
; ECED 3403
; All 22 Instructions
;

	org	#1000

Main	; 1. MOVLZ: Load immediate value (lower byte) into a register
	movlz	#0F,R0		; R0 <- 0x000F
	
	; 2. MOVL: Load immediate value (lower byte) into a register
	movl	#1A,R1		; R1 <- 0x001A
	
	; 3. MOVLS: Load immediate value (lower byte) into a register (shifted left)
	movls	#2B,R2		; R2 <- 0x2B00
	
	; 4. MOVH: Load immediate value (higher byte) into a register
	movh	#3C00,R3	; R3 <- 0x3C00
	
	; 5. ADD: Add SRC/CON to DST
	add	R0,R1		; R1 <- R1 + R0
	
	; 6. ADDC: Add SRC/CON + Carry to DST
	addc	R0,R2		; R2 <- R2 + R0 + Carry
	
	; 7. SUB: Subtract SRC/CON from DST
	sub	R1,R0		; R0 <- R0 - R1
	
	; 8. SUBC: Subtract SRC/CON + Carry from DST
	subc	R2,R1		; R1 <- R1 - R2 - Carry
	
	; 9. DADD: Decimal Add SRC/CON to DST
	dadd	$4,R3		; R3 <- R3 + $4 (Decimal add)
	
	; 10. CMP: Compare DST with SRC/CON
	cmp	#1,R0		; Compare R0 with #1
	
	; 11. XOR: XOR SRC/CON with DST
	xor	#2,R1		; R1 <- R1 ^ #2
	
	; 12. AND: AND SRC/CON with DST
	and	#0,R2		; R2 <- R2 & #0
	
	; 13. OR: OR SRC/CON with DST
	or	#8,R3		; R3 <- R3 | #8
	
	; 14. BIT: Test bits (AND) of SRC/CON with DST
	bit	#0,R0		; Test bits in R0 with #0
	
	; 15. BIC: Clear bits (AND NOT) of SRC/CON in DST
	bic	#1,R1		; R1 <- R1 & ~#1
	
	; 16. BIS: Set bits (OR) of SRC/CON in DST
	bis	#2,R2		; R2 <- R2 | #2
	
	; 17. MOV: Move SRC to DST
	mov	R1,R0		; R0 <- R1
	
	; 18. SWAP: Swap bytes in DST
	swap	R0,R2		; Swap bytes of R0 and R2
	
	; 19. SRA: Shift right arithmetic DST
	sra	R1		; R1 <- R1 >> 1 (arithmetic)
	
	; 20. RRC: Rotate right through carry DST
	rrc	R2		; R2 <- Rotate R2 right through carry
	
	; 21. SWPB: Swap bytes in DST (swap the bytes within the word)
	swpb	R3		; R3 <- Swap bytes within the word of R3
	
	; 22. SXT: Sign extend DST (extend byte to word with sign)
	sxt	R0		; R0 <- Sign extend R0

Done	bra	Done		; Infinite loop to end program

	end	Main		; End of program
