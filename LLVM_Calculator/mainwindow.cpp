#include "mainwindow.h"
#include "calculator.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    calculator = new Calculator(this);


    setCentralWidget(calculator);

    setWindowTitle("Qt Calculator");
    resize(300, 400);
}

MainWindow::~MainWindow()
{
    delete ui;
}
