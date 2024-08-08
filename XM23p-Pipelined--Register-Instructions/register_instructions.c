/*
Name: Iftekhar Rafi
ID: B00871031
Course: ECED 3403 Computer Architecture
Instructor: Larry Hughes

File Name: instructions.c
File Purpose: This file contains the functions to handle execution of specific instructions for the XM23P emulator.
*/

#include "loader.h"
#include "register_instructions.h"

// Function to execute the ADD instruction
void updatePSW_ZF(unsigned short result, unsigned char isByte) {
    psw.ZF = (result == 0);
}

// Function to update the Sign Flag in the PSW
void updatePSW_SF(unsigned short result, unsigned char isByte) {
    if (isByte) {
        psw.SF = ((result & 0x80) != 0); // For byte operations
    }
    else {
        psw.SF = ((result & 0x8000) != 0); // For word operations
    }
}

// Function to update the Overflow Flag in the PSW
void updatePSW_OF(unsigned short a, unsigned short b, unsigned short result, unsigned char isByte) {
    if (isByte) {
        psw.OF = (((a ^ b ^ result ^ (result >> 1)) & 0x80) != 0); // For byte operations
    }
    else {
        psw.OF = (((a ^ b ^ result ^ (result >> 1)) & 0x8000) != 0); // For word operations
    }
}

// Function to update the Carry Flag in the PSW
void updatePSW_CF(unsigned int result, unsigned char isByte) {
    if (isByte) {
        psw.CF = (result > 0xFF); // For byte operations
    }
    else {
        psw.CF = (result > 0xFFFF); // For word operations
    }
}

// Function to execute the ADD instruction
void executeSWAP(unsigned char src, unsigned char dst) {
    unsigned short value = reg_file[dst];
    reg_file[dst] = reg_file[src];
    reg_file[src] = value;
}

// Function to execute the ADD instruction
void executeADD(unsigned char dst, unsigned short operand) {
    unsigned char isByte = wb == 1;
    unsigned int result;

    if (isByte) {
        result = (reg_file[dst] & 0xFF) + (operand & 0xFF);
    }
    else {
        result = reg_file[dst] + operand;
    }

    updatePSW_ZF(result, isByte);
    updatePSW_SF(result, isByte);
    updatePSW_OF(reg_file[dst], operand, result, isByte);
    updatePSW_CF(result, isByte);

    if (isByte) {
        reg_file[dst] = (reg_file[dst] & 0xFF00) | (result & 0xFF);
    }
    else {
        reg_file[dst] = result;
    }
}

// Function to execute the ADDC instruction
void executeADDC(unsigned char dst, unsigned short operand) {
    unsigned char isByte = wb == 1;
    unsigned int result;

    if (isByte) {
        result = (reg_file[dst] & 0xFF) + (operand & 0xFF) + psw.CF;
    }
    else {
        result = reg_file[dst] + operand + psw.CF;
    }

    updatePSW_ZF(result, isByte);
    updatePSW_SF(result, isByte);
    updatePSW_OF(reg_file[dst], operand, result, isByte);
    updatePSW_CF(result, isByte);

    if (isByte) {
        reg_file[dst] = (reg_file[dst] & 0xFF00) | (result & 0xFF);
    }
    else {
        reg_file[dst] = (unsigned short)result;
    }
}

// Function to execute the SUB instruction
void executeSUB(unsigned char dst, unsigned short operand) {
    unsigned char isByte = wb == 1;
    unsigned int result;

    if (isByte) {
        result = (reg_file[dst] & 0xFF) - (operand & 0xFF);
    }
    else {
        result = reg_file[dst] - operand;
    }

    updatePSW_ZF(result, isByte);
    updatePSW_SF(result, isByte);
    updatePSW_OF(reg_file[dst], operand, result, isByte);
    updatePSW_CF(result, isByte);

    if (isByte) {
        reg_file[dst] = (reg_file[dst] & 0xFF00) | (result & 0xFF);
    }
    else {
        reg_file[dst] = result;
    }
}

// Function to execute the SUBC instruction
void executeSUBC(unsigned char dst, unsigned short operand) {
    unsigned char isByte = wb == 1;
    unsigned int result;

    if (isByte) {
        result = (reg_file[dst] & 0xFF) - (operand & 0xFF) - psw.CF;
    }
    else {
        result = reg_file[dst] - operand - psw.CF;
    }

    updatePSW_ZF(result, isByte);
    updatePSW_SF(result, isByte);
    updatePSW_OF(reg_file[dst], operand, result, isByte);
    updatePSW_CF(result, isByte);

    if (isByte) {
        reg_file[dst] = (reg_file[dst] & 0xFF00) | (result & 0xFF);
    }
    else {
        reg_file[dst] = (unsigned short)result;
    }
}

