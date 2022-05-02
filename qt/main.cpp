#include "menu.h"
#include "singleplayer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Singleplayer s;
    s.show();
    return a.exec();
}
