#ifndef READWORD_H
#define READWORD_H

#include "myaxwidget.h"
#include <QAxObject>
#include <QAxWidget>
#include <QDebug>
#include <QException>
#include <QFileDialog>
#include <QFileInfo>
#include <QThread>
#include <Windows.h>
#include <objbase.h>

class ReadWord : public QThread {

public:
    explicit ReadWord(QString path, int task, QWidget* parent = nullptr);
    ~ReadWord();

private:
    QString path;
    HRESULT m_hr;

    void run() override;

    MyAxWidget* axWidget;
    QAxObject* documents;
    QAxObject* document;
    QAxObject* content;

    int task;

    QAxObject* workbooks;
    QAxObject* workbook;
    QAxObject* sheets;
    QAxObject* sheet;
    QAxObject* range;
};

#endif // READWORD_H
