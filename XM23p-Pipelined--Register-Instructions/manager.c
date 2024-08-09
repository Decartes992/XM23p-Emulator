/*
Name: Iftekhar Rafi
ID: B00871031
Course: ECED 3403 Computer Architecture
Instructor: Larry Hughes

File Name: manager.c
File Purpose: This file contains the manager function which handles user input for memory display and calls the loadSRecord function to load S-Records from a file into memory.
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include "loader.h"
#include "debugger_mode.h"
#include "pipeline.h"
#include "execute_instructions.h"
#include "cex_instructions.h"

// Global variables are defined in the manager.c file
unsigned short reg_file[REGFILE_SIZE]; // Define the register file
unsigned short breakpoint = 0xFFFF;    // Initialize breakpoint to an invalid address

// Define the register pointers
unsigned short* PC = &reg_file[7]; // Start execution at address in R7
unsigned short* SP = &reg_file[6]; // Stack Pointer
unsigned short* LR = &reg_file[5]; // Link Register

// Define IMAR, ICTRL, IR, breakpoint, and clock_ticks
unsigned short IMAR;
unsigned short ICTRL;
unsigned short IR;
unsigned long clock_ticks = 0;
unsigned short DMAR; // Data Memory Address Register
unsigned char DCTRL; // Data Control Register
unsigned short DMBR; // Data Memory Buffer Register

// Define variables for instruction fields
unsigned char rc;
unsigned char wb;
unsigned char src;
unsigned char dst;
unsigned char con;
unsigned char bb;
unsigned char prpo;
unsigned char dec;
unsigned char inc;
unsigned char v;
unsigned char c;
unsigned char n;
unsigned char z;
unsigned char slp;
short offset_DR;
unsigned short EA; // Effective Address
short offset_BL;
short offset_BR;
int isBranch; // Flag to indicate if the previous instruction is a branch

// Variables to store the extracted fields from the CEX instruction
unsigned char C;
unsigned char T;
unsigned char F;
unsigned char TC;
unsigned char FC;
unsigned char cex_flag;
unsigned short start_address; // Start address set by S9 record

// Define a 64 KiB word-addressable instruction memory array
unsigned short IMEM[IMEM_SIZE / 2];

// Define a 64 KiB word-addressable data memory array
unsigned short DMEM[DMEM_SIZE / 2];

PSW psw = { 0, 0, 0, 0, 0 }; // Initialize PSW

// Function to manage user input and execute corresponding actions
void manager(int argc, char* argv[]) {
    int start, end;
    char choice;
    char continueChoice;
    unsigned short address;
    char filename[256]; // Ensure filename buffer is properly allocated

    // Load S-Record file if provided as a command-line argument
    if (argc == 2) {
        strcpy(filename, argv[1]);
        loadSRecord(filename);
    }

    do {
        // Prompt user for a command
        printf("Enter command:\n"
            "L to load XME file\n"
            "P to set PC back to starting address\n"
            "I for IMEM\n"
            "D for DMEM\n"
            "R to display registers\n"
            "C to change register\n"
            "M to change memory\n"
            "B to set breakpoint\n"
            "E for execute program\n"
            "X for debugger mode\n"
            "Choice: ");

        fgets(filename, sizeof(filename), stdin); // Use fgets to read the command
        sscanf(filename, " %c", &choice);         // Extract the command character

        switch (choice) {
            // Display Instruction Memory
        case 'I':
        case 'i':
            printf("\nDisplaying Instruction Memory (IMEM):\n");
            printf("Enter start address (in hex): ");
            scanf("%x", &start);
            printf("Enter end address (in hex): ");
            scanf("%x", &end);
            displayMemory((unsigned char*)IMEM, start, end);
            break;

            // Display Data Memory
        case 'D':
        case 'd':
            printf("Displaying Data Memory (DMEM):\n");
            printf("Enter start address (in hex): ");
            scanf("%x", &start);
            printf("Enter end address (in hex): ");
            scanf("%x", &end);
            displayMemory((unsigned char*)DMEM, start, end);
            break;

            // Display Registers
        case 'R':
        case 'r':
            displayRegisters();
            break;

            // Change Register
        case 'C':
        case 'c':
            changeRegister();
            break;

            // Change Memory
        case 'M':
        case 'm':
            changeMemory();
            break;

            // Set Breakpoint
        case 'B':
        case 'b':
            printf("Enter breakpoint address (in hex): ");
            scanf("%hx", &address);
            setBreakpoint(address);
            break;

            // Execute Program
        case 'E':
        case 'e':
            runMode(EXECUTION_MODE);
            break;

            // Debugger Mode
        case 'X':
        case 'x':
            runMode(DEBUGGER_MODE);
            break;

            // Load S-Record File
        case 'L':
        case 'l':
            // Clear the filename buffer before taking input
            memset(filename, 0, sizeof(filename));
            printf("Enter the name of the S-Record file: ");
            fgets(filename, sizeof(filename), stdin);
            // Remove the newline character if present
            filename[strcspn(filename, "\n")] = 0;

            loadSRecord(filename);
            break;

        case 'P':
        case 'p':
            *PC = start_address;
            break;
        default:
            printf("Invalid choice. Please enter a valid command.\n");
        }
        // Ask user if they want to enter another command
        do {
            printf("Do you want to enter another command? (Y for yes, N for no): ");
            scanf(" %c", &continueChoice);
            // Clear the input buffer after using scanf
            while (getchar() != '\n')
                ;
            printf("\n");
        } while (continueChoice != 'Y' && continueChoice != 'y' && continueChoice != 'N' && continueChoice != 'n');

    } while (continueChoice == 'Y' || continueChoice == 'y');
}

// Function to clear instruction and data memory
void clearMemory() {
    memset(IMEM, 0, sizeof(IMEM));
    memset(DMEM, 0, sizeof(DMEM));
}

// Function to reset all registers and the PSW
void resetRegisters() {
    memset(reg_file, 0, sizeof(reg_file));
    memset(&psw, 0, sizeof(psw));
    *PC = 0;
    *SP = 0;
}

#ifdef USE_OLD_CODE
/*
Name : Iftekhar Rafi
ID : B00871031
Course : ECED 3403 Computer Architecture
Instructor : Larry Hughes

File Name : manager.c
File Purpose : This file contains the manager function which handles user input for memory display and calls the loadSRecord function to load S - Records from a file into memory.
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include "loader.h"
#include "debugger_mode.h"
#include "pipeline.h"
#include "execute_instructions.h"
#include "cex_instructions.h"

        // Global variables are defined in the manager.c file
        unsigned short reg_file[REGFILE_SIZE]; // Define the register file
    unsigned short breakpoint = 0xFFFF;    // Initialize breakpoint to an invalid address

    // Define the register pointers
    unsigned short* PC = &reg_file[7]; // Start execution at address in R7
    unsigned short* SP = &reg_file[6]; // Stack Pointer
    unsigned short* LR = &reg_file[5]; // Link Register

    // Define IMAR, ICTRL, IR, breakpoint, and clock_ticks
    unsigned short IMAR;
    unsigned short ICTRL;
    unsigned short IR;
    unsigned long clock_ticks = 0;
    unsigned short DMAR; // Data Memory Address Register
    unsigned char DCTRL; // Data Control Register
    unsigned short DMBR; // Data Memory Buffer Register

    // Define variables for instruction fields
    unsigned char rc;
    unsigned char wb;
    unsigned char src;
    unsigned char dst;
    unsigned char con;
    unsigned char bb;
    unsigned char prpo;
    unsigned char dec;
    unsigned char inc;
    unsigned char v;
    unsigned char c;
    unsigned char n;
    unsigned char z;
    unsigned char slp;
    short offset_DR;
    unsigned short EA; // Effective Address
    short offset_BL;
    short offset_BR;
    int isBranch; // Flag to indicate if the previous instruction is a branch

    // Variables to store the extracted fields from the CEX instruction
    unsigned char C;
    unsigned char T;
    unsigned char F;
    unsigned char TC;
    unsigned char FC;
    unsigned char cex_flag;
    unsigned short start_address; // Start address set by S9 record

    // Define a 64 KiB word-addressable instruction memory array
    unsigned short IMEM[IMEM_SIZE / 2];

    // Define a 64 KiB word-addressable data memory array
    unsigned short DMEM[DMEM_SIZE / 2];

    PSW psw = { 0, 0, 0, 0, 0 }; // Initialize PSW


    void manager(int argc, char* argv[]) {
        int start, end;
        char choice;
        char continueChoice;
        unsigned short address;
        char filename[256]; // Ensure filename buffer is properly allocated

        if (argc == 2) {
            strcpy(filename, argv[1]);
            loadSRecord(filename);
        }

        do {
            char filename[256]; // Ensure filename buffer is properly allocated

            printf("Enter command (L to load XME file, P to set PC back to starting address, I for IMEM, D for DMEM, R to display registers, C to change register, M to change memory, B to set breakpoint, E for execute program, X for debugger mode): ");
            fgets(filename, sizeof(filename), stdin); // Use fgets to read the command
            sscanf(filename, " %c", &choice);         // Extract the command character

            switch (choice) {
                // Display Instruction Memory
            case 'I':
            case 'i':
                printf("\nDisplaying Instruction Memory (IMEM):\n");
                printf("Enter start address (in hex): ");
                scanf("%x", &start);
                printf("Enter end address (in hex): ");
                scanf("%x", &end);
                displayMemory((unsigned char*)IMEM, start, end);
                break;

                // Display Data Memory
            case 'D':
            case 'd':
                printf("Displaying Data Memory (DMEM):\n");
                printf("Enter start address (in hex): ");
                scanf("%x", &start);
                printf("Enter end address (in hex): ");
                scanf("%x", &end);
                displayMemory((unsigned char*)DMEM, start, end);
                break;

                // Display Registers
            case 'R':
            case 'r':
                displayRegisters();
                break;

                // Change Register
            case 'C':
            case 'c':
                changeRegister();
                break;

                // Change Memory
            case 'M':
            case 'm':
                changeMemory();
                break;

                // Set Breakpoint
            case 'B':
            case 'b':
                printf("Enter breakpoint address (in hex): ");
                scanf("%hx", &address);
                setBreakpoint(address);
                break;

                // Execute Program
            case 'E':
            case 'e':
                runMode(EXECUTION_MODE);
                break;

                // Debugger Mode
            case 'X':
            case 'x':
                runMode(DEBUGGER_MODE);
                break;

                // Load S-Record File
            case 'L':
            case 'l':
                //clearMemory();
                //resetRegisters();
                // Clear the filename buffer before taking input
                memset(filename, 0, sizeof(filename));
                printf("Enter the name of the S-Record file: ");
                fgets(filename, sizeof(filename), stdin);
                // Remove the newline character if present
                filename[strcspn(filename, "\n")] = 0;

                loadSRecord(filename);
                break;

            case 'P': case'p':
                *PC = start_address;
                break;
            default:
                printf("Invalid choice. Please enter a valid command.\n");
            }
            // Ask user if they want to enter another command
            do {
                printf("Do you want to enter another command? (Y for yes, N for no): ");
                scanf(" %c", &continueChoice);
                // Clear the input buffer after using scanf
                while (getchar() != '\n')
                    ;
                printf("\n");
            } while (continueChoice != 'Y' && continueChoice != 'y' && continueChoice != 'N' && continueChoice != 'n');

        } while (continueChoice == 'Y' || continueChoice == 'y');
    }

    void clearMemory() {
        memset(IMEM, 0, sizeof(IMEM));
        memset(DMEM, 0, sizeof(DMEM));
    }

    void resetRegisters() {
        memset(reg_file, 0, sizeof(reg_file));
        memset(&psw, 0, sizeof(psw));
        *PC = 0;
        *SP = 0;
    }

#endif