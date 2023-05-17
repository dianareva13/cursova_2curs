
#include "zipmanage.h"

ZipManage::ZipManage(int option, QObject* parent)
    : option(option)
    , QThread { parent }
{
}

void ZipManage::run()
{
    if (option == 1) {
        createArchive(this->selectProjFol, this->createPath);
    } else if (option == 2) {
        extractZip(this->selectProjFol2, this->extrPath);
    }
}

void ZipManage::extractZip(const char* selectProjFol, const char* openPath)
{
    //arch fun

    const int FILE_NAME_SIZE = 256;
    const int BUFFER_SIZE = 256;

    const char* archivePath = openPath;
    const char* directoryPath = selectProjFol;

    unzFile archive = unzOpen(archivePath);
    if (archive == NULL) {
        printf("Can't to open arch %s\n", archivePath);
        return;
    }

    unz_file_info file_info;
    char filename[FILE_NAME_SIZE];

    //---first iter
    int result = unzGoToFirstFile(archive);
    if (result != UNZ_OK) {
        return;
    }
    unzGetCurrentFileInfo(archive, &file_info, filename, sizeof(filename), NULL, 0, NULL, 0);
    unzOpenCurrentFile(archive);

    //set name for file
    string filePath = directoryPath;
    filePath += "/";
    for (int i = 0; i < FILE_NAME_SIZE; ++i) {
        if (filename[i] == '\0') {
            break;
        }
        filePath += filename[i];
    }

    if (filePath.find(".") != std::string::npos) {

        //create fol for file
        size_t last_slash_pos = filePath.find_last_of('/');
        string result_without_slash = filePath.substr(0, last_slash_pos);
        QDir().mkpath(QString::fromStdString(result_without_slash));

        char buffer0[BUFFER_SIZE];
        FILE* out_file0 = fopen(filePath.c_str(), "wb");
        int read_bytes0;
        do {
            read_bytes0 = unzReadCurrentFile(archive, buffer0, sizeof(buffer0));
            fwrite(buffer0, 1, read_bytes0, out_file0);
        } while (read_bytes0 > 0);

        unzCloseCurrentFile(archive);
        fclose(out_file0);
    } else {
        unzCloseCurrentFile(archive);
    }
    //---end first iter

    //---second iter
    do {
        result = unzGoToNextFile(archive);
        if (result != UNZ_OK) {
            break;
        }
        unzGetCurrentFileInfo(archive, &file_info, filename, sizeof(filename), NULL, 0, NULL, 0);

        //set name for file
        string filePath = directoryPath;
        filePath += "/";
        for (int i = 0; i < FILE_NAME_SIZE; ++i) {
            if (filename[i] == '\0') {
                break;
            }
            filePath += filename[i];
        }

        if (!(filePath.find(".") != std::string::npos)) {
            continue;
        }

        unzOpenCurrentFile(archive);

        //create fol for file
        size_t last_slash_pos = filePath.find_last_of('/');
        string result_without_slash = filePath.substr(0, last_slash_pos);
        QDir().mkpath(QString::fromStdString(result_without_slash));

        //write file
        char buffer[BUFFER_SIZE];
        FILE* out_file = fopen(filePath.c_str(), "wb");
        int read_bytes;
        do {
            read_bytes = unzReadCurrentFile(archive, buffer, sizeof(buffer));
            fwrite(buffer, 1, read_bytes, out_file);
        } while (read_bytes > 0);

        unzCloseCurrentFile(archive);
        fclose(out_file);
    } while (result == UNZ_OK);

    unzClose(archive);
    qDebug() << "end extract arch";
}

