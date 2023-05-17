#include "mainwindow.h"
#include "fullinfo.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //db
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DESTIN);

    if (db.open()) {
        qDebug() << "Succ conn to db: " << db.databaseName();
    } else {
        messBox("Error conn to db: " + db.lastError().databaseText());
    }

    //date
    stackedIdx = 0;
    std::chrono::system_clock::time_point currDate = std::chrono::system_clock::now();
    std::time_t current_time2 = std::chrono::system_clock::to_time_t(currDate);

    QVector<QString> tempDate = rangeOfDate(currDate, 27, 30);
    QVector<QVector<QString>> res = castDate(tempDate);

    firstDate = res.front().front();
    lastDate = res.back().back();

    QString currDateQString = dateToString(currDate);

    //find StackedWidget idx
    for (int i = 0; i < res.size(); ++i) {
        for (int k = 0; k < res[i].size(); ++k) {
            QString oneBlockDate = res[i][k];
            if (oneBlockDate == currDateQString) {
                stackedIdx = i;
                break;
            }
        }
    }
    //end date

    stackedWidget = new QStackedWidget();

    for (int i = 0; i < res.size(); ++i) {
        genPage(res[i]);

        stackedWidget->addWidget(page1);
    }

    mainVLayout = new QVBoxLayout();
    mainVLayout->addStretch();

    stackedWidget->setCurrentIndex(stackedIdx);
    idPage = stackedIdx;

    mainVLayout->addWidget(stackedWidget);
    mainVLayout->addStretch();

    ui->widgetMain->setLayout(mainVLayout);

    updateDbData();

    zoomIdx = 5;

    ctrlPress = false;
}

MainWindow::~MainWindow()
{

    clearFu();

    delete ui;
    db.close();
}

