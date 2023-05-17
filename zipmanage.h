
#ifndef ZIPMANAGE_H
#define ZIPMANAGE_H

#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QSharedPointer>
#include <QString>
#include <QTextCodec>
#include <QThread>
#include <QVBoxLayout>
#include <QVector>
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
#include <string>
#include <unzip.h>
#include <wchar.h>
#include <windows.h>
#include <zip.h>

using namespace std;

class ZipManage : public QThread {
public:
    explicit ZipManage(int option, QObject* parent = nullptr);

    int option;
    const char* extrPath;
    const char* selectProjFol2;
    QString createPath;
    QString selectProjFol;

    void setExtrPath(const char* whereSelectFol, const char* archivePath);
    void setCreatePath(QString whereSelectFol, QString whereSave);

    void run() override;

    void addFileToArchive(zipFile& archive, std::string path, std::string archSubFolder);
    std::string transliterate(std::string original_string);
    void createArchive(const QString& folderPath, const QString& archivePath);
    void traverseFolder(zipFile& archive, const QString& path);

    void extractZip(const char* selectProjFol, const char* openPath);
};

#endif // ZIPMANAGE_H
