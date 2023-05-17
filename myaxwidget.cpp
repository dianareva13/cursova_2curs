
#include "myaxwidget.h"
#include <QCloseEvent>
#include <QDebug>
#include <QMessageBox>

MyAxWidget::MyAxWidget(QWidget* parent)
    : QAxWidget(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
}

MyAxWidget::~MyAxWidget()
{
}
