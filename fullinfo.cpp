#include "fullinfo.h"
#include "ui_fullinfo.h"

FullInfo::FullInfo(QString date, QString lineEditText, QString textEditText, QLineEdit* lineEdit_ptr, QTextEdit* textEdit_ptr, QPushButton* saveBtn_ptr, QVector<QPushButton*> btnsLast, QWidget* parent)
    : ui(new Ui::FullInfo)
    , date(date)
    , lineEditText(lineEditText)
    , textEditText(textEditText)
    , lineEdit_ptr(lineEdit_ptr)
    , textEdit_ptr(textEdit_ptr)
    , saveBtn_ptr(saveBtn_ptr)
    , btnsLast(btnsLast)
    , QWidget(parent)
{
    ui->setupUi(this);

    QVector<QString> dateV;
    QVector<QString> titleV;
    QVector<QString> decriptionV;

    QVector<QString> file1;
    QVector<QString> file2;
    QVector<QString> file3;
    QVector<QString> file4;
    QVector<QString> file5;

    QSqlQuery query;
    query.prepare("SELECT * FROM diary_data WHERE date = :date");
    query.bindValue(":date", date);

    if (!query.exec()) {
        qWarning() << "ÐžÑˆÐ¸Ð±ÐºÐ° Ð²Ñ‹Ð¿Ð¾Ð»Ð½ÐµÐ½Ð¸Ñ Ð·Ð°Ð¿Ñ€Ð¾ÑÐ°:" << query.lastError().text();
    }

    while (query.next()) {
        QSqlRecord record = query.record();
        QString val1 = record.value("date").toString();
        QString val2 = record.value("title").toString();
        QString val3 = record.value("description").toString();
        QString val4 = record.value("file1").toString();
        QString val5 = record.value("file2").toString();
        QString val6 = record.value("file3").toString();
        QString val7 = record.value("file4").toString();
        QString val8 = record.value("file5").toString();

        dateV.push_back(val1);
        titleV.push_back(val2);
        decriptionV.push_back(val3);

        file1.push_back(val4);
        file2.push_back(val5);
        file3.push_back(val6);
        file4.push_back(val7);
        file5.push_back(val8);
    }

    ui->label->setText(date);

    if (titleV.size() >= 1) {
        ui->lineEdit->setText(titleV.front());
    } else {
        ui->lineEdit->setText("");
    }

    if (decriptionV.size() >= 1) {
        ui->textEdit->setText(decriptionV.front());
    } else {
        ui->textEdit->setText("");
    }

    //file btn
    QPushButton* cardFileBtn1 = ui->pushButton_3;
    QPushButton* cardFileBtn2 = ui->pushButton_4;
    QPushButton* cardFileBtn3 = ui->pushButton_5;
    QPushButton* cardFileBtn4 = ui->pushButton_6;
    QPushButton* cardFileBtn5 = ui->pushButton_7;

    QVector<QPushButton*> btns = { cardFileBtn1, cardFileBtn2, cardFileBtn3, cardFileBtn4, cardFileBtn5 };

    if (dateV.size() == 0) {
        for (int i = 1; i < btns.size(); ++i) {
            btns[i]->hide();
        }

        connect(btns[0], &QPushButton::clicked, this, [=]() {
            fileBtn_ect_checked_date(date, 1, btns);
        });
    } else if (file1.size() != 0 && file1.front() == "") {

        for (int i = 1; i < btns.size(); ++i) {
            btns[i]->hide();
        }

        connect(btns[0], &QPushButton::clicked, this, [=]() {
            fileBtn_ect(dateV.front(), 1, btns);
        });
    } else {

        if (dateV.size() != 0 && dateV.front() != "") {

            disconnect(btns[0], &QPushButton::clicked, 0, 0);

            int flag1[5] = { 0, 0, 0, 0, 0 };

            if (dateV.size() != 0 && dateV.front() != "") {
                if (file1.size() != 0 && file1.front() != "") {
                    flag1[0] = 1;
                    flag1[1] = 0;
                }

                if (file2.size() != 0 && file2.front() != "") {
                    flag1[1] = 1;
                    flag1[2] = 0;
                }

                if (file3.size() != 0 && file3.front() != "") {
                    flag1[2] = 1;
                    flag1[3] = 0;
                }

                if (file4.size() != 0 && file4.front() != "") {
                    flag1[3] = 1;
                    flag1[4] = 0;
                }

                if (file5.size() != 0 && file5.front() != "") {
                    flag1[4] = 1;
                }
            }

            int k = 1;

            for (int i = 0; i < 5; ++i) {

                if (i + k == 5) {
                    break;
                }

                if (flag1[i] && flag1[i + k] == false) {
                    flag1[i + k] = 2;
                    break;
                }
            }

            QVector<QString> filesVals = { file1.front(), file2.front(), file3.front(), file4.front(), file5.front() };

            for (int i = 0; i < 5; ++i) {

                if (flag1[i] == 2) {
                    connect(btns[i], &QPushButton::clicked, this, [=]() {
                        fileBtn_ect(dateV.front(), i + 1, btns);
                    });
                }
                if (flag1[i] == 1) {

                    QString ic;
                    if (i == 0) {
                        ic = getFileIcon(file1.front());
                    } else if (i == 1) {
                        ic = getFileIcon(file2.front());
                    } else if (i == 2) {
                        ic = getFileIcon(file3.front());
                    } else if (i == 3) {
                        ic = getFileIcon(file4.front());
                    } else if (i == 4) {
                        ic = getFileIcon(file5.front());
                    }

                    btns[i]->setIcon(QIcon(ic));

                    connect(btns[i], &QPushButton::clicked, this, [=]() {
                        openFile(filesVals[i]);
                    });

                } else if (flag1[i] == 0) {
                    btns[i]->hide();
                }
            }
        }
    }
}

