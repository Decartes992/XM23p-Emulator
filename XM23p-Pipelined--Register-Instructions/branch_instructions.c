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
void execute_BL(void) {
    isBranch = TRUE;
    *LR = *PC;
    *PC += offset_BL;
}

void execute_BEQBZ(void) {
    isBranch = TRUE;
    if (psw.ZF == TRUE) {
        *PC += offset_BR;
    }
}

void execute_BNEBNZ(void) {
    isBranch = TRUE;
    if (psw.ZF == FALSE) {
        *PC += offset_BR;
    }
}

void execute_BCBHS(void) {
    isBranch = TRUE;
    if (psw.CF == TRUE) {
        *PC += offset_BR;
    }
}

void execute_BNCBLO(void) {
    isBranch = TRUE;
    if (psw.CF == FALSE) {
        *PC += offset_BR;
    }
}

void execute_BN(void) {
    isBranch = TRUE;
    if (psw.SF == TRUE) {
        *PC += offset_BR;
    }
}

void execute_BGE(void) {
    isBranch = TRUE;
    if (psw.SF == psw.OF) {
        *PC += offset_BR;
    }
}

void execute_BLT(void) {
    isBranch = TRUE;
    if (psw.SF != psw.OF) {
        *PC += offset_BR;
    }
}

void execute_BRA(void) {
    isBranch = TRUE;
    *PC += offset_BR;
}
