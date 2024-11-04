#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;


class Alu {
public:
    int hexToDec(const string& hexStr) {
        int result;
        stringstream line;
        line << hex << hexStr;
        line >> result;
        return result;
    }

    string decToHex(int decNum) {
        stringstream line;
        line << hex << uppercase << decNum;
        string str1 = line.str() ;
        if (str1.size() == 1)
        {
            str1 = "0" +str1;       
        }
        return str1;
    }
};
