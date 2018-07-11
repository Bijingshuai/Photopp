#include "logindialog.h"
#include "ui_logindialog.h"
#include "usertool.h"
#include "QMessageBox"
#include <string.h>
#include "vector"
#include "iostream"
#include "registerdialog.h"
#include "QTimer"
#include "QLineEdit"
#include "QPoint"
int flag=0;
logindialog::logindialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logindialog)
{
    ui->setupUi(this);
    ui->lineEdit_2->setPlaceholderText(QString::fromLocal8Bit("please input password"));
    ui->lineEdit->setPlaceholderText(QString::fromLocal8Bit("please input username"));
    ui->pushButton_4->setStyleSheet(tr("border-image: url(:/new/prefix1/eye.PNG);"));
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowIcon(QIcon(":/new/prefix1/title.PNG"));

    ui->pushButton_5->setStyleSheet("QPushButton:enabled{border-image: url(:/new/prefix1/a.png)}"
                                    "QPushButton:hover{border-image:url(:/new/prefix1/a1.png)}");
    ui->pushButton_6->setStyleSheet("QPushButton:enabled{border-image: url(:/new/prefix1/b1.png)}"
                                    "QPushButton:hover{border-image:url(:/new/prefix1/b.png)}");


}
logindialog::~logindialog()
{
    delete ui;
}

void logindialog::on_pushButton_clicked()
{
    UserTool *usertool=UserTool::getUserTool();
    usertool->login(ui->lineEdit->text(),ui->lineEdit_2->text());
    connect(usertool,SIGNAL(getserverdata(QString)),this,SLOT(login(QString)));
}
void logindialog::login(QString a)
{
    std::string str = a.toStdString();
    const char *s = str.c_str();
  if(a.compare(QString(""))) {
        QMessageBox::warning(this,tr("Warning"),
                tr(s),
                QMessageBox::Yes);
    }
else accept();
}
void logindialog::on_pushButton_3_clicked()
{
   registerDialog dlg2;
   logindialog dlg1;
   if(dlg2.exec()==QDialog::Accepted)
      dlg1.show();
}

void logindialog::on_pushButton_4_clicked()
{
    if(flag==0)
    {
     ui->lineEdit_2->setEchoMode(QLineEdit::Password);flag=1;
       ui->pushButton_4->setStyleSheet(tr("border-image: url(:/new/prefix1/eye2.PNG);"));
    }
    else
    {
        ui->lineEdit_2->setEchoMode(QLineEdit::Normal); flag=0;
        ui->pushButton_4->setStyleSheet(tr("border-image: url(:/new/prefix1/eye.PNG);"));

    }
}
void logindialog::mousePressEvent(QMouseEvent *e)
{
    last=e->globalPos();
}
void logindialog::mouseMoveEvent(QMouseEvent *e)
{
    int dx=e->globalX()-last.x();
    int dy=e->globalY()-last.y();
    last=e->globalPos();
    move(x()+dx,y()+dy);
}
void logindialog::mouseReleaseEvent(QMouseEvent *e)
{
    int dx=e->globalX()-last.x();
    int dy=e->globalY()-last.y();
    move(x()+dx,y()+dy);
}
