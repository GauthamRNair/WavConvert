#ifndef WRITEWAV_H
#define WRITEWAV_H

#include <cstdint>
#include <vector>
#include <cstddef>
#include <fstream>
#include <string>

using namespace std;

#pragma pack(push, 1)
struct WavFileHeader {
    uint32_t riff{0x46464952}; // "RIFF"
    uint32_t file_size = 0;
    uint32_t file_type{0x45564157}; // "WAVE"
    uint32_t format{0x20746d66}; // "fmt "
    uint32_t format_length = 16;
    uint16_t format_type = 1;
    uint16_t num_channels = 1; // Mono = 1, Stereo = 2
    uint32_t sample_rate = 44100; // Samples per second (frequency)
    uint32_t bytes_per_second = 88200; // I can hardcode this value for now
    uint16_t bytes_per_block = 2; // bytes per sample times num channels
    uint16_t bits_per_sample = 16;
    uint32_t data_header{0x61746164};
    uint32_t data_size = 0;
};

void writeWav(string fileName, vector<char> rawBytes) {
    ofstream WAVfout;
    WAVfout.open(fileName, ios::binary);

    if(!WAVfout.is_open()) {
        cerr << "Couldn't open the wav file!!!" << endl;
        return;
    }

    WavFileHeader fileHeader;
    fileHeader.data_size = rawBytes.size();
    fileHeader.data_size += (fileHeader.bytes_per_block - (rawBytes.size() % fileHeader.bytes_per_block)) % fileHeader.bytes_per_block; // Have to make the num data bytes divisible by the bytes per block
    fileHeader.file_size = fileHeader.data_size + 44;

    WAVfout.write(reinterpret_cast<const char*>(&fileHeader), sizeof(fileHeader));

    WAVfout.close();

}

#endif