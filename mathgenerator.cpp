#include "mathgenerator.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

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
    srand(time(0));
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

    int numberOfOperations = maxOperations > 1 ? rand() % (maxOperations + 1) : 1; // sets the number of operations to generate to between 1 and max operations.
    for(int i = 0; i < numberOfOperations; i++) {
        mathOperation operation = mathOperation();
        int maxDigits;

        switch(rand() % 4) {
            case(0): // Multiplication
                maxDigits = maxDigitsMultiplication;
                operation = generateMultiplication(maxDigitsMultiplication);
                break;
            case(1): // Division
                maxDigits = maxDigitsDivision;
                operation = generateDivision(maxDigitsDivision);
                break;
            case(2): // Addition
                maxDigits = maxDigitsAddition;
                operation = generateAddition(maxDigitsAddition);
                break;
            case(3): // Subtraction
                maxDigits = maxDigitsSubtraction;
                operation = generateSubtraction(maxDigitsSubtraction);
                break;
        }
        questionToAsk = "Resolve the following: " + std::to_string(operation.number1) + " " + operation.fetchNotation() + " " + std::to_string(operation.number2);
        answers.push_back(std::to_string(operation.answer));

        for(int j = 0; j < TOTAL_QUESTIONS - 1; j++) {
            int randomAnswer = (operation.answer + (rand() % (int)std::pow(10, maxDigits))) % (int)std::pow(10, maxDigits); // generates a randomized alternative (wrong) answer for the user to not select after solving
            answers.push_back(std::to_string(randomAnswer == operation.answer ? ++randomAnswer : randomAnswer));            // verifies the wrong answer is not correct, if this edge case occurs then add one (making it rightfully wrong)
        }
        returnValue.addQuestion(questionToAsk, answers);
        answers.clear();
    }
    return returnValue;
}
