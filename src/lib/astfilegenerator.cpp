/****************************************************************************
**
** Copyright (C) 2018 N7 Space sp. z o. o.
** Contact: http://n7space.com
**
** This file is part of ASN.1/ACN MalTester - Tool for generating test cases
** based on ASN.1/ACN models and simulating malformed or malicious data.
**
** Tool was developed under a m_processogramme and funded by
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
** along with this m_processogram.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/

#include "astfilegenerator.h"

using namespace MalTester;

static const int PROCESS_TIMEOUT_MS = 5000; // TODO: place for default timeout value (if needed)

AstFileGenerator::AstFileGenerator(const RunParameters &params, const QString &outputPath)
    : m_params(params)
    , m_outputPath(outputPath)
    , m_process(nullptr)
{}

AstFileGenerator::~AstFileGenerator()
{
    m_process->close();
}

AstFileGenerator::State AstFileGenerator::generateAstFile()
{
    m_process.reset(createProcess());
    m_process->start();
    return m_process->waitForFinished(PROCESS_TIMEOUT_MS) ? processFinished() : handleTimeout();
}

QProcess *AstFileGenerator::createProcess() const
{
    auto pr = new QProcess;

    pr->setProgram(m_params.m_asn1SccCommand);
    pr->setArguments(createRunArgs());
    pr->setProcessChannelMode(QProcess::MergedChannels);

    return pr;
}

QStringList AstFileGenerator::createRunArgs() const
{
    return QStringList() << astArg() << outputPathArg() << inputFilesArg();
}

QString AstFileGenerator::astArg() const
{
    return QLatin1String("--xml-ast");
}

QString AstFileGenerator::outputPathArg() const
{
    return m_outputPath;
}

QStringList AstFileGenerator::inputFilesArg() const
{
    return m_params.m_inputFiles;
}

AstFileGenerator::State AstFileGenerator::processFinished() const
{
    switch (m_process->exitStatus()) {
    case (QProcess::NormalExit):
        return handleNormalExit();
    case (QProcess::CrashExit):
        return handleCrashExit();
    default:
        return State::Unknown;
    }
}

AstFileGenerator::State AstFileGenerator::handleNormalExit() const
{
    if (m_process->exitCode() != 0) {
        writeMessage("Build failed");
        return State::BuildFailed;
    }

    return State::BuildSuccess;
}

AstFileGenerator::State AstFileGenerator::handleCrashExit() const
{
    writeMessage("Crashed");
    return State::ProcessCrashed;
}

AstFileGenerator::State AstFileGenerator::handleTimeout() const
{
    writeMessage("Timeouted");
    return State::ProcessTimeouted;
}

void AstFileGenerator::writeMessage(const QString &message) const
{
    auto fullMsg = m_params.m_asn1SccCommand + ": " + message;

    fputs(qPrintable(m_process->readAll()), stderr);
    fputs("\n\n", stderr);
    fputs(qPrintable(fullMsg), stderr);
    fputs("\n\n", stderr);
}
