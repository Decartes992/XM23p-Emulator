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

void updatePSW_ZF(unsigned short result, unsigned char isByte) {
    psw.ZF = (result == 0);
}

void updatePSW_SF(unsigned short result, unsigned char isByte) {
    if (isByte) {
        psw.SF = ((result & 0x80) != 0); // For byte operations
    }
    else {
        psw.SF = ((result & 0x8000) != 0); // For word operations
    }
}

void updatePSW_OF(unsigned short a, unsigned short b, unsigned short result, unsigned char isByte) {
    if (isByte) {
        psw.OF = (((a ^ b ^ result ^ (result >> 1)) & 0x80) != 0); // For byte operations
    }
    else {
        psw.OF = (((a ^ b ^ result ^ (result >> 1)) & 0x8000) != 0); // For word operations
    }
}

void updatePSW_CF(unsigned int result, unsigned char isByte) {
    if (isByte) {
        psw.CF = (result > 0xFF); // For byte operations
    }
    else {
        psw.CF = (result > 0xFFFF); // For word operations
    }
}
void executeSWAP(unsigned char src, unsigned char dst) {
    unsigned short value = reg_file[dst];
    reg_file[dst] = reg_file[src];
    reg_file[src] = value;
}
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

void executeSWPB(unsigned char dst) {
    unsigned short value = reg_file[dst];
    reg_file[dst] = (value << 8) | (value >> 8);
    updatePSW_ZF(reg_file[dst] & 0xFF, 1); // SWPB is a byte operation
    updatePSW_SF(reg_file[dst] & 0xFF, 1);
}

void executeSRA(unsigned char dst) {
    unsigned char isByte = wb == 1;
    unsigned short value = reg_file[dst];

    if (isByte) {
        reg_file[dst] = (value >> 1) | (value & 0x80);
        updatePSW_ZF(reg_file[dst] & 0xFF, isByte);
        updatePSW_SF(reg_file[dst] & 0xFF, isByte);
    }
    else {
        reg_file[dst] = (value >> 1) | (value & 0x8000);
        updatePSW_ZF(reg_file[dst], isByte);
        updatePSW_SF(reg_file[dst], isByte);
    }
}

void executeRRC(unsigned char dst) {
    unsigned char isByte = wb == 1;
    unsigned short value = reg_file[dst];
    unsigned short newCarry;

    if (isByte) {
        newCarry = value & 0x01;
        reg_file[dst] = (value >> 1) | (psw.CF << 7);
        psw.CF = newCarry;
        updatePSW_ZF(reg_file[dst] & 0xFF, isByte);
        updatePSW_SF(reg_file[dst] & 0xFF, isByte);
    }
    else {
        newCarry = value & 0x0001;
        reg_file[dst] = (value >> 1) | (psw.CF << 15);
        psw.CF = newCarry;
        updatePSW_ZF(reg_file[dst], isByte);
        updatePSW_SF(reg_file[dst], isByte);
    }
}

void executeSXT(unsigned char dst) {
    reg_file[dst] = (reg_file[dst] & 0xFF) | ((reg_file[dst] & 0x80) ? 0xFF00 : 0x0000);
    updatePSW_ZF(reg_file[dst], 0); // SXT is a word operation
    updatePSW_SF(reg_file[dst], 0);
}

void executeMOVLZ(unsigned short dst, unsigned short operand) {
    reg_file[dst] = operand & 0x00FF;
}

void executeMOVL(unsigned char dst, unsigned short operand) {
    reg_file[dst] = (reg_file[dst] & 0xFF00) | (operand & 0x00FF);
}

void executeMOVLS(unsigned char dst, unsigned short operand) {
    reg_file[dst] = 0xFF00 | (operand & 0x00FF);
}

void executeMOVH(unsigned char dst, unsigned short operand) {
    reg_file[dst] = (operand << 8) | (reg_file[dst] & 0x00FF);
}

void executeSETCC() {
    if (c) psw.CF = 1;
    if (v) psw.OF = 1;
    if (n) psw.SF = 1;
    if (z) psw.ZF = 1;
    if (slp) psw.slp = 1;
}

void executeCLRCC() {
    if (c) psw.CF = 0;
    if (v) psw.OF = 0;
    if (n) psw.SF = 0;
    if (z) psw.ZF = 0;
    if (slp) psw.slp = 0;
}

