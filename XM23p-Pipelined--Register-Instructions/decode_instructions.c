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

InstructionType getInstructionType(unsigned short instruction) {
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

    return INVALID;
}

void extractFields(unsigned short instruction, InstructionType type, unsigned char* rc, unsigned char* wb, unsigned char* src, unsigned char* dst, unsigned char* con, unsigned char* bb) {
    *rc = (instruction >> 7) & 0x01;    // RC is at bit 7
    *wb = (instruction >> 6) & 0x01;    // WB is at bit 6
    *src = (instruction >> 3) & 0x07;   // SRC/CON is at bits 5-3
    *dst = instruction & 0x07;          // DST is at bits 2-0
    *con = *src;                        // CON is the same as SRC/CON
    *bb = (instruction >> 3) & 0xFF;    // BB is at bits 10-3 (byte-level data)
}

const char* getInstructionName(InstructionType type) {
    switch (type) {
    case ADD: return "ADD";
    case ADDC: return "ADDC";
    case SUB: return "SUB";
    case SUBC: return "SUBC";
    case DADD: return "DADD";
    case CMP: return "CMP";
    case XOR: return "XOR";
    case AND: return "AND";
    case OR: return "OR";
    case BIT: return "BIT";
    case BIC: return "BIC";
    case BIS: return "BIS";
    case MOV: return "MOV";
    case SWAP: return "SWAP";
    case SRA: return "SRA";
    case RRC: return "RRC";
    case SWPB: return "SWPB";
    case SXT: return "SXT";
    case MOVL: return "MOVL";
    case MOVLZ: return "MOVLZ";
    case MOVLS: return "MOVLS";
    case MOVH: return "MOVH";
    default: return "INVALID";
    }
}

void printDecodedInstruction(unsigned short IR, unsigned short PC, InstructionType type, unsigned char rc, unsigned char wb, unsigned char src, unsigned char dst, unsigned char con, unsigned char bb) {
    printf("%04X: %s ", PC, getInstructionName(type));

    // Print the fields based on the instruction type
    if (type == ADD || type == ADDC || type == SUB || type == SUBC || type == DADD || type == CMP || type == XOR || type == AND || type == OR || type == BIT || type == BIC || type == BIS) {
        if (!rc) printf("RC: %d WB: %d SRC: R%d DST: R%d\n", rc, wb, src, dst);
        else printf("RC: %d WB: %d CON: #%d DST: R%d\n", rc, wb, con, dst);
        printf("Registers: ");
        printf("R%d: %04X ", src, reg_file[src]);
    }
    else if (type == MOV) {
        printf("WB: %d SRC: R%d DST: R%d\n", wb, src, dst);
        printf("Registers: ");
        printf("R%d: %04X ", src, reg_file[src]);
    }
    else if (type == SWAP) {
        printf("SRC: R%d DST: R%d\n", src, dst);
        printf("Registers: ");
        printf("R%d: %04X ", src, reg_file[src]);
    }
    else if (type == SWPB || type == SXT) {
        printf("DST: R%d\n", dst);
        printf("Registers: ");
    }
    else if (type == SRA || type == RRC) {
        printf("WB: %d DST: R%d\n", wb, dst);
        printf("Registers: ");
    }
    else if (type == MOVL || type == MOVLZ || type == MOVLS || type == MOVH) {
        printf("DST: R%d BB: %d\n", dst, bb);
        printf("Registers: ");
    }
    else {
        printf("\n");
    }

    // Print the destination register values
    printf("R%d: %04X\n", dst, reg_file[dst]);


    // Print the PSW values
    printf("PSW: [ Z: %d N: %d V: %d C: %d ]\n\n", psw.ZF, psw.SF, psw.OF, psw.CF);
}
