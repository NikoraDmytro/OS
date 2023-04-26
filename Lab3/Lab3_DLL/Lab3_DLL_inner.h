#pragma once

#include <iostream>
#include <fstream>

extern "C" bool CheckControlBlock(char* fileName);
extern "C" bool ReadData(char* fileName, std::ifstream * infile, char** dest, size_t * length);
extern "C" char* CalculateChecksum(const char* data, size_t lenght);

extern "C" unsigned long long Simple();
extern "C" unsigned long long Gdc(unsigned long long, unsigned long long);
extern "C" unsigned long long PowMod(unsigned long long, unsigned long long, unsigned long long);
extern "C";