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
    bool SetAppName();
    bool Instance();
    bool HBeatConfig();
};
