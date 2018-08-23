#ifndef LAB3MAIN_NEW_FUNCTIONS_H
#define LAB3MAIN_NEW_FUNCTIONS_H

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include "functions.h"
#include "functions3.h"

std::vector<int> encrypt(const std::vector<int> &inputData, const int &a, const int &b);

std::vector<int> decrypt(const std::vector<int> &inputData, const int &a, const int &b);

std::map<std::pair<int, int>, int> createBigramMap(const std::vector<int> &inputData);

std::multimap<int, std::pair<int, int>> reverseBigramMap(const std::map<std::pair<int, int>, int> &inputData);

std::vector<std::pair<int, int>> return5CommonBigrams(const std::vector<int> &inputData);

int modulo(int number, int base);

#endif //LAB3MAIN_NEW_FUNCTIONS_H
