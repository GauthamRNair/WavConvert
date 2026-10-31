#include <iostream>
#include <fstream>
#include <string>
#include "writeWav.h"
#include "readWav.h"

using namespace std;

int main(int argc, char* argv[]) {
    string inFileName, outFileName;

    if(argc == 3) {
        inFileName = argv[1];
        outFileName = argv[2];
    } else if(argc == 1) {
        cout << "What file are you reading from?: ";
        cin >> inFileName;
        cout << "What file are you writing to?: ";
        cin >> outFileName;
    } else {
        cerr << "Incorrect number of arguments: \".\\ToWav.exe\" OR \".\\ToWav.exe <input file> <output file>\"" << endl;
        return 1;
    }

    char userChoice;
    cout << "Are you encoding(e) or decoding(d): ";
    cin >> userChoice;

    if(userChoice == 'e') {
        writeWav(inFileName, outFileName);
    }else if(userChoice == 'd') {
        readWav(inFileName, outFileName);
    }

    return 0;
}