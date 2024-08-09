/*
Name: Iftekhar Rafi
ID: B00871031
Course: ECED 3403 Computer Architecture
Instructor: Larry Hughes

File Name: pipeline.c
File Purpose: This file contains the pipeline functions for the execution of instructions
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include "loader.h"
#include "pipeline.h"
#include "execute_instructions.h"
#include "cex_instructions.h"

// Global variable to keep track of interrupt signal
volatile sig_atomic_t interrupted = 0;


// Signal handler function
void handle_sigint(int sig) {
    interrupted = 1;
}

void pipelineExecute(int display, const char step) {
    // Register the signal handler for SIGINT
    signal(SIGINT, handle_sigint);

    InstructionType type;
    int instruction_count = 1;
    unsigned short IR_prev;
    unsigned short IR_prev_dummy = 0;
    IR = 0x6800; // Set the initial instruction to the start of the program
    int count = 0;
    isBranch = 0;
    type = getInstructionType(IR);

    if (display) StatusPrint(IR_prev_dummy);

    while (!(IR == 0x0000 || *PC == breakpoint || interrupted)) {

        F0Stage();        // Fetch the instruction


        D0Stage(&type);        // Decode the instruction

        tick();

        if (display) StatusPrint(IR_prev_dummy);

        IR_prev = IR;        // Save the current instruction to the previous instruction register


        F1Stage();        // Set instruction register to the next instruction


        E0Stage(type);        // Execute the instruction



        E1Stage(type); // Execute memory access completion stage

        IR = IMEM[(*PC - 2) / 2];

        //printDecodedInstruction(*PC, type);

        tick();

        if (display) StatusPrint(IR);
        //displayRegisters();

        count++;
        isBranch = FALSE;
        if (step == 'y' || step == 'Y') getchar(); // Wait for user input to continue

        // Check if the loop was exited due to an interrupt
        if (interrupted) {
            printf("Execution interrupted by user. Stopping...\n\n");
            break; // Exit the loop
        }
    }

    // Proceed with the rest of the function
    if (display) {
        if (*PC == breakpoint) {
            printf("Breakpoint reached at %04X. Execution stopped.\n\n", *PC);
        }
        else if (IR == 0x0000) {
            printf("End of program reached. Execution stopped.\n\n");
        }
    }

    // Reset the interrupted flag
    interrupted = 0;
}

void D0Stage(InstructionType* type) {
    *type = getInstructionType(IR);
    extractFields(IR, *type);
}

void E0Stage(InstructionType type) {
    if (type == CEX) {
        execute_cex();
    }

    if (((TC == 0) && (FC == 0)) || type == CEX) { // CEX disabled
        if (!(type == LD || type == LDR || type == ST || type == STR)) {
            unsigned short operand = getOperand(rc, src);
            executeInstruction(type, operand);
        }
    }
    else { // CEX enabled
        execute_cex_instructions(type); // handle executions accordingly
    }
}

void F0Stage() {
    IMAR = *PC / 2;
    ICTRL = READ;
    *PC += 2;
}

void F1Stage() {
    IR = IMEM[IMAR];
}

void E1Stage(InstructionType type) {
    if (type == LD || type == LDR || type == ST || type == STR) {
        unsigned short operand = getOperand(rc, src);
        executeInstruction(type, operand);
    }
}

void tick() {
    clock_ticks++;
}

void StatusPrint(unsigned short IR_prev) {
    if (clock_ticks != 0) {
        if (clock_ticks % 2 == 0) {
            printf("  %-3d %-9X %-10X F0: %-7X D0: %-5X \n", clock_ticks, IMAR * 2, IMEM[IMAR], *PC, IR);
        }
        else {
            printf("  %-24d F1: %-19X E0: %-7X %d %d %d %d\n", clock_ticks, IR, IMEM[(*PC - 4) / 2], psw.ZF, psw.SF, psw.OF, psw.CF);
        }
    }
    else {
        printf("Clock  PC   Instruction      Fetch      Decode      Execute    Z N V C\n");
        printf("--------------------------------------------------------------------------\n");
    }
}