void MainWindow::on_pushButton_clicked()
{
    int option = 1;

    if (option == 0) {
        withoutAnim(1);
    } else if (option == 1) {
        appearAnim(1);
    } else if (option == 2) {
        sweapAnim(1);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    int option = 1;

    if (option == 0) {
        withoutAnim(0);
    } else if (option == 1) {
        appearAnim(0);
    } else if (option == 2) {
        sweapAnim(0);
    }
}

void MainWindow::genNewCard(QString val)
{
    QVector<QString> date;
    QVector<QString> title;
    QVector<QString> decription;
    QVector<QString> file1;
    QVector<QString> file2;
    QVector<QString> file3;
    QVector<QString> file4;
    QVector<QString> file5;

    QSqlQuery query;
    query.prepare("SELECT * FROM diary_data WHERE date=:date");
    query.bindValue(":date", val.chopped(1));

    if (!query.exec()) {
        qWarning() << "–†—õ–°‚Ç¨–†—ë–†¬±–†—î–†¬∞ –†–Ü–°‚Äπ–†—ó–†—ï–†¬ª–†–Ö–†¬µ–†–Ö–†—ë–°–è –†¬∑–†¬∞–†—ó–°–Ç–†—ï–°–É–†¬∞:" << query.lastError().text();
        db.close();
        return;
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

        date.push_back(val1);
        title.push_back(val2);
        decription.push_back(val3);
        file1.push_back(val4);
        file2.push_back(val5);
        file3.push_back(val6);
        file4.push_back(val7);
        file5.push_back(val8);
    }

    cardVLayout = new QVBoxLayout();
    cardVLayout_ptr.push_back(cardVLayout);

    QString val2 = val;
    // QString chc = val2.left(val2.length() - 5);

    cardLabel = new QLabel(val2);
    cardLabel_ptr.push_back(cardLabel);
    cardLabel->setStyleSheet("border: 1px solid  white;");
    cardLabel->setMaximumHeight(20);
    cardLabel->setAlignment(Qt::AlignHCenter);

    cardFileHLayout = new QHBoxLayout();
    cardFileHLayout_ptr.push_back(cardFileHLayout);

    cardFileBtn1 = new QPushButton();
    cardFileBtn1_ptr.push_back(cardFileBtn1);
    cardFileBtn1->setCursor(Qt::PointingHandCursor);
    cardFileBtn1->setIcon(QIcon(":/my/ic/6.png"));
    cardFileBtn1->setStyleSheet(":hover{background: #dedcd7;} QPushButton{border: 1px solid white}");
    cardFileBtn1->setMaximumWidth(18);

    cardFileBtn2 = new QPushButton();
    cardFileBtn2_ptr.push_back(cardFileBtn2);
    cardFileBtn2->setCursor(Qt::PointingHandCursor);
    cardFileBtn2->setIcon(QIcon(":/my/ic/6.png"));
    cardFileBtn2->setStyleSheet(":hover{background: #dedcd7;} QPushButton{border: 1px solid white}");
    cardFileBtn2->setMaximumWidth(18);

    cardFileBtn3 = new QPushButton();
    cardFileBtn3_ptr.push_back(cardFileBtn3);
    cardFileBtn3->setCursor(Qt::PointingHandCursor);
    cardFileBtn3->setIcon(QIcon(":/my/ic/6.png"));
    cardFileBtn3->setStyleSheet(":hover{background: #dedcd7;} QPushButton{border: 1px solid white}");
    cardFileBtn3->setMaximumWidth(18);

    cardFileBtn4 = new QPushButton();
    cardFileBtn4_ptr.push_back(cardFileBtn4);
    cardFileBtn4->setCursor(Qt::PointingHandCursor);
    cardFileBtn4->setIcon(QIcon(":/my/ic/6.png"));
    cardFileBtn4->setStyleSheet(":hover{background: #dedcd7;} QPushButton{border: 1px solid white}");
    cardFileBtn4->setMaximumWidth(18);

    cardFileBtn5 = new QPushButton();
    cardFileBtn5_ptr.push_back(cardFileBtn5);
    cardFileBtn5->setCursor(Qt::PointingHandCursor);
    cardFileBtn5->setIcon(QIcon(":/my/ic/6.png"));
    cardFileBtn5->setStyleSheet(":hover{background: #dedcd7;} QPushButton{border: 1px solid white}");
    cardFileBtn5->setMaximumWidth(18);

    QVector<QPushButton*> btns = { cardFileBtn1, cardFileBtn2, cardFileBtn3, cardFileBtn4, cardFileBtn5 };

    if (file1.size() >= 1 && file1.front() != "") {

        QString ic = getFileIcon(file1.front());

        cardFileBtn1->setIcon(QIcon(ic));

        connect(cardFileBtn1, &QPushButton::clicked, this, [=]() {
            viewfile = new ViewFile(file1.front());
            viewfile_ptr.push_back(viewfile);
            viewfile->setWindowModality(Qt::ApplicationModal);
            viewfile->show();
        });
    } else {
        connect(cardFileBtn1, &QPushButton::clicked, this, [=]() {
            fileBtn_ect(val, 1, btns);
        });

        cardFileBtn2->hide();
    }

    if (file2.size() >= 1 && file2.front() != "") {
        QString ic = getFileIcon(file2.front());

        cardFileBtn2->setIcon(QIcon(ic));

        connect(cardFileBtn2, &QPushButton::clicked, this, [=]() {
            viewfile = new ViewFile(file2.front());
            viewfile_ptr.push_back(viewfile);
            viewfile->setWindowModality(Qt::ApplicationModal);
            viewfile->show();
        });
    } else {
        connect(cardFileBtn2, &QPushButton::clicked, this, [=]() {
            fileBtn_ect(val, 2, btns);
        });

        cardFileBtn3->hide();
    }

    if (file3.size() >= 1 && file3.front() != "") {
        QString ic = getFileIcon(file3.front());

        cardFileBtn3->setIcon(QIcon(ic));

        connect(cardFileBtn3, &QPushButton::clicked, this, [=]() {
            viewfile = new ViewFile(file3.front());
            viewfile_ptr.push_back(viewfile);
            viewfile->setWindowModality(Qt::ApplicationModal);
            viewfile->show();
        });
    } else {
        connect(cardFileBtn3, &QPushButton::clicked, this, [=]() {
            fileBtn_ect(val, 3, btns);
        });

        cardFileBtn4->hide();
    }

    if (file4.size() >= 1 && file4.front() != "") {
        QString ic = getFileIcon(file4.front());

        cardFileBtn4->setIcon(QIcon(ic));

        connect(cardFileBtn4, &QPushButton::clicked, this, [=]() {
            viewfile = new ViewFile(file4.front());
            viewfile_ptr.push_back(viewfile);
            viewfile->setWindowModality(Qt::ApplicationModal);
            viewfile->show();
        });
    } else {
        connect(cardFileBtn4, &QPushButton::clicked, this, [=]() {
            fileBtn_ect(val, 4, btns);
        });

        cardFileBtn5->hide();
    }

    if (file5.size() >= 1 && file5.front() != "") {
        QString ic = getFileIcon(file5.front());

        cardFileBtn5->setIcon(QIcon(ic));

        connect(cardFileBtn5, &QPushButton::clicked, this, [=]() {
            viewfile = new ViewFile(file5.front());
            viewfile_ptr.push_back(viewfile);
            viewfile->setWindowModality(Qt::ApplicationModal);
            viewfile->show();
        });
    } else {

        connect(cardFileBtn5, &QPushButton::clicked, this, [=]() {
            fileBtn_ect(val, 5, btns);
        });
    }

    cardFileHLayout->addWidget(cardFileBtn1);
    cardFileHLayout->addWidget(cardFileBtn2);
    cardFileHLayout->addWidget(cardFileBtn3);
    cardFileHLayout->addWidget(cardFileBtn4);
    cardFileHLayout->addWidget(cardFileBtn5);
    cardFileHLayout->addStretch();

    cardLineEdit = new QLineEdit();
    cardLineEdit_ptr.push_back(cardLineEdit);
    cardLineEdit->setMinimumHeight(20);
    cardTextEdit = new QTextEdit();
    cardTextEdit_ptr.push_back(cardTextEdit);

    QScrollBar* verticalScrollBar = cardTextEdit->verticalScrollBar();

    verticalScrollBar->setStyleSheet(
        "QScrollBar:vertical {"
        "    background-color: white;"
        "    width: 10px;"
        "}");

    cardDownBtnHLayout = new QHBoxLayout();
    cardDownBtnHLayout_ptr.push_back(cardDownBtnHLayout);

    cardBtn = new QPushButton();
    cardBtn_ptr.push_back(cardBtn);
    cardBtn->setCursor(Qt::PointingHandCursor);
    cardBtn->setStyleSheet("QPushButton{border: 2px solid white} QPushButton:hover{background: #dedcd7;}");
    cardBtn->setIcon(QIcon(":/my/ic/8.png"));
    cardBtn->setMaximumWidth(18);

    cardBtn2 = new QPushButton();
    cardBtn2_ptr.push_back(cardBtn2);
    cardBtn2->setCursor(Qt::PointingHandCursor);
    cardBtn2->setStyleSheet("QPushButton{border: 2px solid white} QPushButton:hover{background: #dedcd7;}");
    cardBtn2->setIcon(QIcon(":/my/ic/10.png"));
    cardBtn2->setMaximumWidth(18);

    cardDownBtnHLayout->addWidget(cardBtn);
    cardDownBtnHLayout->addWidget(cardBtn2);
    cardDownBtnHLayout->addStretch();

    //fill card lay
    cardVLayout->addWidget(cardLabel);
    cardVLayout->addLayout(cardFileHLayout);
    cardVLayout->addWidget(cardLineEdit);
    cardVLayout->addWidget(cardTextEdit);
    cardVLayout->addLayout(cardDownBtnHLayout);

    cardW = new QWidget();
    cardW_ptr.push_back(cardW);
    cardW->setStyleSheet("QWidget{background-color: white; border-radius: 3px; border: 1px solid  rgb(209, 207, 203); width: 15%; height: 15%;}");
    cardW->setLayout(cardVLayout);
}

void MainWindow::genEmptyNewCard()
{
    cardW = new QWidget();
    cardW_ptr.push_back(cardW);
    cardW->setMaximumHeight(270);
    cardW->setMaximumWidth(220);
    cardW->setMinimumHeight(270);
    cardW->setMinimumWidth(220);
    cardW->setStyleSheet("background-color: green;");
}

void MainWindow::genPage(QVector<QString> val)
{

    QString lstDate = (val.back()).mid(11, 4);

    page1 = new QWidget();
    page1_ptr.push_back(page1);
    lay1 = new QVBoxLayout();
    lay1_ptr.push_back(lay1);
    lay1->setSpacing(10);

    mainYearLabel = new QLabel(lstDate);
    mainYearLabel_ptr.push_back(mainYearLabel);
    mainYearLabel->setMaximumHeight(30);
    mainYearLabel->setStyleSheet("font-size: 14px; padding-bottom: 10px; font-weight: 600;");
    mainYearLabel->setAlignment(Qt::AlignHCenter);

    //right halflayout
    cardPromizhHLayout = new QHBoxLayout();
    cardPromizhHLayout_ptr.push_back(cardPromizhHLayout);
    cardPromizhHLayout->addStretch();

    cardPromizhHLayout->setSpacing(10);

    genNewCard(val[0]);
    cardPromizhHLayout->addWidget(cardW);
    genNewCard(val[1]);
    cardPromizhHLayout->addWidget(cardW);
    genNewCard(val[2]);
    cardPromizhHLayout->addWidget(cardW);
    genNewCard(val[3]);
    cardPromizhHLayout->addWidget(cardW);

    cardPromizhHLayout->addStretch();

    //second halflayout

    cardPromizhHLayout2 = new QHBoxLayout();
    cardPromizhHLayout2_ptr.push_back(cardPromizhHLayout2);
    cardPromizhHLayout2->addStretch();

    cardPromizhHLayout2->setSpacing(10);

    genNewCard(val[4]);
    cardPromizhHLayout2->addWidget(cardW);
    genNewCard(val[5]);
    cardPromizhHLayout2->addWidget(cardW);
    genNewCard(val[6]);
    cardPromizhHLayout2->addWidget(cardW);
    //genEmptyNewCard();
    //cardPromizhHLayout2->addWidget(cardW);

    cardPromizhHLayout2->addStretch();

    lay1->addWidget(mainYearLabel);
    lay1->addStretch();
    lay1->addLayout(cardPromizhHLayout);
    lay1->addLayout(cardPromizhHLayout2);

    page1->setLayout(lay1);
}

QVector<QString> MainWindow::rangeOfDate(std::chrono::system_clock::time_point currDate, int daysRangeL, int daysRangeR)
{
    std::time_t current_time = std::chrono::system_clock::to_time_t(currDate);
    std::tm* tm_now_local = std::localtime(&current_time);

    tm_now_local->tm_sec = 0;
    tm_now_local->tm_min = 0;
    tm_now_local->tm_hour = 12;

    QVector<QString> range_dates;

    std::time_t zero_time_local_tem = std::mktime(tm_now_local);
    QString str_dates_tem = std::ctime(&zero_time_local_tem);
    str_dates_tem.remove(10, 9);

    range_dates.emplace_back(str_dates_tem);

    for (int i = 0; i < daysRangeR; ++i) {
        tm_now_local->tm_hour += 24;
        std::time_t zero_time_local = std::mktime(tm_now_local);
        QString str_dates = std::ctime(&zero_time_local);
        str_dates.remove(10, 9);

        range_dates.emplace_back(str_dates);
    }

    current_time = std::chrono::system_clock::to_time_t(currDate);
    tm_now_local = std::localtime(&current_time);
    tm_now_local->tm_sec = 0;
    tm_now_local->tm_min = 0;
    tm_now_local->tm_hour = 12;

    for (int i = 0; i < daysRangeL; ++i) {
        tm_now_local->tm_hour -= 24;
        std::time_t zero_time_local = std::mktime(tm_now_local);
        QString str_dates = std::ctime(&zero_time_local);
        str_dates.remove(10, 9);

        range_dates.emplace(range_dates.begin(), str_dates);
    }

    return range_dates;
}

QVector<QVector<QString>> MainWindow::castDate(QVector<QString> vec)
{
    QVector<QVector<QString>> res;
    QVector<QString> temp;
    QString eq[] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };
    int k = 0;

    for (int i = 0; i < vec.size(); ++i) {

        if (k == 7) {
            k = 0;
            res.push_back(temp);
            temp.clear();
        }

        QString sub = vec[i].mid(0, 3);

        if (sub == eq[k]) {
            temp.push_back(vec[i]);
            k++;
        }
    }

    return res;
}

