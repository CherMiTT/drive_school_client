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
    if(reply->url().toString().endsWith("/api/user-info"))
    {
        qDebug() << "Processing profile info reply";
        processUserInfoRequest(reply);
        return;
    }
    if(reply->url().toString().endsWith("/api/add/user"))
    {
        qDebug() << "Processing add user reply";
        processAddUserRequest(reply);
        return;
    }
    if(reply->url().toString().endsWith("/api/all-users"))
    {
        qDebug() << "Processing all users reply";
        processAllUsersRequest(reply);
        return;
    }
    if(reply->url().toString().endsWith("/api/all-instructors"))
    {
        qDebug() << "Processing all instructors reply";
        processInstructorsRequest(reply);
        return;
    }
    if(reply->url().toString().endsWith("/api/all-students"))
    {
        qDebug() << "Processing all students reply";
        processStudentsRequest(reply);
        return;
    }
    if(reply->url().toString().endsWith("/api/all-admins"))
    {
        qDebug() << "Processing all admins reply";
        processAdminsRequest(reply);
        return;
    }
    if(reply->url().toString().endsWith("/api/all-groups"))
    {
        qDebug() << "Processing groups reply";
        processGroupsRequest(reply);
        return;
    }
    if(reply->url().toString().endsWith("/api/group-list"))
    {
        qDebug() << "Processing group list";
        processGroupListRequest(reply);
        return;
    }
    if(reply->url().toString().endsWith("/api/all-cars"))
    {
        qDebug() << "Processing cars reply";
        processCarsRequest(reply);
        return;
    }
    if(reply->url().toString().endsWith("/api/all-rooms"))
    {
        qDebug() << "Processing rooms reply";
        processRoomsRequest(reply);
        return;
    }
    if(reply->url().toString().endsWith("/api/add/car"))
    {
        qDebug() << "Processing add car";
        processAddCarRequest(reply);
        return;
    }
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
        QString token = doc.object().value("token").toString();
        Session::getInstance()->setToken(token);
        emit successfullyAuthorized();
    }
}

void Requester::processUserInfoRequest(QNetworkReply *reply)
{
    QByteArray r = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(r);
    if(doc.object().value("status") == "fail")
    {
        qDebug() << "User info request failed";
        return;
    }
    else
    {
        QString roleStr = doc.object().value("role").toString();
        Roles role;
        if(roleStr == "a") role = Roles::ADMIN;
        else if(roleStr == "i") role = Roles::INSTRUCTOR;
        else role = Roles::STUDENT;

        Session::getInstance()->setUserInfo(doc.object().value("first_name").toString(),
                                            doc.object().value("middle_name").toString(),
                                            doc.object().value("last_name").toString(),
                                            role);
        emit successfullyGotUserInfo();
    }

}

void Requester::processAddUserRequest(QNetworkReply *reply)
{
    QByteArray r = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(r);
    if(doc.object().value("status") == "fail")
    {
        qDebug() << "Failed to add user";
        emit addUserResult(false);
        return;
    }
    else
    {
        qDebug() << "User added successfully";
        emit addUserResult(true);
        return;
    }
}

void Requester::processAllUsersRequest(QNetworkReply *reply)
{
    QByteArray r = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(r);
    if(doc.object().value("status") == "fail")
    {
        qDebug() << "Failed to get information";
        return;
    }

    QJsonArray arr = doc.array();
    emit showAllUsersArray(arr);
}

void Requester::processAdminsRequest(QNetworkReply *reply)
{
    QByteArray r = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(r);
    if(doc.object().value("status") == "fail")
    {
        qDebug() << "Failed to get information";
        return;
    }

    QJsonArray arr = doc.array();
    emit showAdminsArray(arr);
}

void Requester::processInstructorsRequest(QNetworkReply *reply)
{
    QByteArray r = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(r);
    if(doc.object().value("status") == "fail")
    {
        qDebug() << "Failed to get information";
        return;
    }

    QJsonArray arr = doc.array();
    emit showIstructorsArray(arr);
}

void Requester::processStudentsRequest(QNetworkReply *reply)
{
    QByteArray r = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(r);
    if(doc.object().value("status") == "fail")
    {
        qDebug() << "Failed to get information";
        return;
    }

    QJsonArray arr = doc.array();
    emit showStudentsArray(arr);
}

void Requester::processGroupsRequest(QNetworkReply *reply)
{
    QByteArray r = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(r);
    if(doc.object().value("status") == "fail")
    {
        qDebug() << "Failed to get information";
        return;
    }

    QJsonArray arr = doc.array();
    emit showGroupsArray(arr);
}

void Requester::processCarsRequest(QNetworkReply *reply)
{
    QByteArray r = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(r);
    if(doc.object().value("status") == "fail")
    {
        qDebug() << "Failed to get information";
        return;
    }

    QJsonArray arr = doc.array();
    emit showCarsArray(arr);
}

void Requester::processRoomsRequest(QNetworkReply *reply)
{
    QByteArray r = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(r);
    if(doc.object().value("status") == "fail")
    {
        qDebug() << "Failed to get information";
        return;
    }

    QJsonArray arr = doc.array();
    emit showRoomsArray(arr);
}

void Requester::processGroupListRequest(QNetworkReply *reply)
{
    QByteArray r = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(r);
    if(doc.object().value("status") == "fail")
    {
        qDebug() << "Failed to get information";
        return;
    }

    QJsonArray arr = doc.array();
    QStringList groups;
    for(int i = 0; i < arr.count(); i++)
    {
        QJsonObject o = arr[i].toObject();
        groups << o.value("group").toString();
    }
    emit getStudentGroup(groups);
}

void Requester::processAddCarRequest(QNetworkReply *reply)
{
    QByteArray r = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(r);
    if(doc.object().value("status") == "fail")
    {
        qDebug() << "Failed to get information";
        return;
    }
}
