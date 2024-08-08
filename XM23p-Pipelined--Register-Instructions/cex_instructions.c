/*
Name: Iftekhar Rafi
ID: B00871031
Course: ECED 3403 Computer Architecture
Instructor: Larry Hughes

File Name: cex_instructions.c
File Purpose: This file contains the implementation of the CEX instructions.
*/

#include "cex_instructions.h"
#include "loader.h"
#include "decode_instructions.h"


void execute_cex() {
    // This function manages the conditional execution of instructions
    // It establishes the cex_flag based on the condition prefix
    // TC and FC are set to determine the number of instructions to execute or skip
    enum { EQ, NE, CSHS, CCLO, MI, PL, VS, VC, HI, LS, GE, LT, GT, LE, TR, FL };

    switch (C) {
    case EQ:  // Zero flag set
        cex_flag = (psw.ZF == TRUE);
        break;
    case NE:  // Zero flag not set
        cex_flag = (psw.ZF == FALSE);
        break;
    case CSHS:  // Carry flag set
        cex_flag = (psw.CF == TRUE);
        break;
    case CCLO:  // Carry flag clear
        cex_flag = (psw.CF == FALSE);
        break;
    case MI:  // Negative flag set
        cex_flag = (psw.SF == TRUE);
        break;
    case PL:  // Negative flag clear
        cex_flag = (psw.SF == FALSE);
        break;
    case VS:  // Overflow flag set
        cex_flag = (psw.OF == TRUE);
        break;
    case VC:  // Overflow flag clear
        cex_flag = (psw.OF == FALSE);
        break;
    case HI:  // Carry flag set and Zero flag clear
        cex_flag = (psw.CF == TRUE && psw.ZF == FALSE);
        break;
    case LS:  // Carry flag clear or Zero flag set
        cex_flag = (psw.CF == FALSE || psw.ZF == TRUE);
        break;
    case GE:  // Sign flag equals Overflow flag
        cex_flag = (psw.SF == psw.OF);
        break;
    case LT:  // Sign flag not equal to Overflow flag
        cex_flag = (psw.SF != psw.OF);
        break;
    case GT:  // Zero flag clear and Sign flag equals Overflow flag
        cex_flag = (psw.ZF == FALSE && psw.SF == psw.OF);
        break;
    case LE:  // Zero flag set or Sign flag not equal to Overflow flag
        cex_flag = (psw.ZF == TRUE || psw.SF != psw.OF);
        break;
    case TR:  // Always true
        cex_flag = TRUE;
        break;
    case FL:  // Always false
        cex_flag = FALSE;
        break;
    default:
        printf("Error: Invalid condition prefix\n");
        break;
    }

    TC = T;
    FC = F;
}

void execute_cex_instructions(InstructionType instruction_number) {
    // This function handles the effect of the CEX instruction on subsequent instructions
    // Executes the instruction if the condition is true, otherwise skips it
    // Adjusts the True and False counters accordingly

    if (cex_flag == TRUE) {
        if (TC > 0) {
            unsigned short operand = getOperand(rc, src);
            executeInstruction(instruction_number, operand);
            TC--;
        }
        else {
            printf("CEX skip\n");
            FC--;
        }
    }
    else {
        if (TC > 0) {
            printf("CEX skip\n");
            TC--;
        }
        else {
            unsigned short operand = getOperand(rc, src);
            executeInstruction(instruction_number, operand);
            FC--;
        }
    }
}
