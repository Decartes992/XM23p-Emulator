/*
Name: Iftekhar Rafi
ID: B00871031
Course: ECED 3403 Computer Architecture
Instructor: Larry Hughes

File Name: memory_instructions.h
File Purpose: This file contains the declarations of the memory instructions and helper functions for the XM23P processor.
*/

#ifndef MEMORY_INSTRUCTIONS_H
#define MEMORY_INSTRUCTIONS_H

#include <stdint.h>


// Function prototypes for executing memory instructions
void execute_ldr(unsigned char src, unsigned char dst, short offset);
void execute_str(unsigned char src, unsigned char dst, short offset);
void execute_ld();
void execute_st();

// Helper function prototypes
void adjustAddressWithOffset(unsigned char base_reg, short offset);
void loadFromEffectiveAddress(unsigned char dst, unsigned char wb);
void storeToEffectiveAddress(unsigned char src, unsigned char wb);
void handlePRPOAdjustment(unsigned char reg, unsigned char prpo, unsigned char inc, unsigned char dec, unsigned char wb);
void storeToMemory(unsigned short address, unsigned short value, unsigned char wb);
unsigned short loadFromMemory(unsigned short address, unsigned char wb);

// Memory access function prototypes
void memory_write_byte(unsigned short address, unsigned char value);
void memory_write_word(unsigned short address, unsigned short value);
unsigned char memory_read_byte(unsigned short address);
unsigned short memory_read_word(unsigned short address);

// Sign extension function prototype
short SignExt(short offset, int msb);

#endif // MEMORY_INSTRUCTIONS_H
