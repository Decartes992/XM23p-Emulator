#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include "loader.h"
#include "pipeline.h"
#include "execute_instructions.h"

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

    if (display) printf("Clock  PC   Instruction      Fetch      Decode      Execute    Z N V C\n");
    printf("--------------------------------------------------------------------------\n");
    int count = 0;
    isBranch = 0;
    while (!(IR == 0x0000 || *PC == breakpoint || interrupted)) {

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

        // Memory access stage
        if (type == LD || type == LDR || type == ST || type == STR) {
            E1Stage();  // Add the memory access completion stage
        }

        IR = IMEM[(*PC - 2) / 2];

        printDecodedInstruction(*PC, type);

        if (display) StatusPrint(PC, IR_prev);
        displayRegisters();

        tick();
        count++;
    }
    interrupted = 0;
    // Proceed with the rest of the function
    if (display) {
        if (*PC == breakpoint) {
            printf("Breakpoint reached at %04X. Execution stopped.\n\n", *PC);
        }
        else if (interrupted) {
            printf("Execution interrupted by user. Stopping...\n\n");
        }
        else {
            printf("End of program reached. Execution stopped.\n\n");
        }
    }

    return;
}

void D0Stage(InstructionType* type) {
    *type = getInstructionType(IR);
    extractFields(IR, *type);
}

void E0Stage(InstructionType type) {
         // Save register contents to file
    if (type != INVALID) {
        unsigned short operand = getOperand(rc, src);
        executeInstruction(type, operand);
        saveRegisterInfoToFile();
    }
}

void F0Stage() {
    IMAR = *PC/2;
    ICTRL = READ;
    *PC += 2;
}

void F1Stage() {
    IR = IMEM[IMAR];
}

void E1Stage() {
    //if (DCTRL == READ) {
    //    DMBR = memory_read_byte(DMAR);
    //}
    //else if (DCTRL == WRITE) {
    //    memory_write_byte(DMAR, DMBR);
    //}
}


void tick() {
    clock_ticks++;
}

void StatusPrint(unsigned short IR_prev) {
    if (clock_ticks % 2 == 0)
        printf("  %-3d %-9X %-10X F0: %-7X D0: %-5X \n", clock_ticks, IMAR, IMEM[IMAR / 2], IMAR, IR);
    else
        printf("  %-24d F1: %-19X E0: %-7X %d %d %d %d\n", clock_ticks, IR, IR_prev, psw.ZF, psw.SF, psw.OF, psw.CF);
}
