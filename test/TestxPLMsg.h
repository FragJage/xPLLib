#include <cassert>
#include "UnitTest/UnitTest.h"
#include "xPLLib/Schemas/SchemaControl.h"
#include "xPLLib/Schemas/SchemaConfig.h"

using namespace std;

class TestxPLMsg : public TestClass<TestxPLMsg>
{
public:
    TestxPLMsg();
    ~TestxPLMsg();

    bool SchemaObject();
    bool ControlBasic();
    bool ControlBasicCheck();
    bool ControlBasicThrow();
    bool SchemaConfig();

private:
    bool TryControlBasic(xPL::SchemaControlBasic::controlType type, const string& value, int errorNumber);
};
