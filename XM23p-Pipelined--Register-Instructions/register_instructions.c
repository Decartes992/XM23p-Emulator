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

void executeADD(unsigned char dst, unsigned short operand) {
    unsigned short result = reg_file[dst] + operand;
    updatePSW_ZF(result);
    updatePSW_SF(result);
    updatePSW_OF(reg_file[dst], operand, result);
    updatePSW_CF((unsigned int)reg_file[dst] + operand);
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

void executeADDC(unsigned char dst, unsigned short operand) {
    unsigned int result = reg_file[dst] + operand + psw.CF;
    updatePSW_ZF(result);
    updatePSW_SF(result);
    updatePSW_OF(reg_file[dst], operand, result);
    updatePSW_CF(result);
    reg_file[dst] = (unsigned short)result;
}

void executeSUBC(unsigned char dst, unsigned short operand) {
    unsigned int result = reg_file[dst] - operand - psw.CF;
    updatePSW_ZF(result);
    updatePSW_SF(result);
    updatePSW_OF(reg_file[dst], operand, result);
    updatePSW_CF(result);
    reg_file[dst] = (unsigned short)result;
}

void executeDADD(unsigned char dst, unsigned short operand) {
    unsigned int result = reg_file[dst] + operand + psw.CF;
    updatePSW_ZF(result);
    updatePSW_CF(result);
    reg_file[dst] = (unsigned short)result;
}

void executeCMP(unsigned char dst, unsigned short operand) {
    unsigned short result = reg_file[dst] - operand;
    updatePSW_ZF(result);
    updatePSW_SF(result);
    updatePSW_OF(reg_file[dst], operand, result);
    updatePSW_CF((unsigned int)reg_file[dst] - operand);
}

void executeXOR(unsigned char dst, unsigned short operand) {
    unsigned short result = reg_file[dst] ^ operand;
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
    reg_file[dst] &= ~operand;
    updatePSW_ZF(reg_file[dst]);
    updatePSW_SF(reg_file[dst]);
}

void executeBIS(unsigned char dst, unsigned short operand) {
    reg_file[dst] |= operand;
    updatePSW_ZF(reg_file[dst]);
    updatePSW_SF(reg_file[dst]);
}

void executeMOV(unsigned char dst, unsigned short operand) {
    reg_file[dst] = operand;
    updatePSW_ZF(reg_file[dst]);
    updatePSW_SF(reg_file[dst]);
}

void executeSWPB(unsigned char dst) {
    unsigned short value = reg_file[dst];
    reg_file[dst] = (value << 8) | (value >> 8);
    updatePSW_ZF(reg_file[dst]);
    updatePSW_SF(reg_file[dst]);
}

void executeSRA(unsigned char dst) {
    unsigned short value = reg_file[dst];
    reg_file[dst] = (value >> 1) | (value & 0x8000);
    updatePSW_ZF(reg_file[dst]);
    updatePSW_SF(reg_file[dst]);
}

void executeRRC(unsigned char dst) {
    unsigned short value = reg_file[dst];
    unsigned short newCarry = value & 0x0001;
    reg_file[dst] = (value >> 1) | (psw.CF << 15);
    psw.CF = newCarry;
    updatePSW_ZF(reg_file[dst]);
    updatePSW_SF(reg_file[dst]);
}

void executeSWAP(unsigned char src, unsigned char dst) {
    unsigned short value = reg_file[dst];
    reg_file[dst] = reg_file[src];
    reg_file[src] = value;
}

void executeSXT(unsigned char dst) {
    reg_file[dst] = (reg_file[dst] & 0xFF) | ((reg_file[dst] & 0x80) ? 0xFF00 : 0x0000);
    updatePSW_ZF(reg_file[dst]);
    updatePSW_SF(reg_file[dst]);
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


