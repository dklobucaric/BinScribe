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
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QIcon>
#include <QMessageBox>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Postavljanje naslova prozora i ikone aplikacije
    setWindowTitle("BinScribe v1.1.1");
    setWindowIcon(QIcon(":/BinScribe.ico"));

    // Povezivanje akcija s custom slotovima
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::newFile);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::saveAsBinary()
{
    QString text = ui->textEdit->toPlainText();
    QString binaryOutput;

    for (int i = 0; i < text.size(); ++i) {
        QChar ch = text.at(i);
        // 16-bitno binarno kodiranje (Unicode)
        binaryOutput += QString::number(static_cast<ushort>(ch.unicode()), 2).rightJustified(16, '0');

    }

    QString fileName = QFileDialog::getSaveFileName(this, "Spremi kao binarni tekst", "", "Text Files (*.txt)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << binaryOutput;
            file.close();

            QMessageBox::information(this, "Spremljeno", QString("Datoteka '%1' je spremljena.").arg(fileName));
            return true;
        }
    }

    return false;
}


void MainWindow::newFile()
{
    if (!ui->textEdit->toPlainText().isEmpty()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Novi dokument",
                                      "Tekst nije prazan. Želite li ga spremiti prije brisanja?",
                                      QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        if (reply == QMessageBox::Yes) {
            if (!saveAsBinary()) return;
            ui->textEdit->clear();
        } else if (reply == QMessageBox::No) {
            ui->textEdit->clear();
        }
        // Ako je Cancel — ne radi ništa
    } else {
        ui->textEdit->clear();
    }
}

void MainWindow::openFile()
{
    if (!ui->textEdit->toPlainText().isEmpty()) {
        QMessageBox::StandardButton reply = QMessageBox::question(
            this, "Spremi promjene",
            "Želite li spremiti trenutni dokument prije otvaranja novog?",
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        if (reply == QMessageBox::Yes) {
            if (!saveAsBinary()) return;
        } else if (reply == QMessageBox::Cancel) {
            return;
        }
    }

    QString fileName = QFileDialog::getOpenFileName(this, "Open Text File", "", "Text Files (*.txt)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString content = in.readAll();
            file.close();

            // Provjeri je li binarni sadržaj (samo 0 i 1) i duljina višekratnik 16
            static const QRegularExpression binRe("^[01]+$");
            if (binRe.match(content).hasMatch() && content.length() % 16 == 0) {
                QString decoded;
                for (int i = 0; i < content.length(); i += 16) {
                    QString binary16 = content.mid(i, 16);
                    bool ok;
                    ushort unicode = binary16.toUShort(&ok, 2);
                    if (ok) {
                        decoded.append(QChar(unicode));
                    } else {
                        QMessageBox::warning(this, "Greška", "Dekodiranje nije uspjelo (neispravna binarna riječ).");
                        return;
                    }
                }
                ui->textEdit->setPlainText(decoded);
                return;
            }

            // Inače normalni tekst
            ui->textEdit->setPlainText(content);
        }
    }
}


void MainWindow::saveFile()
{
    saveAsBinary();
}
#include <QMessageBox>

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "About BinScribe",
                       "BinScribe v1.1.2\n\nSimple application to convert text to binary and back.\n\n© 2025 Dalibor Klobučarić\nReleased under GNU GPL v3.");
}
