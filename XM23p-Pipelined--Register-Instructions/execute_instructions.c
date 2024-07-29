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

void executeInstruction(InstructionType type, unsigned short operand){
    operand = getOperand(rc, src);

    // Execute the instruction based on the decoded type
    switch (type) {
    case ADD:
        executeADD(dst, operand);
        return;
    case ADDC:
        executeADDC(dst, operand);
        return;
    case SUB:
        executeSUB(dst, operand);
        return;
    case SUBC:
        executeSUBC(dst, operand);
        return;
    case DADD:
        executeDADD(dst, operand);
        return;
    case CMP:
        executeCMP(dst, operand);
        return;
    case XOR:
        executeXOR(dst, operand);
        return;
    case AND:
        executeAND(dst, operand);
        return;
    case OR:
        executeOR(dst, operand);
        return;
    case BIT:
        executeBIT(dst, operand);
        return;
    case BIC:
        executeBIC(dst, operand);
        return;
    case BIS:
        executeBIS(dst, operand);
        return;
    case MOV:
        executeMOV(dst, operand);
        return;
    case SWAP:
        executeSWAP(src, dst);
        return;
    case SRA:
        executeSRA(dst);
        return;
    case RRC:
        executeRRC(dst);
        return;
    case SWPB:
        executeSWPB(dst);
        return;
    case SXT:
        executeSXT(dst);
        return;
    case MOVLZ:
        executeMOVLZ(dst, bb);
        return;
    case MOVL:
        executeMOVL(dst, bb);
        return;
    case MOVLS:
        executeMOVLS(dst, bb);
        return;
    case MOVH:
        executeMOVH(dst, bb);
        return;
    case SETCC:
        executeSETCC(v, c, slp, n, z);
		return;
    case CLRCC:
		executeCLRCC(v, c, slp, n, z);
	    return;
    case LD:
        execute_ld(src, dst);
        return;
    case LDR:
        execute_ldr(src, dst, (char)operand);
        return;
    case ST:
        execute_st(src, dst);
        return;
    case STR:
        execute_str(src, dst, (char)operand);
        return;
    default:
        // Handle invalid instruction or not implemented
        return;
    }
}
