/*
 TODO:
 - Dodati podršku za spremanje datoteka
 - Omogućiti učitavanje binarnih .txt fajlova
*/


#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
