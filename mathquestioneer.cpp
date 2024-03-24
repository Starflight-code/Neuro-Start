#include "mathquestioneer.h"
#include "ui_mathquestioneer.h"

MathQuestioneer::MathQuestioneer(QWidget* parent) : QMainWindow(parent),
                                                    ui(new Ui::MathQuestioneer) {
    ui->setupUi(this);
}

MathQuestioneer::~MathQuestioneer() {
    delete ui;
}

void MathQuestioneer::check(int answerIndex) {
    if(randomIndexes[answerIndex] == 0) { // correct
        printf("Correct Answer\n");
    } else { // wrong
        printf("Wrong Answer\n");
    }

    if(nextUp.questionsAsked.size() <= questionIndex) { // out of questions... TODO: Make this go back to the menu
        exit(0);
    } else {
        next();
    }
}

void MathQuestioneer::start() {
    for(int i = 0; i < 4; i++) {
        randomIndexes[i] = -1;
    }

    nextUp = mathGenerator::generateQuestion(mathGenerator::difficulty::difficult, true);

    questionIndex = 0;
    next();
}

void MathQuestioneer::next() {
    ui->mathQuestion->setText(QString::fromStdString(nextUp.questionsAsked[questionIndex]));
    int indexesLeft[5] = {0, 1, 2, 3, -1};
    srand(time(0));
    for(int i = 0; i < 4; i++) {
        int indexSelected = rand() % (4 - i);
        randomIndexes[i] = indexesLeft[indexSelected];
        for(int j = indexSelected; j < 4; j++) {
            indexesLeft[j] = indexesLeft[j + 1];
        }
    }
    ui->answer1->setText(QString::fromStdString(nextUp.answers[questionIndex][randomIndexes[0]]));
    ui->answer2->setText(QString::fromStdString(nextUp.answers[questionIndex][randomIndexes[1]]));
    ui->answer3->setText(QString::fromStdString(nextUp.answers[questionIndex][randomIndexes[2]]));
    ui->answer4->setText(QString::fromStdString(nextUp.answers[questionIndex][randomIndexes[3]]));

    questionIndex++;
}

void MathQuestioneer::on_answer1_clicked() {
    check(0);
}

void MathQuestioneer::on_answer2_clicked() {
    check(1);
}

void MathQuestioneer::on_answer3_clicked() {
    check(2);
}

void MathQuestioneer::on_answer4_clicked() {
    check(3);
}
