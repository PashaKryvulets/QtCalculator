#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QIcon icon(":/img/QtCalculatorlogo.png");
    w.setWindowIcon(icon);
    w.setWindowTitle("QtCalculator");
    w.setFixedSize(339, 461);
    w.show();
    return a.exec();
}