QString MainWindow::dateToString(std::chrono::system_clock::time_point currDate)
{
    std::time_t current_time = std::chrono::system_clock::to_time_t(currDate);
    QString res = (std::ctime(&current_time));
    res.remove(10, 9);
    return res;
}

void MainWindow::clearFu()
{

    for (auto el : fullinfo_ptr) {
        delete el;
    }

    for (auto el : viewfile_ptr) {
        delete el;
    }

    for (auto el : cardBtn_ptr) {
        el->deleteLater();
    }

    for (auto el : cardBtn2_ptr) {
        el->deleteLater();
    }

    for (auto el : cardDownBtnHLayout_ptr) {
        el->deleteLater();
    }

    for (auto el : cardTextEdit_ptr) {
        el->deleteLater();
    }

    for (auto el : cardLineEdit_ptr) {
        el->deleteLater();
    }

    for (auto el : cardLabel_ptr) {
        el->deleteLater();
    }

    for (auto el : cardFileBtn1_ptr) {
        el->deleteLater();
    }

    for (auto el : cardFileBtn2_ptr) {
        el->deleteLater();
    }

    for (auto el : cardFileBtn3_ptr) {
        el->deleteLater();
    }

    for (auto el : cardFileBtn4_ptr) {
        el->deleteLater();
    }

    for (auto el : cardFileBtn5_ptr) {
        el->deleteLater();
    }

    for (auto el : cardFileHLayout_ptr) {
        el->deleteLater();
    }

    for (auto el : cardVLayout_ptr) {
        el->deleteLater();
    }

    for (auto el : cardW_ptr) {
        el->deleteLater();
    }

    for (auto el : cardPromizhHLayout2_ptr) {
        el->deleteLater();
    }

    for (auto el : cardPromizhHLayout_ptr) {
        el->deleteLater();
    }

    for (auto el : mainYearLabel_ptr) {
        el->deleteLater();
    }

    for (auto el : lay1_ptr) {
        el->deleteLater();
    }

    for (auto el : page1_ptr) {
        el->deleteLater();
    }

    stackedWidget->deleteLater();
    mainVLayout->deleteLater();
}

