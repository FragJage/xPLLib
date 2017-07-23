#include <cassert>
#include "xPLLib/Schemas/SchemaSensor.h"
#include "UnitTest/UnitTest.h"

using namespace std;

class TestxPLAddress : public TestClass<TestxPLAddress>
{
public:
    TestxPLAddress();
    ~TestxPLAddress();

    bool Constructor();
    bool Exception();
};
