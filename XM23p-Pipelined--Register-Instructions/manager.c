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

unsigned short reg_file[REGFILE_SIZE]; // Define the register file
unsigned short breakpoint = 0xFFFF; // Initialize breakpoint to an invalid address

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
        case 'I':
        case 'i':
            printf("\nDisplaying Instruction Memory (IMEM):\n");
            printf("Enter start address (in hex): ");
            scanf("%x", &start);
            printf("Enter end address (in hex): ");
            scanf("%x", &end);
            displayMemory((unsigned char*)IMEM, start, end);
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
            printf("Enter breakpoint address (in hex): ");
            scanf("%hx", &address);
            setBreakpoint(address);
            break;
        case 'E':
        case 'e':
            runMode(0); // Execute mode
            break;
        case 'X':
        case 'x':
            runMode(1); // Debugger mode
            break;
        default:
            printf("Invalid choice. Please enter a valid command.\n");
        }

        do {
            printf("Do you want to enter another command? (Y for yes, N for no): ");
            scanf(" %c", &continueChoice);
            printf("\n");
        } while (continueChoice != 'Y' && continueChoice != 'y' && continueChoice != 'N' && continueChoice != 'n');

    } while (continueChoice == 'Y' || continueChoice == 'y');
}
