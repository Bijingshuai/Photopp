#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPushButton>
#include<dialog.h>
#include<QMessageBox>
#include<QFileDialog>
#include "QTextEdit"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QApplication::setStyle("windows");





}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openDialog(QTableWidgetItem*)
{
    Dialog dlg1;
    dlg1.resize(400,400);
    dlg1.exec();
}



void MainWindow::on_upbtn_clicked()
{
    PhotoTool *photoTool = PhotoTool::getPhotoTool();
    QString path=QFileDialog::getOpenFileName(this,tr("Open Image"),".",tr("Image Files(*.jpg * .png)"));
    if(path.length()==0)
    {
        QMessageBox::information(NULL,tr("Path"),tr("You didn't select any files."));
    }
    else
    {
        QMessageBox::information(NULL,tr("Path"),tr("You selected")+path);
        photoTool->uploadPhoto(path);
        connect(photoTool, SIGNAL(imageVector(vector<vector<vector<Image> > >)),this,SLOT(configWidget(vector<vector<vector<Image> > >)));
    }
}

void MainWindow::configWidget(vector<vector<vector<Image> > >prama_vec)
{
    vec = prama_vec;
    ui->tableWidget->setItemDelegate(new QPixmapItemdele());


    int rowcount;
    int colcount=4;
    int width;
    int a;
    const char * b;
    QTextEdit *tb=new QTextEdit;
    ui->tableWidget->setCellWidget(a,0,tb);
   ui->tableWidget->setRowHeight(a,100);
   QString str(tr(b));
   tb->setStyleSheet("border-style:outset");
   for(int i=0; i<ui->tableWidget->columnCount(); i++)
   {

     ui->tableWidget->setColumnWidth(i,width);
     for(int i=0;i<50;++i)
      {
       QTableWidgetItem *itemi = new QTableWidgetItem();
       ui->tableWidget->setItem(0,i,itemi);
       itemi->setData(Qt::DisplayRole,QVariant::fromValue<QPixmap>(QPixmap(":/new/prefix1/a.png").scaled(60,60)));
       }

}
    ui->tableWidget->setItemDelegate(new QPixmapItemdele());

        ui->tableWidget->setColumnCount(colcount);
        ui->tableWidget->setRowCount(rowcount);
        ui->tableWidget->horizontalHeader()->setVisible(false);
        ui->tableWidget->verticalHeader()->setVisible(false);
        ui->tableWidget->setSelectionMode(ui->tableWidget->NoSelection);
        ui->tableWidget->setEditTriggers(ui->tableWidget->SelectedClicked);
        ui->tableWidget->setShowGrid(true);
        ui->tableWidget->setFrameShape(QFrame::NoFrame);
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

connect(ui->tableWidget,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(openDialog(QTableWidgetItem*)));

}
void MainWindow::on_pushButton_clicked()
{
    MainWindow::configWidget(vec);
}


void MainWindow::on_pushButton_2_clicked()
{
     MainWindow::configWidget(vec);
}


void MainWindow::on_pushButton_3_clicked()
{
    MainWindow::configWidget(vec);
}