void MainWindow::sweapAnim(int button)
{
    if (button == 0) {
        QPropertyAnimation* animation2 = new QPropertyAnimation(stackedWidget, "geometry");
        animation2->setStartValue(QRect(stackedWidget->x(), stackedWidget->y(), stackedWidget->width(), stackedWidget->height()));

        animation2->setDuration(1000);
        animation2->setEasingCurve(QEasingCurve::Linear);
        animation2->setEndValue(QRect(stackedWidget->x(), stackedWidget->y(), stackedWidget->width(), stackedWidget->height()));
        animation2->start(QAbstractAnimation::DeleteWhenStopped);

        animation2->setKeyValueAt(0.45, QRect(stackedWidget->x() + stackedWidget->width() * 2, stackedWidget->y(), stackedWidget->width(), stackedWidget->height()));
        animation2->setKeyValueAt(0.50, QRect(stackedWidget->x() + stackedWidget->width() * 2, stackedWidget->y() - stackedWidget->height() * 2, stackedWidget->width(), stackedWidget->height()));
        animation2->setKeyValueAt(0.55, QRect(stackedWidget->x() - stackedWidget->width() * 4, stackedWidget->y() - stackedWidget->height() * 2, stackedWidget->width(), stackedWidget->height()));
        animation2->setKeyValueAt(0.65, QRect(stackedWidget->x() - stackedWidget->width() * 4, stackedWidget->y(), stackedWidget->width(), stackedWidget->height()));

        connect(animation2, &QPropertyAnimation::finished, [&]() {
            leftChanger();
        });

    } else if (button == 1) {
        QPropertyAnimation* animation2 = new QPropertyAnimation(stackedWidget, "geometry");
        animation2->setStartValue(QRect(stackedWidget->x(), stackedWidget->y(), stackedWidget->width(), stackedWidget->height()));

        animation2->setDuration(1000);
        animation2->setEasingCurve(QEasingCurve::Linear);
        animation2->setEndValue(QRect(stackedWidget->x(), stackedWidget->y(), stackedWidget->width(), stackedWidget->height()));
        animation2->start(QAbstractAnimation::DeleteWhenStopped);

        animation2->setKeyValueAt(0.45, QRect(-1 * (stackedWidget->x() + stackedWidget->width() * 2), stackedWidget->y(), stackedWidget->width(), stackedWidget->height()));
        animation2->setKeyValueAt(0.50, QRect(-1 * (stackedWidget->x() + stackedWidget->width() * 2), stackedWidget->y() - stackedWidget->height() * 2, stackedWidget->width(), stackedWidget->height()));
        animation2->setKeyValueAt(0.55, QRect(-1 * (stackedWidget->x() - stackedWidget->width() * 4), stackedWidget->y() - stackedWidget->height() * 2, stackedWidget->width(), stackedWidget->height()));
        animation2->setKeyValueAt(0.65, QRect(-1 * (stackedWidget->x() - stackedWidget->width() * 4), stackedWidget->y(), stackedWidget->width(), stackedWidget->height()));

        connect(animation2, &QPropertyAnimation::finished, [&]() {
            rightChanger();
        });
    }
}

void MainWindow::appearAnim(int button)
{

    QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect();
    opacityEffect->setOpacity(0.0);
    stackedWidget->setGraphicsEffect(opacityEffect);

    QPropertyAnimation* animation = new QPropertyAnimation(opacityEffect, "opacity");
    animation->setDuration(200);
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->setEndValue(1.0);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    if (button == 0) {

        leftChanger();
    } else if (button == 1) {
        rightChanger();
    }

    updateDbData();
}

