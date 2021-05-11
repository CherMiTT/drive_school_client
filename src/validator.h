/*!
* \file
* \brief Header file for validator class
* \author CherMiTT
* \date	08.04.2021
* \version 1.0
*/

#ifndef VALIDATOR_H
#define VALIDATOR_H

#pragma once

#include <QString>
#include <QRegularExpression>

/*!
 * \brief class for validating user input
 */

class Validator
{
public:
    static bool validateLogin(const QString&);
    static bool validatePassword(const QString&);
};

#endif // VALIDATOR_H
