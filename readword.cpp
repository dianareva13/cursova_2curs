#include "readword.h"
#include "windows.h"

ReadWord::ReadWord(QString path, int task, QWidget* parent)
    : task(task)
    , QThread(parent)
{
    this->path = path.replace("/", "\\");
}

ReadWord::~ReadWord()
{

    if (task == 1) {
        delete content;
        delete document;
        delete documents;
        delete axWidget;
    } else if (task == 2) {
        delete workbooks;
        delete workbook;
        delete sheets;
        delete sheet;
        delete range;
    }

    delete axWidget;
}

void ReadWord::run()
{
    m_hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    if (FAILED(m_hr)) {
        qCritical() << "Failed to initialize COM";
        return;
    }

    if (task == 1) {
        axWidget = new MyAxWidget();

        if (axWidget != nullptr) {
            axWidget->setControl("Word.Application");
            documents = axWidget->querySubObject("Documents");
            document = documents->querySubObject("Open(const QString&, bool, bool)", path, false, true);
            content = document->querySubObject("Content");
            QString text = content->property("Text").toString();

            axWidget->setProperty("Visible", true);
            axWidget->dynamicCall("Activate()");
        }

    } else if (task == 2) {
        axWidget = new MyAxWidget();

        if (axWidget != nullptr) {
            axWidget->setControl("Excel.Application");
            QAxObject* workbooks = axWidget->querySubObject("Workbooks");
            QAxObject* workbook = workbooks->querySubObject("Open(const QString&, bool, bool)", path, false, true);
            QAxObject* sheets = workbook->querySubObject("Sheets");
            QAxObject* sheet = sheets->querySubObject("Item(int)", 1);
            QAxObject* range = sheet->querySubObject("Range(const QString&)", "A1");
            QString text = range->property("Value").toString();

            axWidget->setProperty("Visible", true);
        }
    }

    CoUninitialize();
}
