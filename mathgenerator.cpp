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
    int number2 = rand() % (int)std::pow(10, maxDigits == 1 ? 1 : maxDigits - 1); // ensures number 2 is a smaller number from number1
    number2 = number2 == 0 ? 1 : number2;
    number1 -= number1 % number2; // ensures a integer results from division
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

int mathGenerator::generateNumber(int maxDigits) {
    short carry = 1;
    if(maxDigits < 0) {
        carry = -1;
    }
    return (rand() % (int)std::pow(10, abs(maxDigits))) * carry;
}

char mathGenerator::fetchNotation(mathOperator operation) {
    switch(operation) {
        case multiplication:
            return '*';
        case division:
            return '/';
        case addition:
            return '+';
        case subtraction:
            return '-';
        default:
            return '?';
    }
};

mathGenerator::questions mathGenerator::generateQuestion(difficulty level, bool isAlgebra) {
    srand(time(0));
    if(isAlgebra) {
        equation algebra = generateAlgebra(level);
        std::vector<std::string> answers = std::vector<std::string>();
        int numberOfDigits;
        short carryNegative = 0;
        if(algebra.answer < 0) {
            numberOfDigits = (int)std::ceil(std::log10(algebra.answer == 0 ? 1 : -1 * algebra.answer));
            carryNegative = -1;
        } else {
            numberOfDigits = (int)std::ceil(std::log10(algebra.answer == 0 ? 1 : algebra.answer)); // 10 ^ 4.2 = 20549 // 10 ^ 4 = 10000 10 ^ 5 = 100000 5
            carryNegative = 1;
        }
        answers.push_back(std::to_string(algebra.answer));
        for(int j = 0; j < TOTAL_QUESTIONS - 1; j++) {
            int randomAnswer = generateNumber(numberOfDigits * carryNegative);                                 // generates a randomized alternative (wrong) answer for the user to not select after solving
            answers.push_back(std::to_string(randomAnswer == algebra.answer ? ++randomAnswer : randomAnswer)); // verifies the wrong answer is not correct, if this edge case occurs then add one (making it rightfully wrong)
        }
        questions returnValue = questions();
        returnValue.addQuestion(algebra.viewableEquation, answers);
        return returnValue;

    } else {
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

        int numberOfOperations = rand() % (maxOperations + 1); // sets the number of operations to generate to between 1 and max operations.
        numberOfOperations = numberOfOperations == 0 ? 1 : numberOfOperations;
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
}

mathGenerator::equation mathGenerator::generateAlgebra(difficulty level) {
    srand(time(0));
    int maxDigits[4];
    int maxOperations;

    switch(level) {
        case easy:
            maxDigits[0] = 1; // multiplication
            maxDigits[1] = 1; // division
            maxDigits[2] = 2; // addition
            maxDigits[3] = 2; // subtraction
            maxOperations = 1;
            break;
        case moderate:
            maxDigits[0] = 1; // multiplication
            maxDigits[1] = 1; // division
            maxDigits[2] = 2; // addition
            maxDigits[3] = 2; // subtraction
            maxOperations = 2;
            break;
        case difficult:
            maxDigits[0] = 2; // multiplication
            maxDigits[1] = 2; // division
            maxDigits[2] = 2; // addition
            maxDigits[3] = 2; // subtraction
            maxOperations = 3;
            break;
        case extreme:
            maxDigits[0] = 2; // multiplication
            maxDigits[1] = 2; // division
            maxDigits[2] = 3; // addition
            maxDigits[3] = 3; // subtraction
            maxOperations = 4;
            break;
    }
    // 0-230942
    // 0 - maxOperations (inclusive) maxoperations: 4 // 1,2,3,4
    // rand() % 4 + 1 (5) - > 9/5 = 4

    // maxOperations = 2
    int operations = rand() % (maxOperations + 1);
    operations = operations == 0 ? 1 : operations;
    int operatorCount[4] = {0, 0, 0, 0}; // count of each operator in mathOperators
    std::vector<int> numbersInProblem;
    for(int i = 0; i < operations + 1; i++) {
        numbersInProblem.push_back(-1);
    }
    std::vector<mathOperator> mathOperators = std::vector<mathOperator>();
    for(int i = 0; i < operations; i++) { // int i = 0; 0 < 2
        switch(rand() % 4) {
            case(0): // Multiplication
                mathOperators.push_back(multiplication);
                operatorCount[0]++;
                break;
            case(1): // Division
                mathOperators.push_back(division);
                operatorCount[1]++;
                break;
            case(2): // Addition
                mathOperators.push_back(addition);
                operatorCount[2]++;
                break;
            case(3): // Subtraction
                mathOperators.push_back(subtraction);
                operatorCount[3]++;
                break;
        }
    }
    int numberOfDivisionsFound = 0;
    for(int i = 0; i < mathOperators.size(); i++) {
        if(numberOfDivisionsFound >= operatorCount[1]) { // break if we found all the division operators
            break;
        }

        if(mathOperators[i] == division) {
            mathOperation selectedOperation = generateDivision(maxDigits[1]);
            numbersInProblem[i] = selectedOperation.number1;
            numbersInProblem[i + 1] = selectedOperation.number2;
            numberOfDivisionsFound++;
        }
    }
    for(int i = 0; i < numbersInProblem.size(); i++) {
        if(numbersInProblem[i] == -1) { // 5 (4) 4 (3)
            numbersInProblem[i] = generateNumber(maxDigits[mathOperators[i < mathOperators.size() ? i : i - 1]]);
        }
    }

    std::string viewableEquation = "Resolve the following: ";
    for(int i = 0; i < numbersInProblem.size(); i++) {
        viewableEquation += std::to_string(numbersInProblem[i]) + " ";
        if(i != numbersInProblem.size() - 1) {
            viewableEquation += fetchNotation(mathOperators.at(i));
            viewableEquation += " ";
        }
    }
    // 20 * 21 / 2 + 11 - 2 / 1
    // 210 / 2 + 11 - 2 / 1
    // 20 * 21 = 420 / 2 = 210
    // 210 + 11 - 2
    // 210 + 11 = 221 - 2 = 219
    std::vector<int> numbersForCalc = numbersInProblem;
    std::vector<mathOperator> operatorsForCalc = mathOperators;

    for(int i = 0; i < operatorsForCalc.size(); i++) {
        if(operatorsForCalc[i] == multiplication) {
            numbersForCalc[i] = numbersForCalc[i] * numbersForCalc[i + 1];
            numbersForCalc.erase(numbersForCalc.begin() + i + 1); // TODO: Verify this remove the indexed value instead of setting the content to null or something
            operatorsForCalc.erase(operatorsForCalc.begin() + i);
            i--;
        } else if(operatorsForCalc[i] == division) {
            numbersForCalc[i] = numbersForCalc[i] / numbersForCalc[i + 1];
            numbersForCalc.erase(numbersForCalc.begin() + i + 1);
            operatorsForCalc.erase(operatorsForCalc.begin() + i);
            i--;
        }
    }

    for(int i = 0; i < operatorsForCalc.size(); i++) {
        if(operatorsForCalc[i] == addition) {
            numbersForCalc[i] = numbersForCalc[i] + numbersForCalc[i + 1];
            numbersForCalc.erase(numbersForCalc.begin() + i + 1); // TODO: Verify this remove the indexed value instead of setting the content to null or something
            operatorsForCalc.erase(operatorsForCalc.begin() + i);
            i--;
        } else if(operatorsForCalc[i] == subtraction) {
            numbersForCalc[i] = numbersForCalc[i] - numbersForCalc[i + 1];
            numbersForCalc.erase(numbersForCalc.begin() + i + 1);
            operatorsForCalc.erase(operatorsForCalc.begin() + i);
            i--;
        }
    }

    return equation(numbersInProblem, mathOperators, numbersForCalc[0], viewableEquation);
};