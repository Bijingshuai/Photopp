#include "phototool.h"
#include "exif.h"
#include <QUrl>
#include <QByteArray>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <iostream>
#include <QDebug>

#include <iostream>
#include <iomanip>
#include <cassert>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonValue>


PhotoTool::PhotoTool()
{
    updownManager=new QNetworkAccessManager(this);
    UserTool *jwtManager=UserTool::getUserTool();
    classifyManager=new QNetworkAccessManager(this);
    jwtString=jwtManager->getjwt();
}

PhotoTool::~PhotoTool(){

}

void PhotoTool::uploadPhoto(QString filepath){
    QImage image(filepath);
    QByteArray ba;
    QBuffer buf(&ba);
    buf.open(QIODevice::WriteOnly);
    image.save(&buf,"jpg");

    path=filepath;

    QByteArray postdata;
    QString gpsdata=readexif(filepath);
    QString posturl("image="+ba.toBase64()+"&jwt="+jwtString+"&GPS="+gpsdata);
    posturl.replace("+","%2B");//解决post
    postdata.append(posturl);
    buf.close();


    QNetworkRequest request;
    request.setUrl(QUrl("http://159.89.198.64:8086/image/upload"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    updownManager->post(request,postdata);

    connect(updownManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(uploadFinished(QNetworkReply*)));
}

void PhotoTool::uploadFinished(QNetworkReply *reply){
    int statuscode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray fromserver= reply->readAll();
    qDebug()<<statuscode;


    QJsonParseError *error=new QJsonParseError;
    QJsonDocument doc=QJsonDocument::fromJson(fromserver,error);
    QJsonObject obj;
    if(error->error==QJsonParseError::NoError){
            obj=doc.object();//取得最外层这个大对象
        }
        else{
            qDebug()<<error->errorString();
        }


    if (!commmonVec.size())
        commmonVec.push_back(vector<Image>());

        QString id = obj.value("id").toString();
        QString location = obj.value("location").toString();
        bool face = obj.value("face").toBool();

        QFile::copy(path,QString("/Users/mac/Downloads/testphoto/"+id+".jpg"));//修改路径

        commmonVec[0].push_back(Image{id, location, face});

        //locationVec
        bool flag = false;
        for (int index = 0, len = locationVec.size(); (index < len) && !flag; index++) {
            if (!QString::compare(locationVec[index].at(0).location, location)) {
                flag = true;
                locationVec[index].push_back(Image{id, location, face});
            }
        }
        if (!flag) {
            locationVec.push_back(vector<Image>());
            locationVec[locationVec.size()-1].push_back(Image{id, location, face});
        }

        //facevector
        bool flag2=false;
        for(int index = 0,len = faceVec.size(); (index<len) && !flag2; index++){
            if(faceVec[index].at(0).face==face){
                flag2 = true;
                faceVec[index].push_back(Image{id,location,face});
            }
        }
        if(!flag2){
            faceVec.push_back(vector<Image>());
            faceVec[faceVec.size()-1].push_back(Image{id,location,face});
        }

}


QString PhotoTool::readexif(QString filepath){
    QFile file(filepath);
    if(file.open(QIODevice::ReadOnly)){
        QByteArray ba=file.readAll();
        int fsize=ba.size();
        const unsigned char* buf = reinterpret_cast<const unsigned char*>(ba.data());

        easyexif::EXIFInfo result;

        int code= result.parseFrom(buf, fsize);
        if((code!=0)||((result.GeoLocation.Latitude==0)&&(result.GeoLocation.Longitude==0))){
            return NULL;
        }
        else{
            QString gps(QString::number(result.GeoLocation.Longitude,'f',4)+","+QString::number(result.GeoLocation.Latitude,'f',4));
            qDebug()<<QString::number(result.GeoLocation.Latitude,'f',4);
            qDebug()<<QString::number(result.GeoLocation.Longitude,'f',4);
            return gps;
        }


    }
}


void PhotoTool::confirmId(){
    QDir dir("/Users/mac/Downloads/testphoto");//修改路径
         dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
         dir.setSorting(QDir::Size | QDir::Reversed);

         QFileInfoList list = dir.entryInfoList();
         QJsonObject obj;
         obj.insert("jwt",jwtString);

         QJsonArray arr;
         for (int i = 0; i < list.size(); ++i) {
             QFileInfo fileInfo = list.at(i);
             arr.insert(i,fileInfo.baseName());

         }
         obj.insert("array",QJsonValue(arr));


     QNetworkRequest request;
     request.setUrl(QUrl("http://159.89.198.64:8086/image/download"));
     request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");//修改header


     QJsonDocument doc;
     doc.setObject(obj);
     QByteArray postdata=doc.toJson(QJsonDocument::Compact);

     updownManager->post(request,postdata);

     connect(updownManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(downloadPhoto(QNetworkReply*)));
}

void PhotoTool::downloadPhoto(QNetworkReply *reply){
    int statuscode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray fromserver= reply->readAll();
//    qDebug()<<fromserver.count();
    qDebug()<<statuscode;
    QJsonParseError *error=new QJsonParseError;
    QJsonDocument doc=QJsonDocument::fromJson(fromserver,error);
    QJsonArray arr;
    if(error->error==QJsonParseError::NoError){
        arr=doc.array();
        //qDebug()<<arr;
        //qDebug()<<arr.count();
    }else{
        qDebug()<<"这里"<<error->errorString();
    }

    for(int i=0;i<arr.count();i++){
        QJsonValue val=arr.at(i);
        QJsonObject obj=val.toObject();
        //qDebug()<<obj.value("id").toString();
        //qDebug()<<obj.value("image").toString();
        QString id=obj.value("id").toString();
        QString data64(obj.value("image").toString());
        QByteArray byte;
        byte.append(data64);
        QByteArray rebyte;
        rebyte=QByteArray::fromBase64(byte);
        QBuffer buf(&rebyte);
        buf.open(QIODevice::WriteOnly);

        QPixmap photoresult;
        photoresult.loadFromData(rebyte);
        photoresult.save(QString("/Users/mac/Downloads/testphoto/"+id+".jpg"),0);//修改路径

    }


    QNetworkRequest request;
    request.setUrl(QUrl("http://159.89.198.64:8086/image/classify"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    QByteArray postdata;
    postdata.append(QString("jwt="+jwtString));
    classifyManager->post(request,postdata);

    connect(classifyManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(classification(QNetworkReply*)));
}

void PhotoTool::classification(QNetworkReply *reply){
    int statuscode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray fromserver= reply->readAll();
    qDebug()<<statuscode;
    //qDebug()<<fromserver;
    QJsonParseError *error=new QJsonParseError;
    QJsonDocument doc=QJsonDocument::fromJson(fromserver,error);
    QJsonArray arr;
    if(error->error==QJsonParseError::NoError){
            arr=doc.array();//取得最外层这个大对象
        }
        else{
            qDebug()<<error->errorString();
        }

    commmonVec.push_back(vector<Image>());
    for(int i=0;i<arr.count();i++){
        QJsonValue val=arr.at(i);
        QJsonObject obj=val.toObject();

        QString id = obj.value("id").toString();
        QString location = obj.value("location").toString();
        bool face = obj.value("face").toBool();

        commmonVec[0].push_back(Image{id, location, face});

        //locationVec
        bool flag = false;
        for (int index = 0, len = locationVec.size(); (index < len) && !flag; index++) {
            if (!QString::compare(locationVec[index].at(0).location, location)) {
                flag = true;
                locationVec[index].push_back(Image{id, location, face});
            }
        }
        if (!flag) {
            locationVec.push_back(vector<Image>());
            locationVec[locationVec.size()-1].push_back(Image{id, location, face});
        }

        //facevector
        bool flag2=false;
        for(int index = 0,len = faceVec.size(); (index<len) && !flag2; index++){
            if(faceVec[index].at(0).face==face){
                flag2 = true;
                faceVec[index].push_back(Image{id,location,face});
            }
        }
        if(!flag2){
            faceVec.push_back(vector<Image>());
            faceVec[faceVec.size()-1].push_back(Image{id,location,face});
        }


    }
    qDebug()<<commmonVec[0].at(0).id;
    qDebug()<<locationVec.size();

}