FullInfo::~FullInfo()
{
    for (auto el : viewfile_ptr) {
        delete el;
    }

    delete ui;
}

void FullInfo::on_pushButton_clicked()
{
    if (lineEdit_ptr->text() == "") {
        if (ui->lineEdit->text() == "") {
            messBox("Please fill title!");
        } else {

            QSqlQuery query;
            query.prepare("INSERT INTO diary_data (date, title, description) VALUES (:date, :title, :description)");
            query.bindValue(":date", ui->label->text());
            query.bindValue(":title", ui->lineEdit->text());
            query.bindValue(":description", ui->textEdit->toPlainText());

            if (!query.exec()) {
                messBox("Error inserting data in db");
            }

            lineEditText = ui->lineEdit->text();
            textEditText = ui->textEdit->toPlainText();

            messBox("Data saved");

            lineEdit_ptr->setReadOnly(true);
            textEdit_ptr->setReadOnly(true);
            saveBtn_ptr->setEnabled(false);

            if (ui->lineEdit->text().size() <= 30) {
                lineEdit_ptr->setText(ui->lineEdit->text());
            } else {
                QString subStr = ui->lineEdit->text().left(30);
                lineEdit_ptr->setText(subStr + "...");
            }

            if (ui->textEdit->toPlainText().size() <= 280) {
                textEdit_ptr->setText(ui->textEdit->toPlainText());
            } else {
                QString subStr = ui->textEdit->toPlainText().left(280);
                textEdit_ptr->setText(subStr + "...");
            }
        }

    } else {
        if (ui->lineEdit->text() == "") {
            messBox("Please fill title!");
        } else {
            QSqlQuery query;
            query.prepare("UPDATE diary_data SET title = :title, description = :description WHERE date = :date");
            query.bindValue(":date", ui->label->text());
            query.bindValue(":title", ui->lineEdit->text());
            query.bindValue(":description", ui->textEdit->toPlainText());

            if (!query.exec()) {
                messBox("Error updating data in db");
            }

            messBox("Data saved");

            lineEdit_ptr->setReadOnly(true);
            textEdit_ptr->setReadOnly(true);
            saveBtn_ptr->setEnabled(false);

            if (ui->lineEdit->text().size() <= 30) {
                lineEdit_ptr->setText(ui->lineEdit->text());
            } else {
                QString subStr = ui->lineEdit->text().left(30);
                lineEdit_ptr->setText(subStr + "...");
            }

            if (ui->textEdit->toPlainText().size() <= 280) {
                textEdit_ptr->setText(ui->textEdit->toPlainText());
            } else {
                QString subStr = ui->textEdit->toPlainText().left(280);
                textEdit_ptr->setText(subStr + "...");
            }
        }
    }
}

