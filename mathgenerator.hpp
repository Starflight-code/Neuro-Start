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

    enum mathOperator { // 29 x 92 / 29 / 3
                        // List<int> = 29 92 29 3
                        // List<mathOperator> = multiplication division division
                        // 1: division or multiplication 2: addition or subtraction // MD - AS
                        // List<mathOperators> x
                        // for (x) -> list<int>[i] = x[i] == multi || x[i] div + x[i] == add || x[i] sub // sdasfa
        multiplication = 0,
        division = 1,
        addition = 2,
        subtraction = 3
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

    public:
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
                default:
                    return '?';
            }
        }
    };

    struct equation {
    public:
        std::vector<int> numbers;
        std::vector<mathOperator> operators;
        int answer;
        std::string viewableEquation;

        equation() {
            this->numbers = std::vector<int>();
            this->operators = std::vector<mathOperator>();
            answer = 0;
            viewableEquation = "";
        }
        equation(std::vector<int> numbers, std::vector<mathOperator> operators, int answer, std::string viewableEquation) {
            this->numbers = numbers;
            this->operators = operators;
            this->answer = answer;
            this->viewableEquation = viewableEquation;
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
    static mathOperation generateDivisionWithNumerator(int numerator);
    static mathOperation generateAddition(int maxDigits);
    static mathOperation generateSubtraction(int maxDigits);
    static equation generateAlgebra(difficulty level);
    static int findNumberOfDigits(int answer);
    static void generateRandomAnswers(std::vector<std::string>* answers, int answer, int numberOfQuestions, int numberOfDigits);
    static int generateNumber(int maxDigits);
    static char fetchNotation(mathOperator operation);
    static questions generateQuestion(difficulty level, bool isAlgebra);
};

// #endif
