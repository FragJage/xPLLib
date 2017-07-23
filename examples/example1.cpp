/***********************************************************************************************/
/**                                                                                           **/
/** EXAMPLE 1                                                                                 **/
/**                                                                                           **/
/** Make and parse xPL Messages                                                               **/
/**                                                                                           **/
/***********************************************************************************************/

#include <iostream>
#include "Schemas/SchemaObject.h"
#include "Schemas/SchemaHbeat.h"
#include "Schemas/SchemaControl.h"
#include "Schemas/SchemaSensor.h"

using namespace std;
using namespace xPL;

int main()
{
    string msg;
    SchemaObject sch;

    SchemaHbeatBasic HeartbeatMsg(5);
    msg = HeartbeatMsg.ToMessage("fragxpl-test.default", "*");
    sch.Parse(msg);
    cout << "==================================" << endl;
    cout << "MAKE hbeat xPL message :" << endl;
    cout << msg << endl;
    cout << "----------------------------------" << endl;
    cout << "PARSE hbeat xPL message :" << endl;
    cout << "Class : " << sch.GetClass() << endl;
    cout << "Type : " << sch.GetType() << endl;
    cout << "Interval : " << sch.GetValue("interval") << endl;
    cout << "==================================" << endl << endl << endl;

    SchemaControlBasic ControlMsg("light", SchemaControlBasic::output, "high");
    msg = ControlMsg.ToMessage("fragxpl-test.default", "fragxpl-room.default");
    sch.Parse(msg);
    cout << "==================================" << endl;
    cout << "MAKE control.basic xPL message :" << endl;
    cout << msg << endl;
    cout << "----------------------------------" << endl;
    cout << "PARSE control.basic xPL message :" << endl;
    cout << "Class : " << sch.GetClass() << endl;
    cout << "Type : " << sch.GetType() << endl;
    cout << "Device : " << sch.GetValue("device") << endl;
    cout << "Current : " << sch.GetValue("current") << endl;
    cout << "==================================" << endl << endl << endl;

    SchemaSensorBasic SensorMsg("temperature", SchemaSensorTypeUtility::temp);
    SensorMsg.SetCurrent("23");
    SensorMsg.SetUnit("C");
    msg = SensorMsg.ToMessage("fragxpl-room.default", "*");
    sch.Parse(msg);
    cout << "==================================" << endl;
    cout << "MAKE sensor.basic xPL message :" << endl;
    cout << msg << endl;
    cout << "----------------------------------" << endl;
    cout << "PARSE sensor.basic xPL message :" << endl;
    cout << "Class : " << sch.GetClass() << endl;
    cout << "Type : " << sch.GetType() << endl;
    cout << "Device : " << sch.GetValue("device") << endl;
    cout << "Current : " << sch.GetValue("current") << endl;
    cout << "==================================" << endl << endl << endl;

    return 0;
}
