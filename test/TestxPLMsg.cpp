#include "TestxPLMsg.h"
#include "xPLLib/Schemas/SchemaControl.h"

using namespace std;

TestxPLMsg::TestxPLMsg() : TestClass("xPLMsg", this)
{
	addTest("SchemaObject", &TestxPLMsg::SchemaObject);
	addTest("ControlBasic", &TestxPLMsg::ControlBasic);
	addTest("ControlBasicCheck", &TestxPLMsg::ControlBasicCheck);
}

TestxPLMsg::~TestxPLMsg()
{
}

bool TestxPLMsg::SchemaObject()
{
    xPL::SchemaObject sch;
    bool isOK;

    assert(1==sch.GetHop());

    sch.SetMsgType("xpl-cmnd");
    assert(xPL::ISchema::cmnd==sch.GetMsgType());

    sch.SetMsgType("xpl-stat");
    assert(xPL::ISchema::stat==sch.GetMsgType());

    sch.SetMsgType("xpl-trig");
    assert(xPL::ISchema::trig==sch.GetMsgType());

    isOK = false;
    try
    {
        sch.SetMsgType("xpl-zzzz");
    }
    catch(const xPL::SchemaObject::Exception &e)
    {
        if(e.GetNumber()==0x0008) isOK = true;
    }
    assert(true==isOK);

    return true;
}
bool TestxPLMsg::ControlBasic()
{
    xPL::SchemaControlBasic scb1;
    xPL::SchemaControlBasic scb2;
    xPL::SchemaControlBasic scb3("Ctrl3", xPL::SchemaControlBasic::controlType::flag);
    xPL::SchemaControlBasic scb4("Ctrl4", xPL::SchemaControlBasic::controlType::slider, "127");
    xPL::SchemaControlBasic scb5;

    scb1.SetDeviceName("Ctrl1");
    scb1.SetDeviceType(xPL::SchemaControlBasic::controlType::balance);
    scb1.SetCurrent("12");

    scb2.SetDeviceName("Ctrl2");
    scb2.SetDeviceType("variable");
    scb2.SetCurrent("24");

    scb3.SetFlag(xPL::SchemaControlBasic::flagSet::clear);

    scb5.SetDeviceName("Ctrl5");
    scb5.SetDeviceType("manual");
    scb5.SetCurrent("MM");

    scb1.Check();
    scb2.Check();
    scb3.Check();
    scb4.Check();

    assert("12"==scb1.GetCurrent());
    assert("24"==scb2.GetCurrent());
    assert("clear"==scb3.GetCurrent());
    assert("127"==scb4.GetCurrent());
    assert("MM"==scb5.GetCurrent());

    return true;
}

bool TestxPLMsg::ControlBasicCheck()
{
    xPL::SchemaControlBasic scb;
    scb.SetDeviceName("Ctrl1");

    scb.SetDeviceType(xPL::SchemaControlBasic::controlType::flag);
    scb.SetFlag(xPL::SchemaControlBasic::flagSet::neutral);
    scb.Check();

    scb.SetDeviceType(xPL::SchemaControlBasic::controlType::infrared);
    scb.SetCurrent("send");
    scb.Check();
    scb.SetCurrent("enable_rx");
    scb.Check();
    scb.SetCurrent("disable_rx");
    scb.Check();
    scb.SetCurrent("enable_tx");
    scb.Check();
    scb.SetCurrent("disable_tx");
    scb.Check();
    scb.SetCurrent("sendx");
    scb.Check();

    scb.SetDeviceType(xPL::SchemaControlBasic::controlType::input);
    scb.SetCurrent("enable");
    scb.Check();
    scb.SetCurrent("disable");
    scb.Check();

    scb.SetDeviceType(xPL::SchemaControlBasic::controlType::macro);
    scb.SetCurrent("enable");
    scb.Check();
    scb.SetCurrent("disable");
    scb.Check();
    scb.SetCurrent("do");
    scb.Check();

    scb.SetDeviceType(xPL::SchemaControlBasic::controlType::mute);
    scb.SetCurrent("yes");
    scb.Check();
    scb.SetCurrent("no");
    scb.Check();

    scb.SetDeviceType(xPL::SchemaControlBasic::controlType::output);
    scb.SetCurrent("enable");
    scb.Check();
    scb.SetCurrent("disable");
    scb.Check();
    scb.SetCurrent("high");
    scb.Check();
    scb.SetCurrent("low");
    scb.Check();
    scb.SetCurrent("toggle");
    scb.Check();
    scb.SetCurrent("pulse");
    scb.Check();

    scb.SetDeviceType(xPL::SchemaControlBasic::controlType::variable);
    scb.SetCurrent("inc");
    scb.Check();
    scb.SetCurrent("dec");
    scb.Check();

    scb.SetDeviceType(xPL::SchemaControlBasic::controlType::periodic);
    scb.SetCurrent("started");
    scb.Check();
    scb.SetCurrent("enable");
    scb.Check();
    scb.SetCurrent("disable");
    scb.Check();

    scb.SetDeviceType(xPL::SchemaControlBasic::controlType::scheduled);
    scb.SetCurrent("started");
    scb.Check();
    scb.SetCurrent("enable");
    scb.Check();
    scb.SetCurrent("disable");
    scb.Check();

    scb.SetDeviceType(xPL::SchemaControlBasic::controlType::timer);
    scb.SetCurrent("went off");
    scb.Check();
    scb.SetCurrent("start");
    scb.Check();
    scb.SetCurrent("stop");
    scb.Check();
    scb.SetCurrent("halt");
    scb.Check();
    scb.SetCurrent("resume");
    scb.Check();

    return true;
}