// Function to execute the CMP instruction
void executeDADD(unsigned char dst, unsigned short operand) {
    unsigned char isByte = wb == 1;
    unsigned int result;

    if (isByte) {
        result = (reg_file[dst] & 0xFF) + (operand & 0xFF) + psw.CF;
    }
    else {
        result = reg_file[dst] + operand + psw.CF;
    }

    updatePSW_ZF(result, isByte);
    updatePSW_CF(result, isByte);

    if (isByte) {
        reg_file[dst] = (reg_file[dst] & 0xFF00) | (result & 0xFF);
    }
    else {
        reg_file[dst] = (unsigned short)result;
    }
}

// Function to execute the CMP instruction
void executeCMP(unsigned char dst, unsigned short operand) {
    unsigned char isByte = wb == 1;
    unsigned int result;

    if (isByte) {
        result = (reg_file[dst] & 0xFF) - (operand & 0xFF);
    }
    else {
        result = reg_file[dst] - operand;
    }

    updatePSW_ZF(result, isByte);
    updatePSW_SF(result, isByte);
    updatePSW_OF(reg_file[dst], operand, result, isByte);
    updatePSW_CF(result, isByte);
}

// Function to execute the DADD instruction
void executeXOR(unsigned char dst, unsigned short operand) {
    unsigned char isByte = wb == 1;
    unsigned short result;

    if (isByte) {
        result = (reg_file[dst] & 0xFF) ^ (operand & 0xFF);
    }
    else {
        result = reg_file[dst] ^ operand;
    }

    updatePSW_ZF(result, isByte);
    updatePSW_SF(result, isByte);

    if (isByte) {
        reg_file[dst] = (reg_file[dst] & 0xFF00) | (result & 0xFF);
    }
    else {
        reg_file[dst] = result;
    }
}

// Function to execute the AND instruction
void executeAND(unsigned char dst, unsigned short operand) {
    unsigned char isByte = wb == 1;
    unsigned short result;

    if (isByte) {
        result = (reg_file[dst] & 0xFF) & (operand & 0xFF);
    }
    else {
        result = reg_file[dst] & operand;
    }

    updatePSW_ZF(result, isByte);
    updatePSW_SF(result, isByte);

    if (isByte) {
        reg_file[dst] = (reg_file[dst] & 0xFF00) | (result & 0xFF);
    }
    else {
        reg_file[dst] = result;
    }
}

// Function to execute the OR instruction
void executeOR(unsigned char dst, unsigned short operand) {
    unsigned char isByte = wb == 1;
    unsigned short result;

    if (isByte) {
        result = (reg_file[dst] & 0xFF) | (operand & 0xFF);
    }
    else {
        result = reg_file[dst] | operand;
    }

    updatePSW_ZF(result, isByte);
    updatePSW_SF(result, isByte);

    if (isByte) {
        reg_file[dst] = (reg_file[dst] & 0xFF00) | (result & 0xFF);
    }
    else {
        reg_file[dst] = result;
    }
}

// Function to execute the BIT instruction
void executeBIT(unsigned char dst, unsigned short operand) {
    unsigned char isByte = wb == 1;
    unsigned short result;

    if (isByte) {
        result = (reg_file[dst] & 0xFF) & (operand & 0xFF);
    }
    else {
        result = reg_file[dst] & operand;
    }

    updatePSW_ZF(result, isByte);
    updatePSW_SF(result, isByte);
}

// Function to execute the BIC instruction
void executeBIC(unsigned char dst, unsigned short operand) {
    unsigned char isByte = wb == 1;

    if (isByte) {
        reg_file[dst] &= ~(operand & 0xFF);
        updatePSW_ZF(reg_file[dst] & 0xFF, isByte);
    }
    else {
        reg_file[dst] &= ~operand;
        updatePSW_ZF(reg_file[dst], isByte);
    }
    updatePSW_SF(reg_file[dst], isByte);
}

// Function to execute the BIS instruction
void executeBIS(unsigned char dst, unsigned short operand) {
    unsigned char isByte = wb == 1;

    if (isByte) {
        reg_file[dst] |= (operand & 0xFF);
        updatePSW_ZF(reg_file[dst] & 0xFF, isByte);
    }
    else {
        reg_file[dst] |= operand;
        updatePSW_ZF(reg_file[dst], isByte);
    }
    updatePSW_SF(reg_file[dst], isByte);
}

