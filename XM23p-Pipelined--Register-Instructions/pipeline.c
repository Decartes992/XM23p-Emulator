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
    int instruction_count = 1;
    unsigned char rc, wb, src, dst, con, bb;

    // Initialize the execution
    initialize_execution(PC);

    while (1) {
        printf("Instruction: %d\n\n", instruction_count++);

        F0Stage(PC);
        printf("\n");

        D0Stage(&type, &rc, &wb, &src, &dst, &con, &bb, display, PC);
        tick();

        F1Stage();
        E0Stage(type, rc, wb, src, dst, con, bb);

        // Print the destination register values
        printf("                  Output: R%d: %04X\n", dst, reg_file[dst]);

        // Print the PSW values
        printf("                  PSW: [ Z: %d N: %d V: %d C: %d ]\n\n", psw.ZF, psw.SF, psw.OF, psw.CF);

        tick();

        if (IR == 0x0000 || *PC == breakpoint) {
            if (display) {
                printf("%04X: %04X\n", *PC, IR);
                if (*PC == breakpoint) {
                    printf("Breakpoint reached at %04X. Execution stopped.\n\n", *PC);
                }
                else {
                    printf("End of program reached. Execution stopped.\n\n");
                }
            }
            break;
        }
    }
}

void initialize_execution(unsigned short* PC) {
    printf("\n");
    printf("Pipeline Execution:\n\n");
    printf("Start Address: %04X\n", *PC);
    printf("Clock Ticks: %ld\n", clock_ticks);
    printf("Initializing Instructions:\n\n");
    F0Stage(PC);
    F1Stage();
    printf("\n");
    tick();
}

void F0Stage(unsigned short* PC) {
    IMAR = *PC;
    ICTRL = READ;
    *PC += 2;
    printf("        F0 Stage: IMAR: %04X ICTRL: %d\n\n", IMAR, ICTRL);
}

void D0Stage(InstructionType* type, unsigned char* rc, unsigned char* wb, unsigned char* src, unsigned char* dst, unsigned char* con, unsigned char* bb, int display, unsigned short* PC) {
    *type = getInstructionType(IR);
    extractFields(IR, *type, rc, wb, src, dst, con, bb);
    printf("        D0 Stage: IR: %04X\n\n", IR);

    if (display) {
        printDecodedInstruction(*PC, *type, *rc, *wb, *src, *dst, *con, *bb);
    }
}

void F1Stage() {
    IR = IMEM[IMAR / 2];
    printf("        F1 Stage: IR: %04X\n\n", IR);
}

void E0Stage(InstructionType type, unsigned char rc, unsigned char wb, unsigned char src, unsigned char dst, unsigned char con, unsigned char bb) {
    if (type != INVALID) {
        printf("        E0 Stage: Executing instruction...\n\n");
        unsigned short operand = getOperand(rc, src);
        executeInstruction(type, operand, rc, wb, src, dst, con, bb);
    }
}

void tick() {
    clock_ticks++;
    printf("    Clock Ticks: %ld\n\n", clock_ticks);
}
