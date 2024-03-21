// #ifndef _MATH_GENERATOR_HPP
// #define _MATH_GENERATOR_HPP
#pragma once

#include <string>
#include <vector>

namespace puzzleGeneration {
    class mathGenerator;
}

class mathGenerator {

public:
    struct questions {
        std::vector<std::string> questionsAsked;
        std::vector<std::vector<std::string>> answers;

        questions() {}

        questions(std::vector<std::string> question, std::vector<std::string> answers) {
            this->questionsAsked = question;
            this->answers.push_back(answers);
        }

        void addQuestion(std::string question, std::vector<std::string> answers) { // NOTE: Verify this way of copying the vectors doesn't cause a segfault or undefined behavior
            this->questionsAsked.push_back(question);
            this->answers.push_back(answers);
        }
    };

    enum mathOperator {
        multiplication,
        division,
        addition,
        subtraction
    };

    struct mathOperation {
        int number1;
        int number2;
        int answer;
        mathOperator operation;

        mathOperation() {
            number1 = 0;
            number2 = 0;
            answer = 0;
            operation = multiplication;
        }
        mathOperation(int number1, int number2, int answer, mathOperator operation) {
            this->number1 = number1;
            this->number2 = number2;
            this->answer = answer;
            this->operation = operation;
        }

        char fetchNotation() {
            switch(operation) {
                case multiplication:
                    return '*';
                case division:
                    return '/';
                case addition:
                    return '+';
                case subtraction:
                    return '-';
            }
            return '?';
        }
    };

    enum difficulty {
        easy,
        moderate,
        difficult,
        extreme
    };
    static mathOperation generateMultiplication(int maxDigits);
    static mathOperation generateDivision(int maxDigits);
    static mathOperation generateAddition(int maxDigits);
    static mathOperation generateSubtraction(int maxDigits);
    static questions generateQuestion(difficulty level);
};

// #endif
