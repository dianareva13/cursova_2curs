#ifndef FULLINFO_H
#define FULLINFO_H

#include "OS_CHECK.h"
#include "viewfile.h"
#include <QDebug>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QTextCodec>
#include <QTextEdit>
#include <QVector>
#include <QWidget>

namespace Ui {
class FullInfo;
}

class FullInfo : public QWidget {
    Q_OBJECT

public:
    explicit FullInfo(QString date, QString lineEditText, QString textEditText, QLineEdit* lineEdit_ptr, QTextEdit* textEdit_ptr, QPushButton* saveBtn_ptr, QVector<QPushButton*> btns, QWidget* parent = nullptr);
    ~FullInfo();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void fileBtn_ect(QString date, int btn_num, QVector<QPushButton*> btns);

    void fileBtn_ect_checked_date(QString date, int btn_num, QVector<QPushButton*> btns);

    void openFile(QString path);

private:
    Ui::FullInfo* ui;

    QString date;
    QString lineEditText;
    QString textEditText;

    void messBox(QString val);

    QLineEdit* lineEdit_ptr;
    QTextEdit* textEdit_ptr;
    QPushButton* saveBtn_ptr;

    ViewFile* viewfile;
    QVector<ViewFile*> viewfile_ptr;

    QVector<QPushButton*> btnsLast;

    QString getFileIcon(QString path);

    std::string transliterate(std::string original_string);
};

#endif // FULLINFO_H