void MainWindow::leftChanger()
{
    idPage--;
    if (idPage < 0) {
        idPage = 0;
        std::chrono::system_clock::time_point fstDate = qstring_to_time_point(firstDate);
        QVector<QString> additVec = rangeOfDate(fstDate, 10, 0);
        QVector<QVector<QString>> matrixDate = castDate(additVec);

        firstDate = matrixDate.front().front();

        for (int i = 0; i < matrixDate.size(); ++i) {
            genPage(matrixDate[i]);
            stackedWidget->insertWidget(0, page1);
        }

        additVec.clear();
        matrixDate.clear();
    }
    stackedWidget->setCurrentIndex(idPage);
}

void MainWindow::rightChanger()
{

    idPage++;
    if (idPage > stackedWidget->count() - 1) {

        std::chrono::system_clock::time_point lstDate = qstring_to_time_point(lastDate);
        QVector<QString> additVec = rangeOfDate(lstDate, 0, 10);
        QVector<QVector<QString>> matrixDate = castDate(additVec);
        lastDate = matrixDate.back().back();

        for (int i = 0; i < matrixDate.size(); ++i) {
            genPage(matrixDate[i]);
            stackedWidget->addWidget(page1);
        }

        additVec.clear();
        matrixDate.clear();
    }
    stackedWidget->setCurrentIndex(idPage);
}

void MainWindow::withoutAnim(int button)
{

    if (button == 0) {
        leftChanger();
    } else if (button == 1) {
        rightChanger();
    }

    updateDbData();
}

std::chrono::system_clock::time_point MainWindow::qstring_to_time_point(QString val)
{
    std::string str = val.toStdString();
    std::istringstream ss(str);
    std::tm tm = {};
    ss >> std::get_time(&tm, "%a %b %d %Y");
    std::time_t t = std::mktime(&tm);
    std::chrono::system_clock::time_point tp = std::chrono::system_clock::from_time_t(t);
    return tp;
}

void MainWindow::updateDbData()
{

    QVector<QString> date;
    QVector<QString> title;
    QVector<QString> decription;

    QSqlQuery query;
    query.prepare("SELECT * FROM diary_data");

    if (!query.exec()) {
        messBox("–†—õ–°‚Ç¨–†—ë–†¬±–†—î–†¬∞ –†–Ü–°‚Äπ–†—ó–†—ï–†¬ª–†–Ö–†¬µ–†–Ö–†—ë–°–è –†¬∑–†¬∞–†—ó–°–Ç–†—ï–°–É–†¬∞: " + query.lastError().text());
        db.close();
        return;
    }

    int i = 0;

    while (query.next()) {
        QSqlRecord record = query.record();
        QString val1 = record.value("date").toString();
        QString val2 = record.value("title").toString();
        QString val3 = record.value("description").toString();

        date.push_back(val1);
        title.push_back(val2);
        decription.push_back(val3);

        //        qDebug() << date[i] << title[i];
        i++;
    }

    for (int i = 0; i < cardLabel_ptr.size(); ++i) {

        int v = -9999;

        for (int k = 0; k < date.size(); ++k) {
            QString str1 = date[k] + "\n";
            QString str2 = (QString)cardLabel_ptr[i]->text();

            if (str1 == str2) {
                v = k;
            }
        }

        if (v != -9999) {

            cardLineEdit_ptr[i]->setProperty("title", title[v]);
            cardTextEdit_ptr[i]->setProperty("decription", decription[v]);

            if (title[v].size() <= 30) {
                cardLineEdit_ptr[i]->setText(title[v]);
            } else {
                QString subStr = title[v].left(30);
                cardLineEdit_ptr[i]->setText(subStr + "...");
            }

            cardLineEdit_ptr[i]->setReadOnly(true);

            if (decription[v].size() <= 280) {
                cardTextEdit_ptr[i]->setText(decription[v]);
            } else {
                QString subStr = decription[v].left(280);
                cardTextEdit_ptr[i]->setText(subStr + "...");
            }

            cardTextEdit_ptr[i]->setReadOnly(true);

            cardBtn_ptr[i]->setEnabled(false);
        }
    }

    insertDbData();
}

void MainWindow::limitDate(QVector<QVector<QString>>& vec, int index)
{
    vec.erase(vec.begin() + index);
}

