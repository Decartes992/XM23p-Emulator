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
    unsigned short IR_prev = 0;
    unsigned char rc, wb, src, dst, con, bb, v = psw.OF, c = psw.CF, slp = psw.slp, z = psw.ZF, n = psw.SF;
    IR = 0x6800;


    printf("Clock  PC   Instruction      Fetch      Decode      Execute    Z N V C\n");
    printf("--------------------------------------------------------------------------\n");

    while (1) {

        F0Stage(PC);
        D0Stage(&type, &rc, &wb, &src, &dst, &con, &bb, display, PC, &v, &c, &slp, &n, &z);

        if (display) printf("  %-3d %-9X %-10X F0: %-7X D0: %-5X \n", clock_ticks, *PC - 2, IMEM[IMAR / 2], IMAR, IR);

        tick();
        IR_prev = IR;
        F1Stage();
        E0Stage(type, rc, wb, src, dst, con, bb, v, c, slp, n, z);


        if(display) printf("  %-24d F1: %-19X E0: %-7X %d %d %d %d\n", clock_ticks, IR, IR_prev, psw.ZF, psw.SF, psw.OF, psw.CF);


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

}

void F0Stage(unsigned short* PC) {
    IMAR = *PC;
    ICTRL = READ;
    *PC += 2;
}

void D0Stage(InstructionType* type, unsigned char* rc, unsigned char* wb, unsigned char* src, unsigned char* dst, unsigned char* con, unsigned char* bb, int display, unsigned short* PC, unsigned char* v, unsigned char* c, unsigned char* slp, unsigned char* n, unsigned char* z) {
    *type = getInstructionType(IR);
    extractFields(IR, *type, rc, wb, src, dst, con, bb, v, c, slp, n, z);
}

void F1Stage() {
    IR = IMEM[IMAR / 2];
}

void E0Stage(InstructionType type, unsigned char rc, unsigned char wb, unsigned char src, unsigned char dst, unsigned char con, unsigned char bb, unsigned char* v, unsigned char* c, unsigned char* slp, unsigned char* n, unsigned char* z) {
    if (type != INVALID) {
        unsigned short operand = getOperand(rc, src);
        executeInstruction(type, operand, rc, wb, src, dst, con, bb, v, c, slp, n, z);
    }
}

void tick() {
    clock_ticks++;
}
