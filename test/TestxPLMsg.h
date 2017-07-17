#include <cassert>
#include "UnitTest/UnitTest.h"

using namespace std;

class TestxPLMsg : public TestClass<TestxPLMsg>
{
public:
    TestxPLMsg();
    ~TestxPLMsg();

    bool ControlBasic();
    bool ControlBasicCheck();
};
