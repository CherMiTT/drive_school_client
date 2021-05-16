/*!
* \file
* \brief Source file for requests for and to server
* \author CherMiTT
* \date	07.04.2021
* \version 1.0
*/

#include "requester.h"
#include "session.h"

const QString Requester::httpTemplate = "http://%1:%2/api/%3";
const QString Requester::httpsTemplate = "https://%1:%2/api/%3";
Requester *Requester::instance = nullptr;


Requester::Requester(QObject* parent) : QObject(parent)
{
    this->manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinishRequest(QNetworkReply*)));
    qDebug() << "connected manager";
}

void Requester::initRequester(const QString& host, int port, QSslConfiguration* value)
{
    this->host = host;
    this->port = port;
    sslConfig = value;

    if (sslConfig != nullptr)
        pathTemplate = httpsTemplate;
    else
        pathTemplate = httpTemplate;
}

void Requester::sendRequest(const QString& apiStr, Requester::Type type, const QByteArray& data) const
{
    QNetworkRequest request = createRequest(apiStr);

    qDebug() << data;

    QNetworkReply *reply;

    switch (type) {
    case Type::POST:
    {
        request.setHeader(QNetworkRequest::ContentLengthHeader, data.count());
        qDebug() << "Length of data = " << data.count();
        reply = manager->post(request, data);
        break;
    }
    case Type::GET:
    {
        reply = manager->get(request);
        break;
    }
    case Type::PATCH:
    {
        qCritical() << "Don't support PATCH yet, ah-ha";
        reply = nullptr;
        Q_ASSERT(false);
    }
    case Type::DELETE:
    {
        qCritical() << "Don't support DELETE yet, ah-ha";
        reply = nullptr;
        Q_ASSERT(false);
    }
    default:
    {
        qCritical() << "Something went wrong!";
        reply = nullptr;
        Q_ASSERT(false);
    }

    }

}

Requester* Requester::getInstance()
{
    if(instance == nullptr)
    {
        instance = new Requester();
    }
    return instance;
}

QNetworkRequest Requester::createRequest(const QString &apiStr) const
{
    QNetworkRequest request;
    QString url = pathTemplate.arg(host).arg(port).arg(apiStr);
    request.setUrl(QUrl(url));
    request.setRawHeader("Content-Type","application/json");
    if(!token.isEmpty())
        request.setRawHeader("Authorization", QString("token %1").arg(token).toUtf8());
    if (sslConfig != nullptr)
        request.setSslConfiguration(*sslConfig);

    return request;
}


//TODO: maybe obsolete
QByteArray Requester::variantMapToJson(QVariantMap data)
{
    QJsonDocument postDataDoc = QJsonDocument::fromVariant(data);
    QByteArray postDataByteArray = postDataDoc.toJson();

    return postDataByteArray;
}

void Requester::onFinishRequest(QNetworkReply* reply)
{
    qDebug() << "In finished";

    //qDebug() << reply->url();
    if(reply->error() != QNetworkReply::NoError)
    {
        qDebug() << reply->url() << " " << reply->error();
        return;
    }

    //if it's login request
    if(reply->url().toString().endsWith("/api/login"))
    {
        qDebug() << "Processing authorization reply";
        processAuthorizationRequest(reply);
        return;
    }

    //if it's profile info request
    if(reply->url().toString().endsWith("/api/profile-info"))
    {
        qDebug() << "Processing profile info reply";
        return;
    }
    /*
    QByteArray r = reply->readAll();

    QJsonDocument doc = QJsonDocument::fromJson(r, &error);
    qDebug() << doc.object().value("status");
    */
}

void Requester::processAuthorizationRequest(QNetworkReply *reply)
{
    QByteArray r = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(r);
    if(doc.object().value("status") == "fail")
    {
        qDebug() << "Authorization request failed";
        emit wrongAuthorizationData();
        return;
    }
    else
    {
        QString token  = doc.object().value("token").toString();
        Session::getInstance()->setToken(token);
        emit successfulyAuthorized();
    }
}
