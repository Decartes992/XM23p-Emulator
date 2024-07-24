#ifndef PIPELINE_H
#define PIPELINE_H

#include "decode_instructions.h"

// Function prototypes for pipeline execution
void pipelineExecute(unsigned short* PC, int display);
void initialize_execution(unsigned short* PC);
void F0Stage(unsigned short* PC);
void D0Stage(InstructionType* type, unsigned char* rc, unsigned char* wb, unsigned char* src, unsigned char* dst, unsigned char* con, unsigned char* bb, int display, unsigned short* PC, unsigned char* v, unsigned char* c, unsigned char* slp, unsigned char* n, unsigned char* z);
void F1Stage();
void E0Stage(InstructionType type, unsigned char rc, unsigned char wb, unsigned char src, unsigned char dst, unsigned char con, unsigned char bb, unsigned char* v, unsigned char* c, unsigned char* slp, unsigned char* n, unsigned char* z);
void tick();
void StatusPrint(unsigned short* PC, unsigned short IR_prev);

#endif // PIPELINE_H