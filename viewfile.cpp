#include "viewfile.h"
#include "OS_CHECK.h"
#include "ui_viewfile.h"

ViewFile::ViewFile(QString path, QWidget* parent)
    : QWidget(parent)
    , path(path)
    , ui(new Ui::ViewFile)
{
    ui->setupUi(this);

    QFileInfo fileInfo(path);
    QString fileName = fileInfo.fileName();
    QString fileExtension = fileInfo.suffix();

    ui->label->setText(fileName);
    ui->label_2->setText(fileExtension);

    if (fileExtension == "png" || fileExtension == "jpg") {
        ui->stackedWidget->setCurrentIndex(1);
        QPixmap pixmap(path);
        ui->label_2->setPixmap(pixmap);

    } else if (fileExtension == "txt") {
        ui->stackedWidget->setCurrentIndex(0);
        QFile file(path);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString fileContent = in.readAll();
            ui->textBrowser->setText(fileContent);
            file.close();
        } else {
            ui->textBrowser->setText("Unable to open file.");
        }
    } else if (fileExtension == "docx") {
        ui->label_3->setText("Please weit few second for starting app OR save and open on pc.");

        if (OS == 1) {
            threadWord = new ReadWord(path, 1);
            threadWord_ptr.push_back(threadWord);
            threadWord->start();
        }

    } else if (fileExtension == "xlsx") {
        ui->label_3->setText("Please weit few second for starting app OR save and open on pc.");

        if (OS == 1) {
            threadWord = new ReadWord(path, 2);
            threadWord_ptr.push_back(threadWord);
            threadWord->start();
        }

    } else {
        ui->stackedWidget->setCurrentIndex(3);
        ui->label_3->setText("Can't provide this format (" + fileExtension + ")! Please save and open in other app.");
    }
}

ViewFile::~ViewFile()
{
    for (auto el : threadWord_ptr) {
        el->quit();
        delete el;
    }

    delete ui;
}

void ViewFile::on_pushButton_clicked()
{
    QFileInfo fileInfo(path);
    QString defaultPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

    QString fileExt;
    QString genPath = defaultPath + "/" + fileInfo.baseName();

    if (fileInfo.suffix() == "txt") {
        fileExt = "Text Files (*.txt);";
    } else if (fileInfo.suffix() == "jpg") {
        fileExt = "JPEG Image (*.jpg);";
    } else if (fileInfo.suffix() == "png") {
        fileExt = "PNG Image(*.png);";
    } else {
        fileExt = "All Files (*.*);";
        genPath = defaultPath + "/" + fileInfo.fileName() + "." + fileInfo.suffix();
    }

    QString savePath = QFileDialog::getSaveFileName(this,
        "Save File", genPath, fileExt);

    QFile::copy(path, savePath);
    QFile::setPermissions(savePath, QFile::WriteOwner | QFile::ReadOwner);
}
