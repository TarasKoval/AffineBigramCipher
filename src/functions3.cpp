#include "functions3.h"

int multiply(std::pair<int, int> X1) {
    int x1 = X1.first * alphabetLength + X1.second;
    return x1;
}

int gcd(const int a, const int b) {
    int q, remainder, xCur, yCur, xPrev1 = 0, xPrev2 = 1, yPrev1 = 1, yPrev2 = 0, aTemp = a, bTemp = b;
    if (bTemp == 0) {
        return aTemp;
    }
    while (bTemp > 0) {
        q = aTemp / bTemp;
        remainder = aTemp - q * bTemp;

        xCur = xPrev2 - q * xPrev1;
        yCur = yPrev2 - q * yPrev1;

        aTemp = bTemp;
        bTemp = remainder;

        xPrev2 = xPrev1;
        xPrev1 = xCur;

        yPrev2 = yPrev1;
        yPrev1 = yCur;
    }
    return abs(aTemp);
}

int reversed(const int a, const int b) {
    int q, remainder, xCur, yCur, xPrev1 = 0, xPrev2 = 1, yPrev1 = 1, yPrev2 = 0, aTemp = a, bTemp = b;
    if (bTemp == 0) {
        return aTemp;
    }
    while (bTemp > 0) {
        q = aTemp / bTemp;
        remainder = aTemp - q * bTemp;

        xCur = xPrev2 - q * xPrev1;
        yCur = yPrev2 - q * yPrev1;

        aTemp = bTemp;
        bTemp = remainder;

        xPrev2 = xPrev1;
        xPrev1 = xCur;

        yPrev2 = yPrev1;
        yPrev1 = yCur;
    }
    return xPrev2;
}

std::vector<int> solveLinearEquation(int a, int b, int m) {
    int remainder = gcd(a, m);
    std::vector<int> output;

    if (remainder == 1) {
        output.push_back(modulo((b * reversed(a, m)) % m, squaredAlphabetLength));
    } else {
        if (b % remainder) {

        } else {
            output.push_back(
                    modulo(((b / remainder) * reversed(a / remainder, m / remainder)) % m, squaredAlphabetLength)
            );
            for (unsigned long i = 1; i < remainder; ++i) {
                output.push_back(modulo((output.at(i - 1) + m / remainder) % m, squaredAlphabetLength));
            }
        }
    }
    return output;
}

std::vector<std::pair<int, int>> solveTheSystem(const std::pair<int, int> inputX1, const std::pair<int, int> inputY1,
                                                const std::pair<int, int> inputX2, const std::pair<int, int> inputY2) {
    int X1 = multiply(inputX1);
    int X2 = multiply(inputX2);
    int Y1 = multiply(inputY1);
    int Y2 = multiply(inputY2);

    auto reversedSolution = solveLinearEquation(modulo(Y1 - Y2, squaredAlphabetLength),
                                                modulo(X1 - X2, squaredAlphabetLength),
                                                squaredAlphabetLength);

    std::vector<std::pair<int, int>> keysVector;
    int keyA, keyB;
    for (auto iter : reversedSolution) {
        keyA = modulo(reversed(iter, squaredAlphabetLength), squaredAlphabetLength);
        keyB = modulo((Y1 - keyA * X1), squaredAlphabetLength);
        keysVector.emplace_back(keyA, keyB);
    }
    return keysVector;
}

std::pair<int, int> calcKeys(const std::vector<int> &encryptedText) {
    std::cout << "key calculation started, may take some time" << std::endl;
    const std::array<std::pair<int, int>, 5> perfectFrequentBigrams = {std::make_pair(17, 18),
                                                                       std::make_pair(13, 14),
                                                                       std::make_pair(18, 14),
                                                                       std::make_pair(5, 13),
                                                                       std::make_pair(13, 8)};
    auto commonBigrams = return5CommonBigrams(encryptedText);

    double closestDifference = 1;
    int closestKeyA = -1, closestKeyB = -1;
    std::vector<int> tempDecipheredText;

    for (unsigned long i1 = 0; i1 < 5; i1++) {
        for (unsigned long i2 = 0; i2 < 5; i2++) {
            for (unsigned long i3 = 0; i3 < 5; i3++) {
                for (unsigned long i4 = i2 + 1; i4 < 5; i4++) {
                    if (i1 == i3) {
                        continue;
                    }

                    auto keyPairs = solveTheSystem(perfectFrequentBigrams.at(i2), commonBigrams.at(i1),
                                                   perfectFrequentBigrams.at(i4), commonBigrams.at(i3));
                    for (auto iter : keyPairs) {
                        tempDecipheredText.clear();
                        tempDecipheredText = decrypt(encryptedText, iter.first, iter.second);
                        auto tempIndex = calcIndexOfCoincidence(tempDecipheredText);
                        auto difference = fabs(tempIndex - russianIndexOfCoincidence);
                        if (difference < closestDifference) {
                            closestKeyA = iter.first;
                            closestKeyB = iter.second;
                            closestDifference = difference;
                        }
                    }

                }
            }
        }
    }
    auto outputData = std::make_pair(closestKeyA, closestKeyB);
    return outputData;
}

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
