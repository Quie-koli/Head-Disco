#include "HeadDisco.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HeadDisco w;
    w.show();
    return a.exec();
}
