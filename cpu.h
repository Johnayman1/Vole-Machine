#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include "alu.h"
#include "memory.h"
#include "register.h"
#include "cu.h"


class Cpu {
private:
    int PC;
    Register register1;
    Alu alu;

public:
    Cu cu1;

    Cpu(string start) : PC(alu.hexToDec(start)) {}

    void Execute(Register& reg, Memory& mem) {
        while (PC < mem.getSize()) {
            char opcode = mem.getMemContent(PC)[0];
            switch (opcode) {
            case '1':
                cu1.load(alu.hexToDec(mem.getMemContent(PC).substr(1, 1)), alu.hexToDec(mem.getMemContent(PC + 1)), reg, mem);
                PC += 2;  // Move to next instruction
                break;
            case '2':
                cu1.loadReg(alu.hexToDec(mem.getMemContent(PC).substr(1, 1)), mem.getMemContent(PC + 1), reg);
                PC += 2;  // Move to next instruction
                break;
            case '3':
                cu1.store(alu.hexToDec(mem.getMemContent(PC).substr(1, 1)), alu.hexToDec(mem.getMemContent(PC + 1)), reg, mem);
                if (mem.getCell(PC+1) == "00")
                {
                    cout << "Cell 00 = " << mem.getMemContent(0) << endl;
                }
                PC += 2;  // Move to next instruction
                break;
            case '4':
                cu1.move(alu.hexToDec(mem.getMemContent(PC).substr(1, 1)), alu.hexToDec(mem.getMemContent(PC + 1)), reg);
                PC += 2;  // Move to next instruction
                break;
            case '5':
                cu1.add(alu.hexToDec(mem.getMemContent(PC).substr(1, 1)), alu.hexToDec(mem.getMemContent(PC + 1).substr(0,1)), alu.hexToDec(mem.getMemContent(PC +1).substr(1,1)), reg);
                PC += 2;  // Move to next instruction
                break;
            case '6':
                cu1.addFloatingPoint(alu.hexToDec(mem.getMemContent(PC).substr(1, 1)), alu.hexToDec(mem.getMemContent(PC + 1).substr(0,1)), alu.hexToDec(mem.getMemContent(PC +1).substr(1,1)), reg);
                PC += 2;  // Move to next instruction
                break;
            case '7':
                cu1.bitwiseOr(alu.hexToDec(mem.getMemContent(PC).substr(1, 1)), alu.hexToDec(mem.getMemContent(PC + 1).substr(0,1)), alu.hexToDec(mem.getMemContent(PC +1).substr(1,1)), reg);
                PC += 2;  // Move to next instruction
                break;
            case '8':
                cu1.bitwiseAnd(alu.hexToDec(mem.getMemContent(PC).substr(1, 1)), alu.hexToDec(mem.getMemContent(PC + 1).substr(0,1)), alu.hexToDec(mem.getMemContent(PC +1).substr(1,1)), reg);
                PC += 2;  // Move to next instruction
                break;
            case '9':
                cu1.bitwiseXor(alu.hexToDec(mem.getMemContent(PC).substr(1, 1)), alu.hexToDec(mem.getMemContent(PC + 1).substr(0,1)), alu.hexToDec(mem.getMemContent(PC +1).substr(1,1)), reg);
                PC += 2;  // Move to next instruction
                break;
            case 'A':
                cu1.rotate(alu.hexToDec(mem.getMemContent(PC).substr(1, 1)),alu.hexToDec(mem.getMemContent(PC + 1).substr(1,1)),reg);
                PC += 2;
                break;    
            case 'B':
                {
                    int registerAddress = alu.hexToDec(mem.getMemContent(PC).substr(1, 1));
                    int jumpAddress = alu.hexToDec(mem.getMemContent(PC + 1));
                    if (reg.get(registerAddress) == reg.get(0)) { // Check if jump condition is met
                        if (jumpAddress % 2 != 0)
                        {
                            cout << "*****"<<endl;
                            cout << "Cannot Jump to odd cell . " << endl;
                            cout << "Program Halted " << endl;
                            return;
                        }
                        PC = jumpAddress; // Update PC to the jump address
                        continue;
                    } else {
                        PC += 2; // Move to the next instruction if not jumping
                    }
                    break;
                    
                }
            case 'C':
                return;  //Halt  Stop execution

            default:
                cout << "Unknown instruction: " << opcode << endl;
                return; 
            }
        }

    
    }
};
