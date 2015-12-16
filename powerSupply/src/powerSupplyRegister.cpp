// Copyright information and license terms for this software can be
// found in the file LICENSE that is included with the distribution

/*powerSupplyRegister.cpp */

/**
 * @author mrk
 * @date 2013.07.24
 */


/* Author: Marty Kraimer */

#include <cstddef>
#include <cstdlib>
#include <cstddef>
#include <string>
#include <cstdio>
#include <memory>
#include <iostream>

#include <cantProceed.h>
#include <epicsStdio.h>
#include <epicsMutex.h>
#include <epicsEvent.h>
#include <epicsThread.h>
#include <iocsh.h>

#include <pv/pvIntrospect.h>
#include <pv/pvData.h>
#include <pv/pvAccess.h>
#include <pv/pvDatabase.h>

#include <epicsExport.h>
#include <pv/powerSupply.h>

using namespace epics::pvData;
using namespace epics::pvAccess;
using namespace epics::pvDatabase;
using namespace std;


static const iocshArg testArg0 = { "recordName", iocshArgString };
static const iocshArg *testArgs[] = {
    &testArg0};

static const iocshFuncDef powerSupplyFuncDef = {
    "powerSupplyCreateRecord", 1, testArgs};
static void powerSupplyCallFunc(const iocshArgBuf *args)
{
    char *recordName = args[0].sval;
    if(!recordName) {
        throw std::runtime_error("powerSupplyCreateRecord invalid number of arguments");
    }
cout << "powerSupplyCreateRecord " << recordName << endl;
    PowerSupplyPtr record = PowerSupply::create(recordName);
    bool result = PVDatabase::getMaster()->addRecord(record);
    if(!result) cout << "recordname" << " not added" << endl;
}

static void powerSupplyRegister(void)
{
    static int firstTime = 1;
cout << "powerSupplyRegister firstTime " << firstTime << endl;
    if (firstTime) {
        firstTime = 0;
        iocshRegister(&powerSupplyFuncDef, powerSupplyCallFunc);
    }
}

extern "C" {
    epicsExportRegistrar(powerSupplyRegister);
}