// Function to execute the MOV instruction
void executeMOV(unsigned char dst, unsigned short operand) {
    unsigned char isByte = wb == 1;

    if (isByte) {
        reg_file[dst] = (reg_file[dst] & 0xFF00) | (operand & 0x00FF);
        updatePSW_ZF(reg_file[dst] & 0xFF, isByte);
    }
    else {
        reg_file[dst] = operand;
        updatePSW_ZF(reg_file[dst], isByte);
    }
    updatePSW_SF(reg_file[dst], isByte);
}

// Function to execute the SWPB instruction
void executeSWPB(unsigned char dst) {
    unsigned short value = reg_file[dst];
    reg_file[dst] = (value << 8) | (value >> 8);
    updatePSW_ZF(reg_file[dst] & 0xFF, 1); // SWPB is a byte operation
    updatePSW_SF(reg_file[dst] & 0xFF, 1);
}

// Function to execute the SXT instruction
void executeSRA(unsigned char dst) {
    unsigned char isByte = wb == 1;
    unsigned short value = reg_file[dst];

    if (isByte) {                                           // For byte operations
        reg_file[dst] = (value >> 1) | (value & 0x80);
        updatePSW_ZF(reg_file[dst] & 0xFF, isByte);
        updatePSW_SF(reg_file[dst] & 0xFF, isByte);
    }
    else {  										        // For word operations
        reg_file[dst] = (value >> 1) | (value & 0x8000);
        updatePSW_ZF(reg_file[dst], isByte);
        updatePSW_SF(reg_file[dst], isByte);
    }
}

// Function to execute the SXT instruction
void executeRRC(unsigned char dst) {
    unsigned char isByte = wb == 1;
    unsigned short value = reg_file[dst];
    unsigned short newCarry;

    // Rotate right through carry
    if (isByte) {                                           // For byte operations
        newCarry = value & 0x01;
        reg_file[dst] = (value >> 1) | (psw.CF << 7);
        psw.CF = newCarry;
        updatePSW_ZF(reg_file[dst] & 0xFF, isByte);
        updatePSW_SF(reg_file[dst] & 0xFF, isByte);
    }
    else {												  // For word operations
        newCarry = value & 0x0001;
        reg_file[dst] = (value >> 1) | (psw.CF << 15);
        psw.CF = newCarry;
        updatePSW_ZF(reg_file[dst], isByte);
        updatePSW_SF(reg_file[dst], isByte);
    }
}

// Function to execute the SXT instruction
void executeSXT(unsigned char dst) {
    reg_file[dst] = (reg_file[dst] & 0xFF) | ((reg_file[dst] & 0x80) ? 0xFF00 : 0x0000);
    updatePSW_ZF(reg_file[dst], 0); // SXT is a word operation
    updatePSW_SF(reg_file[dst], 0);
}

// Function to execute the MOVLZ instruction
void executeMOVLZ(unsigned short dst, unsigned short operand) {
    reg_file[dst] = operand & 0x00FF; // Load low byte
}

// Function to execute the MOVL instruction
void executeMOVL(unsigned char dst, unsigned short operand) {
    // Keep the high byte of the destination register and load the low byte of the operand
    reg_file[dst] = (reg_file[dst] & 0xFF00) | (operand & 0x00FF); 
}

// Function to execute the MOVLS instruction
void executeMOVLS(unsigned char dst, unsigned short operand) {
    // Keep the high byte of the destination register and load the low byte of the operand
    reg_file[dst] = 0xFF00 | (operand & 0x00FF);
}

// Function to execute the MOVH instruction
void executeMOVH(unsigned char dst, unsigned short operand) {
    // Keep the low byte of the destination register and load the high byte of the operand
    reg_file[dst] = (operand << 8) | (reg_file[dst] & 0x00FF);
}

// Function to execute the MOVHS instruction
void executeSETCC() {
    // Set the flags based on the condition codes
    if (c) psw.CF = 1;
    if (v) psw.OF = 1;
    if (n) psw.SF = 1;
    if (z) psw.ZF = 1;
    if (slp) psw.slp = 1;
}

// Function to execute the MOVHS instruction
void executeCLRCC() {
    // Clear the flags based on the condition codes
    if (c) psw.CF = 0;
    if (v) psw.OF = 0;
    if (n) psw.SF = 0;
    if (z) psw.ZF = 0;
    if (slp) psw.slp = 0;
}

