/*
Name: Iftekhar Rafi
ID: B00871031
Course: ECED 3403 Computer Architecture
Instructor: Larry Hughes

File Name: instructions.c
File Purpose: This file contains the functions to handle execution of specific instructions for the XM23P emulator.
*/

#include "instructions.h"
#include "loader.h"

// Function to update the Zero Flag (ZF)
void updatePSW_ZF(unsigned short result) {
    psw.ZF = (result == 0);
}

// Function to update the Sign Flag (SF)
void updatePSW_SF(unsigned short result) {
    psw.SF = ((result & 0x8000) != 0);
}

// Function to update the Overflow Flag (OF)
void updatePSW_OF(unsigned short a, unsigned short b, unsigned short result) {
    psw.OF = (((a ^ b ^ result ^ (result >> 1)) & 0x8000) != 0);
}

// Function to update the Carry Flag (CF)
void updatePSW_CF(unsigned int result) {
    psw.CF = (result > 0xFFFF);
}

// Example function to execute an ADD instruction
void executeADD(unsigned char dst, unsigned short operand) {
    unsigned short result = reg_file[dst] + operand;
    updatePSW_ZF(result);
    updatePSW_SF(result);
    updatePSW_OF(reg_file[dst], operand, result);
    updatePSW_CF((unsigned int)reg_file[dst] + operand);
    reg_file[dst] = result;
}

// Function to execute a SUB instruction
void executeSUB(unsigned char dst, unsigned short operand) {
    unsigned short result = reg_file[dst] - operand;
    updatePSW_ZF(result);
    updatePSW_SF(result);
    updatePSW_OF(reg_file[dst], operand, result);
    updatePSW_CF((unsigned int)reg_file[dst] - operand);
    reg_file[dst] = result;
}

// Function to execute an AND instruction
void executeAND(unsigned char dst, unsigned short operand) {
    unsigned short result = reg_file[dst] & operand;
    updatePSW_ZF(result);
    updatePSW_SF(result);
    reg_file[dst] = result;
}

// Function to execute an OR instruction
void executeOR(unsigned char dst, unsigned short operand) {
    unsigned short result = reg_file[dst] | operand;
    updatePSW_ZF(result);
    updatePSW_SF(result);
    reg_file[dst] = result;
}

// Function to execute an ADDC instruction
void executeADDC(unsigned char dst, unsigned short operand) {
    unsigned int result = reg_file[dst] + operand + psw.CF;
    updatePSW_ZF(result);
    updatePSW_SF(result);
    updatePSW_OF(reg_file[dst], operand, result);
    updatePSW_CF(result);
    reg_file[dst] = (unsigned short)result;
}

// Function to execute a SUBC instruction
void executeSUBC(unsigned char dst, unsigned short operand) {
    unsigned int result = reg_file[dst] - operand - psw.CF;
    updatePSW_ZF(result);
    updatePSW_SF(result);
    updatePSW_OF(reg_file[dst], operand, result);
    updatePSW_CF(result);
    reg_file[dst] = (unsigned short)result;
}

// Function to execute a DADD instruction
void executeDADD(unsigned char dst, unsigned short operand) {
    unsigned int result = reg_file[dst] + operand + psw.CF;

    // Update PSW flags for decimal addition
    updatePSW_ZF(result);
    updatePSW_CF(result);

    reg_file[dst] = (unsigned short)result;
}

// Function to execute a CMP instruction
void executeCMP(unsigned char dst, unsigned short operand) {
    unsigned short result = reg_file[dst] - operand;
    updatePSW_ZF(result);
    updatePSW_SF(result);
    updatePSW_OF(reg_file[dst], operand, result);
    updatePSW_CF((unsigned int)reg_file[dst] - operand);
}

// Function to execute an XOR instruction
void executeXOR(unsigned char dst, unsigned short operand) {
    unsigned short result = reg_file[dst] ^ operand;
    updatePSW_ZF(result);
    updatePSW_SF(result);
    reg_file[dst] = result;
}

// Function to execute a BIT instruction
void executeBIT(unsigned char dst, unsigned short operand) {
    unsigned short result = reg_file[dst] & operand;
    updatePSW_ZF(result);
    updatePSW_SF(result);
}

// Function to execute a BIC instruction
void executeBIC(unsigned char dst, unsigned short operand) {
    reg_file[dst] &= ~operand;
    updatePSW_ZF(reg_file[dst]);
    updatePSW_SF(reg_file[dst]);
}