void FullInfo::messBox(QString val)
{
    QMessageBox msgBox(QMessageBox::Information, "Info", val);
    msgBox.setStyleSheet("QMessageBox {background-color: white; color: black;}"
                         "QPushButton { padding-left: 10px; padding-right: 10px; padding-top: 3px; padding-bottom: 3px; background-color: white; border-radius: 3px; border: 1px solid  rgb(209, 207, 203);}"
                         "QPushButton:hover{background: #dedcd7;}");

    msgBox.exec();
}

void FullInfo::on_pushButton_2_clicked()
{
    QSqlQuery query;
    query.prepare("DELETE FROM diary_data WHERE date = :date");
    query.bindValue(":date", date);

    if (query.exec()) {
        messBox("Entry removed");
        ui->lineEdit->setText("");
        ui->textEdit->setText("");
        lineEdit_ptr->setText("");
        lineEdit_ptr->setReadOnly(false);
        textEdit_ptr->setText("");
        textEdit_ptr->setReadOnly(false);
        saveBtn_ptr->setEnabled(true);
    } else {
        messBox("Error: " + query.lastError().text());
    }
}

void FullInfo::fileBtn_ect(QString date, int btn_num, QVector<QPushButton*> btns)
{

    QPushButton* currBtn = (QPushButton*)sender();

    QString path;

    if (OS == 1) {
        path = QFileDialog::getOpenFileName(this, "Choose File", "C:/Users/" + qUsername + "/Desktop/");
    } else if (OS == 2) {
        path = QFileDialog::getOpenFileName(this, "Choose File", "/Users/" + qUsername + "/Desktop/");
    } else if (OS == 3) {
        path = QFileDialog::getOpenFileName(this, "Choose File", "/home/" + qUsername + "/Desktop/");
    }

    QFileInfo fileInfo(path);

    messBox("File attached");

    if (path != "") {

        QDir dirOfDates(DB_DIR_PATH + "/DATES/");
        if (!dirOfDates.exists(date)) {
            dirOfDates.mkdir(date);
        }

        //rewrite folder with file
        QDir folder(DB_DIR_PATH + "DATES/" + date + "/" + QString::number(btn_num));
        folder.removeRecursively();

        QDir folder1(DB_DIR_PATH + "DATES/" + date + "/");
        if (!folder1.exists("1")) {
            folder1.mkdir("1");
        }

        QDir folder2(DB_DIR_PATH + "DATES/" + date + "/");
        if (!folder2.exists("2")) {
            folder2.mkdir("2");
        }

        QDir folder3(DB_DIR_PATH + "DATES/" + date + "/");
        if (!folder3.exists("3")) {
            folder3.mkdir("3");
        }

        QDir folder4(DB_DIR_PATH + "DATES/" + date + "/");
        if (!folder4.exists("4")) {
            folder4.mkdir("4");
        }

        QDir folder5(DB_DIR_PATH + "DATES/" + date + "/");
        if (!folder5.exists("5")) {
            folder5.mkdir("5");
        }

        QString q_first_part = DB_DIR_PATH + "DATES/" + date + "/" + QString::number(btn_num) + "/";
        std::string first_part = QTextCodec::codecForName("CP1251")->fromUnicode(q_first_part).data();
        std::string second_part = QTextCodec::codecForName("CP1251")->fromUnicode(fileInfo.fileName()).data();
        std::string destin_std_translit = first_part + transliterate(second_part);
        QString destin_res = QString::fromStdString(destin_std_translit);

        qDebug() << destin_res;

        QFile::copy(path, destin_res);
        QFile::setPermissions(destin_res, QFile::WriteOwner | QFile::ReadOwner);

        QString ic;
        ic = getFileIcon(path);

        currBtn->setIcon(QIcon(ic));

        if (btn_num < 5) {
            btns[btn_num]->setVisible(true);
            btnsLast[btn_num]->setVisible(true);
        }

        btnsLast[btn_num - 1]->setIcon(QIcon(ic));
        disconnect(btnsLast[btn_num - 1], &QPushButton::clicked, 0, 0);
        connect(btnsLast[btn_num - 1], &QPushButton::clicked, this, [=]() {
            openFile(path);
        });

        QSqlQuery query2;
        query2.prepare("UPDATE diary_data SET " + QString("file%1").arg(btn_num) + "= :path WHERE date = :date");
        query2.bindValue(":path", destin_res);
        query2.bindValue(":date", date);

        if (!query2.exec()) {
            messBox("Error updating data in db");
        }

        disconnect(currBtn, &QPushButton::clicked, 0, 0);

        connect(currBtn, &QPushButton::clicked, this, [=]() {
            viewfile = new ViewFile(destin_res);
            viewfile_ptr.push_back(viewfile);
            viewfile->setWindowModality(Qt::ApplicationModal);
            viewfile->show();
        });

        if (btn_num < 5) {

            disconnect(btns[btn_num], &QPushButton::clicked, 0, 0);

            connect(btns[btn_num], &QPushButton::clicked, this, [=]() {
                fileBtn_ect(date, btn_num + 1, btns);
            });
        }
    }
}

