/*!
* \file
* \brief Header file for current session of the program
* \author CherMiTT
* \date	09.04.2021
* \version 1.0
*/

#ifndef SESSION_H
#define SESSION_H

#include <QString>
#include <QDateTime>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonDocument>

#include "requester.h"

/*!
 * \brief singleton class of current session
 */
class Session
{
public:
    static void updateSession(const QString& login, const QString& password);
    [[nodiscard]] static QByteArray getAuthorizationJson();
    [[nodiscard]] static Requester *getRequester();
    [[nodiscard]] static Session *getInstance();
    void setToken(QString token);
    [[nodiscard]] QString getToken();

private:
    Session();

    QString login;
    QString password;
    QString token;
    QDateTime lastUpdateTime;
    Requester *requester;

    static Session* instance;

};

#endif // SESSION_H
