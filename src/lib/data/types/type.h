/****************************************************************************
**
** Copyright (C) 2018 N7 Space sp. z o. o.
** Contact: http://n7space.com
**
** This file is part of ASN.1/ACN MalTester - Tool for generating test cases
** based on ASN.1/ACN models and simulating malformed or malicious data.
**
** Tool was developed under a programme and funded by
** European Space Agency.
**
** This Tool is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This Tool is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/
#pragma once

#include <QString>

#include <data/acnparameters.h>
#include <data/constraint.h>

namespace MalTester {
namespace Data {
namespace Types {

class Type
{
public:
    Type()
        : m_constraint(nullptr)
        , m_acnParams(nullptr)
    {}

    virtual ~Type()
    {
        delete m_constraint;
        delete m_acnParams;
    }

    virtual QString name() const = 0;
    virtual QString label() const = 0;

    Constraint *constraint() const { return m_constraint; }
    AcnParameters *acnParams() const { return m_acnParams; }

protected:
    Constraint *m_constraint;
    AcnParameters *m_acnParams;

private:
    virtual QString baseIconFile() const = 0;
};

} // namespace Types
} // namespace Data
} // namespace MalTester
