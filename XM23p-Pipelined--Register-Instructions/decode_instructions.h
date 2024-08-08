// decode_instructions.h

#ifndef DECODE_INSTRUCTIONS_H
#define DECODE_INSTRUCTIONS_H


// Define the instruction types
typedef enum {
    ADD, ADDC, SUB, SUBC, DADD, CMP, XOR, AND, OR,
    BIT, BIC, BIS, MOV, SWAP, SRA, RRC, SWPB, SXT,
    MOVL, MOVLZ, MOVLS, MOVH, SETCC, CLRCC, LD, LDR,
    ST, STR, BL, BEQ, BNE, BC, BNC, BN, BGE, BLT,BRA, CEX,   
    INVALID
} InstructionType;

// Function prototypes
InstructionType getInstructionType(unsigned short instruction);
void extractFields(unsigned short instruction, InstructionType type);
const char* getInstructionName(InstructionType type);
void printDecodedInstruction(unsigned short PC, InstructionType type);
unsigned short getOperand(unsigned char rc, unsigned char src);

#endif // DECODE_INSTRUCTIONS_H
