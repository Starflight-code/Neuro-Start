#include "mathgenerator.h"
#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>

#pragma once

const int TOTAL_QUESTIONS = 4;

enum mathOperator {
    multiplication,
    division,
    addition,
    subtraction
};

enum difficulty {
    easy,
    moderate,
    difficult,
    extreme
};

mathGenerator::mathOperation mathGenerator::generateMultiplication(int maxDigits) {
    int number1 = rand() % (int)std::pow(10, maxDigits);
    int number2 = rand() % (int)std::pow(10, maxDigits);
    int answer = number1 * number2;
    return mathOperation(number1, number2, answer, multiplication);
}

mathGenerator::mathOperation mathGenerator::generateDivision(int maxDigits) {
    int number1 = rand() % (int)std::pow(10, maxDigits);
    int number2 = (rand() + 1) % (int)std::pow(10, maxDigits == 1 ? 1 : maxDigits - 1); // ensures number 2 is a smaller number from number1
    number1 -= number1 % number2;                                                       // ensures a integer results from division
    int answer = number1 / number2;
    return mathOperation(number1, number2, answer, division);
}

mathGenerator::mathOperation mathGenerator::generateAddition(int maxDigits) {
    int number1 = rand() % (int)std::pow(10, maxDigits);
    int number2 = rand() % (int)std::pow(10, maxDigits);
    int answer = number1 + number2;
    return mathOperation(number1, number2, answer, addition);
}

mathGenerator::mathOperation mathGenerator::generateSubtraction(int maxDigits) {
    int number1 = rand() % (int)std::pow(10, maxDigits);
    int number2 = rand() % (int)std::pow(10, maxDigits);
    if(number1 < number2) {
        int temp = number1;
        number1 = number2;
        number2 = temp;
    } // ensures the result is a positive number
    int answer = number1 - number2;
    return mathOperation(number1, number2, answer, subtraction);
}

mathGenerator::questions mathGenerator::generateQuestion(difficulty level) {
    int maxDigitsMultiplication;
    int maxDigitsDivision;
    int maxDigitsAddition;
    int maxDigitsSubtraction;
    int maxOperations;

    switch(level) {
        case easy:
            maxDigitsMultiplication = 1;
            maxDigitsDivision = 1;
            maxDigitsAddition = 2;
            maxDigitsSubtraction = 2;
            maxOperations = 1;
            break;
        case moderate:
            maxDigitsMultiplication = 1;
            maxDigitsDivision = 1;
            maxDigitsAddition = 2;
            maxDigitsSubtraction = 2;
            maxOperations = 2;
            break;
        case difficult:
            maxDigitsMultiplication = 2;
            maxDigitsDivision = 2;
            maxDigitsAddition = 2;
            maxDigitsSubtraction = 2;
            maxOperations = 3;
            break;
        case extreme:
            maxDigitsMultiplication = 2;
            maxDigitsDivision = 2;
            maxDigitsAddition = 3;
            maxDigitsSubtraction = 3;
            maxOperations = 4;
            break;
    }
    std::string questionToAsk;
    std::vector<std::string> answers = std::vector<std::string>();
    questions returnValue = questions();

    int numberOfOperations = maxOperations != 0 ? rand() % (maxOperations - 1) + 1 : 1; // sets the number of operations to generate to between 1 and max operations.
    for(int i = 0; i < numberOfOperations; i++) {
        mathOperation operation = mathOperation();
        int number1;
        int number2;
        int answer;
        int maxDigits;

        switch(rand() % 4) {
            case(0): // Multiplication

                // number1 = rand() % (int)std::pow(10, maxDigitsMultiplication);
                // number2 = rand() % (int)std::pow(10, maxDigitsMultiplication);
                maxDigits = maxDigitsMultiplication;
                // answer = number1 * number2;
                operation = generateMultiplication(maxDigitsMultiplication);
                break;
            case(1): // Division
                // number1 = rand() % (int)std::pow(10, maxDigitsDivision);
                // number2 = (rand() + 1) % (int)std::pow(10, maxDigitsDivision == 1 ? 1 : maxDigitsDivision - 1); // ensures number 2 is a smaller number from number1
                // number1 -= number1 % number2;                                                                   // ensures a integer results from division
                maxDigits = maxDigitsDivision;
                operation = generateDivision(maxDigitsDivision);
                // answer = number1 / number2;
                // questionToAsk = "Resolve the following: " + std::to_string(number1) + " / " + std::to_string(number2);
                break;
            case(2): // Addition
                // number1 = rand() % (int)std::pow(10, maxDigitsAddition);
                // number2 = rand() % (int)std::pow(10, maxDigitsAddition);
                maxDigits = maxDigitsAddition;
                operation = generateAddition(maxDigitsAddition);
                // answer = number1 + number2;
                // questionToAsk = "Resolve the following: " + std::to_string(number1) + " + " + std::to_string(number2);
                break;
            case(3): // Subtraction
                // number1 = rand() % (int)std::pow(10, maxDigitsSubtraction);
                // number2 = rand() % (int)std::pow(10, maxDigitsSubtraction);
                // if(number1 < number2) {
                //     int temp = number1;
                //     number1 = number2;
                //     number2 = temp;
                // } // ensures the result is a positive number
                maxDigits = maxDigitsSubtraction;
                operation = generateSubtraction(maxDigitsSubtraction);
                // answer = number1 - number2;
                // questionToAsk = "Resolve the following: " + std::to_string(number1) + " + " + std::to_string(number2);
                break;
        }
        questionToAsk = "Resolve the following: " + std::to_string(operation.number1) + " " + operation.fetchNotation() + " " + std::to_string(operation.number2);
        answers.push_back(std::to_string(answer));

        for(int j = 0; j < TOTAL_QUESTIONS - 1; j++) {
            int randomAnswer = (answer + (rand() % (int)std::pow(10, maxDigits))) % (int)std::pow(10, maxDigits); // generates a randomized alternative (wrong) answer for the user to not select after solving
            answers.push_back(std::to_string(randomAnswer == answer ? ++randomAnswer : randomAnswer));            // verifies the wrong answer is not correct, if this edge case occurs then add one (making it rightfully wrong)
        }
        returnValue.addQuestion(questionToAsk, answers);
        answers.clear();
    }
    return returnValue;
}
