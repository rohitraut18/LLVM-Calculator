// calculator.cpp
#include "calculator.h"
#include "ui_calculator.h"
#include <QPushButton>
#include <QString>
#include <QLineEdit>

Calculator::Calculator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);

    // Connect buttons to the slot
    connect(ui->button_0, &QPushButton::clicked, this, &Calculator::on_buttonClicked);
    connect(ui->button_1, &QPushButton::clicked, this, &Calculator::on_buttonClicked);
    // Similarly for other buttons (button_2 to button_9, operators, etc.)

    connect(ui->button_equals, &QPushButton::clicked, this, &Calculator::on_buttonClicked);
    connect(ui->button_clear, &QPushButton::clicked, this, &Calculator::on_buttonClicked);
}

Calculator::~Calculator() {
    delete ui;
}

void Calculator::on_buttonClicked() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    QString buttonText = button->text();

    // Clear the input field if "C" button is clicked
    if (buttonText == "C") {
        ui->lineEdit_display->clear();
        return;
    }

    // Handle equals button to evaluate expression
    if (buttonText == "=") {
        std::string expression = ui->lineEdit_display->text().toStdString();
        double result = evaluator.evaluateExpression(expression);
        ui->lineEdit_display->setText(QString::number(result));
        return;
    }

    // Append the clicked button text to the display
    ui->lineEdit_display->setText(ui->lineEdit_display->text() + buttonText);
}
