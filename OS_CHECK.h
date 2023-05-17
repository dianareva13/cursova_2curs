#ifndef OS_CHECK_H
#define OS_CHECK_H

#include <QString>

const QString DATA_FOLDER_NAME = "Diary_App";
const QString DB_NAME = "diary2.db";
const QString DB_SOURCE = ":/mydb/" + DB_NAME;

#if defined(Q_OS_WIN)
#define qUsername QString::fromLocal8Bit(qgetenv("USERNAME").constData()).toUtf8()
#elif defined(Q_OS_UNIX)
#define qUsername qgetenv("USER").constData()
#endif

#ifdef Q_OS_WIN
#define OS 1
const QString DIR_PATH = "C:/Users/" + qUsername + "/AppData/Roaming/";
const QString DB_DIR_PATH = "C:/Users/" + qUsername + "/AppData/Roaming/" + DATA_FOLDER_NAME + "/";
const QString DESTIN = "C:/Users/" + qUsername + "/AppData/Roaming/" + DATA_FOLDER_NAME + "/DB/" + DB_NAME;
const QString DIR_PATH_NO_LAST_SLASH = "C:/Users/" + qUsername + "/AppData/Roaming/" + DATA_FOLDER_NAME;
const QString ROAMING_DIR_PATH_NO_LAST_SLASH = "C:/Users/" + qUsername + "/AppData/Roaming";

#endif

#ifdef Q_OS_MAC
#define OS 2
QString DIR_PATH = "/Users/" + qUsername + "/Library/Application Support/";
QString DB_DIR_PATH = "/Users/" + qUsername + "/Library/Application Support/" + DATA_FOLDER_NAME + "/";
QString DESTIN = "/Users/" + qUsername + "/Library/Application Support/" + DATA_FOLDER_NAME + "/DB/" + DB_NAME;
#endif

#ifdef Q_OS_LINUX
#define OS 3
QString DIR_PATH = "/home/" + qUsername + "/.local/share/";
QString DB_DIR_PATH = "/home/" + qUsername + "/.local/share/" + DATA_FOLDER_NAME + "/";
QString DESTIN = "/home/" + qUsername + "/.local/share/" + DATA_FOLDER_NAME + "/DB/" + DB_NAME;
#endif

#endif // OS_CHECK_H
