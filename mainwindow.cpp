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

    path = QString("D:\\Users\\Photopp\\");


}

void MainWindow::afterLogin() {
    classifyType = 0;
    PhotoTool *photoTool = PhotoTool::getPhotoTool();
    photoTool->confirmId();
    QObject::connect(photoTool, SIGNAL(imageVector(vector<vector<vector<Image> > >)), this, SLOT(configWidget(vector<vector<vector<Image> > >)));
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
    QString up_path=QFileDialog::getOpenFileName(this,tr("Open Image"),".",tr("Image Files(* .jpg * .png)"));
    if(up_path.length()==0)
    {
        QMessageBox::information(NULL,tr("Path"),tr("You didn't select any files."));
    }
    else
    {
        QMessageBox::information(NULL,tr("Path"),tr("You selected")+up_path);
        photoTool->uploadPhoto(up_path);
        connect(photoTool, SIGNAL(imageVector(vector<vector<vector<Image> > >)),this,SLOT(configWidget(vector<vector<vector<Image> > >)));
    }
}

void MainWindow::configWidget(vector<vector<vector<Image> > >prama_vec)
{
    vec = prama_vec;
    ui->tableWidget->setItemDelegate(new QPixmapItemdele());
    ui->tableWidget->clear();

    if (classifyType == 0) {//common
        vector<vector<Image>> commonVec = vec[0];
        int groups = commonVec.size();
        int total = 0;
        for (int index = 0; index < groups; index++) {
            int rows;
            if (commonVec[index].size()%4 == 0) {
                rows = commonVec[index].size()/4;
            } else {
                rows = commonVec[index].size()/4 + 1;
            }

            //set image
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < 4; j++) {
                    QTableWidgetItem *item = new QTableWidgetItem();
                    ui->tableWidget->setItem(i+total, j, item);
                    QString str = QString(path+commonVec[index].at(4*i+j).id+".jpg");
                    item->setData(Qt::DisplayRole,QVariant::fromValue<QPixmap>(QPixmap(str).scaled(60,60)));
                    if (i == rows-1 && j ==commonVec[index].size()%4-1) {
                        break;
                    }
                }
            }
            total += rows;
        }
        ui->tableWidget->setRowCount(total);
    } else if (classifyType == 1) {//location
        vector<vector<Image>> locationVec = vec[1];
        int groups = locationVec.size();
        int total = 0;
        for (int index = 0; index < groups; index++) {
            QTextEdit *tb=new QTextEdit;
            ui->tableWidget->setCellWidget(total,0,tb);
            tb->setText(locationVec[index].at(0).location);
            tb->setStyleSheet("border-style:outset");
            total += 1;
            int rows;
            if (locationVec[index].size()%4 == 0) {
                rows = locationVec[index].size()/4;
            } else {
                rows = locationVec[index].size()/4 + 1;
            }

            //set image
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < 4; j++) {
                    QTableWidgetItem *item = new QTableWidgetItem();
                    ui->tableWidget->setItem(i+total, j, item);
                    QString str = QString(path+locationVec[index].at(4*i+j).id+".jpg");
                    item->setData(Qt::DisplayRole,QVariant::fromValue<QPixmap>(QPixmap(str).scaled(60,60)));
                    if (i == rows-1 && j ==locationVec[index].size()%4-1) {
                        break;
                    }
                }
            }
            total += rows;
        }
        ui->tableWidget->setRowCount(total);
    } else if (classifyType == 2) {//face
        vector<vector<Image>> faceVec = vec[2];
        int groups = faceVec.size();
        int total = 0;
        for (int index = 0; index < groups; index++) {
            if (faceVec[index].at(0).face == false)
                continue;
            int rows;
            if (faceVec[index].size()%4 == 0) {
                rows = faceVec[index].size()/4;
            } else {
                rows = faceVec[index].size()/4 + 1;
            }

            //set image
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < 4; j++) {
                    QTableWidgetItem *item = new QTableWidgetItem();
                    ui->tableWidget->setItem(i+total, j, item);
                    QString str = QString(path+faceVec[index].at(4*i+j).id+".jpg");
                    item->setData(Qt::DisplayRole,QVariant::fromValue<QPixmap>(QPixmap(str).scaled(60,60)));
                    if (i == rows-1 && j ==faceVec[index].size()%4-1) {
                        break;
                    }
                }
            }
            total += rows;
        }
        ui->tableWidget->setRowCount(total);
    } else {

    }


    ui->tableWidget->setItemDelegate(new QPixmapItemdele());

        ui->tableWidget->setColumnCount(4);

        ui->tableWidget->horizontalHeader()->setVisible(false);
        ui->tableWidget->verticalHeader()->setVisible(false);
        ui->tableWidget->setSelectionMode(ui->tableWidget->NoSelection);
        ui->tableWidget->setEditTriggers(ui->tableWidget->SelectedClicked);
        ui->tableWidget->setShowGrid(false);
        ui->tableWidget->setFrameShape(QFrame::NoFrame);
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

connect(ui->tableWidget,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(openDialog(QTableWidgetItem*)));

}

void MainWindow::on_pushButton_clicked()
{
    classifyType = 0;//common
    MainWindow::configWidget(vec);
}


void MainWindow::on_pushButton_2_clicked()
{
    classifyType = 1;//location
     MainWindow::configWidget(vec);
}


void MainWindow::on_pushButton_3_clicked()
{
    classifyType = 2;//face
    MainWindow::configWidget(vec);
}


