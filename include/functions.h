#ifndef CHARACTER_PROCESSING_FUNCTIONS_H
#define CHARACTER_PROCESSING_FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <cstring>

const int alphabetLength = 31;
const int doubledAlphabetLength = alphabetLength * 2;
const int squaredAlphabetLength = alphabetLength * alphabetLength;
const double russianIndexOfCoincidence = 0.056378;

void readAbc(std::map<std::string, int> &renamingMap, const std::string &path);

void readAbcReverse(std::map<int, std::string> &renamingMap, const std::string &path);

std::string readRawData(const std::string &path);

void outputToFile(const std::vector<std::string> &finalData, const std::string &path);

std::vector<int> utf16ToInt(const std::string &rawData);

std::vector<std::string> intToUtf16(const std::vector<int> &vectorInt);

std::map<int, int> createCharMap(const std::vector<int> &inputData);

double calcIndexOfCoincidence(const std::vector<int> &inputData);

#endif //CHARACTER_PROCESSING_FUNCTIONS_H
