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

#include <QObject>
#include <QTest>

#include "astxmlconstraintparser_tests.h"
#include "astxmlparser_tests.h"
#include "nodereconstructingvisitor_tests.h"
#include "reconstructor_tests.h"

#include "data/constraints/printingvisitor_tests.h"

#include "data/range_tests.h"
#include "data/rangelist_tests.h"

int main(int argc, char *argv[])
{
    int ret = 0;
    const auto runTest = [&ret, argc, argv](QObject *obj) {
        ret += QTest::qExec(obj, argc, argv);
        delete obj;
    };

    runTest(new MalTester::Tests::AstXmlParserTests);
    runTest(new MalTester::Tests::NodeReconstructingVisitorTests);
    runTest(new MalTester::Tests::ReconstructorTests);
    runTest(new MalTester::Tests::AstXmlConstraintParserTests);
    runTest(new MalTester::Data::Tests::RangeTests);
    runTest(new MalTester::Data::Tests::RangeListTests);
    runTest(new MalTester::Data::Constraints::Tests::PrintingVisitorTests);

    return ret;
}
