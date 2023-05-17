#ifndef VIEWFILE_H
#define VIEWFILE_H

#include "readword.h"
#include <QAxBase>
#include <QAxObject>
#include <QAxSelect>
#include <QAxWidget>
#include <QCloseEvent>
#include <QDebug>
#include <QEventLoop>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFuture>
#include <QLabel>
#include <QMetaObject>
#include <QPixmap>
#include <QProcess>
#include <QStandardPaths>
#include <QTextStream>
#include <QThread>
#include <QVector>
#include <QWidget>
#include <iostream>

namespace Ui {
class ViewFile;
}

class ViewFile : public QWidget {
    Q_OBJECT

public:
    explicit ViewFile(QString path, QWidget* parent = nullptr);
    ~ViewFile();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ViewFile* ui;

    QString path;

    ReadWord* threadWord;
    QVector<ReadWord*> threadWord_ptr;
};

#endif // VIEWFILE_H
