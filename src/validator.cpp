/*!
* \file
* \brief Code file for validator class
* \author CherMiTT
* \date	08.04.2021
* \version 1.0
*/

#include "validator.h"

/*!
 * \brief validates login
 * \param login - QString of login
 * \return true if login is valid, false otherwise
 *
 * Valid login is:
 *  between 4 and 20 characters
 *  contains only A-Z, a-z, numbers, - and _
 *  starts with letter
 *  does not contain __
 */
bool Validator::validateLogin(const QString& login)
{
    QRegularExpression rx("^[a-zA-Z][a-zA-Z0-9-_]{3,20}$");
    QRegularExpressionMatch m = rx.match(login);
    return (m.hasMatch() and !login.contains("__"));
}

/*!
 * \brief validates password
 * \param password - QString of login
 * \return true if password is valid, false otherwise
 *
 * From stackoverflow:
 * ^                 # start-of-string
 *  (?=.*[0-9])       # a digit must occur at least once
 *  (?=.*[a-z])       # a lower case letter must occur at least once
 *  (?=.*[A-Z])       # an upper case letter must occur at least once
 *  (?=.*[@#$%^&+=])  # a special character must occur at least once
 *  (?=\S+$)          # no whitespace allowed in the entire string
 *  .{8,}             # anything, at least eight places though
 *  $                 # end-of-string
 *
 *  password must be <= 32 characters
 */
bool Validator::validatePassword(const QString& pass)
{
    //TODO:
    return false;
}
