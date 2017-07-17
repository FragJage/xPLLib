#include <cassert>
#include "xPLLib/xPLDevice.h"
#include "UnitTest/UnitTest.h"

using namespace std;

class TestxPLDevice : public TestClass<TestxPLDevice>
{
public:
    TestxPLDevice();
    ~TestxPLDevice();

    bool Initialisation();
    bool InitException();
    bool SetAppName();
    bool Instance();
    bool HBeatConfig();
    bool GroupsFeature();
    bool FiltersFeature();
    bool WaitRecv();
    bool MsgAnswer();
    bool LogCoverage();
    bool TCPPort();
    bool isDevice();

private:
    bool TryInit(string vendor, string device, string instance, int errorNumber);
    bool TryInstance(string instance, int errorNumber);
};
