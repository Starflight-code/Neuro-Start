#ifndef MATHQUESTIONEER_H
#define MATHQUESTIONEER_H

#include "mathgenerator.hpp"
#include <QMainWindow>

namespace Ui {
    class MathQuestioneer;
}

class MathQuestioneer : public QMainWindow {
    Q_OBJECT

public:
    void start();
    void next();
    void check(int answerIndex);
    explicit MathQuestioneer(QWidget* parent = nullptr);
    ~MathQuestioneer();

private slots:
    void on_answer1_clicked();

    void on_answer2_clicked();

    void on_answer3_clicked();

    void on_answer4_clicked();

private:
    Ui::MathQuestioneer* ui;
    mathGenerator::questions nextUp;
    int questionIndex;
    int randomIndexes[4];
};

#endif // MATHQUESTIONEER_H
