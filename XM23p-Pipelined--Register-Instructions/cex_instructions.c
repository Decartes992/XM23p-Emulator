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
    // This function handles the effect of the CEX instruction on subsequent instructions.
    // Executes the instruction if the condition is true, otherwise skips it.
    // Adjusts the True and False counters accordingly.

    static unsigned short PC_prev = 0; // Store the previous value of the Program Counter (PC)
    static unsigned char in_subroutine = 0; // Flag to indicate if in a subroutine

    // Check if the condition for execution is true
    if (cex_flag == TRUE) {
        // If there are instructions left to execute under the true condition
        if (TC > 0) {
            // Check if the current instruction is a branch or if the PC has changed
            if (isBranch || PC_prev != *PC) {
                in_subroutine = 1; // Set flag to indicate a branch or subroutine entry
            }
            else if (in_subroutine && PC_prev == *PC) {
                in_subroutine = 0; // Reset flag if PC has returned to previous value
            }

            // Get the operand for the instruction
            unsigned short operand = getOperand(rc, src);
            // Execute the instruction
            executeInstruction(instruction_number, operand);
            // Update the Instruction Register (IR) with the current instruction
            IR = IMEM[(*PC - 2) / 2];

            // Decrement TC only if not in a branch or subroutine
            if (!in_subroutine) TC--;
        }
        else {
            // If no instructions left to execute under the true condition, skip
            printf("CEX skip\n");
            FC--; // Decrement the false counter
        }
    }
    else {
        // If the condition for execution is false
        if (TC > 0) {
            // Skip the instruction and decrement the true counter
            printf("CEX skip\n");
            TC--;
        }
        else {
            // If no instructions left to skip under the false condition
            if (isBranch || PC_prev != *PC) {
                in_subroutine = 1; // Set flag to indicate a branch or subroutine entry
            }
            else if (in_subroutine && PC_prev == *PC) {
                in_subroutine = 0; // Reset flag if PC has returned to previous value
            }

            // Get the operand for the instruction
            unsigned short operand = getOperand(rc, src);
            // Execute the instruction
            executeInstruction(instruction_number, operand);
            // Update the Instruction Register (IR) with the current instruction
            IR = IMEM[(*PC - 2) / 2];

            // Decrement FC only if not in a branch or subroutine
            if (!in_subroutine) FC--;
        }
    }

    // Update PC_prev to the current PC value
    PC_prev = *PC;
}



// Older version of the function execute_cex_instructions with comments added 
//and function checks for subroutine calls through both branches and register instructions
#ifdef USE_OLD_CODE 
          
void execute_cex_instructions(InstructionType instruction_number) {
    // This function handles the effect of the CEX instruction on subsequent instructions.
    // Executes the instruction if the condition is true, otherwise skips it.
    // Adjusts the True and False counters accordingly.

    unsigned short state = 0; // State to track if a branch or subroutine is entered
    unsigned short PC_prev = *PC; // Store the previous value of the Program Counter (PC)

    // Check if the condition for execution is true
    if (cex_flag == TRUE) {
        // If there are instructions left to execute under the true condition
        if (TC > 0) {
            // Check if the current instruction is a branch or if the PC has changed
            if (isBranch || PC_prev != *PC) {
                PC_prev = *PC + 2; // Update PC_prev to the new PC value
                state = 1; // Set state to indicate a branch or subroutine entry
            }
            if (PC_prev == *PC) state = 0; // Reset state if PC has not changed

            // Get the operand for the instruction
            unsigned short operand = getOperand(rc, src);
            // Execute the instruction
            executeInstruction(instruction_number, operand);
            // Update the Instruction Register (IR) with the current instruction
            IR = IMEM[(*PC - 2) / 2];

            // Decrement TC only if not in a branch or subroutine
            if (state != 1) TC--;
        }
        else {
            // If no instructions left to execute under the true condition, skip
            printf("CEX skip\n");
            FC--; // Decrement the false counter
        }
    }
    else {
        // If the condition for execution is false
        if (TC > 0) {
            // Skip the instruction and decrement the true counter
            printf("CEX skip\n");
            TC--;
        }
        else {
            // If no instructions left to skip under the false condition
            if (isBranch || PC_prev != *PC) {
                PC_prev = *PC + 2; // Update PC_prev to the new PC value
                state = 1; // Set state to indicate a branch or subroutine entry
            }
            if (PC_prev == *PC) state = 0; // Reset state if PC has not changed

            // Get the operand for the instruction
            unsigned short operand = getOperand(rc, src);
            // Execute the instruction
            executeInstruction(instruction_number, operand);
            // Update the Instruction Register (IR) with the current instruction
            IR = IMEM[(*PC - 2) / 2];

            // Decrement FC only if not in a branch or subroutine
            if (state != 1) FC--;
        }
    }
}
#endif // !1


// Older version of the function  without comments and 
// function checks for subroutine calls through branches only
#ifdef USE_OLD_CODE

void execute_cex_instructions(InstructionType instruction_number) {
    // This function handles the effect of the CEX instruction on subsequent instructions
    // Executes the instruction if the condition is true, otherwise skips it
    // Adjusts the True and False counters accordingly
    unsigned short state = 0;
    unsigned short PC_prev = *PC;
    if (cex_flag == TRUE) {
        if (TC > 0) {
            if (isBranch) {
                PC_prev = *PC + 2;
                state = 1;
            }
            if (PC_prev == *PC) state = 0;

            unsigned short operand = getOperand(rc, src);
            executeInstruction(instruction_number, operand);
            IR = IMEM[(*PC - 2) / 2];

            if (state != 1) TC--;
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
            if (isBranch) {
                PC_prev = *PC + 2;
                state = 1;
            }
            if (PC_prev == *PC) state = 0;
            unsigned short operand = getOperand(rc, src);
            executeInstruction(instruction_number, operand);
            IR = IMEM[(*PC - 2) / 2];
            if (state != 1) FC--;

        }
    }
}


#endif // !1