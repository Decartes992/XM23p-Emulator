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
#include "debugger_mode.h"


void runMode(int debug) {
    unsigned short * PC = &reg_file[7];  // Start execution at address in R7
    pipelineExecute( PC, debug);          // Execute instructions
    displayRegisters();                  // Display register contents
    saveRegisterInfoToFile();            // Save register contents to file
    return;
}

// Function to display register contents
void displayRegisters() {
    printf("Register Contents:\n");
    for (int i = 0; i < REGFILE_SIZE; i++) {
        printf("R%d: %04X\n", i, reg_file[i]);
    }
    printf("\n");
    return;
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
    return;
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
    return;
}

// Function to set a breakpoint
void setBreakpoint(unsigned short address) {
    breakpoint = address;
    printf("Breakpoint set at address %04X\n", address);
    return;
}

void saveRegisterInfoToFile() {
    FILE* file = fopen("RegisterFile.txt", "w");
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }

    fprintf(file, "Register Contents:\n");
    for (int i = 0; i < REGFILE_SIZE; i++) {
        fprintf(file, "R%d: %04X\n", i, reg_file[i]);
    }

    fclose(file);
    return;
}
//
//
//#include <stdio.h>
//#include "loader.h"
//#include "debugger_mode.h"
//#include "pipeline.h"
//
//// Function to run the program in debug mode
//void runMode(int debug) {
//    unsigned short PC = reg_file[7];
//    if (debug) {
//        while (1) {
//            printf("Debugger> ");
//            char command[80];
//            fgets(command, 80, stdin);
//
//            switch (command[0]) {
//            case 'r': displayRegisters(); break;
//            case 'm': changeMemory(); break;
//            case 'c': changeRegister(); break;
//            case 'b': {
//                unsigned short address;
//                sscanf(command + 1, "%hx", &address);
//                setBreakpoint(address);
//                break;
//            }
//            case 's': {
//                pipelineExecute(&PC, 1);
//                break;
//            }
//            case 'q': return;
//            default: printf("Unknown command\n");
//            }
//        }
//    }
//    else {
//        pipelineExecute(&PC, 0);
//    }
//}
//
//// Display register contents
//void displayRegisters() {
//    for (int i = 0; i < 8; i++) {
//        printf("R%d: %04X\n", i, reg_file[i]);
//    }
//    printf("PSW: Z=%d N=%d V=%d C=%d SLP=%d\n", psw.ZF, psw.SF, psw.OF, psw.CF, psw.slp);
//}
//
//// Change register contents
//void changeRegister() {
//    unsigned short reg, value;
//    printf("Enter register number (0-7): ");
//    scanf("%hx", &reg);
//    printf("Enter new value (hex): ");
//    scanf("%hx", &value);
//    if (reg < 8) {
//        reg_file[reg] = value;
//    }
//    else {
//        printf("Invalid register number\n");
//    }
//}
//
//// Change memory contents
//void changeMemory() {
//    unsigned short address, value;
//    printf("Enter memory address (hex): ");
//    scanf("%hx", &address);
//    printf("Enter new value (hex): ");
//    scanf("%hx", &value);
//    if (address < DMEM_SIZE) {
//        DMEM[address] = value;
//    }
//    else {
//        printf("Invalid memory address\n");
//    }
//}
//
//// Set breakpoint
//void setBreakpoint(unsigned short address) {
//    breakpoint = address;
//    printf("Breakpoint set at %04X\n", address);
//}
//
//// Save register information to file
//void saveRegisterInfoToFile() {
//    FILE* file = fopen("registers.txt", "w");
//    if (file) {
//        for (int i = 0; i < 8; i++) {
//            fprintf(file, "R%d: %04X\n", i, reg_file[i]);
//        }
//        fprintf(file, "PSW: Z=%d N=%d V=%d C=%d SLP=%d\n", psw.ZF, psw.SF, psw.OF, psw.CF, psw.slp);
//        fclose(file);
//        printf("Register information saved to registers.txt\n");
//    }
//    else {
//        printf("Error opening file for writing\n");
//    }
//}
