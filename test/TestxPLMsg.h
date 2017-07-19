#include <cassert>
#include "UnitTest/UnitTest.h"
#include "xPLLib/Schemas/SchemaControl.h"
#include "xPLLib/Schemas/SchemaConfig.h"
#include "xPLLib/Schemas/SchemaSensor.h"

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
    bool SchemaSensor();

private:
    bool TryControlBasic(xPL::SchemaControlBasic::controlType type, const string& value, int errorNumber);
};
