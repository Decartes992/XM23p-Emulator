#ifndef DECODE_INSTRUCTIONS_H
#define DECODE_INSTRUCTIONS_H

#include "loader.h"

// Declare an enum for instruction types
typedef enum {
    ADD, ADDC, SUB, SUBC, DADD, CMP, XOR, AND, OR, BIT, BIC, BIS, MOV, SWAP, SRA, RRC, SWPB, SXT, MOVLZ, MOVL, MOVLS, MOVH, SETCC, CLRCC, INVALID
} InstructionType;

// Declare functions for getting the type of an instruction, extracting fields from an instruction, and getting the name of an instruction type
InstructionType getInstructionType(unsigned short instruction);
void extractFields(unsigned short instruction, InstructionType type, unsigned char* rc, unsigned char* wb, unsigned char* src, unsigned char* dst, unsigned char* con, unsigned char* bb, unsigned char* v, unsigned char* c, unsigned char* slp, unsigned char* n, unsigned char* z);
const char* getInstructionName(InstructionType type);
void printDecodedInstruction( unsigned short PC, InstructionType type, unsigned char rc, unsigned char wb, unsigned char src, unsigned char dst, unsigned char con, unsigned char bb);
unsigned short getOperand(unsigned char rc, unsigned char src);
#endif // DECODE_INSTRUCTIONS_H
