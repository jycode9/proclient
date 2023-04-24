#include "view/mainwindow/mainwindow.h"
#include <QApplication>
#include "base/glog.h"

int main(int argc, char *argv[])
{
    GLog::getInstance()->setLogMode(GLogMode::Console);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
