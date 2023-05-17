#include "OS_CHECK.h"
#include "mainwindow.h"
#include "shlwapi.h"
#include "windows.h"
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QLocale>
#include <QProgressBar>
#include <QSplashScreen>
#include <QString>
#include <QSysInfo>
#include <QTextCodec>
#include <wchar.h>
#include <zip.h>

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    QApplication a(argc, argv);

    QApplication::setWindowIcon(QIcon(":/my/ic/main.png"));

    QLocale::setDefault(QLocale(QLocale::Russian, QLocale::RussianFederation));
    a.setWindowIcon(QIcon(":/my/ic/main.png"));

    //db move
    QDir dir(DIR_PATH);

    if (!dir.exists(DATA_FOLDER_NAME)) {
        dir.mkdir(DATA_FOLDER_NAME);
    }

    QDir dirOfDb(DB_DIR_PATH);

    if (!dirOfDb.exists("DB")) {
        dirOfDb.mkdir("DB");
    }

    QDir dirOfDates(DB_DIR_PATH);

    if (!dirOfDates.exists("DATES")) {
        dirOfDates.mkdir("DATES");
    }

    if (!QFile(DB_SOURCE).exists()) {
        qWarning("The sourrse doesnt exist");
        return 1;
    }

    QFile::copy(DB_SOURCE, DESTIN);
    QFile::setPermissions(DESTIN, QFile::WriteOwner | QFile::ReadOwner);

    //load screen
    QSplashScreen* splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/my/ic/wallpaper2.jpg"));

    splash->show();

    QTimer::singleShot(10, splash, &QSplashScreen::close);

    MainWindow w;

    QTimer::singleShot(10, &w, &MainWindow::showMaximized);

    return a.exec();
}