void MainWindow::on_pushButton_4_clicked()
{
    zoomIdx--;

    if (zoomIdx < 0) {
        zoomIdx = 0;
    } else {
        chPerText();
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    zoomIdx++;

    if (zoomIdx > 5) {
        zoomIdx = 5;
    } else {
        chPerText();
    }
}

void MainWindow::chPerText()
{
    QLabel* lab = ui->percent_lab;

    if (zoomIdx == 5) {
        lab->setText("100%");
        ui->centralwidget->setMaximumSize(centralWidgetWidth, centralWidgetHeight);
    } else if (zoomIdx == 4) {
        lab->setText(" 80%");
        ui->centralwidget->setMaximumSize(centralWidgetWidth * 0.9, centralWidgetHeight * 0.95);
    } else if (zoomIdx == 3) {
        lab->setText(" 60%");
        ui->centralwidget->setMaximumSize(centralWidgetWidth * 0.8, centralWidgetHeight * 0.90);

    } else if (zoomIdx == 2) {
        lab->setText(" 40%");
        ui->centralwidget->setMaximumSize(centralWidgetWidth * 0.7, centralWidgetHeight * 0.85);
    } else if (zoomIdx == 1) {
        lab->setText(" 20%");
        ui->centralwidget->setMaximumSize(centralWidgetWidth * 0.6, centralWidgetHeight * 0.80);
    } else if (zoomIdx == 0) {
        lab->setText("  0%");
        ui->centralwidget->setMaximumSize(centralWidgetWidth * 0.5, centralWidgetHeight * 0.75);
    }
}

void MainWindow::wheelEvent(QWheelEvent* event)
{

    int delta = event->angleDelta().y();

    if (delta < 0 && ctrlPress) {
        zoomIdx--;

        if (zoomIdx < 0) {
            zoomIdx = 0;
        } else {
            chPerText();
        }
    } else if (delta > 0 && ctrlPress) {
        zoomIdx++;

        if (zoomIdx > 5) {
            zoomIdx = 5;
        } else {
            chPerText();
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Control) {
        ctrlPress = true;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Control) {
        ctrlPress = false;
    }
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    zoomIdx = 5;

    QSize size = event->size();
    int width = size.width();
    int height = size.height();

    ui->percent_lab->setText("100%");
    ui->centralwidget->setMaximumSize(width, height);

    centralWidgetWidth = width;
    centralWidgetHeight = height;
}

void MainWindow::saveDbInfo(QString date, QString lineEditText, QString textEditText, int idx)
{
    bool checkEmptyField = true;

    if (lineEditText == "") {
        checkEmptyField = false;
    }

    if (checkEmptyField) {

        QMessageBox msgBox(QMessageBox::Question, "Saving", "Do you want to save?", QMessageBox::Yes | QMessageBox::No);
        msgBox.setStyleSheet("QMessageBox {background-color: white; color: black;}"
                             "QPushButton { padding-left: 10px; padding-right: 10px; padding-top: 3px; padding-bottom: 3px; background-color: white; border-radius: 3px; border: 1px solid  rgb(209, 207, 203);}"
                             "QPushButton:hover{background: #dedcd7;}");

        int result = msgBox.exec();

        if (result == msgBox.Yes) {

            cardBtn_ptr[idx]->setEnabled(false);
            cardLineEdit_ptr[idx]->setReadOnly(true);
            cardTextEdit_ptr[idx]->setReadOnly(true);

            QSqlQuery query;
            query.prepare("INSERT INTO diary_data (date, title, description) VALUES (:date, :title, :description)");
            query.bindValue(":date", date);
            query.bindValue(":title", lineEditText);
            query.bindValue(":description", textEditText);

            if (!query.exec()) {
                messBox("Error inserting data in db");
            }
        }

    } else {

        messBox("Please fill title!");
    }
}

void MainWindow::sendInfoToUncMode(QString date, QString lineEditText, QString textEditText, QLineEdit* lineEdit_ptr, QTextEdit* textEdit_ptr, QPushButton* saveBtn_ptr, QVector<QPushButton*> btns)
{
    fullinfo = new FullInfo(date, lineEditText, textEditText, lineEdit_ptr, textEdit_ptr, saveBtn_ptr, btns);
    fullinfo_ptr.push_back(fullinfo);
    fullinfo->setWindowModality(Qt::ApplicationModal);
    fullinfo->show();
}

void MainWindow::insertDbData()
{
    for (int i = idxBtn; i < cardBtn_ptr.size(); ++i) {
        connect(cardBtn_ptr[i], &QPushButton::clicked, this, [=]() {
            saveDbInfo(((cardLabel_ptr[i])->text()).chopped(1), (cardLineEdit_ptr[i])->text(), (cardTextEdit_ptr[i])->toPlainText(), i);
        });

        QVector<QPushButton*> btns;

        btns.push_back(cardFileBtn1_ptr[i]);
        btns.push_back(cardFileBtn2_ptr[i]);
        btns.push_back(cardFileBtn3_ptr[i]);
        btns.push_back(cardFileBtn4_ptr[i]);
        btns.push_back(cardFileBtn5_ptr[i]);

        //conn for uncover card mode
        connect(cardBtn2_ptr[i], &QPushButton::clicked, this, [=]() {
            sendInfoToUncMode(((cardLabel_ptr[i])->text()).chopped(1),
                (cardLineEdit_ptr[i])->property("title").toString(),
                (cardTextEdit_ptr[i])->property("decription").toString(),
                cardLineEdit_ptr[i], cardTextEdit_ptr[i],
                cardBtn_ptr[i],
                btns);
        });
    }

    idxBtn = cardBtn_ptr.size();
}

void MainWindow::fileBtn_ect(QString date, int btn_num, QVector<QPushButton*> btns)
{
    QVector<QString> dateBd;
    QVector<QString> title;
    QVector<QString> decription;
    QVector<QString> file1;
    QVector<QString> file2;
    QVector<QString> file3;
    QVector<QString> file4;
    QVector<QString> file5;

    QSqlQuery query;
    query.prepare("SELECT * FROM diary_data WHERE date=:date");
    query.bindValue(":date", date.chopped(1));

    if (!query.exec()) {
        qWarning() << "Select from bd where date = date:" << query.lastError().text();
        db.close();
        return;
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

        dateBd.push_back(val1);
        title.push_back(val2);
        decription.push_back(val3);
        file1.push_back(val4);
        file2.push_back(val5);
        file3.push_back(val6);
        file4.push_back(val7);
        file5.push_back(val8);
    }

    if (title.size() == 0) {
        messBox("Fill and save title!");
    } else {

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
            if (!dirOfDates.exists(date.chopped(1))) {
                dirOfDates.mkdir(date.chopped(1));
            }

            //rewrite folder with file
            QDir folder(DB_DIR_PATH + "DATES/" + date.chopped(1) + "/" + QString::number(btn_num));
            folder.removeRecursively();

            QDir folder1(DB_DIR_PATH + "DATES/" + date.chopped(1) + "/");
            if (!folder1.exists("1")) {
                folder1.mkdir("1");
            }

            QDir folder2(DB_DIR_PATH + "DATES/" + date.chopped(1) + "/");
            if (!folder2.exists("2")) {
                folder2.mkdir("2");
            }

            QDir folder3(DB_DIR_PATH + "DATES/" + date.chopped(1) + "/");
            if (!folder3.exists("3")) {
                folder3.mkdir("3");
            }

            QDir folder4(DB_DIR_PATH + "DATES/" + date.chopped(1) + "/");
            if (!folder4.exists("4")) {
                folder4.mkdir("4");
            }

            QDir folder5(DB_DIR_PATH + "DATES/" + date.chopped(1) + "/");
            if (!folder5.exists("5")) {
                folder5.mkdir("5");
            }

            QString q_first_part = DB_DIR_PATH + "DATES/" + date.chopped(1) + "/" + QString::number(btn_num) + "/";
            std::string first_part = QTextCodec::codecForName("CP1251")->fromUnicode(q_first_part).data();
            std::string second_part = QTextCodec::codecForName("CP1251")->fromUnicode(fileInfo.fileName()).data();
            std::string destin_std_translit = first_part + transliterate(second_part);
            QString destin_res = QString::fromStdString(destin_std_translit);

            qDebug() << destin_res;

            QFile::copy(path, destin_res);
            QFile::setPermissions(destin_res, QFile::WriteOwner | QFile::ReadOwner);

            QString ic = getFileIcon(path);

            currBtn->setIcon(QIcon(ic));

            if (btn_num < 5) {
                btns[btn_num]->setVisible(true);
            }

            QSqlQuery query2;
            query2.prepare("UPDATE diary_data SET " + QString("file%1").arg(btn_num) + "= :path WHERE date = :date");
            query2.bindValue(":path", destin_res);
            query2.bindValue(":date", date.chopped(1));

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
        }
    }
}

QString MainWindow::getFileIcon(QString path)
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

void MainWindow::messBox(QString val)
{
    QMessageBox msgBox(QMessageBox::Information, "Info", val);
    msgBox.setStyleSheet("QMessageBox {background-color: white; color: black;}"
                         "QPushButton { padding-left: 10px; padding-right: 10px; padding-top: 3px; padding-bottom: 3px; background-color: white; border-radius: 3px; border: 1px solid  rgb(209, 207, 203);}"
                         "QPushButton:hover{background: #dedcd7;}");

    msgBox.exec();
}

void MainWindow::on_pushButton_6_clicked()
{
    QString defaultPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

    QString fileExt;
    QString genPath = defaultPath + "/" + "diary_settings";
    QString savePath = QFileDialog::getSaveFileName(this, "Save File", genPath, "Zip files (*.zip);");

    if (savePath == "") {
        return;
    }

    ZipManage* zipManage = new ZipManage(1);
    zipManage->setCreatePath(DIR_PATH_NO_LAST_SLASH, savePath);
    connect(zipManage, &ZipManage::finished, this, [=]() {
        messBox("Settings saved. Please restart program!");
    });
    zipManage->start();

    messBox("Wait end of operation. Will be message!");
}

void MainWindow::on_pushButton_7_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Choose File", "C:/Users/" + qUsername + "/Desktop/");
    QByteArray path_ba = QTextCodec::codecForName("CP1251")->fromUnicode(path);

    if (path == "") {
        return;
    }

    QMessageBox msgBox(QMessageBox::Question, "Clearing", "This operation clear all date. Do you want to clear data?", QMessageBox::Yes | QMessageBox::No);
    msgBox.setStyleSheet("QMessageBox {background-color: white; color: black;}"
                         "QPushButton { padding-left: 10px; padding-right: 10px; padding-top: 3px; padding-bottom: 3px; background-color: white; border-radius: 3px; border: 1px solid  rgb(209, 207, 203);}"
                         "QPushButton:hover{background: #dedcd7;}");

    int result = msgBox.exec();

    if (result == msgBox.Yes) {

        QByteArray fol_path_ba = QTextCodec::codecForName("CP1251")->fromUnicode(ROAMING_DIR_PATH_NO_LAST_SLASH);

        ZipManage* zipManage = new ZipManage(2);
        zipManage->setExtrPath(fol_path_ba, path_ba);
        connect(zipManage, &ZipManage::finished, this, [=]() {
            messBox("Settings imported. Please restart program!");
        });
        zipManage->start();

        messBox("Wait end of operation. Will be message!");
    }
}

