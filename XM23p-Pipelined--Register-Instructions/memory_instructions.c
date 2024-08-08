/*
Name: Iftekhar Rafi
ID: B00871031
Course: ECED 3403 Computer Architecture
Instructor: Larry Hughes

File Name: memory_instructions.c
File Purpose: This file contains the implementation of the memory instructions
*/

#include "loader.h"
#include "memory_instructions.h"




// Function to execute the LD instruction
void execute_ld() {
    handlePRPOAdjustment(PRE, src, prpo, inc, dec, wb); // Adjust the address after operation if needed

    reg_file[dst] = loadFromMemory(reg_file[src], wb);
    handlePRPOAdjustment(POST, src, prpo, inc, dec, wb); // Adjust the address after operation if needed

}

// Function to execute the ST instruction
void execute_st(){
    handlePRPOAdjustment(PRE, dst, prpo, inc, dec, wb); // Adjust the address after operation if needed
    storeToMemory(reg_file[dst], reg_file[src], wb);
    handlePRPOAdjustment(POST, dst, prpo, inc, dec, wb); // Adjust the address after operation if needed
}

// LDR - Load register with value from memory with an offset
void execute_ldr(unsigned char src, unsigned char dst, short offset) {
    short effective_offset = SignExt(offset, 6);
    adjustAddressWithOffset(src, effective_offset);
    reg_file[dst] = loadFromMemory(DMAR, wb);
}

// STR - Store register value into memory with an offset
void execute_str(unsigned char src, unsigned char dst, short offset) {
    short effective_offset = SignExt(offset, 6);
    adjustAddressWithOffset(dst, effective_offset);
    storeToMemory(DMAR, reg_file[src], wb);
}

// Helper function to adjust the address with an offset
void adjustAddressWithOffset(unsigned char base_reg, short offset) {
    DMAR = (reg_file[base_reg] + offset/2);
    DCTRL = (wb == WRITE) ? WRITE : READ;
}

// Helper function to store a value to memory
void storeToMemory(unsigned short address, unsigned short value, unsigned char wb) {
    if (wb == WORD) {
        DMEM[address / 2] = value; // Store word
    }
    else {
        unsigned short wordVal = DMEM[address / 2];
        if (address % 2 == 0) {
            wordVal = (wordVal & 0xFF00) | (value & 0x00FF); // Store low byte
        }
        else {
            wordVal = (wordVal & 0x00FF) | ((value & 0x00FF) << 8); // Store high byte
        }
        DMEM[address / 2] = wordVal;
    }
}
// Helper function to load a value from memory
unsigned short loadFromMemory(unsigned short address, unsigned char wb) {
    if (wb == WORD) {
        return DMEM[address / 2]; // Load word
        reg_file[dst] = DMEM[DMAR / 2]; // dst shouldnt change
    }
    else {
        unsigned short wordVal = DMEM[address / 2];
        return (address % 2 == 0) ? (wordVal & 0x00FF) : ((wordVal & 0xFF00) >> 8); // Load byte
        reg_file[dst] = DMEM[DMAR / 2] & 0x00FF; // dst shouldnt change
    }
}


// Helper function to handle post-increment/decrement adjustments
void handlePRPOAdjustment(int PRPO, unsigned char reg, unsigned char prpo, unsigned char inc, unsigned char dec, unsigned char wb) {

    if (prpo == PRPO) {
        if (inc == SET) {
            reg_file[reg] += (wb == WORD) ? 2 : 1;
        }
        if (dec == SET) {
            reg_file[reg] -= (wb == WORD) ? 2 : 1;
        }
    }
}

short SignExt(short offset, int msb) {
    /*
    Sign extension function to handle sign extensions
    - it extends the sign of the offset if the msb is set
    - it returns the offset
    */

    if ((offset >> msb) & 0x01) {
        offset |= ((0xFFFF) << msb); // Extend the sign if the msb is set
    }

    return offset << 1;
}

