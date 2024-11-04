#include "cpu.h"



int main() {
    string choice;
    string adr;
    cout << "****  Welcome to our Vole machine  ****" << endl;
    while (true) {
        cout << "Please select start from default cell or select a cell." << endl;
        cout << "Select 1 to Default." << endl;
        cout << "Select 2 to select a Start position." << endl;
        cout << "Your choice: ";
        cin >> choice;
        cout << endl;
        if (choice == "1") {
            adr = "10";
            break;
        } else if (choice == "2") {
            cout << "Please enter the Start position: " << endl;
            cin >> adr;
            break;
        } else {
            cout << "Please select the right one." << endl;
            continue;
        }
    }
    
    Memory memory; 
    memory.LoadProgramFile(adr);
    Register reg;
    Alu alu1;
    Cpu cpu(adr);
    cpu.Execute(reg, memory);

    cout << "Memory" << endl;

    // Display memory content
    for (int i = 0; i < memory.getSize(); i++) {
        cout << setw(2) << setfill('0') << alu1.decToHex(i) << ":"
             << setw(2) << setfill('0') << memory.getMemContent(i) << ' ';
        if ((i + 1) % 16 == 0) {
            cout << endl;
        }
    }
    cout << endl << endl;

    cout << "Registers" << endl;

    // Display register content
    for (int i = 0; i < 16; i++) {
        cout << setw(2) << i << ":" << setw(2) << setfill('0') << reg.reg[i] << endl;
    }
    cout << endl; // Ensure output is clean
    return 0;
}
