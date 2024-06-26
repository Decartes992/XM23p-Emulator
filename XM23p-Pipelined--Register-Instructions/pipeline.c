/*
Name: Iftekhar Rafi
ID: B00871031
Course: ECED 3403 Computer Architecture
Instructor: Larry Hughes

File Name: pipeline.c
File Purpose: This file contains functions to fetch, decode, and execute instructions from IMEM.
*/

#include <stdio.h>
#include "loader.h"
#include "pipeline.h"
#include "decode_instructions.h"
#include "execute_instructions.h"
#include "instructions.h"

extern unsigned short breakpoint;
unsigned short IMAR;
unsigned short ICTRL;
unsigned short IR;
unsigned long clock_ticks; // Global variable to store clock ticks


void pipelineExecute(unsigned short* PC, int display) {
    InstructionType type;
    unsigned char rc, wb, src, dst, con, bb;

    while (1) {

        F0Stage(PC);
        D0Stage(&type, &rc, &wb, &src, &dst, &con, &bb);

        tick();

        F1Stage();
        E0Stage(type, rc, wb, src, dst, con, bb);

        tick();

        if (display) {
            printDecodedInstruction(IR, *PC, type, rc, wb, src, dst, con, bb);
        }

        if (IR == 0x0000 || *PC == breakpoint) {
            if (display) {
                printf("%04X: %04X\n", *PC, IR);
                if (*PC == breakpoint) {
                    printf("Breakpoint reached at %04X. Execution stopped.\n", *PC);
                }
            }
            break;
        }
    }
}

void F0Stage(unsigned short* PC) {
    IMAR = *PC;
    ICTRL = READ;
    *PC += 2;
}

void D0Stage(InstructionType* type, unsigned char* rc, unsigned char* wb, unsigned char* src, unsigned char* dst, unsigned char* con, unsigned char* bb) {
    *type = getInstructionType(IR);
    extractFields(IR, *type, rc, wb, src, dst, con, bb);
}

void F1Stage() {
    IR = IMEM[IMAR / 2];
}

void E0Stage(InstructionType type, unsigned char rc, unsigned char wb, unsigned char src, unsigned char dst, unsigned char con, unsigned char bb) {
    if (type != INVALID) {
        executeInstruction(type, rc, wb, src, dst, con, bb);
    }
}

void tick() {
    clock_ticks++;
}