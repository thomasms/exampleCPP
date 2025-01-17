/*
 * Copyright information and license terms for this software can be
 * found in the file LICENSE that is included with the distribution
 */

/**
 * @author mrk
 * @date 2013.07.24
 */


/* Author: Marty Kraimer */

#include <iocsh.h>
#include <pv/pvDatabase.h>
#include <pv/channelProviderLocal.h>

// The following must be the last include for code database uses
#include <epicsExport.h>
#define epicsExportSharedSymbols
#include "pv/exampleSoftRecord.h"

using namespace epics::pvData;
using namespace epics::pvAccess;
using namespace epics::pvDatabase;
using namespace epics::exampleCPP::database;
using namespace std;

static const iocshArg testArg0 = { "recordName", iocshArgString };
static const iocshArg *testArgs[] = {
    &testArg0};

static const iocshFuncDef exampleSoftRecordFuncDef = {"exampleSoftRecordCreate", 1,testArgs};

static void exampleSoftRecordCallFunc(const iocshArgBuf *args)
{
    char *recordName = args[0].sval;
    if(!recordName) {
        throw std::runtime_error("exampleSoftRecordCreate invalid number of arguments");
    }
    ExampleSoftRecordPtr record = ExampleSoftRecord::create(recordName);
    bool result = PVDatabase::getMaster()->addRecord(record);
    if(!result) cout << "recordname" << " not added" << endl;
}

static void exampleSoftRecordRegister(void)
{
    static int firstTime = 1;
    if (firstTime) {
        firstTime = 0;
        iocshRegister(&exampleSoftRecordFuncDef, exampleSoftRecordCallFunc);
    }
}

extern "C" {
    epicsExportRegistrar(exampleSoftRecordRegister);
}
