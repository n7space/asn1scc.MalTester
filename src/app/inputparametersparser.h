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

#include <QCommandLineOption>
#include <QCommandLineParser>

#include <runparameters.h>

namespace MalTester {

class InputParametersParser
{
public:
    InputParametersParser();

    void parse(int argc, char *argv[]);
    RunParameters parameters() const;

private:
    void setupParser();
    void updateRunParams();

    QStringList readFilesList();
    Data::TypeReference readMainStructure();
    QString readAsn1SccPath();
    QStringList readAsn1SccFlags();
    QString readOutputDir();
    RunParameters::CcsdsWrap readCcsdsValue();

    void printUsageAndExit(const QString &message = QString());

    QCommandLineOption m_mainStructure;
    QCommandLineOption m_asn1sccPath;
    QCommandLineOption m_asn1sccFlags;
    QCommandLineOption m_outputDir;
    QCommandLineOption m_wrapAsCcsds;

    QCommandLineParser m_parser;
    RunParameters m_params;
};

} // namespace MalTester
