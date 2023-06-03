#include <QCoreApplication>
#include "armserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ARMserver s;
    return a.exec();
}
