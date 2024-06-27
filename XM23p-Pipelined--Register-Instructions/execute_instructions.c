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

void executeInstruction(InstructionType type, unsigned char rc, unsigned char wb, unsigned char src, unsigned char dst, unsigned char con, unsigned char bb) {
    unsigned short operand;

    // Determine if the operand is a constant or a register value
    if (rc) {
        operand = con;
    }
    else {
        operand = reg_file[src];
    }

    // Execute the instruction based on the decoded type
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
