#ifndef READWAV_H
#define READWAV_H

#include <cstdint>
#include <vector>
#include <cstddef>
#include <fstream>
#include <string>
#include "getBytes.h"

using namespace std;

void readWav(string inFileName, string outFileName) {
    // Ensure this is a valid .wav
    if(inFileName.substr(inFileName.size() - 4, 4) != ".wav") {
        cerr << "The input is not a \".wav\" file!" << endl;
        return;
    }

    // Get raw bytes
    vector<char> rawBytes = getRawBytes(inFileName, true);

    // Doublecheck 'RIFF' and 'WAVE' from the file header
    if(!(rawBytes[0] == 'R' && rawBytes[1] == 'I' && rawBytes[2] == 'F' && rawBytes[3] == 'F')) {
        if(!(rawBytes[8] == 'W' && rawBytes[9] == 'A' && rawBytes[10] == 'V' && rawBytes[11] == 'E')) {
            cerr << "The input file may be a corrupted \".wav\" file!" << endl;
            return;
        }
    }

    // Also check my own identifier 'GNTW'
    if(!(rawBytes[44] == 'G' && rawBytes[45] == 'N' && rawBytes[46] == 'T' && rawBytes[47] == 'W')) {
        cerr << "The input file may not be one of my encoded \".wav\" files!" << endl;
        return;
    }

    int dataSize;
    memcpy(&dataSize, &rawBytes[40], sizeof(int)); // Get the audio data size I put in the header
    dataSize -= 4; // Quick fix since my four identifier chars were included in the size

    rawBytes.erase(rawBytes.begin(), rawBytes.begin()+48); // Start at the act data

    if(dataSize < rawBytes.size()) {
        rawBytes.resize(dataSize); // Remove any padding bytes I added on encoding
    }

    ofstream RAWout;
    RAWout.open(outFileName, ios::binary);

    RAWout.write(rawBytes.data(), rawBytes.size());

    RAWout.close();
}

#endif