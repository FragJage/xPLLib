#include <cassert>
#include "UnitTest/UnitTest.h"
#include "xPLLib/xPLDevCfg.h"
#include "xPLLib/Extensions/Sensors.h"

using namespace std;

class TestxPLExtSensors : public TestClass<TestxPLExtSensors>
{
public:
    TestxPLExtSensors();
    ~TestxPLExtSensors();

    bool AddMessage1();
    bool AddMessage2();
    bool AddMessage3();
    bool AddMessage4();
    bool AddSensorMessage1();
    bool AddSensorMessage2();
    bool GetMessage();
    bool ModifyMessage();
    bool MsgAnswer();
    bool RemoveMessage();
    bool RemoveAllMessages();

private:
    xPL::xPLDevCfg m_xPLDevice;
    xPL::Sensors m_Sensors;
};
