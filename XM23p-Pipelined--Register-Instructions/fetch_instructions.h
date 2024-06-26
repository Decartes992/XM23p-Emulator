#ifndef FETCH_INSTRUCTIONS_H
#define FETCH_INSTRUCTIONS_H

// Function prototypes
void F0Stage(unsigned short* PC);
void D0Stage(InstructionType* type, unsigned char* rc, unsigned char* wb, unsigned char* src, unsigned char* dst, unsigned char* con, unsigned char* bb);
void F1Stage();
void E0Stage(InstructionType type, unsigned char rc, unsigned char wb, unsigned char src, unsigned char dst, unsigned char con, unsigned char bb);

#endif // FETCH_INSTRUCTIONS_H
