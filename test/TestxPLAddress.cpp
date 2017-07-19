#include "TestxPLAddress.h"

using namespace std;

TestxPLAddress::TestxPLAddress() : TestClass("TestxPLAddress", this)
{
	addTest("Constructor", &TestxPLAddress::Constructor);
	addTest("Exception", &TestxPLAddress::Exception);
}

TestxPLAddress::~TestxPLAddress()
{
}

bool TestxPLAddress::Constructor()
{
    xPL::Address adr1("frag1-test1.default1");
    xPL::Address adr2("frag2", "test2", "default2");

    assert("frag1"==adr1.GetVendor());
    assert("test1"==adr1.GetDevice());
    assert("default1"==adr1.GetInstance());
    assert("frag2-test2.default2"==adr2.ToString());

    return true;
}

bool TestxPLAddress::Exception()
{
    xPL::Address adr;
    bool isOK = false;

    try
    {
        adr.ToString();
    }
    catch(const xPL::Address::Exception &e)
    {
        if(e.GetNumber()==0x0109) isOK = true;
    }

    assert(true==isOK);

    return true;
}
