#include <cassert>
#include "UnitTest/UnitTest.h"
#include "xPLLib/Schemas/SchemaSensor.h"

using namespace std;

class TestxPLAddress : public TestClass<TestxPLAddress>
{
public:
    TestxPLAddress();
    ~TestxPLAddress();

    bool Constructor();
    bool Exception();
};
