#include "../include/functions2.h"
#include "../include/functions3.h"

std::vector<int> encrypt(const std::vector<int> &inputData, const int &a, const int &b) {
    std::vector<int> encipheredText;

    auto iter = inputData.begin();
    auto end = inputData.end();

    int X, Y;
    int y1, y2;
    while (iter != end && (iter + 1) != end) {
        X = (*iter) * alphabetLength + (*(iter + 1));
        Y = (a * X + b) % (squaredAlphabetLength);

        y1 = Y / alphabetLength;
        y2 = Y % alphabetLength;
        encipheredText.push_back(y1);
        encipheredText.push_back(y2);

        iter += 2;
    }
    return encipheredText;
}

int modulo(int number, int base) {
    while (number < 0) {
        number += base;
    }
    number = number % base;
    return number;
}

std::vector<int> decrypt(const std::vector<int> &inputData, const int &a, const int &b) {
    std::vector<int> decipheredText;

    auto iter = inputData.begin();
    auto end = inputData.end();

    int Y, X;
    int x1, x2;
    int reversedA = reversed(a, squaredAlphabetLength);

    while (iter != end && (iter + 1) != end) {
        Y = (*iter) * alphabetLength + (*(iter + 1));
        X = modulo((reversedA * (Y - b)), squaredAlphabetLength);

        x1 = X / alphabetLength;
        x2 = modulo(X, alphabetLength);


        decipheredText.push_back(x1);
        decipheredText.push_back(x2);

        iter += 2;
    }
    return decipheredText;
}

std::map<std::pair<int, int>, int> createBigramMap(const std::vector<int> &inputData) {
    std::map<std::pair<int, int>, int> charMap;
    auto iter = inputData.begin();
    auto end = inputData.end();

    std::pair<int, int> tempPair;

    while (iter != end && (iter + 1) != end) {
        tempPair = std::make_pair(*iter, *(iter + 1));

        auto findIter = charMap.find(tempPair);
        if (findIter == charMap.end()) {
            // not found
            charMap.emplace(tempPair, 1);
        } else {
            // found
            findIter->second++;
        }

        iter += 2;
    }
    return charMap;
}

std::multimap<int, std::pair<int, int>> reverseBigramMap(const std::map<std::pair<int, int>, int> &inputData) {
    std::multimap<int, std::pair<int, int>> outputData;

    for (const auto &iter : inputData) {
        outputData.emplace(iter.second, iter.first);
    }

    return outputData;
}

std::vector<std::pair<int, int>> return5CommonBigrams(const std::vector<int> &inputData) {
    auto biagramMap = createBigramMap(inputData);
    auto reversedMap = reverseBigramMap(biagramMap);

    std::vector<std::pair<int, int>> output;

    auto riter = reversedMap.rbegin();
    auto end = reversedMap.rend();
    for (int counter = 0; riter != end && counter < 5; counter++) {
        output.push_back(riter->second);
        riter++;
    }
    return output;
}
