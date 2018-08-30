#include "functions2.h"

int modulo(int number, int base) {
    return (number < 0 ? (number % base) + base : number % base);
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
    auto bigramMap = createBigramMap(inputData);
    auto reversedMap = reverseBigramMap(bigramMap);

    std::vector<std::pair<int, int>> output;

    auto rIter = reversedMap.rbegin();
    auto end = reversedMap.rend();
    for (int counter = 0; rIter != end && counter < 5; counter++) {
        output.push_back(rIter->second);
        rIter++;
    }
    return output;
}
