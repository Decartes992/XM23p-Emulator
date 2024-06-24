/*
Name: Iftekhar Rafi
ID: B00871031
Course: ECED 3403 Computer Architecture
Instructor: Larry Hughes

File Name: manager.c
File Purpose: This file contains the manager function which handles user input for memory display and calls the loadSRecord function to load S-Records from a file into memory.
*/
#include <stdio.h>
#include "loader.h"

unsigned short reg_file[REGFILE_SIZE]; // Define the register file
unsigned short breakpoint = 0xFFFF; // Initialize breakpoint to an invalid address

// Function prototypes
void displayRegisters();
void changeRegister();
void changeMemory();
void setBreakpoint();

void manager(int argc, char* argv[]) {
    if (argc != ARG_COUNT) {
        fprintf(stderr, "Error: XME file not detected.");
        getchar();
        return;
    }

    const char* filename = argv[1];
    int start, end;
    char choice;
    char continueChoice;

    loadSRecord(argv[1]);

    do {
        printf("Enter command (I for IMEM, D for DMEM, R to display registers, C to change register, M to change memory, B to set breakpoint): ");
        scanf(" %c", &choice);

        switch (choice) {
        case 'I':
        case 'i':
            printf("\nDisplaying Instruction Memory (IMEM):\n");
            printf("Enter start address (in hex): ");
            scanf("%x", &start);
            printf("Enter end address (in hex): ");
            scanf("%x", &end);
            displayMemory((unsigned char*)IMEM, start, end);
            printf("Displaying Decoded Instructions:\n");
            fetchInstructions();
            break;
        case 'D':
        case 'd':
            printf("Displaying Data Memory (DMEM):\n");
            printf("Enter start address (in hex): ");
            scanf("%x", &start);
            printf("Enter end address (in hex): ");
            scanf("%x", &end);
            displayMemory(DMEM, start, end);
            break;
        case 'R':
        case 'r':
            displayRegisters();
            break;
        case 'C':
        case 'c':
            changeRegister();
            break;
        case 'M':
        case 'm':
            changeMemory();
            break;
        case 'B':
        case 'b':
            unsigned short address;
            printf("Enter breakpoint address (in hex): ");
            scanf("%hx", &address);
            setBreakpoint(address);
            break;
        default:
            printf("Invalid choice. Please enter a valid command.\n");
        }

        do {
            printf("Do you want to enter another command? (Y for yes, N for no): ");
            scanf(" %c", &continueChoice);
            printf("\n");
        } while (continueChoice != 'Y' && continueChoice != 'y' && continueChoice != 'N' && continueChoice != 'n');
        /*printf("Do you want to enter another command? (Y for yes, N for no): ");
        scanf(" %c", &continueChoice);
        printf("\n");*/

    } while (continueChoice == 'Y' || continueChoice == 'y');
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
            IMEM[address / 2] = value;
            printf("IMEM[%04X] changed to %04X\n", address, value);
        }
        else {
            printf("Invalid IMEM address.\n");
        }
    }
    else if (memType == 'D' || memType == 'd') {
        if (address < DMEM_SIZE) {
            DMEM[address] = value & 0xFF;
            DMEM[address + 1] = (value >> 8) & 0xFF;
            printf("DMEM[%04X] changed to %04X\n", address, value);
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
