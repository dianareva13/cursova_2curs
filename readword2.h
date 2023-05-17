#ifndef READWORD2_H
#define READWORD2_H

#include <QAxObject>
#include <QAxWidget>
#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>
#include <QThread>
#include <QWidget>
#include <Windows.h>
#include <objbase.h>

class ReadWord2 : public QThread {

public:
    explicit ReadWord2(QString path, int task, QWidget* parent = nullptr);
    ~ReadWord2();

protected:
    QString path;
    HRESULT m_hr;

    void run() override;

    QAxWidget* axWidget;
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

#endif // READWORD2_H
