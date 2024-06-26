#ifndef LOADER_H
#define LOADER_H

// Define memory sizes and other constants
#define IMEM_SIZE 65536
#define DMEM_SIZE 65536
#define REGFILE_SIZE 8
#define ARG_COUNT 2
#define HEX_BASE 16
#define ASCII_PRINTABLE_START 32
#define ASCII_PRINTABLE_END 126
#define HEADER_START 8
#define BYTE_SIZE 2
#define ASCII_SIZE 4
#define IMEM_SHIFT 1
#define DMEM_SHIFT 2
#define BYTE_MASK 0xFF
#define ADDRESS_SHIFT 1
#define DATA_SHIFT 8
#define LINE_SIZE 100
#define READ 0x1

// Declare memory arrays
extern unsigned short IMEM[IMEM_SIZE / 2];
extern unsigned char DMEM[DMEM_SIZE];
extern unsigned short reg_file[REGFILE_SIZE];
extern unsigned short IMAR;
extern unsigned short ICTRL;
extern unsigned long clock_ticks; // Global variable to store clock ticks

// Declare functions for loading S-Records, displaying memory, and fetching and decoding instructions
void loadSRecord(const char* filename);
void displayMemory(unsigned char* memory, int start, int end);
void fetchInstructions();
void decodeInstruction(unsigned short instruction, unsigned short address);
void tick();

// Declare an enum for instruction types
typedef enum {
    ADD, ADDC, SUB, SUBC, DADD, CMP, XOR, AND, OR, BIT, BIC, BIS, MOV, SWAP, SRA, RRC, SWPB, SXT, MOVLZ, MOVL, MOVLS, MOVH, INVALID
} InstructionType;

// Declare functions for getting the type of an instruction, extracting fields from an instruction, and getting the name of an instruction type
InstructionType getInstructionType(unsigned short instruction);
void extractFields(unsigned short instruction, InstructionType type, unsigned char* rc, unsigned char* wb, unsigned char* src, unsigned char* dst, unsigned char* con, unsigned char* bb);
const char* getInstructionName(InstructionType type);
void executeInstruction(InstructionType type, unsigned char rc, unsigned char wb, unsigned char src, unsigned char dst, unsigned char con, unsigned char bb);
void printDecodedInstruction(unsigned short IR, unsigned short PC, InstructionType type, unsigned char rc, unsigned char wb, unsigned char src, unsigned char dst, unsigned char con, unsigned char bb);

#endif // LOADER_H
