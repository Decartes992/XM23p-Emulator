/*
Name: Iftekhar Rafi
ID: B00871031
Course: ECED 3403 Computer Architecture
Instructor: Larry Hughes

File Name: instructions.c
File Purpose: This file contains the functions to execute each type of instruction.
*/

#include "loader.h"

// Helper functions to update PSW
void updatePSW_ZF(unsigned short result) {
    psw.ZF = (result == 0);
}

void updatePSW_SF(unsigned short result) {
    psw.SF = ((result & 0x8000) != 0);
}

void updatePSW_OF(unsigned short a, unsigned short b, unsigned short result) {
    psw.OF = (((a ^ b ^ result ^ (result >> 1)) & 0x8000) != 0);
}

void updatePSW_CF(unsigned int result) {
    psw.CF = (result > 0xFFFF);
}

// Instruction functions
void executeADD(unsigned char dst, unsigned short operand) {
    unsigned short result = reg_file[dst] + operand;
    updatePSW_ZF(result);
    updatePSW_SF(result);
    updatePSW_OF(reg_file[dst], operand, result);
    updatePSW_CF((unsigned int)reg_file[dst] + operand);
    reg_file[dst] = result;
}

void executeADDC(unsigned char dst, unsigned short operand) {
    unsigned int result = reg_file[dst] + operand + psw.CF;
    updatePSW_ZF(result);
    updatePSW_SF(result);
    updatePSW_OF(reg_file[dst], operand, result);
    updatePSW_CF(result);
    reg_file[dst] = result;
}

void executeSUB(unsigned char dst, unsigned short operand) {
    unsigned short result = reg_file[dst] - operand;
    updatePSW_ZF(result);
    updatePSW_SF(result);
    updatePSW_OF(reg_file[dst], operand, result);
    updatePSW_CF((unsigned int)reg_file[dst] - operand);
    reg_file[dst] = result;
}

void executeSUBC(unsigned char dst, unsigned short operand) {
    unsigned int result = reg_file[dst] - operand - !psw.CF;
    updatePSW_ZF(result);
    updatePSW_SF(result);
    updatePSW_OF(reg_file[dst], operand, result);
    updatePSW_CF(result);
    reg_file[dst] = result;
}

void executeDADD(unsigned char dst, unsigned short operand) {
    unsigned short result = reg_file[dst] + operand + (psw.CF ? 6 : 0);
    updatePSW_ZF(result);
    updatePSW_SF(result);
    updatePSW_OF(reg_file[dst], operand, result);
    updatePSW_CF(result > 9);
    reg_file[dst] = result;
}

void executeCMP(unsigned char dst, unsigned short operand) {
    unsigned short result = reg_file[dst] - operand;
    updatePSW_ZF(result);
    updatePSW_SF(result);
    updatePSW_OF(reg_file[dst], operand, result);
    updatePSW_CF((unsigned int)reg_file[dst] - operand);
}

// Other instruction functions
void executeXOR(unsigned char dst, unsigned short operand) {
    unsigned short result = reg_file[dst] ^ operand;
    updatePSW_ZF(result);
    updatePSW_SF(result);
    reg_file[dst] = result;
}

void executeAND(unsigned char dst, unsigned short operand) {
    unsigned short result = reg_file[dst] & operand;
    updatePSW_ZF(result);
    updatePSW_SF(result);
    reg_file[dst] = result;
}

void executeOR(unsigned char dst, unsigned short operand) {
    unsigned short result = reg_file[dst] | operand;
    updatePSW_ZF(result);
    updatePSW_SF(result);
    reg_file[dst] = result;
}

void executeBIT(unsigned char dst, unsigned short operand) {
    unsigned short result = reg_file[dst] & operand;
    updatePSW_ZF(result);
    updatePSW_SF(result);
}

void executeBIC(unsigned char dst, unsigned short operand) {
    unsigned short result = reg_file[dst] & ~operand;
    updatePSW_ZF(result);
    updatePSW_SF(result);
    reg_file[dst] = result;
}

void executeBIS(unsigned char dst, unsigned short operand) {
    unsigned short result = reg_file[dst] | operand;
    updatePSW_ZF(result);
    updatePSW_SF(result);
    reg_file[dst] = result;
}

void executeMOV(unsigned char dst, unsigned short operand) {
    reg_file[dst] = operand;
    updatePSW_ZF(reg_file[dst]);
    updatePSW_SF(reg_file[dst]);
}

void executeSWAP(unsigned char dst) {
    unsigned short result = (reg_file[dst] << 8) | (reg_file[dst] >> 8);
    reg_file[dst] = result;
    updatePSW_ZF(result);
    updatePSW_SF(result);
}

void executeSRA(unsigned char dst) {
    unsigned short result = (reg_file[dst] >> 1) | (reg_file[dst] & 0x8000);
    reg_file[dst] = result;
    updatePSW_ZF(result);
    updatePSW_SF(result);
}

void executeRRC(unsigned char dst) {
    unsigned short result = (reg_file[dst] >> 1) | (psw.CF << 15);
    psw.CF = reg_file[dst] & 1;
    reg_file[dst] = result;
    updatePSW_ZF(result);
    updatePSW_SF(result);
}

void executeSWPB(unsigned char dst) {
    unsigned short result = (reg_file[dst] >> 8) | (reg_file[dst] << 8);
    reg_file[dst] = result;
}

void executeSXT(unsigned char dst) {
    unsigned short result = (short)((char)reg_file[dst]);
    reg_file[dst] = result;
    updatePSW_ZF(result);
    updatePSW_SF(result);
}

void executeMOVLZ(unsigned char dst, unsigned short operand) {
    reg_file[dst] = operand;
    updatePSW_ZF(reg_file[dst]);
    updatePSW_SF(reg_file[dst]);
}

void executeMOVL(unsigned char dst, unsigned short operand) {
    reg_file[dst] = operand;
}

void executeMOVLS(unsigned char dst, unsigned short operand) {
    reg_file[dst] = operand;
    updatePSW_SF(reg_file[dst]);
}

void executeMOVH(unsigned char dst, unsigned short operand) {
    reg_file[dst] = operand << 8;
}
