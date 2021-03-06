#include <cassert>
#include "xPLLib/xPLDevCfg.h"
#include "UnitTest/UnitTest.h"

using namespace std;

class TestxPLDevCfg : public TestClass<TestxPLDevCfg>
{
public:
    TestxPLDevCfg();
    ~TestxPLDevCfg();

    bool GetConfigList();
    bool SetConfig();
    bool GetCurrentConfig();
    bool LoadConfig();
    bool GetConfigItem();
    bool RemoveConfig();

private:
    xPL::xPLDevCfg m_xPLDevice;
};
