#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "OS_CHECK.h"
#include "fullinfo.h"
#include "viewfile.h"
#include "zipmanage.h"
#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QGraphicsOpacityEffect>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMessageBox>
#include <QMetaMethod>
#include <QProcess>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QScopedPointer>
#include <QScrollBar>
#include <QSharedPointer>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QStackedWidget>
#include <QString>
#include <QTextCodec>
#include <QTextEdit>
#include <QThread>
#include <QTimer>
#include <QVBoxLayout>
#include <QVector>
#include <QWheelEvent>
#include <algorithm>
#include <chrono>
#include <codecvt>
#include <cstring>
#include <ctime>
#include <direct.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <locale>
#include <memory>
#include <mutex>
#include <string>
#include <unzip.h>
#include <wchar.h>
#include <zip.h>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    int idPage = 0;

protected:
    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void saveDbInfo(QString date, QString lineEditText, QString textEditText, int idx);

    void sendInfoToUncMode(QString date, QString lineEditText, QString textEditText, QLineEdit* lineEdit_ptr, QTextEdit* textEdit_ptr, QPushButton* saveBtn_ptr, QVector<QPushButton*> btns);

    void on_pushButton_6_clicked();

    void fileBtn_ect(QString date, int btn_num, QVector<QPushButton*> btns);

    void on_pushButton_7_clicked();

    void on_actionClear_Db_triggered();

    void on_actionSave_As_triggered();

    void on_actionImport_triggered();

private:
    Ui::MainWindow* ui;
    QVBoxLayout* mainVLayout;
    QStackedWidget* stackedWidget;
    QVBoxLayout* lay1;
    QWidget* page1;
    QLabel* mainYearLabel;

    //cardItems
    QWidget* cardW;
    QVBoxLayout* cardVLayout;
    QLabel* cardLabel;
    QHBoxLayout* cardFileHLayout;
    QPushButton* cardFileBtn1;
    QPushButton* cardFileBtn2;
    QPushButton* cardFileBtn3;
    QPushButton* cardFileBtn4;
    QPushButton* cardFileBtn5;
    QLineEdit* cardLineEdit;
    QTextEdit* cardTextEdit;
    QPushButton* cardBtn;
    QHBoxLayout* cardPromizhHLayout;
    QHBoxLayout* cardPromizhHLayout2;
    QHBoxLayout* cardDownBtnHLayout;
    QPushButton* cardBtn2;

    void genNewCard(QString val);
    void genEmptyNewCard();
    void genPage(QVector<QString> val);

    //функции для даты
    QVector<QString> rangeOfDate(std::chrono::system_clock::time_point currDate, int daysRangeL = 0, int daysRangeR = 0);
    QVector<QVector<QString>> castDate(QVector<QString> vec);
    QString dateToString(std::chrono::system_clock::time_point currDate);
    void limitDate(QVector<QVector<QString>>& vec, int index);

    int stackedIdx;

    QVector<QWidget*> page1_ptr;
    QVector<QVBoxLayout*> lay1_ptr;
    QVector<QHBoxLayout*> cardPromizhHLayout_ptr;
    QVector<QHBoxLayout*> cardPromizhHLayout2_ptr;
    QVector<QVBoxLayout*> cardVLayout_ptr;
    QVector<QLabel*> cardLabel_ptr;
    QVector<QLineEdit*> cardLineEdit_ptr;
    QVector<QTextEdit*> cardTextEdit_ptr;
    QVector<QPushButton*> cardBtn_ptr;
    QVector<QWidget*> cardW_ptr;
    QVector<QPushButton*> cardBtn2_ptr;
    QVector<QLabel*> mainYearLabel_ptr;
    QVector<QHBoxLayout*> cardFileHLayout_ptr;
    QVector<QPushButton*> cardFileBtn1_ptr;
    QVector<QPushButton*> cardFileBtn2_ptr;
    QVector<QPushButton*> cardFileBtn3_ptr;
    QVector<QPushButton*> cardFileBtn4_ptr;
    QVector<QPushButton*> cardFileBtn5_ptr;
    QVector<QHBoxLayout*> cardDownBtnHLayout_ptr;

    void clearFu();

    //changer for anim
    void leftChanger();
    void rightChanger();

    //anim fro slider
    void sweapAnim(int button);
    void appearAnim(int button);
    void withoutAnim(int button);

    QString firstDate;
    QString lastDate;

    //cast qstring to chrono::system_clock::time_point
    std::chrono::system_clock::time_point qstring_to_time_point(QString val);

    //db
    QSqlDatabase db;
    void updateDbData();

    int zoomIdx;
    void chPerText();

    bool ctrlPress;
    int centralWidgetWidth;
    int centralWidgetHeight;

    void insertDbData();

    int idxBtn = 0;

    FullInfo* fullinfo;
    QVector<FullInfo*> fullinfo_ptr;

    ViewFile* viewfile;
    QVector<ViewFile*> viewfile_ptr;

    QString getFileIcon(QString path);

    void messBox(QString val);

    std::string transliterate(std::string original_string);
};

#endif // MAINWINDOW_H
