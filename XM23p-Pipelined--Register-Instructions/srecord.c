/*
Name: Iftekhar Rafi
ID: B00871031
Course: ECED 3403 Computer Architecture
Instructor: Larry Hughes

File Name: srecord.c
File Purpose: This file contains the function to load S-Records from a file and store them in memory.
*/
#include <stdio.h>
#include "loader.h"

unsigned int calculateChecksum(const char* line, int count, int dataLength) {
    unsigned int checksum = 0;
    int i;

    // Add count and address bytes
    for (i = 2; i < HEADER_START; i += BYTE_SIZE) {
        unsigned int byte;
        sscanf(line + i, "%2x", &byte);
        checksum += byte;
    }

    // Add data bytes
    for (i = HEADER_START; i < HEADER_START + dataLength; i += BYTE_SIZE) {
        unsigned int byte;
        sscanf(line + i, "%2x", &byte);
        checksum += byte;
    }

    // Calculate checksum: least significant byte of one's complement of sum
    checksum = (~checksum) & 0xFF;
    return checksum;
}

void loadSRecord(const char* filename) {
    unsigned int byte;
    unsigned int data;

    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }
    char line[LINE_SIZE];
    while (fgets(line, sizeof(line), file)) {

        if (line[0] != 'S') continue; // Not an S-Record
        int count, address;
        sscanf(line + 2, "%2x%4x", &count, &address);
        int dataLength = (count - 3) * BYTE_SIZE;

        // Calculate checksum
        unsigned int calculatedChecksum = calculateChecksum(line, count, dataLength);
        unsigned int givenChecksum;
        sscanf(line + 2 + count * BYTE_SIZE, "%2x", &givenChecksum);

        if (calculatedChecksum != givenChecksum) {
            printf("Checksum error in line: %s\n", line);
            continue;
        }

        if (line[1] == '0') {
            // S0 record: header
            printf("Header (ASCII): ");
            for (int i = 0; i < dataLength; i += BYTE_SIZE) {
                sscanf(line + HEADER_START + i, "%2x", &byte);
                printf("%c", byte);
            }
            printf("\n");
            printf("Header (Bytes): ");
            for (int i = 0; i < dataLength + BYTE_SIZE; i += BYTE_SIZE) {
                sscanf(line + HEADER_START + i, "%2x", &byte);
                printf("%02X ", byte);
            }
            printf("\n");
        }
        else if (line[1] == '1') {
            // S1 record: IMEM data
            for (int i = 0; i < dataLength; i += ASCII_SIZE) {
                sscanf(line + HEADER_START + i, "%4x", &data);
                IMEM[(address >> IMEM_SHIFT) + (i >> BYTE_SIZE)] = (data >> DATA_SHIFT) | ((data & BYTE_MASK) << DATA_SHIFT); // Correctly handle high and low byte
            }
        }
        else if (line[1] == '2') {
            // S2 record: DMEM data
            for (int i = 0; i < dataLength; i += ASCII_SIZE) {
                sscanf(line + HEADER_START + i, "%4x", &data);
                DMEM[(address >> DMEM_SHIFT) + (i >> BYTE_SIZE)] = (data >> DATA_SHIFT) | ((data & BYTE_MASK) << DATA_SHIFT); // Correctly handle high and low byte
            }
        }
        else if (line[1] == '9') {
            // S9 record: starting address
            sscanf(line + 4, "%4x", &address);
            printf("Starting address: %04X\n\n", address);
            reg_file[7] = address; // Store starting address in PC
        }
    }
    fclose(file);
}