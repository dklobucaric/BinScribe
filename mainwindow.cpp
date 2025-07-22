#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::saveAsBinary);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveAsBinary()
{
    QString text = ui->textEdit->toPlainText();

    QString binaryOutput;
    for (QChar ch : text) {
        binaryOutput += QString("%1").arg(static_cast<ushort>(ch.unicode()), 8, 2, QLatin1Char('0'));
    }

    QString fileName = QFileDialog::getSaveFileName(this, "Save Binary File", "", "Text Files (*.txt)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << binaryOutput;
            file.close();
        }
    }
}
