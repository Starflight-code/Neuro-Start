#include "../mathgenerator.cpp"
#include <cstdlib>

int main(int argc, char** argv) {
    mathOperation operation = mathOperation();
    int exitcode = 0;
    switch(atoi(argv[1])) {
        case 0: // Multiplication
            for(int i = 1; i < 10; i++) {
                operation = generateMultiplication(i);
                if(operation.number1 > pow(10, i) || operation.number2 > pow(10, i)) {
                    printf("Number1: %d Number2: %d greater than %d digits\n", operation.number1, operation.number2, i);
                    exitcode = 1;
                }
                if(operation.answer != operation.number1 * operation.number2) {
                    printf("Answer incorrect: %d * %d != %d\n", operation.number1, operation.number2, operation.answer);
                    exitcode = 1;
                }
            }
            break;
        case 1: // Division
            for(int i = 1; i < 10; i++) {
                operation = generateDivision(i);
                if(operation.number1 > pow(10, i) || operation.number2 > pow(10, i)) {
                    printf("Number1: %d or Number2: %d greater than %d digits\n", operation.number1, operation.number2, i);
                    exitcode = 1;
                }
                if(operation.answer != operation.number1 / operation.number2) {
                    printf("Answer incorrect: %d / %d != %d\n", operation.number1, operation.number2, operation.answer);
                    exitcode = 1;
                }
                if(operation.number1 % operation.number2 != 0) {
                    printf("Uneven Division: %d mod %d != 0\n", operation.number1, operation.number2);
                    exitcode = 1;
                }
            }
            break;
        case 2: // Addition
            for(int i = 1; i < 10; i++) {
                operation = generateAddition(i);
                if(operation.number1 > pow(10, i) || operation.number2 > pow(10, i)) {
                    printf("Number1: %d or Number2: %d greater than %d digits\n", operation.number1, operation.number2, i);
                    exitcode = 1;
                }
                if(operation.answer != operation.number1 + operation.number2) {
                    printf("Answer incorrect: %d - %d != %d\n", operation.number1, operation.number2, operation.answer);
                    exitcode = 1;
                }
            }
            break;
        case 3: // Subtraction
            for(int i = 1; i < 10; i++) {
                operation = generateSubtraction(i);
                if(operation.number1 > pow(10, i) || operation.number2 > pow(10, i)) {
                    printf("Number1: %d or Number2: %d greater than %d digits\n", operation.number1, operation.number2, i);
                    exitcode = 1;
                }
                if(operation.answer != operation.number1 - operation.number2) {
                    printf("Answer incorrect: %d - %d != %d\n", operation.number1, operation.number2, operation.answer);
                    exitcode = 1;
                }
            }
            break;
        default:
            return 1; // raise an exception upon invalid args
    }
    return exitcode;
}