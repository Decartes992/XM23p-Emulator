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

void pipelineExecute(int display) {
    // Register the signal handler for SIGINT
    signal(SIGINT, handle_sigint);

    InstructionType type;
    int instruction_count = 1;
    unsigned short IR_prev = 0;
    IR = 0x6800;
    int count = 0;
    isBranch = 0;
    type = getInstructionType(IR);

    if (display) StatusPrint(IR_prev);

    while (!(IR == 0x0000 || *PC == breakpoint || interrupted)) {
        if (type == LD || type == LDR || type == ST || type == STR) {
            E1Stage(type);  // Execute memory access completion stage
        }

        // Fetch the instruction
        F0Stage();

        // Decode the instruction
        D0Stage(&type);

        if (display) StatusPrint(PC, IR_prev);

        tick();

        // Save the current instruction to the previous instruction register
        IR_prev = IR;

        // Set instruction register to the next instruction
        F1Stage();

        // Execute the instruction
        E0Stage(type);

        IR = IMEM[(*PC - 2) / 2];

        printDecodedInstruction(*PC, type);

        if (display) StatusPrint(PC, IR_prev);
        displayRegisters();

        tick();
        count++;

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
        unsigned short operand = getOperand(rc, src);
        executeInstruction(type, operand);
        saveRegisterInfoToFile();
    }
    else { // CEX enabled
        execute_cex_instructions(IR); // handle executions accordingly
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
    if (type == LD || type == ST) {
        execute_ld();
    }
    else if (type == LDR || type == STR) {
        execute_st();
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
            printf("  %-24d F1: %-19X E0: %-7X %d %d %d %d\n", clock_ticks, IR, IR_prev, psw.ZF, psw.SF, psw.OF, psw.CF);
        }
    }
    else {
        printf("Clock  PC   Instruction      Fetch      Decode      Execute    Z N V C\n");
        printf("--------------------------------------------------------------------------\n");
    }
}
