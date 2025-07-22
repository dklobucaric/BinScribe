// verzija 1.1.0
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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newFile();
    void openFile();
    void saveFile();

private:
    bool saveAsBinary();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