// Function to execute a BIS instruction
void executeBIS(unsigned char dst, unsigned short operand) {
    reg_file[dst] |= operand;
    updatePSW_ZF(reg_file[dst]);
    updatePSW_SF(reg_file[dst]);
}

// Function to execute a MOV instruction
void executeMOV(unsigned char dst, unsigned short operand) {
    reg_file[dst] = operand;
    updatePSW_ZF(reg_file[dst]);
    updatePSW_SF(reg_file[dst]);
}

// Function to execute a SWAP instruction
void executeSWPB(unsigned char dst) {
    unsigned short value = reg_file[dst];
    reg_file[dst] = (value << 8) | (value >> 8);
    updatePSW_ZF(reg_file[dst]);
    updatePSW_SF(reg_file[dst]);
}

// Function to execute an SRA instruction
void executeSRA(unsigned char dst) {
    unsigned short value = reg_file[dst];
    reg_file[dst] = (value >> 1) | (value & 0x8000);
    updatePSW_ZF(reg_file[dst]);
    updatePSW_SF(reg_file[dst]);
}

// Function to execute an RRC instruction
void executeRRC(unsigned char dst) {
    unsigned short value = reg_file[dst];
    unsigned short newCarry = value & 0x0001;
    reg_file[dst] = (value >> 1) | (psw.CF << 15);
    psw.CF = newCarry;
    updatePSW_ZF(reg_file[dst]);
    updatePSW_SF(reg_file[dst]);
}

// Function to execute an SWPB instruction
void executeSWAP(unsigned char src, unsigned char dst) {
    unsigned short value = reg_file[dst];
    reg_file[dst] = reg_file[src];
    reg_file[src] = value;
}

// Function to execute an SXT instruction
void executeSXT(unsigned char dst) {
    reg_file[dst] = (reg_file[dst] & 0xFF) | ((reg_file[dst] & 0x80) ? 0xFF00 : 0x0000);
    updatePSW_ZF(reg_file[dst]);
    updatePSW_SF(reg_file[dst]);
}
// Function to execute a MOVLZ instruction
void executeMOVLZ(unsigned short dst, unsigned short operand) {
    reg_file[dst] = operand & 0x00FF;    // Low byte of operand to low byte of destination
}

// Function to execute a MOVL instruction
void executeMOVL(unsigned char dst, unsigned short operand) {
    reg_file[dst] = (reg_file[dst] & 0xFF00) | (operand & 0x00FF);    // Low byte of operand to low byte of destination
}

// Function to execute a MOVLS instruction
void executeMOVLS(unsigned char dst, unsigned short operand) {
    reg_file[dst] = 0xFF00 | (operand & 0x00FF);    // Low byte of operand to low byte of destination, high byte set to 11111111
}

// Function to execute a MOVH instruction
void executeMOVH(unsigned char dst, unsigned short operand) {
    reg_file[dst] = (operand << 8) | (reg_file[dst] & 0x00FF);
}

// Function to execute a SETCC instruction
void executeSETCC(unsigned char v, unsigned char c, unsigned char slp, unsigned char n, unsigned char z) {
   if (c) psw.CF = 1;
   if (v) psw.OF = 1;
   if (n) psw.SF = 1;
   if (z) psw.ZF = 1;
   if (slp) psw.slp = 1;
}

// Function to execute a CLRCC instruction
void executeCLRCC(unsigned char v, unsigned char c, unsigned char slp, unsigned char n, unsigned char z) {
   if (c) psw.CF = 0;
   if (v) psw.OF = 0;
   if (n) psw.SF = 0;
   if (z) psw.ZF = 0;
   if (slp) psw.slp = 0;
}


void execute_ld(unsigned char src, unsigned char dst) {
    DMAR = reg_file[src];
    DCTRL = READ;
    DMBR = DMEM[DMAR];
    reg_file[dst] = DMBR;
}

void execute_ldr(unsigned char src, unsigned char dst, char offset) {
    DMAR = reg_file[src] + offset;
    DCTRL = READ;
    DMBR = DMEM[DMAR];
    reg_file[dst] = DMBR;
}

void execute_st(unsigned char src, unsigned char dst) {
    DMAR = reg_file[dst];
    DCTRL = WRITE;
    DMBR = reg_file[src];
    DMEM[DMAR] = DMBR;
}

void execute_str(unsigned char src, unsigned char dst, char offset) {
    DMAR = reg_file[dst] + offset;
    DCTRL = WRITE;
    DMBR = reg_file[src];
    DMEM[DMAR] = DMBR;
}