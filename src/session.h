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
    [[nodiscard]] static const Requester* getRequester();

private:
    Session();

    QString login;
    QString password;
    QDateTime lastUpdateTime;
    Requester* requester;

    static Session* instance;
};

#endif // SESSION_H
