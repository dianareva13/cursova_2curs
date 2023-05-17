
#ifndef MYAXWIDGET_H
#define MYAXWIDGET_H

#include <QAxWidget>

class MyAxWidget : public QAxWidget {
public:
    explicit MyAxWidget(QWidget* parent = nullptr);
    ~MyAxWidget();

private:
};

#endif // MYAXWIDGET_H
