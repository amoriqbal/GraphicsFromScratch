#include "dda.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DDA w;
    w.show();
    return a.exec();
}
