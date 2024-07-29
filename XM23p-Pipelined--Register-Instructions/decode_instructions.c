/*
Name: Iftekhar Rafi
ID: B00871031
Course: ECED 3403 Computer Architecture
Instructor: Larry Hughes

File Name: decode_instructions.c
File Purpose: This file contains the function to decode instructions from IMEM.
*/
#include <stdio.h>
#include "loader.h"
#include "decode_instructions.h"

void extractFields(unsigned short instruction, InstructionType type) {
    rc = (instruction >> 7) & 0x01;    // RC is at bit 7
    wb = (instruction >> 6) & 0x01;    // WB is at bit 6
    src = (instruction >> 3) & 0x07;   // SRC/CON is at bits 5-3
    dst = instruction & 0x07;          // DST is at bits 2-0
    con = src;                         // CON is the same as SRC/CON
    bb = (instruction >> 3) & 0xFF;    // BB is at bits 10-3 (byte-level data)
    prpo = (instruction >> 10) & 0x01; // PRPO is at bit 10
    dec = (instruction >> 9) & 0x01;   // DEC is at bit 9
    inc = (instruction >> 8) & 0x01;   // INC is at bit 8

    if (type == SETCC || type == CLRCC) {
        v = (instruction >> 4) & 0x01; // V is bit 4
        c = instruction & 0x01;        // C is bit 0
        n = (instruction >> 2) & 0x01; // N is bit 2
        z = (instruction >> 1) & 0x01; // Z is bit 1
        slp = (instruction >> 5) & 0x01; // SLP is bit 5
    }
}
InstructionType getInstructionType(unsigned short instruction) {


    // Check for LD and ST instructions
    switch (instruction & 0xFC00) {  // Check bits 15-10
    case 0x5800: return LD;      // 010110xxxxxx
    case 0x5C00: return ST;      // 010111xxxxxx
    }


    // Check for LDR and STR instructions
    switch (instruction & 0xC000) {  // Check bits 15-14
    case 0x8000: return LDR;     // 10xxxxxxxxxx
    case 0xC000: return STR;     // 11xxxxxxxxxx
    }


    // Check for other instructions
    switch (instruction & 0xFF00) {  // Check bits 15-8
    case 0x4000: return ADD;
    case 0x4100: return ADDC;
    case 0x4200: return SUB;
    case 0x4300: return SUBC;
    case 0x4400: return DADD;
    case 0x4500: return CMP;
    case 0x4600: return XOR;
    case 0x4700: return AND;
    case 0x4800: return OR;
    case 0x4900: return BIT;
    case 0x4A00: return BIC;
    case 0x4B00: return BIS;
    }

    switch (instruction & 0xFF80) {  // Check bits 15-8
    case 0x4C00: return MOV;
    case 0x4D00:
        switch (instruction & 0x0038) {  // Check bits 5-3
        case 0x0000: return SRA;
        case 0x0008: return RRC;
        }
    }

    switch (instruction & 0xFFC0) {  // Check bits 15-6
    case 0x4C80: return SWAP;
    }

    switch (instruction & 0xFFF8) {  // Check bits 15-3
    case 0x4D18: return SWPB;
    case 0x4D20: return SXT;
    }

    switch (instruction & 0xF800) {  // Check bits 15-11
    case 0x6000: return MOVL;
    case 0x6800: return MOVLZ;
    case 0x7000: return MOVLS;
    case 0x7800: return MOVH;
    }

    switch (instruction & 0xFFE0) {  // Check bits 15-5
    case 0x4DA0: return SETCC;
    case 0x4DC0: return CLRCC;
    }

    return INVALID;
}

void printDecodedInstruction(unsigned short PC, InstructionType type) {
    printf("                  %04X: %s ", PC - 4, getInstructionName(type));

    // Print the fields based on the instruction type
    if (type == ADD || type == ADDC || type == SUB || type == SUBC || type == DADD || type == CMP || type == XOR || type == AND || type == OR || type == BIT || type == BIC || type == BIS) {
        if (!rc) {
            printf("RC: %d WB: %d SRC: R%d DST: R%d\n", rc, wb, src, dst);
            printf("                  Registers: ");
            printf("R%d: %04X ", src, reg_file[src]);
        }
        else {
            printf("RC: %d WB: %d CON: #%d DST: R%d\n", rc, wb, con, dst);
            printf("                  Registers: ");
        }
    }
    else if (type == MOV) {
        printf("WB: %d SRC: R%d DST: R%d\n", wb, src, dst);
        printf("                  Registers: ");
        printf("R%d: %04X ", src, reg_file[src]);
    }
    else if (type == SWAP) {
        printf("SRC: R%d DST: R%d\n", src, dst);
        printf("                  Registers: ");
        printf("R%d: %04X ", src, reg_file[src]);
    }
    else if (type == SWPB || type == SXT) {
        printf("DST: R%d\n", dst);
        printf("                  Registers: ");
    }
    else if (type == SRA || type == RRC) {
        printf("WB: %d DST: R%d\n", wb, dst);
        printf("                  Registers: ");
    }
    else if (type == MOVL || type == MOVLZ || type == MOVLS || type == MOVH) {
        printf("DST: R%d BB: %d\n", dst, bb);
        printf("                  Registers: ");
    }
    else {
        printf("\n                  ");
    }

    // Print the destination register values
    printf("R%d: %04X\n", dst, reg_file[dst]);
    printf("\n");
}

// Function to get the operand based on the rc flag and src value
unsigned short getOperand(unsigned char rc, unsigned char src) {
    if (rc) {
        // Return the constant value
        return src;
    }
    else {
        // Return the register value
        return reg_file[src];
    }
}

