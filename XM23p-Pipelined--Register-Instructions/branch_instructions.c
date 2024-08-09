/*
Name: Iftekhar Rafi
ID: B00871031
Course: ECED 3403 Computer Architecture
Instructor: Larry Hughes

File Name: branch_instructions.c
File Purpose: This file contains the implementation of the branch instructions.
*/

#include "loader.h"
#include "register_instructions.h"  // For PSW flags
#include "branch_instructions.h"

// Implementations of branch instructions

// Branch with Link (BL)
// Saves the current PC to the Link Register (LR) and updates the PC with the offset
void execute_BL(void) {
    *LR = *PC;          // Save the current PC to the Link Register
    *PC += offset_BL;   // Update the PC with the offset for BL
}

// Branch if Equal or Branch if Zero (BEQBZ)
// Updates the PC with the offset if the Zero Flag (ZF) is set
void execute_BEQBZ(void) {
    if (psw.ZF == TRUE) {  // Check if the Zero Flag is set
        *PC += offset_BR;  // Update the PC with the offset for BEQBZ
    }
}

// Branch if Not Equal or Branch if Not Zero (BNEBNZ)
// Updates the PC with the offset if the Zero Flag (ZF) is not set
void execute_BNEBNZ(void) {
    if (psw.ZF == FALSE) {  // Check if the Zero Flag is not set
        *PC += offset_BR;   // Update the PC with the offset for BNEBNZ
    }
}

// Branch if Carry Set or Branch if Higher or Same (BCBHS)
// Updates the PC with the offset if the Carry Flag (CF) is set
void execute_BCBHS(void) {
    if (psw.CF == TRUE) {  // Check if the Carry Flag is set
        *PC += offset_BR;  // Update the PC with the offset for BCBHS
    }
}

// Branch if Not Carry or Branch if Lower (BNCBLO)
// Updates the PC with the offset if the Carry Flag (CF) is not set
void execute_BNCBLO(void) {
    if (psw.CF == FALSE) {  // Check if the Carry Flag is not set
        *PC += offset_BR;   // Update the PC with the offset for BNCBLO
    }
}

// Branch if Negative (BN)
// Updates the PC with the offset if the Sign Flag (SF) is set
void execute_BN(void) {
    if (psw.SF == TRUE) {  // Check if the Sign Flag is set
        *PC += offset_BR;  // Update the PC with the offset for BN
    }
}

// Branch if Greater or Equal (BGE)
// Updates the PC with the offset if the Sign Flag (SF) equals the Overflow Flag (OF)
void execute_BGE(void) {
    if (psw.SF == psw.OF) {  // Check if the Sign Flag equals the Overflow Flag
        *PC += offset_BR;    // Update the PC with the offset for BGE
    }
}

// Branch if Less Than (BLT)
// Updates the PC with the offset if the Sign Flag (SF) does not equal the Overflow Flag (OF)
void execute_BLT(void) {
    if (psw.SF != psw.OF) {  // Check if the Sign Flag does not equal the Overflow Flag
        *PC += offset_BR;    // Update the PC with the offset for BLT
    }
}

// Branch Always (BRA)
// Unconditionally updates the PC with the offset
void execute_BRA(void) {
    *PC += offset_BR;  // Update the PC with the offset for BRA
}