void FullInfo::fileBtn_ect_checked_date(QString date, int btn_num, QVector<QPushButton*> btns)
{
    QVector<QString> dateV;
    QVector<QString> titleV;

    QSqlQuery query;
    query.prepare("SELECT * FROM diary_data WHERE date = :date");
    query.bindValue(":date", date);

    if (!query.exec()) {
        messBox("Error executin query: " + query.lastError().text());
    }

    while (query.next()) {
        QSqlRecord record = query.record();
        QString val1 = record.value("date").toString();
        QString val2 = record.value("title").toString();

        dateV.push_back(val1);
        titleV.push_back(val2);
    }

    if (titleV.size() != 0) {

        QPushButton* currBtn = (QPushButton*)sender();

        QString path;

        if (OS == 1) {
            path = QFileDialog::getOpenFileName(this, "Choose File", "C:/Users/" + qUsername + "/Desktop/");
        } else if (OS == 2) {
            path = QFileDialog::getOpenFileName(this, "Choose File", "/Users/" + qUsername + "/Desktop/");
        } else if (OS == 3) {
            path = QFileDialog::getOpenFileName(this, "Choose File", "/home/" + qUsername + "/Desktop/");
        }

        QFileInfo fileInfo(path);

        if (path != "") {
            messBox("File attached");

            QDir dirOfDates(DB_DIR_PATH + "/DATES/");
            if (!dirOfDates.exists(date)) {
                dirOfDates.mkdir(date);
            }

            //rewrite folder with file
            QDir folder(DB_DIR_PATH + "DATES/" + date + "/" + QString::number(btn_num));
            folder.removeRecursively();

            QDir folder1(DB_DIR_PATH + "DATES/" + date + "/");
            if (!folder1.exists("1")) {
                folder1.mkdir("1");
            }

            QDir folder2(DB_DIR_PATH + "DATES/" + date + "/");
            if (!folder2.exists("2")) {
                folder2.mkdir("2");
            }

            QDir folder3(DB_DIR_PATH + "DATES/" + date + "/");
            if (!folder3.exists("3")) {
                folder3.mkdir("3");
            }

            QDir folder4(DB_DIR_PATH + "DATES/" + date + "/");
            if (!folder4.exists("4")) {
                folder4.mkdir("4");
            }

            QDir folder5(DB_DIR_PATH + "DATES/" + date + "/");
            if (!folder5.exists("5")) {
                folder5.mkdir("5");
            }

            QString destin = DB_DIR_PATH + "DATES/" + date + "/" + QString::number(btn_num) + "/" + fileInfo.fileName();

            QFile::copy(path, destin);
            QFile::setPermissions(destin, QFile::WriteOwner | QFile::ReadOwner);

            QString ic = getFileIcon(path);

            currBtn->setIcon(QIcon(ic));

            if (btn_num < 5) {
                btns[btn_num]->setVisible(true);
                btnsLast[btn_num]->setVisible(true);
            }

            btnsLast[btn_num - 1]->setIcon(QIcon(ic));
            disconnect(btnsLast[btn_num - 1], &QPushButton::clicked, 0, 0);
            connect(btnsLast[btn_num - 1], &QPushButton::clicked, this, [=]() {
                openFile(path);
            });

            QSqlQuery query2;
            query2.prepare("UPDATE diary_data SET " + QString("file%1").arg(btn_num) + "= :path WHERE date = :date");
            query2.bindValue(":path", destin);
            query2.bindValue(":date", date);

            if (!query2.exec()) {
                messBox("Error updating data in db");
            }

            disconnect(currBtn, &QPushButton::clicked, 0, 0);

            connect(currBtn, &QPushButton::clicked, this, [=]() {
                viewfile = new ViewFile(destin);
                viewfile_ptr.push_back(viewfile);
                viewfile->setWindowModality(Qt::ApplicationModal);
                viewfile->show();
            });

            if (btn_num < 5) {

                disconnect(btns[btn_num], &QPushButton::clicked, 0, 0);

                connect(btns[btn_num], &QPushButton::clicked, this, [=]() {
                    fileBtn_ect(date, btn_num + 1, btns);
                });
            }
        }

    } else {
        messBox("Fill and save title");
    }
}

