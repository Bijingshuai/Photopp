#include "logindialog.h"
#include "ui_logindialog.h"
#include "usertool.h"
#include "QMessageBox"
#include <string.h>
#include "vector"
#include "iostream"
#include "registerdialog.h"
logindialog::logindialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logindialog)
{
    ui->setupUi(this);

}

logindialog::~logindialog()
{
    delete ui;
}

void logindialog::on_pushButton_clicked()
{
    UserTool *usertool=new UserTool();
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
