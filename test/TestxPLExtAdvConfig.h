#include <cassert>
#include "xPLLib/xPLDevCfg.h"
#include "xPLLib/Extensions/AdvanceConfig.h"
#include "UnitTest/UnitTest.h"

using namespace std;

class TestxPLExtAdvConfig : public TestClass<TestxPLExtAdvConfig>
{
public:
    TestxPLExtAdvConfig();
    ~TestxPLExtAdvConfig();

    bool Initialisation();
    bool List();
    bool Current();
    bool LoadConfig();
    bool Request();
    bool RequestSingle();
    bool Delete();
    bool NoResponse();
    bool AddConfig();
    bool DeleteConfig();

private:
    xPL::xPLDevCfg m_xPLDevice;
    xPL::AdvanceConfig m_AdvanceConfig;
    map<string, string> m_Config1;
    map<string, string> m_Config2;
};
