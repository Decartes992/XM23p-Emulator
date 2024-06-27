/*
Name: Iftekhar Rafi
ID: B00871031
Course: ECED 3403 Computer Architecture
Instructor: Larry Hughes

File Name: debugger_mode.c
File Purpose: This file contains the runMode function which executes instructions and shows memory contents and decoded instructions if in debug mode.
*/

#include <stdio.h>
#include "loader.h"
#include "pipeline.h"


void runMode(int debug) {
    unsigned short PC = 0x1000;

    pipelineExecute(&PC, debug);

    // Check for breakpoint or end of instructions
    if (IR == 0x0000 || PC == breakpoint) {
        if (IR == 0x0000 || PC == breakpoint) {
            if (debug) {
                printf("Program terminated at address %04X.\n", PC);
                if (PC == breakpoint) {
                    printf("Breakpoint reached at %04X. Execution stopped.\n", PC);
                }
            }
        }
    }
}

// Function to display register contents
void displayRegisters() {
    printf("Register Contents:\n");
    for (int i = 0; i < REGFILE_SIZE; i++) {
        printf("R%d: %04X\n", i, reg_file[i]);
    }
    printf("\n");
}

// Function to change register contents
void changeRegister() {
    int reg;
    unsigned short value;
    printf("Enter register number (0-7): ");
    scanf("%d", &reg);
    if (reg < 0 || reg >= REGFILE_SIZE) {
        printf("Invalid register number.\n");
        return;
    }
    printf("Enter new value (in hex): ");
    scanf("%hx", &value);
    reg_file[reg] = value;
    printf("Register R%d changed to %04X\n", reg, value);
}

// Function to change memory contents
void changeMemory() {
    unsigned int address;
    unsigned short value;
    char memType;
    printf("Choose memory to change (I for IMEM, D for DMEM): ");
    scanf(" %c", &memType);
    printf("Enter address (in hex): ");
    scanf("%x", &address);
    printf("Enter new value (in hex): ");
    scanf("%hx", &value);

    if (memType == 'I' || memType == 'i') {
        if (address < IMEM_SIZE) {
            IMEM[address >> 1] = value;  // Store as word
            printf("IMEM[%04X] changed to %04X\n", address >> 1, value);
        }
        else {
            printf("Invalid IMEM address.\n");
        }
    }
    else if (memType == 'D' || memType == 'd') {
        if (address < DMEM_SIZE) {
            DMEM[address >> 1] = value;  // Store as word
            printf("DMEM[%04X] changed to %04X\n", address >> 1, value);
        }
        else {
            printf("Invalid DMEM address.\n");
        }
    }
    else {
        printf("Invalid memory type.\n");
    }
}

// Function to set a breakpoint
void setBreakpoint(unsigned short address) {
    breakpoint = address;
    printf("Breakpoint set at address %04X\n", address);
}
