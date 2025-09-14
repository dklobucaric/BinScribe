// verzija 1.1.2
/*
 * BinScribe — jednostavna aplikacija za zapisivanje teksta u binarnom obliku
 * Copyright (C) 2025  Dalibor Klobučarić
 *
 * Ovaj program je slobodni softver: možete ga redistribuirati i/ili mijenjati
 * pod uvjetima GNU General Public License verzije 3 ili novije.
 *
 * Ovaj program se distribuira u nadi da će biti koristan,
 * ali BEZ IKAKVOG JAMSTVA; pogledajte GNU GPL za više detalja.
 *
 * Više informacija: https://www.gnu.org/licenses/gpl-3.0.html
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
