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

    if (prpo != POST) { // Pre-increment/decrement
        if (inc == SET) {
            reg_file[src] += (wb == WORD) ? 2 : 1;
        }
        if (dec == SET) {
            reg_file[src] -= (wb == WORD) ? 2 : 1;
        }
    }
    reg_file[dst] = loadFromMemory(reg_file[src], wb);
    handlePRPOAdjustment(src, prpo, inc, dec, wb); // Adjust the address after operation if needed
}

// Function to execute the ST instruction
void execute_st(){

    if (prpo != POST) { // Pre-increment/decrement
        if (inc == SET) {
            reg_file[dst] += (wb == WORD) ? 2 : 1;
        }
        if (dec == SET) {
            reg_file[dst] -= (wb == WORD) ? 2 : 1;
        }
    }
    storeToMemory(reg_file[dst], reg_file[src], wb);
    handlePRPOAdjustment(dst, prpo, inc, dec, wb); // Adjust the address after operation if needed
}

// LDR - Load register with value from memory with an offset
void execute_ldr(unsigned char src, unsigned char dst, short offset) {
    short effective_offset = SignExt(offset, 6);
    adjustAddressWithOffset(src, effective_offset);
    reg_file[dst] = loadFromMemory(EA, wb);
}

// STR - Store register value into memory with an offset
void execute_str(unsigned char src, unsigned char dst, short offset) {
    short effective_offset = SignExt(offset, 6);
    adjustAddressWithOffset(dst, effective_offset);
    storeToMemory(EA, reg_file[src], wb);
}

// Helper function to adjust the address with an offset
void adjustAddressWithOffset(unsigned char base_reg, short offset) {
    EA = (reg_file[base_reg] + offset/2);
    DCTRL = (wb == WRITE) ? WRITE : READ;
}

//// Helper function to load a value from the effective address into a register
//void loadFromEffectiveAddress(unsigned char dst, unsigned char wb) {
//    if (wb == WORD) {
//        reg_file[dst] = memory_read_word(EA);
//    }
//    else {
//        reg_file[dst] = memory_read_byte(EA);
//    }
//}
//
//// Helper function to store a value from a register into the effective address
//void storeToEffectiveAddress(unsigned char src, unsigned char wb) {
//    DMBR = reg_file[src];
//    if (wb == WORD) {
//        memory_write_word(EA, DMBR);
//    }
//    else {
//        memory_write_byte(EA, DMBR & 0x00FF);
//    }
//}


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

unsigned short loadFromMemory(unsigned short address, unsigned char wb) {
    if (wb == WORD) {
        return DMEM[address / 2]; // Load word
        reg_file[dst] = DMEM[EA / 2]; // dst shouldnt change
    }
    else {
        unsigned short wordVal = DMEM[address / 2];
        return (address % 2 == 0) ? (wordVal & 0x00FF) : ((wordVal & 0xFF00) >> 8); // Load byte
        reg_file[dst] = DMEM[EA / 2] & 0x00FF; // dst shouldnt change
    }
}

//// Function to write a byte to memory
//void memory_write_word(unsigned short address, unsigned short value) {
//    DMEM[address / 2] = value;
//}
//
//
//// Function to write a word to memory
//void memory_write_byte(unsigned short address, unsigned char value) {
//    unsigned short wordVal = DMEM[address / 2];
//    if (address % 2 == 0) {
//        // Store to low byte
//        wordVal = (wordVal & 0xFF00) | (value & 0x00FF);
//    }
//    else {
//        // Store to high byte
//        wordVal = (wordVal & 0x00FF) | ((value & 0x00FF) << 8);
//    }
//    DMEM[address / 2] = wordVal;
//}


// Function to read a byte from memory
unsigned short memory_read_word(unsigned short address) {
    return DMEM[address/2];
}

// Function to read a word from memory
unsigned char memory_read_byte(unsigned short address) {
    unsigned short wordVal = DMEM[address / 2];
    return (address % 2 == 0) ? (wordVal & 0x00FF) : ((wordVal & 0xFF00) >> 8); // Load byte
}


// Helper function to handle post-increment/decrement adjustments
void handlePRPOAdjustment(unsigned char reg, unsigned char prpo, unsigned char inc, unsigned char dec, unsigned char wb) {

    if (prpo = POST) {
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

