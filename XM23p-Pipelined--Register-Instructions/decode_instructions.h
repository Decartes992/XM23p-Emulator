#ifndef DECODE_INSTRUCTIONS_H
#define DECODE_INSTRUCTIONS_H

InstructionType getInstructionType(unsigned short instruction);
void extractFields(unsigned short instruction, InstructionType type, unsigned char* rc, unsigned char* wb, unsigned char* src, unsigned char* dst, unsigned char* con, unsigned char* bb);
const char* getInstructionName(InstructionType type);
void printDecodedInstruction(unsigned short IR, unsigned short PC, InstructionType type, unsigned char rc, unsigned char wb, unsigned char src, unsigned char dst, unsigned char con, unsigned char bb);

#endif // DECODE_INSTRUCTIONS_H
