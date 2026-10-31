#include <iostream>
#include <fstream>
#include "writeWav.h"

using namespace std;

int main(int argc, char* argv[]) {
    if(argc != 3) {
        cerr << "Incorrect number of arguments: \".\\ToWav.exe <input file> <output file>\"" << endl;
    }

    ifstream fin;
    fin.open(argv[1], ios::binary | ios::ate);

    if(!fin.is_open()) {
        cerr << "Input file couldn't open!!!" << endl;
    }

    streamsize fsize = fin.tellg(); // Since we opened file at the end, we get the size when reading curr pos in stream
    fin.seekg(0, ios::beg); // Get back to beginning

    vector<char> rawBytes(fsize);

    fin.read(rawBytes.data(), fsize); // Read all bytes
    fin.close();

    rawBytes.insert(rawBytes.begin(), {'G', 'N', 'T', 'W'}); // My identifier so I know its my file

    writeWav("test.wav", rawBytes);

    return 0;
}