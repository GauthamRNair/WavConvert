#ifndef GETBYTES_H
#define GETBYTES_H

#include <cstdint>
#include <vector>
#include <cstddef>
#include <fstream>
#include <string>

using namespace std;

vector<char> getRawBytes(string inFileName, bool isWav) {
    ifstream RAWfin;
    RAWfin.open(inFileName, ios::binary | ios::ate);

    if(!RAWfin.is_open()) {
        cerr << "Input file couldn't open!!!" << endl;
    }

    streamsize fsize = RAWfin.tellg(); // Since we opened file at the end, we get the size when reading curr pos in stream
    RAWfin.seekg(0, ios::beg); // Get back to beginning

    vector<char> rawBytes(fsize);

    RAWfin.read(rawBytes.data(), fsize); // Read all bytes
    RAWfin.close();

    if(!isWav) {
        rawBytes.insert(rawBytes.begin(), {'G', 'N', 'T', 'W'}); // My identifier so I know its my file
    }

    return rawBytes;
}

#endif