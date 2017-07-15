#include "TestxPLMsg.h"
#include "xPLLib/Schemas/SchemaControl.h"

using namespace std;

TestxPLMsg::TestxPLMsg() : TestClass("xPLMsg", this)
{
	addTest("ControlBasic", &TestxPLMsg::ControlBasic);
}

TestxPLMsg::~TestxPLMsg()
{
}

bool TestxPLMsg::ControlBasic()
{
    xPL::SchemaControlBasic scb1;
    xPL::SchemaControlBasic scb2;
    xPL::SchemaControlBasic scb3("Ctrl3", xPL::SchemaControlBasic::controlType::flag);
    xPL::SchemaControlBasic scb4("Ctrl4", xPL::SchemaControlBasic::controlType::slider, "127");

    scb1.SetDeviceName("Ctrl1");
    scb1.SetDeviceType(xPL::SchemaControlBasic::controlType::balance);
    scb1.SetCurrent("12");

    scb2.SetDeviceName("Ctrl2");
    scb2.SetDeviceType("variable");
    scb2.SetCurrent("24");

    scb3.SetFlag(xPL::SchemaControlBasic::flagSet::clear);

    scb1.Check();
    scb2.Check();
    scb3.Check();
    scb4.Check();

    assert("12"==scb1.GetCurrent());
    assert("24"==scb2.GetCurrent());
    assert("clear"==scb3.GetCurrent());
    assert("127"==scb4.GetCurrent());

    return true;
}
