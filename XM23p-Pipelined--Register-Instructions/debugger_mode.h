#ifndef DEBUGGER_MODE_H
#define DEBUGGER_MODE_H

void runMode(int debug);
void displayRegisters();
void changeRegister();
void changeMemory();
void setBreakpoint(unsigned short address);
#endif // DEBUGGER_MODE_H
