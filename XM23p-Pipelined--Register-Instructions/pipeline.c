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
#include "execute_instructions.h"



void pipelineExecute(unsigned short* PC, int display) {
    InstructionType type;
    unsigned char rc, wb, src, dst, con, bb;
    printf("\n\n");
    F0Stage(PC);
    F1Stage();
    printf("\n\n");
    tick();


    while (1) {

        F0Stage(PC);
        D0Stage(&type, &rc, &wb, &src, &dst, &con, &bb);

        if (display) {
            printDecodedInstruction(*PC, type, rc, wb, src, dst, con, bb);
        }

        tick();

        F1Stage();


        E0Stage(type, rc, wb, src, dst, con, bb);

        // Print the destination register values
        printf("Output: R%d: %04X\n", dst, reg_file[dst]);

        // Print the PSW values
        printf("PSW: [ Z: %d N: %d V: %d C: %d ]\n\n", psw.ZF, psw.SF, psw.OF, psw.CF);

        tick();

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
    printf("F0 Stage: IMAR: %04X ICTRL: %d\n", IMAR, ICTRL);
}

void D0Stage(InstructionType* type, unsigned char* rc, unsigned char* wb, unsigned char* src, unsigned char* dst, unsigned char* con, unsigned char* bb) {
    *type = getInstructionType(IR);
    extractFields(IR, *type, rc, wb, src, dst, con, bb);
    printf("D0 Stage: IR: %04X\n", IR);
}

void F1Stage() {
    IR = IMEM[IMAR / 2];
    printf("F1 Stage: IR: %04X\n", IR);
}

void E0Stage(InstructionType type, unsigned char rc, unsigned char wb, unsigned char src, unsigned char dst, unsigned char con, unsigned char bb) {
    if (type != INVALID) {
        printf("E0 Stage: Executing instruction...\n");
        executeInstruction(type, rc, wb, src, dst, con, bb);
    }
}

void tick() {
    clock_ticks++;
    printf("Clock Ticks: %ld\n\n", clock_ticks);
}