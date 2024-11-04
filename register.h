#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;




class Register {
public:
    vector<string> reg;

    Register() : reg(16, "00") {}

    string get(int addr) {
        return (addr >= 0 && addr < reg.size()) ? reg[addr] : "00";
    }

    void set(int addr, const string& val) {
        if (addr >= 0 && addr < reg.size()) {
            reg[addr] = val;
        }
    }
};
