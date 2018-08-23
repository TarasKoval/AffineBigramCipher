#include "functions.h"

void readAbc(std::map<std::string, int> &renamingMap, const std::string &path) {

    std::string rawData = readRawData(path);
    unsigned long dataLength = rawData.length();

    if (dataLength != doubledAlphabetLength) {
        std::cerr << "dataLength is not " << doubledAlphabetLength << " (size of russian abc x2)" << std::endl;
        exit(3);
    }

    std::string tempStr;
    int tempInt = 0;
    for (unsigned int i = 0; i < dataLength; i += 2) {
        tempStr = rawData.substr(i, 2);
        renamingMap.emplace(tempStr, tempInt++);
    }
}

void readAbcReverse(std::map<int, std::string> &renamingMap, const std::string &path) {

    std::string rawData = readRawData(path);
    unsigned long dataLength = rawData.length();

    if (dataLength != doubledAlphabetLength) {
        std::cerr << "dataLength is not " << doubledAlphabetLength << " (size of russian abc x2)" << std::endl;
        exit(3);
    }

    std::string tempStr;
    int tempInt = 0;
    for (unsigned int i = 0; i < dataLength; i += 2) {
        tempStr = rawData.substr(i, 2);
        renamingMap.emplace(tempInt++, tempStr);
    }
}

std::string readRawData(const std::string &path) {
    std::ifstream inputStream(path, std::ios::binary);
    if (!inputStream.is_open()) {
        std::cerr << "error opening text file" << std::endl;
        exit(1);
    }

    std::string rawData((std::istreambuf_iterator<char>(inputStream)),
                        std::istreambuf_iterator<char>());

    char charsToDelete[] = "\n";
    for (unsigned int i = 0; i < strlen(charsToDelete); ++i) {
        rawData.erase(std::remove(rawData.begin(), rawData.end(), charsToDelete[i]), rawData.end());
    }

    inputStream.close();
    return rawData;
}

void outputToFile(const std::vector<std::string> &finalData, const std::string &path) {
    std::ofstream outputStream(path, std::ios::binary);
    if (!outputStream.is_open()) {
        std::cerr << "error opening output file" << std::endl;
        exit(1);
    }

    for (const auto &iter : finalData) {
        outputStream << iter;
    }

    outputStream.close();
}

std::vector<int> utf16ToInt(const std::string &rawData) {
    unsigned long dataLength = rawData.length();

    if (dataLength % 2 != 0) {
        std::cerr << "data is not %2" << std::endl;
        exit(2);
    }

    std::vector<int> outputVector;
    std::map<std::string, int> renamingMap;
    readAbc(renamingMap, "../resources/abc.txt");

    std::string tempStr;
    for (unsigned int i = 0; i < dataLength; i += 2) {
        tempStr = rawData.substr(i, 2);
        if (tempStr == "ё") {
            tempStr = "е";
        }
        auto findIter = renamingMap.find(tempStr);
        if (findIter == renamingMap.end()) {
            // not found
            std::cerr << "didn't find string in renamingMap: " << tempStr << std::endl;
        } else {
            // found
            outputVector.push_back(findIter->second);
        }
    }
    return outputVector;
}

std::vector<std::string> intToUtf16(const std::vector<int> &vectorInt) {
    std::map<int, std::string> renamingMapReverse;
    readAbcReverse(renamingMapReverse, "../resources/abc.txt");

    std::vector<std::string> vectorDecryptedData;

    std::string tempStr;
    for (auto iter : vectorInt) {
        auto findIter = renamingMapReverse.find(iter);
        if (findIter == renamingMapReverse.end()) {
            // not found
            std::cerr << "didn't find string in renamingMapReverse: " << tempStr << std::endl;
        } else {
            // found
            vectorDecryptedData.push_back(findIter->second);
        }
    }
    return vectorDecryptedData;
}

std::map<int, int> createCharMap(const std::vector<int> &inputData) {
    std::map<int, int> charMap;

    for (auto iter : inputData) {
        auto findIter = charMap.find(iter);
        if (findIter == charMap.end()) {
            // not found
            charMap.emplace(iter, 1);
        } else {
            // found
            findIter->second++;
        }
    }
    return charMap;
}

double calcIndexOfCoincidence(const std::vector<int> &inputData) {
    double dataLength = inputData.size();
    if (dataLength <= 1) {
        std::cout << "from calcIndexOfCoincidence: data length <= 1: " << dataLength << std::endl;
        exit(4);
    }

    auto charMap = createCharMap(inputData);

    double sum = 0;
    for (auto &iter : charMap) {
        sum += iter.second * (iter.second - 1);
    }

    double matchingIndex = sum / dataLength / (dataLength - 1);
    return matchingIndex;
}
