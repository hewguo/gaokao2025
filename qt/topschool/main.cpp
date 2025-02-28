#include "mainwindow.h"

#include <QApplication>
#include <QScreen>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;

    QScreen *scr=a.primaryScreen();
    int scr_w=scr->size().width();
    int scr_h=scr->size().height();
    w.move((scr_w-w.width())/2,(scr_h-w.height())/2);

    w.show();
    return a.exec();
}