void MainWindow::on_actionClear_Db_triggered()
{
    QMessageBox msgBox(QMessageBox::Question, "Clearing", "Do you want to clear all data?", QMessageBox::Yes | QMessageBox::No);
    msgBox.setStyleSheet("QMessageBox {background-color: white; color: black;}"
                         "QPushButton { padding-left: 10px; padding-right: 10px; padding-top: 3px; padding-bottom: 3px; background-color: white; border-radius: 3px; border: 1px solid  rgb(209, 207, 203);}"
                         "QPushButton:hover{background: #dedcd7;}");

    int result = msgBox.exec();

    if (result == msgBox.Yes) {

        QSqlQuery query;
        query.prepare("DELETE FROM diary_data");

        if (!query.exec()) {
            messBox("Error inserting data in db");
        }

        messBox("Data cleared. Restart program!");
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    QString defaultPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

    QString fileExt;
    QString genPath = defaultPath + "/" + "diary_settings";
    QString savePath = QFileDialog::getSaveFileName(this, "Save File", genPath, "Zip files (*.zip);");

    if (savePath == "") {
        return;
    }

    ZipManage* zipManage = new ZipManage(1);
    zipManage->setCreatePath(DIR_PATH_NO_LAST_SLASH, savePath);
    connect(zipManage, &ZipManage::finished, this, [=]() {
        messBox("Settings saved. Please restart program!");
    });
    zipManage->start();

    messBox("Wait end of operation. Will be message!");
}

void MainWindow::on_actionImport_triggered()
{
    QString path = QFileDialog::getOpenFileName(this, "Choose File", "C:/Users/" + qUsername + "/Desktop/");
    QByteArray path_ba = QTextCodec::codecForName("CP1251")->fromUnicode(path);

    if (path == "") {
        return;
    }

    QMessageBox msgBox(QMessageBox::Question, "Clearing", "This operation clear all date. Do you want to clear data?", QMessageBox::Yes | QMessageBox::No);
    msgBox.setStyleSheet("QMessageBox {background-color: white; color: black;}"
                         "QPushButton { padding-left: 10px; padding-right: 10px; padding-top: 3px; padding-bottom: 3px; background-color: white; border-radius: 3px; border: 1px solid  rgb(209, 207, 203);}"
                         "QPushButton:hover{background: #dedcd7;}");

    int result = msgBox.exec();

    if (result == msgBox.Yes) {

        QByteArray fol_path_ba = QTextCodec::codecForName("CP1251")->fromUnicode(ROAMING_DIR_PATH_NO_LAST_SLASH);

        ZipManage* zipManage = new ZipManage(2);
        zipManage->setExtrPath(fol_path_ba, path_ba);
        connect(zipManage, &ZipManage::finished, this, [=]() {
            messBox("Settings imported. Please restart program!");
        });
        zipManage->start();

        messBox("Wait end of operation. Will be message!");
    }
}

std::string MainWindow::transliterate(std::string original_string)
{
    std::string result_string = "";

    for (int i = 0; i < original_string.length(); i++) {
        if (original_string[i] == '¿' || original_string[i] == '‡') {
            result_string += "a";
        } else if (original_string[i] == '¡' || original_string[i] == '·') {
            result_string += "b";
        } else if (original_string[i] == '¬' || original_string[i] == '‚') {
            result_string += "v";
        } else if (original_string[i] == '√' || original_string[i] == '„') {
            result_string += "g";
        } else if (original_string[i] == 'ƒ' || original_string[i] == '‰') {
            result_string += "d";
        } else if (original_string[i] == '≈' || original_string[i] == 'Â') {
            result_string += "ye";
        } else if (original_string[i] == '®' || original_string[i] == '∏') {
            result_string += "yo";
        } else if (original_string[i] == '∆' || original_string[i] == 'Ê') {
            result_string += "zh";
        } else if (original_string[i] == '«' || original_string[i] == 'Á') {
            result_string += "z";
        } else if (original_string[i] == '»' || original_string[i] == 'Ë') {
            result_string += "i";
        } else if (original_string[i] == '…' || original_string[i] == 'È') {
            result_string += "yi";
        } else if (original_string[i] == ' ' || original_string[i] == 'Í') {
            result_string += "k";
        } else if (original_string[i] == 'À' || original_string[i] == 'Î') {
            result_string += "l";
        } else if (original_string[i] == 'Ã' || original_string[i] == 'Ï') {
            result_string += "m";
        } else if (original_string[i] == 'Õ' || original_string[i] == 'Ì') {
            result_string += "n";
        } else if (original_string[i] == 'Œ' || original_string[i] == 'Ó') {
            result_string += "o";
        } else if (original_string[i] == 'œ' || original_string[i] == 'Ô') {
            result_string += "p";
        } else if (original_string[i] == '–' || original_string[i] == '') {
            result_string += "r";
        } else if (original_string[i] == '—' || original_string[i] == 'Ò') {
            result_string += "s";
        } else if (original_string[i] == '“' || original_string[i] == 'Ú') {
            result_string += "t";
        } else if (original_string[i] == '”' || original_string[i] == 'Û') {
            result_string += "u";
        } else if (original_string[i] == '‘' || original_string[i] == 'Ù') {
            result_string += "f";
        } else if (original_string[i] == '’' || original_string[i] == 'ı') {
            result_string += "h";
        } else if (original_string[i] == '÷' || original_string[i] == 'ˆ') {
            result_string += "ts";
        } else if (original_string[i] == '◊' || original_string[i] == '˜') {
            result_string += "Òh";
        } else if (original_string[i] == 'ÿ' || original_string[i] == '¯') {
            result_string += "sh";
        } else if (original_string[i] == 'Ÿ' || original_string[i] == '˘') {
            result_string += "shch";
        } else if (original_string[i] == '≤' || original_string[i] == '≥') {
            result_string += 'i';
        } else if (original_string[i] == '€' || original_string[i] == '˚') {
            result_string += 'i';
        } else if (original_string[i] == 'ﬂ' || original_string[i] == 'ˇ') {
            result_string += "ya";
        } else if (original_string[i] == 'ﬁ' || original_string[i] == '˛') {
            result_string += "yu";
        } else if (original_string[i] == 'ﬂ' || original_string[i] == 'ˇ') {
            result_string += "ya";
        } else if (original_string[i] == '›' || original_string[i] == '˝') {
            result_string += 'e';
        } else if (original_string[i] == '™' || original_string[i] == '∫') {
            result_string += "ye";
        } else if (original_string[i] == 'Ø' || original_string[i] == 'ø') {
            result_string += "yi";
        } else if (original_string[i] == '¸' || original_string[i] == '˙' || original_string[i] == '‹' || original_string[i] == '⁄') {
            result_string += "";
        } else if (original_string[i] == '0' || original_string[i] == '1' || original_string[i] == '2' || original_string[i] == '3' || original_string[i] == '4' || original_string[i] == '5' || original_string[i] == '6' || original_string[i] == '7' || original_string[i] == '8' || original_string[i] == '9') {
            result_string += original_string[i];
        } else {
            result_string += original_string[i];
        }
    }

    return result_string;
}
