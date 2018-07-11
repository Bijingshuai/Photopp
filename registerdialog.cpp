#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "usertool.h"
#include "QMessageBox"
registerDialog::registerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->pushButton_3->setStyleSheet("QPushButton:enabled{border-image: url(:/new/prefix1/a.png)}"
                                    "QPushButton:hover{border-image:url(:/new/prefix1/a1.png)}");
    ui->pushButton_4->setStyleSheet("QPushButton:enabled{border-image: url(:/new/prefix1/b1.png)}"
                                    "QPushButton:hover{border-image:url(:/new/prefix1/b.png)}");
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
void registerDialog::mousePressEvent(QMouseEvent *e)
{
    last=e->globalPos();
}
void registerDialog::mouseMoveEvent(QMouseEvent *e)
{
    int dx=e->globalX()-last.x();
    int dy=e->globalY()-last.y();
    last=e->globalPos();
    move(x()+dx,y()+dy);
}
void registerDialog::mouseReleaseEvent(QMouseEvent *e)
{
    int dx=e->globalX()-last.x();
    int dy=e->globalY()-last.y();
    move(x()+dx,y()+dy);
}
