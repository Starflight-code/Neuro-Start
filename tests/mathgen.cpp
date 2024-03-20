#include "../mathgenerator.cpp"
#include <cstdlib>

int main(int argc, char** argv) {
    mathOperation operation = mathOperation();
    switch(atoi(argv[1])) {
        case 0: // Multiplication
            for(int i = 1; i < 10; i++) {
                operation = generateMultiplication(i);
                if(operation.number1 > pow(10, i) || operation.number2 > pow(10, i)) {
                    return 1;
                }
                if(operation.answer != operation.number1 * operation.number2) {
                    return 1;
                }
            }
            break;
        case 1: // Division
            break;
        case 2: // Addition
            break;
        case 3: // Subtraction
            break;
        default:
            return 1; // raise an exception upon invalid args
    }
    return 0;
}