/*!
* \file
* \brief Source file for current session of the program
* \author CherMiTT
* \date	09.04.2021
* \version 1.0
*/

#include "session.h"

Session* Session::instance;

/*!
 * \brief updates parametrs of current session
 * \param login - new login
 * \param password - new password
 */
void Session::updateSession(const QString& login, const QString& password)
{
    if(instance == nullptr)
    {
        instance = new Session();
    }

    instance->login = login;
    instance->password = password;
    instance->lastUpdateTime = QDateTime::currentDateTimeUtc();

    if(instance->requester == nullptr)
    {
        instance->requester = Requester::getInstance();
        instance->requester->initRequester("localhost", 9090, nullptr);
    }
}


/*!
 * \brief provides data package neccessary for authorization
 * \return QByteArray of Json object with login and password
 */
QByteArray Session::getAuthorizationJson()
{
    QJsonObject obj {{"login", instance->login}, {"password", instance->password}};
    return QJsonDocument(obj).toJson();
}

/*!
 * \brief returns pointer to the instance of requester
 * \return pointer to requester
 */
Requester *Session::getRequester()
{
    return instance->requester;
}

Session *Session::getInstance()
{
    if(instance == nullptr)
    {
        instance = new Session();
    }
    return instance;
}

void Session::setToken(QString token)
{
    instance->token = token;
}

QString Session::getToken()
{
    return instance->token;
}

/*!
 * \brief Private constructor of the singleton
 */
Session::Session()
{
    instance = nullptr;
    login = "";
    password = "";
    lastUpdateTime = QDateTime::currentDateTimeUtc();
    token = "";
    requester = nullptr;
}
