#ifndef PIPELINE_H
#define PIPELINE_H

#include "decode_instructions.h"

// Function prototypes for pipeline execution
void pipelineExecute(unsigned short* PC, int display);
void F0Stage(unsigned short* PC);
void D0Stage(InstructionType* type, unsigned char* rc, unsigned char* wb, unsigned char* src, unsigned char* dst, unsigned char* con, unsigned char* bb);
void F1Stage();
void E0Stage(InstructionType type, unsigned char rc, unsigned char wb, unsigned char src, unsigned char dst, unsigned char con, unsigned char bb);
void tick();

#endif // PIPELINE_H