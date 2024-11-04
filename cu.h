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


class Cu {
private:
    Alu alu;

public:
    void load(int registerAddress, int memoryAddress, Register& registerObj, Memory& memory) {
        string memoryContent = memory.getCell(memoryAddress);
        registerObj.set(registerAddress, memoryContent);
    }

    void loadReg(int registerAddress, const string& val, Register& reg) {
        reg.set(registerAddress, val);
    }

    void store(int registerAddress, int memoryAddress, Register& registerObj, Memory& memory) {
        string registerContent = registerObj.get(registerAddress);
        memory.setCell(memoryAddress, registerContent);
        
    }

    void move(int registerRAddress, int registerSAddress, Register& registerObj) {
        string registerRContent = registerObj.get(registerRAddress);
        registerObj.set(registerSAddress, registerRContent);
    }

     void add(int regR, int regS, int regT, Register& reg) {
        int valueS = alu.hexToDec(reg.get(regS));
        int valueT = alu.hexToDec(reg.get(regT));
        int result = valueS + valueT;
        reg.set(regR, alu.decToHex(result));
    }
    void addFloatingPoint(int regR, int regS, int regT, Register& reg) {
        int valueS = alu.hexToDec(reg.get(regS));
        int valueT = alu.hexToDec(reg.get(regT));
        float floatValS = static_cast<float>(valueS) / 16.0f;
        float floatValT = static_cast<float>(valueT) / 16.0f;
        float result = floatValS + floatValT;
        int hexResult = static_cast<int>(result * 16.0f);
        reg.set(regR, alu.decToHex(hexResult));
    }

    void bitwiseAnd(int registerR_Address, int registerS_Address, int registerTAddress, Register &registerObj) {
        int registerS_Content = alu.hexToDec(registerObj.get(registerS_Address));
        int registerT_Content = alu.hexToDec(registerObj.get(registerTAddress));
        int result = registerS_Content & registerT_Content;
        registerObj.set(registerR_Address, alu.decToHex(result));
    }

    void bitwiseOr(int registerR_Address, int registerS_Address, int registerTAddress, Register &registerObj) {
        int registerS_Content = alu.hexToDec(registerObj.get(registerS_Address));
        int registerT_Content = alu.hexToDec(registerObj.get(registerTAddress));
        int result = registerS_Content | registerT_Content;
        registerObj.set(registerR_Address, alu.decToHex(result));
    }

    void bitwiseXor(int registerR_Address, int registerS_Address, int registerTAddress, Register &registerObj) {
        int registerS_Content = alu.hexToDec(registerObj.get(registerS_Address));
        int registerT_Content = alu.hexToDec(registerObj.get(registerTAddress));
        int result = registerS_Content ^ registerT_Content; 
        registerObj.set(registerR_Address, alu.decToHex(result));
    }
    void rotate(int registerAddress, int times, Register &registerObj) {
        int registerR_Content = alu.hexToDec(registerObj.get(registerAddress));
        int result = rotateRight(registerR_Content, times);
        registerObj.set(registerAddress,alu.decToHex(result));
    }
    int rotateRight(int registerContent, int times) {
        unsigned int un = static_cast<unsigned int>(registerContent);
        un = (un >> times) | (un << (8 - times));
        return static_cast<int>(un);
    }
    
};
