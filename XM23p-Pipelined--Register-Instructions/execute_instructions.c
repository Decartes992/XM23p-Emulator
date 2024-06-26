/*
Name: Iftekhar Rafi
ID: B00871031
Course: ECED 3403 Computer Architecture
Instructor: Larry Hughes

File Name: execute_instructions.c
File Purpose: This file contains the function to execute instructions.
*/

#include "loader.h"
#include "execute_instructions.h"
#include "instructions.h"

// Function prototypes for instruction functions
void executeADD(unsigned char dst, unsigned short operand);
void executeADDC(unsigned char dst, unsigned short operand);
void executeSUB(unsigned char dst, unsigned short operand);
void executeSUBC(unsigned char dst, unsigned short operand);
void executeDADD(unsigned char dst, unsigned short operand);
void executeCMP(unsigned char dst, unsigned short operand);
void executeXOR(unsigned char dst, unsigned short operand);
void executeAND(unsigned char dst, unsigned short operand);
void executeOR(unsigned char dst, unsigned short operand);
void executeBIT(unsigned char dst, unsigned short operand);
void executeBIC(unsigned char dst, unsigned short operand);
void executeBIS(unsigned char dst, unsigned short operand);
void executeMOV(unsigned char dst, unsigned short operand);
void executeSWAP(unsigned char dst);
void executeSRA(unsigned char dst);
void executeRRC(unsigned char dst);
void executeSWPB(unsigned char dst);
void executeSXT(unsigned char dst);
void executeMOVLZ(unsigned char dst, unsigned short operand);
void executeMOVL(unsigned char dst, unsigned short operand);
void executeMOVLS(unsigned char dst, unsigned short operand);
void executeMOVH(unsigned char dst, unsigned short operand);

void executeInstruction(InstructionType type, unsigned char rc, unsigned char wb, unsigned char src, unsigned char dst, unsigned char con, unsigned char bb) {
    unsigned short operand;

    if (rc) {
        operand = con;
    }
    else {
        operand = reg_file[src];
    }

    switch (type) {
    case ADD:
        executeADD(dst, operand);
        break;
    case ADDC:
        executeADDC(dst, operand);
        break;
    case SUB:
        executeSUB(dst, operand);
        break;
    case SUBC:
        executeSUBC(dst, operand);
        break;
    case DADD:
        executeDADD(dst, operand);
        break;
    case CMP:
        executeCMP(dst, operand);
        break;
    case XOR:
        executeXOR(dst, operand);
        break;
    case AND:
        executeAND(dst, operand);
        break;
    case OR:
        executeOR(dst, operand);
        break;
    case BIT:
        executeBIT(dst, operand);
        break;
    case BIC:
        executeBIC(dst, operand);
        break;
    case BIS:
        executeBIS(dst, operand);
        break;
    case MOV:
        executeMOV(dst, operand);
        break;
    case SWAP:
        executeSWAP(dst);
        break;
    case SRA:
        executeSRA(dst);
        break;
    case RRC:
        executeRRC(dst);
        break;
    case SWPB:
        executeSWPB(dst);
        break;
    case SXT:
        executeSXT(dst);
        break;
    case MOVLZ:
        executeMOVLZ(dst, operand);
        break;
    case MOVL:
        executeMOVL(dst, operand);
        break;
    case MOVLS:
        executeMOVLS(dst, operand);
        break;
    case MOVH:
        executeMOVH(dst, operand);
        break;
    default:
        // Handle invalid instruction or not implemented
        break;
    }
}
