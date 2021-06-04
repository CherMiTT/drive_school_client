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
 * \brief roles of users enum
 */
enum class Roles
{
    STUDENT,
    INSTRUCTOR,
    ADMIN
};

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
    void setUserInfo(QString first_name, QString middle_name, QString last_name, Roles role);
    [[nodiscard]] Roles getRole() {return instance->role;}
    [[nodiscard]] QString getFirstName() {return instance->first_name;}
    [[nodiscard]] QString getMiddleName() {return instance->middle_name;}
    [[nodiscard]] QString getLastName() {return instance->last_name;}

private:
    Session();

    QString login;
    QString password;
    QString token;
    QDateTime lastUpdateTime;
    Requester *requester;

    QString first_name;
    QString middle_name;
    QString last_name;
    Roles role;

    static Session* instance;
};

#endif // SESSION_H
