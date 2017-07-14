#include <cassert>
#include "UnitTest/UnitTest.h"
#include "xPLLib/xPLDevCfg.h"
#include "xPLLib/Extensions/AdvanceConfig.h"

using namespace std;

class TestxPLExtAdvConfig : public TestClass<TestxPLExtAdvConfig>
{
public:
    TestxPLExtAdvConfig();
    ~TestxPLExtAdvConfig();

    bool Initialisation();
    bool List();
    bool Current();
    bool Request();
    bool RequestSingle();
    bool Delete();

private:
    xPL::xPLDevCfg m_xPLDevice;
    xPL::AdvanceConfig m_AdvanceConfig;
};
