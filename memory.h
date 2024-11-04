#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include "alu.h"



using namespace std;
class Memory {
private:
    vector<string> mem;
    Alu alu;

public:
    Memory() : mem(256, "00") {}

    void LoadProgramFile(string location) {
        string inp_file;
        cout << "Enter test file name: \n";
        cin >> inp_file;
        ifstream input_file(inp_file);
        if (input_file.is_open()) {
            string line;
            int address = alu.hexToDec(location);
            while (getline(input_file, line)) {
                for (char& c : line) {
                    c = toupper(c);
                }
                for (size_t i = 0; i < line.length(); i += 2) {
                    if (address < mem.size()) {
                        mem[address] = line.substr(i, 2);
                        address++;
                    } else {
                        cout << "Memory overflow.\n";
                        return;
                    }
                }
            }
            input_file.close();
        } else {
            cout << "Unable to open file.\n";
        }
    }

    void setCell(int address, const string& value) {
        if (address >= 0 && address < mem.size()) {
            mem[address] = value;
        }
    }

    string getCell(int address) {
        return (address >= 0 && address < mem.size()) ? mem[address] : "00";
    }

    int getSize() const {
        return mem.size();
    }

    string getMemContent(int index) const {
        return mem[index];
    }
};
