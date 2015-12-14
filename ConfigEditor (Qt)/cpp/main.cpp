#include "confige.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConfigE w;
    w.show();

    return a.exec();
}