std::string ZipManage::transliterate(std::string original_string)
{
    std::string result_string = "";

    for (int i = 0; i < original_string.length(); i++) {
        if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += "a";
        } else if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += "b";
        } else if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += "v";
        } else if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += "g";
        } else if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += "d";
        } else if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += "ye";
        } else if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += "yo";
        } else if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += "zh";
        } else if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += "z";
        } else if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += "i";
        } else if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += "yi";
        } else if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += "k";
        } else if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += "l";
        } else if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += "m";
        } else if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += "n";
        } else if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += "o";
        } else if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += "p";
        } else if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += "r";
        } else if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += "s";
        } else if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += "t";
        } else if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += "u";
        } else if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += "f";
        } else if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += "h";
        } else if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += "ts";
        } else if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += "�h";
        } else if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += "sh";
        } else if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += "shch";
        } else if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += 'i';
        } else if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += 'i';
        } else if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += "ya";
        } else if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += "yu";
        } else if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += "ya";
        } else if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += 'e';
        } else if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += "ye";
        } else if (original_string[i] == '�' || original_string[i] == '�') {
            result_string += "yi";
        } else if (original_string[i] == '�' || original_string[i] == '�' || original_string[i] == '�' || original_string[i] == '�') {
            result_string += "";
        } else if (original_string[i] == '0' || original_string[i] == '1' || original_string[i] == '2' || original_string[i] == '3' || original_string[i] == '4' || original_string[i] == '5' || original_string[i] == '6' || original_string[i] == '7' || original_string[i] == '8' || original_string[i] == '9') {
            result_string += original_string[i];
        } else {
            result_string += original_string[i];
        }
    }

    return result_string;
}

void ZipManage::createArchive(const QString& folderPath, const QString& archivePath)
{
    QString zipFilePath = archivePath;
    if (QFile::exists(zipFilePath)) {
        QFile::remove(zipFilePath);
    }

    zipFile archive = zipOpen(QTextCodec::codecForName("CP1251")->fromUnicode(archivePath).data(), APPEND_STATUS_CREATE);

    traverseFolder(archive, folderPath);

    zipClose(archive, NULL);
    qDebug() << "end create arch";
}

void ZipManage::traverseFolder(zipFile& archive, const QString& path)
{
    QDir dir(path);
    QFileInfoList list = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries, QDir::DirsFirst);

    foreach (QFileInfo fileInfo, list) {
        if (fileInfo.isDir()) {
            traverseFolder(archive, fileInfo.absoluteFilePath());
        } else {
            qDebug() << fileInfo.absoluteFilePath();
            addFileToArchive(archive, QTextCodec::codecForName("CP1251")->fromUnicode(fileInfo.absoluteFilePath()).data(), "Diary_App");
        }
    }
}

void ZipManage::addFileToArchive(zipFile& archive, std::string path, std::string archSubFolder)
{

    QFileInfo fileInfo(QString::fromStdString(path));

    std::string str_path = (fileInfo.absolutePath()).toStdString();
    std::string search_str = archSubFolder;
    std::size_t pos = str_path.find(search_str);
    std::string archPath = "";
    if (pos != std::string::npos) {
        archPath = str_path.substr(pos);
    }

    std::string copy_path = path;
    std::size_t pos2 = copy_path.find_last_of("/\\");
    std::string filename = copy_path.substr(pos2 + 1);
    std::size_t dot_pos = filename.find_last_of(".");
    std::string name_without_extension = filename.substr(0, dot_pos);

    string archPathRes = archPath + "/" + transliterate(name_without_extension) + "." + (fileInfo.suffix()).toStdString();

    zip_fileinfo file_info = {};
    zipOpenNewFileInZip(archive, archPathRes.c_str(), &file_info, NULL, 0, NULL, 0, NULL, Z_DEFLATED, Z_DEFAULT_COMPRESSION);

    FILE* file = fopen(path.c_str(), "rb");
    if (!file) {
        zipClose(archive, NULL);
        return;
    }

    char buffer[1024];
    int size = 0;
    do {
        size = fread(buffer, 1, sizeof(buffer), file);
        zipWriteInFileInZip(archive, buffer, size);
    } while (size > 0);

    zipCloseFileInZip(archive);
    fclose(file);
}

void ZipManage::setCreatePath(QString whereSelectFol, QString whereSave)
{
    this->selectProjFol = whereSelectFol;
    this->createPath = whereSave;
}

void ZipManage::setExtrPath(const char* whereSelectFol, const char* archivePath)
{
    this->selectProjFol2 = whereSelectFol;
    this->extrPath = archivePath;
}
