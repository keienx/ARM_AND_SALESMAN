#include "mainwindow.h"

#include <QApplication>
#include <QWidget>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("ARM release v.0.2");
    w.show();
    return a.exec();
}
