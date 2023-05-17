#include "readword2.h"
#include "ui_readword2.h"

ReadWord2::ReadWord2(QString path, int task, QWidget* parent)
    : task(task)
    , QThread(parent)
{

    this->path = path.replace("/", "\\");
}

ReadWord2::~ReadWord2()
{
    delete ui;
}

void ReadWord2::run()
{
    m_hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    if (FAILED(m_hr)) {
        qCritical() << "Failed to initialize COM";
        return;
    }

    if (task == 1) {
        axWidget = new QAxWidget();

        if (axWidget != nullptr) {
            axWidget->setControl("Word.Application");
            axWidget->setProperty("Visible", true);

            axWidget->dynamicCall("Activate()");
            documents = axWidget->querySubObject("Documents");
            document = documents->querySubObject("Open(const QString&, bool, bool)", path, false, true);
            content = document->querySubObject("Content");
            QString text = content->property("Text").toString();
        }
    } else if (task == 2) {
        axWidget = new QAxWidget();

        if (axWidget != nullptr) {
            axWidget->setControl("Excel.Application");
            axWidget->setProperty("Visible", true);

            QAxObject* workbooks = axWidget->querySubObject("Workbooks");
            QAxObject* workbook = workbooks->querySubObject("Open(const QString&, bool, bool)", path, false, true);
            QAxObject* sheets = workbook->querySubObject("Sheets");
            QAxObject* sheet = sheets->querySubObject("Item(int)", 1);
            QAxObject* range = sheet->querySubObject("Range(const QString&)", "A1");
            QString text = range->property("Value").toString();
        }
    }

    CoUninitialize();
}
