#include "dialog.h"
#include "ui_dialog.h"
#include"mainwindow.h"
#include"usertool.h"
#include"phototool.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
    QPixmap *pixmap=new QPixmap();
    pixmap->scaled(ui->label->size(),Qt::KeepAspectRatio);
    ui->label->setScaledContents(true);
    ui->label->setPixmap(*pixmap);
}
