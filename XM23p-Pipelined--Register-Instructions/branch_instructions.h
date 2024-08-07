/*
Name: Iftekhar Rafi
ID: B00871031
Course: ECED 3403 Computer Architecture
Instructor: Larry Hughes

File Name: branch_instructions.h
File Purpose: This header file contains the function declarations for branch instructions.
*/

#ifndef BRANCH_INSTRUCTIONS_H
#define BRANCH_INSTRUCTIONS_H

// Function declarations for branch operations

/**
 * @brief Branch with Link
 *
 * This function branches to the specified offset and stores the return address in the link register.
 */
void execute_BL(void);

/**
 * @brief Branch if Equal or Zero
 *
 * This function branches to the specified offset if the zero flag is set.
 */
void execute_BEQBZ(void);

/**
 * @brief Branch if Not Equal or Not Zero
 *
 * This function branches to the specified offset if the zero flag is not set.
 */
void execute_BNEBNZ(void);

/**
 * @brief Branch if Carry or Higher or Same (unsigned)
 *
 * This function branches to the specified offset if the carry flag is set.
 */
void execute_BCBHS(void);

/**
 * @brief Branch if No Carry or Lower (unsigned)
 *
 * This function branches to the specified offset if the carry flag is not set.
 */
void execute_BNCBLO(void);

/**
 * @brief Branch if Negative
 *
 * This function branches to the specified offset if the negative flag is set.
 */
void execute_BN(void);

/**
 * @brief Branch if Greater or Equal (signed)
 *
 * This function branches to the specified offset if the negative and overflow flags are equal.
 */
void execute_BGE(void);

/**
 * @brief Branch if Less (signed)
 *
 * This function branches to the specified offset if the negative and overflow flags are not equal.
 */
void execute_BLT(void);

/**
 * @brief Branch Always
 *
 * This function always branches to the specified offset.
 */
void execute_BRA(void);

#endif // BRANCH_INSTRUCTIONS_H
