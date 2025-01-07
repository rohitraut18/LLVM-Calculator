// calculator.h
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include "llvm_evaluator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QWidget {
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void on_buttonClicked();

private:
    Ui::Calculator *ui;
    LLVM_Evaluator evaluator;  // Object to evaluate expressions
};

#endif // CALCULATOR_H
