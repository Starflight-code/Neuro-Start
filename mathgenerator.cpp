#include "mathgenerator.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>
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
    number1 = number1 == 0 ? number2 : number1;
    int answer = number1 / number2;
    return mathOperation(number1, number2, answer, division);
}

mathGenerator::mathOperation mathGenerator::generateDivisionWithNumerator(int numerator) {
    int primes[] = {1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    int number1 = numerator;
    int maxDigits = findNumberOfDigits(numerator);
    int number2 = rand() % (int)std::pow(10, maxDigits == 0 ? 1 : maxDigits - 1); // ensures number 2 is a smaller number from number1
    number2 = number2 == 0 ? 1 : number2;
    // number1 -= number1 % number2; // ensures a integer results from division
    /*
    25 / 4 -> 6.25
    25 / (4 (25 % 4) = 5) = 5



    */
    int highestPrimeFactor;
    for(int i = 9; i >= 0; i--) {
        if(number1 % primes[i] == 0) {
            highestPrimeFactor = primes[i];
            break;
        }
    }
    if(highestPrimeFactor == 1) {
        number2 = 1;
    } else {
        number2 -= number2 % highestPrimeFactor == number2 ? number2 % highestPrimeFactor - highestPrimeFactor : number2 % highestPrimeFactor; // 28 / 7 | 19 % 7 = 5 = 19 - 5 = 14 | 28/14.....
    }
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

int mathGenerator::findNumberOfDigits(int answer) {
    bool isNonNegative = answer < 0 ? false : true; // if answer is negative, then isPositive = false. Otherwise true.
    answer = answer == 0 ? 1 : answer;
    int numberOfDigits = (int)std::ceil(std::log10(abs(answer)));
    return numberOfDigits * (isNonNegative * 2 - 1);
}

void mathGenerator::generateRandomAnswers(std::vector<std::string>* answers, int answer, int numberOfQuestions, int numberOfDigits) {
    for(int i = 0; i < numberOfDigits; i++) {
        int randomAnswer = generateNumber(numberOfDigits);
        answers->push_back(std::to_string(randomAnswer == answer ? ++randomAnswer : randomAnswer));
    }
}

mathGenerator::questions mathGenerator::generateQuestion(difficulty level, bool isAlgebra) {
    srand(time(0));
    if(isAlgebra) {
        equation algebra = generateAlgebra(level);
        std::vector<std::string> answers = std::vector<std::string>();

        int numberOfDigits = findNumberOfDigits(algebra.answer);

        answers.push_back(std::to_string(algebra.answer));
        mathGenerator::generateRandomAnswers(&answers, algebra.answer, TOTAL_QUESTIONS - 1, numberOfDigits);

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

        std::mt19937 gen(time(0));

        int numberOfOperations = gen() % (maxOperations + 1); // sets the number of operations to generate to between 1 and max operations.
        numberOfOperations = numberOfOperations == 0 ? 1 : numberOfOperations;
        numberOfOperations = (maxOperations + 1) - numberOfOperations;
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
    int divisionAnswers[numbersInProblem.size() - 1];
    for(int i = 0; i < mathOperators.size(); i++) {
        if(numberOfDivisionsFound >= operatorCount[1]) { // break if we found all the division operators
            break;
        } else {
        }

        if(mathOperators[i] == division) {
            mathOperation selectedOperation;
            if(i != 0 && mathOperators[i - 1] == division) {
                selectedOperation = generateDivisionWithNumerator(divisionAnswers[i - 1]);
            } else {
                selectedOperation = generateDivision(maxDigits[1]); // TODO: sometimes outputs a zero as numerator, triggering 0 outputs on generateDivisionWithNumerator
            }
            numbersInProblem[i] = selectedOperation.number1;
            numbersInProblem[i + 1] = selectedOperation.number2;
            divisionAnswers[i] = numbersInProblem[i] / numbersInProblem[i + 1];
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
    std::vector<int> numbersForCalc = numbersInProblem;
    std::vector<mathOperator> operatorsForCalc = mathOperators;

    for(int i = 0; i < operatorsForCalc.size(); i++) {
        if(operatorsForCalc[i] == multiplication) {
            numbersForCalc[i] = numbersForCalc[i] * numbersForCalc[i + 1];
            numbersForCalc.erase(numbersForCalc.begin() + i + 1);
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
            numbersForCalc.erase(numbersForCalc.begin() + i + 1);
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
