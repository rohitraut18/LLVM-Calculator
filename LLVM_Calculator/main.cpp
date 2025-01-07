#include "calculator.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    // Initialize the QApplication with command line arguments
    QApplication a(argc, argv);

    // Create and display the Calculator widget
    Calculator w;
    w.show();

    // Start the Qt event loop
    return a.exec();
}
