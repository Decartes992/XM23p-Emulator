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
#include "debugger_mode.h"

//Global variables are defined in the manager.c file
unsigned short reg_file[REGFILE_SIZE]; // Define the register file
unsigned short breakpoint = 0xFFFF; // Initialize breakpoint to an invalid address

// Define IMAR, ICTRL, IR, breakpoint, and clock_ticks
unsigned short breakpoint;
unsigned short IMAR;
unsigned short ICTRL;
unsigned short IR;
unsigned long clock_ticks = 0; 

// Define a 64 KiB word-addressable instruction memory array
unsigned short IMEM[IMEM_SIZE / 2];

// Define a 64 KiB word-addressable data memory array
unsigned short DMEM[DMEM_SIZE/2];

PSW psw = { 0, 0, 0, 0, 0 }; // Initialize PSW

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
    unsigned short address;

    loadSRecord(argv[1]);
    do {
        printf("Enter command (I for IMEM, D for DMEM, R to display registers, C to change register, M to change memory, B to set breakpoint, E for execute program, X for debugger mode): ");
        scanf(" %c", &choice);

        switch (choice) {

        // Display Instruction Memory
        case 'I':case 'i': 
            printf("\nDisplaying Instruction Memory (IMEM):\n");
            printf("Enter start address (in hex): ");
            scanf("%x", &start);
            printf("Enter end address (in hex): ");
            scanf("%x", &end);
            displayMemory((unsigned char*)IMEM, start, end);
            break;

        // Display Data Memory
        case 'D':case 'd': 
            printf("Displaying Data Memory (DMEM):\n");
            printf("Enter start address (in hex): ");
            scanf("%x", &start);
            printf("Enter end address (in hex): ");
            scanf("%x", &end);
            displayMemory((unsigned char*)DMEM, start, end);
            break;

        // Display Registers
        case 'R':case 'r':
            displayRegisters();
            break;

		// Change Register
        case 'C': case 'c': 
            changeRegister(); 
            break;

        // Change Memory
        case 'M': case 'm':
            changeMemory();
            break;

        // Set Breakpoint
        case 'B':case 'b':
            printf("Enter breakpoint address (in hex): ");
            scanf("%hx", &address);
            setBreakpoint(address);
            break;

        // Execute Program
        case 'E':case 'e':
            runMode(EXECUTION_MODE); 
            break;

        // Debugger Mode
        case 'X':case 'x':
            runMode(DEBUGGER_MODE); 
            break;

        // Invalid command
        default:
            printf("Invalid choice. Please enter a valid command.\n");
        }

        // Ask user if they want to enter another command
        do {
            printf("Do you want to enter another command? (Y for yes, N for no): ");
            scanf(" %c", &continueChoice);
            printf("\n");
        } while (continueChoice != 'Y' && continueChoice != 'y' && continueChoice != 'N' && continueChoice != 'n');

    } while (continueChoice == 'Y' || continueChoice == 'y');
    return;
}
