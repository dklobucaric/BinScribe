// verzija 1.1.0
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
    setWindowTitle("BinScribe v1.1");
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
        binaryOutput += QString("%1").arg(static_cast<ushort>(ch.unicode()), 8, 2, QLatin1Char('0'));
    }

    QString fileName = QFileDialog::getSaveFileName(this, "Save Binary File", "", "Text Files (*.txt)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << binaryOutput;
            file.close();

            QMessageBox::information(this, "Datoteka spremljena",
                                     QString("Datoteka '%1' je uspješno spremljena.").arg(fileName));
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
            saveAsBinary();
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

            // Provjeri je li sadržaj binaran (samo 0 i 1, duljina višekratnik 8)
            static const QRegularExpression re("^[01]+$");
            if (re.match(content).hasMatch() && content.length() % 8 == 0) {
                QString decoded;
                for (int i = 0; i < content.length(); i += 8) {
                    QString byteString = content.mid(i, 8);
                    bool ok;
                    ushort unicodeValue = byteString.toUShort(&ok, 2);
                    if (ok) {
                        decoded.append(QChar(unicodeValue));
                    } else {
                        QMessageBox::warning(this, "Greška", "Ne mogu dekodirati binarni sadržaj.");
                        return;
                    }
                }
                ui->textEdit->setPlainText(decoded);
            } else {
                // Normalni UTF tekst
                ui->textEdit->setPlainText(content);
            }
        }
    }
}


void MainWindow::saveFile()
{
    saveAsBinary();
}
