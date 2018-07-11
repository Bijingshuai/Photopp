#include "usertool.h"
#include <QUrl>
#include <QByteArray>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <iostream>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonValue>

using namespace std;

UserTool::UserTool(){
    signmanager=new QNetworkAccessManager(this);
    connect(signmanager,SIGNAL(finished(QNetworkReply*)),this,SLOT(finishedslot(QNetworkReply*)));
}

UserTool::~UserTool(){

}

void UserTool::checkconnection(){
    QNetworkRequest request;
    request.setUrl(QUrl("http://159.89.198.64:8086"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    signmanager->get(request);
}

void UserTool::login(QString user, QString pass){
    QNetworkRequest request;
    request.setUrl(QUrl("http://159.89.198.64:8086/user/login"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    QByteArray postdata;
    postdata.append(QString("username="+user+"&password="+pass));
    signmanager->post(request,postdata);
}

void UserTool::signup(QString user, QString pass){
    QNetworkRequest request;
    request.setUrl(QUrl("http://159.89.198.64:8086/user/register"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    QByteArray postdata;
    postdata.append(QString("username="+user+"&password="+pass));
    signmanager->post(request,postdata);
}



void UserTool::finishedslot(QNetworkReply *reply){
    int statuscode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray fromserver= reply->readAll();
    qDebug()<<statuscode;
    QJsonParseError *error=new QJsonParseError;
    QJsonDocument doc=QJsonDocument::fromJson(fromserver,error);
    QJsonObject obj;
    if(error->error==QJsonParseError::NoError){
        if(doc.isObject()){
            obj=doc.object();//取得最外层这个大对象
            qDebug()<<obj;
            }
        }
        else{
            qDebug()<<error->errorString();
        }


    if(obj.contains("error")){
        QJsonValue errorval=obj.value("error");
        QString errorstr=errorval.toString();
        qDebug()<<errorstr;
        emit getserverdata(errorstr);
    }
    if(obj.contains("jwt")){
        QJsonValue jwtval=obj.value("jwt");
        jwt=jwtval.toString();
        qDebug()<<jwt;
    }

    reply->deleteLater();
}

QString UserTool::getjwt(){
    return jwt;
}
