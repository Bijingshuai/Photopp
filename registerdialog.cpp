#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "usertool.h"
#include "QMessageBox"
registerDialog::registerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerDialog)
{
    ui->setupUi(this);
}

registerDialog::~registerDialog()
{
    delete ui;
}

void registerDialog::on_pushButton_clicked()
{
    UserTool *usertool=new UserTool();
    usertool->signup(ui->lineEdit->text(),ui->lineEdit_2->text());
    connect(usertool,SIGNAL(getserverdata(QString)),this,SLOT(signup(QString)));
}
void registerDialog::signup(QString a)
{
    std::string str = a.toStdString();
    const char *s = str.c_str();
    if(a.compare(QString(""))) {
        QMessageBox::warning(this,tr("Warning"),
                tr(s),
                QMessageBox::Yes );
    }
else { QMessageBox::warning(this,tr("Warning"),
                            tr(s),
                            QMessageBox::Yes); accept();}
}