void FullInfo::openFile(QString path)
{
    viewfile = new ViewFile(path);
    viewfile_ptr.push_back(viewfile);
    viewfile->setWindowModality(Qt::ApplicationModal);
    viewfile->show();
}

QString FullInfo::getFileIcon(QString path)
{
    QString res;

    QFileInfo fileInfo(path);

    if (fileInfo.suffix() == "docx") {
        res = ":/my/ic/11.png";
    } else if (fileInfo.suffix() == "xlsx") {
        res = ":/my/ic/12.png";
    } else if (fileInfo.suffix() == "pdf") {
        res = ":/my/ic/16.png";
    } else if (fileInfo.suffix() == "jpg") {
        res = ":/my/ic/15.png";
    } else if (fileInfo.suffix() == "png") {
        res = ":/my/ic/17.png";
    } else if (fileInfo.suffix() == "txt") {
        res = ":/my/ic/18.png";
    } else {
        res = ":/my/ic/13.png";
    }

    return res;
}

std::string FullInfo::transliterate(std::string original_string)
{
    std::string result_string = "";

    for (int i = 0; i < original_string.length(); i++) {
        if (original_string[i] == 'À' || original_string[i] == 'à') {
            result_string += "a";
        } else if (original_string[i] == 'Á' || original_string[i] == 'á') {
            result_string += "b";
        } else if (original_string[i] == 'Â' || original_string[i] == 'â') {
            result_string += "v";
        } else if (original_string[i] == 'Ã' || original_string[i] == 'ã') {
            result_string += "g";
        } else if (original_string[i] == 'Ä' || original_string[i] == 'ä') {
            result_string += "d";
        } else if (original_string[i] == 'Å' || original_string[i] == 'å') {
            result_string += "ye";
        } else if (original_string[i] == '¨' || original_string[i] == '¸') {
            result_string += "yo";
        } else if (original_string[i] == 'Æ' || original_string[i] == 'æ') {
            result_string += "zh";
        } else if (original_string[i] == 'Ç' || original_string[i] == 'ç') {
            result_string += "z";
        } else if (original_string[i] == 'È' || original_string[i] == 'è') {
            result_string += "i";
        } else if (original_string[i] == 'É' || original_string[i] == 'é') {
            result_string += "yi";
        } else if (original_string[i] == 'Ê' || original_string[i] == 'ê') {
            result_string += "k";
        } else if (original_string[i] == 'Ë' || original_string[i] == 'ë') {
            result_string += "l";
        } else if (original_string[i] == 'Ì' || original_string[i] == 'ì') {
            result_string += "m";
        } else if (original_string[i] == 'Í' || original_string[i] == 'í') {
            result_string += "n";
        } else if (original_string[i] == 'Î' || original_string[i] == 'î') {
            result_string += "o";
        } else if (original_string[i] == 'Ï' || original_string[i] == 'ï') {
            result_string += "p";
        } else if (original_string[i] == 'Ð' || original_string[i] == 'ð') {
            result_string += "r";
        } else if (original_string[i] == 'Ñ' || original_string[i] == 'ñ') {
            result_string += "s";
        } else if (original_string[i] == 'Ò' || original_string[i] == 'ò') {
            result_string += "t";
        } else if (original_string[i] == 'Ó' || original_string[i] == 'ó') {
            result_string += "u";
        } else if (original_string[i] == 'Ô' || original_string[i] == 'ô') {
            result_string += "f";
        } else if (original_string[i] == 'Õ' || original_string[i] == 'õ') {
            result_string += "h";
        } else if (original_string[i] == 'Ö' || original_string[i] == 'ö') {
            result_string += "ts";
        } else if (original_string[i] == '×' || original_string[i] == '÷') {
            result_string += "ñh";
        } else if (original_string[i] == 'Ø' || original_string[i] == 'ø') {
            result_string += "sh";
        } else if (original_string[i] == 'Ù' || original_string[i] == 'ù') {
            result_string += "shch";
        } else if (original_string[i] == '²' || original_string[i] == '³') {
            result_string += 'i';
        } else if (original_string[i] == 'Û' || original_string[i] == 'û') {
            result_string += 'i';
        } else if (original_string[i] == 'ß' || original_string[i] == 'ÿ') {
            result_string += "ya";
        } else if (original_string[i] == 'Þ' || original_string[i] == 'þ') {
            result_string += "yu";
        } else if (original_string[i] == 'ß' || original_string[i] == 'ÿ') {
            result_string += "ya";
        } else if (original_string[i] == 'Ý' || original_string[i] == 'ý') {
            result_string += 'e';
        } else if (original_string[i] == 'ª' || original_string[i] == 'º') {
            result_string += "ye";
        } else if (original_string[i] == '¯' || original_string[i] == '¿') {
            result_string += "yi";
        } else if (original_string[i] == 'ü' || original_string[i] == 'ú' || original_string[i] == 'Ü' || original_string[i] == 'Ú') {
            result_string += "";
        } else if (original_string[i] == '0' || original_string[i] == '1' || original_string[i] == '2' || original_string[i] == '3' || original_string[i] == '4' || original_string[i] == '5' || original_string[i] == '6' || original_string[i] == '7' || original_string[i] == '8' || original_string[i] == '9') {
            result_string += original_string[i];
        } else {
            result_string += original_string[i];
        }
    }

    return result_string;
}
