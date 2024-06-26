#ifndef EXECUTE_INSTRUCTIONS_H
#define EXECUTE_INSTRUCTIONS_H

#include "decode_instructions.h"

// Function prototype for executing an instruction
void executeInstruction(InstructionType type, unsigned char rc, unsigned char wb, unsigned char src, unsigned char dst, unsigned char con, unsigned char bb);

#endif // EXECUTE_INSTRUCTIONS_H
