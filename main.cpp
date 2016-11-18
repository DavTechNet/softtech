#include <QtGui/QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include "IHM/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Traduction des chaines Qt
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),
        QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&qtTranslator);

    MainWindow w;
    w.show();
    
    return a.exec();
}
