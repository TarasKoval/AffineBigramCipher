#ifndef LAB3MAIN_FUNCTIONS3_H
#define LAB3MAIN_FUNCTIONS3_H

#include <iostream>
#include <vector>
#include "functions.h"
#include "functions2.h"

int multiply(std::pair<int, int> X1);

int gcd(int a, int b);

int reversed(int a, int b);

std::vector<int> solveLinearEquation(int a, int b, int m);

std::vector<std::pair<int, int>> solveTheSystem(std::pair<int, int> inputX1, std::pair<int, int> inputY1,
                                                std::pair<int, int> inputX2, std::pair<int, int> inputY2);

std::pair<int, int> calcKeys(const std::vector<int> &encipheredData);

template<typename T>
void outputVector(const std::vector<T> &data) {
    for (const auto &iter : data) {
        std::cout << iter;
    }
    std::cout << std::endl;
}

#endif //LAB3MAIN_FUNCTIONS3_H
