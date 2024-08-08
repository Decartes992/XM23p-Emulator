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
    // Extract common fields
    rc = (instruction >> 7) & 0x01;    // RC is at bit 7
    wb = (instruction >> 6) & 0x01;    // WB is at bit 6
    src = (instruction >> 3) & 0x07;   // SRC/CON is at bits 5-3
    dst = instruction & 0x07;          // DST is at bits 2-0
    con = src;                         // CON is the same as SRC/CON
    bb = (instruction >> 3) & 0xFF;    // BB is at bits 10-3 (byte-level data)

    switch (type) {
    case LD: case ST: case LDR: case STR:
        prpo = (instruction >> 10) & 0x01; // PRPO is at bit 10
        dec = (instruction >> 8) & 0x01;   // DEC is at bit 9
        inc = (instruction >> 7) & 0x01;   // INC is at bit 8
        offset_DR = ((instruction >> 7) & 0x7f); // get the offset bit (LDR-STR)
        break;
    case SETCC: case CLRCC:
        v = (instruction >> 4) & 0x01; // V is bit 4
        c = instruction & 0x01;        // C is bit 0
        n = (instruction >> 2) & 0x01; // N is bit 2
        z = (instruction >> 1) & 0x01; // Z is bit 1
        slp = (instruction >> 5) & 0x01; // SLP is bit 5
        break;
    case BEQ: case BNE: case BC: case BNC: case BN: case BGE: case BLT: case BRA:
        offset_BR = (instruction & 0x03FF); // get the offset bit (BR-BRA)
        offset_BR = SignExt(offset_BR, 9); // Sign-extend the offset buffer (was 9 bits)
        break;
    case BL:
        offset_BL = ((instruction) & 0x1FFF); // get the offset bit (BL)
        offset_BL = SignExt(offset_BL, 12); // Sign-extend the offset buffer (was 12 bits)
        break;
    case CEX:
        C = (instruction >> 6) & 0x0F;  // C is at bits 9-6
        T = (instruction >> 3) & 0x07;  // T is at bits 5-3
        F = instruction & 0x07;         // F is at bits 2-0
        break;
    }

    if (type == SETCC || type == CLRCC) {
        // Additional processing if needed
    }
}


// Updated getInstructionType function to include branch instructions and CEX
InstructionType getInstructionType(unsigned short instruction) {

    // Check for LDR and STR instructions
    switch (instruction & 0xC000) {  // Check bits 15-14
    case 0x8000: return LDR;     // 10xxxxxxxxxx
    case 0xC000: return STR;     // 11xxxxxxxxxx
    }
    // Check for branch instructions
    switch (instruction & 0xE000) {  // Check bits 15-13
    case 0x0000: return BL;       // 000000000000xxxx
    }

    switch (instruction & 0xFC00) {  // Check bits 15-10
    case 0x2000: return BEQ;      
    case 0x2400: return BNE;      
    case 0x2800: return BC;       
    case 0x2C00: return BNC;      
    case 0x3000: return BN;       
    case 0x3400: return BGE;      
    case 0x3800: return BLT;      
    case 0x3C00: return BRA;
    case 0x5800: return LD;      // 010110xxxxxx
    case 0x5C00: return ST;      // 010111xxxxxx
    case 0x5000: return CEX;     // 0101xxxxxxxx
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
    printf("%04x", IR);
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
    else if (type == BEQ || type == BNE || type == BC || type == BNC || type == BN || type == BGE || type == BLT || type == BRA) {
        // For branch instructions, print the offset value
        printf("Offset: #%d\n", offset_BR);
        printf("                  PC: %04X\n", PC);
    }
    else if (type == BL) {
        // For branch instructions, print the offset value
        printf("Offset: #%d\n", offset_BL);
        printf("                  PC: %04X\n", PC);
    }
	else if (type == LD || type == ST || type == LDR || type == STR) {
		printf("PRPO: %d DEC: %d INC: %d Offset: #%d\n", prpo, dec, inc, offset_DR);
		printf("                  Registers: ");
	}
	else if (type == SETCC || type == CLRCC) {
		printf("V: %d C: %d N: %d Z: %d SLP: %d\n", v, c, n, z, slp);
		printf("                  ");
	}
    else {
        printf("\n                  ");
    }

    // Print the destination register values
    if (type != BL && type != BEQ && type != BNE && type != BC && type != BNC && type != BN && type != BGE && type != BLT && type != BRA) {
        printf("R%d: %04X\n", dst, reg_file[dst]);
    }
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


// Function to get the name of the instruction type
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
    case SETCC: return "SETCC";
    case CLRCC: return "CLRCC";
    case LD: return "LD";
    case LDR: return "LDR";
    case ST: return "ST";
    case STR: return "STR";
    case BL: return "BL";
    case BEQ: return "BEQ";
    case BNE: return "BNE";
    case BC: return "BC";
    case BNC: return "BNC";
    case BN: return "BN";
    case BGE: return "BGE";
    case BLT: return "BLT";
    case BRA: return "BRA";
    case CEX: return "CEX";

    default: return "INVALID";
    }
}
