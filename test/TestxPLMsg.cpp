#include "TestxPLMsg.h"

using namespace std;

TestxPLMsg::TestxPLMsg() : TestClass("xPLMsg", this)
{
	addTest("SchemaObject", &TestxPLMsg::SchemaObject);
	addTest("ControlBasic", &TestxPLMsg::ControlBasic);
	addTest("ControlBasicCheck", &TestxPLMsg::ControlBasicCheck);
	addTest("ControlBasicThrow", &TestxPLMsg::ControlBasicThrow);
	addTest("SchemaConfig", &TestxPLMsg::SchemaConfig);
	addTest("SchemaSensor", &TestxPLMsg::SchemaSensor);
	addTest("SchemaSensorType", &TestxPLMsg::SchemaSensorType);
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

    scb.SetDeviceType(xPL::SchemaControlBasic::controlType::manual);
    scb.Check();

    scb.SetDeviceType(xPL::SchemaControlBasic::controlType::infrared);
    scb.SetCurrent("send");
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

bool TestxPLMsg::TryControlBasic(xPL::SchemaControlBasic::controlType type, const string& value, int errorNumber)
{
    xPL::SchemaControlBasic scb;
    bool isOK;


    scb.SetDeviceName("Ctrl1");
    scb.SetDeviceType(type);
    scb.SetCurrent(value);
    isOK = false;
    try
    {
        scb.Check();
    }
    catch(const xPL::SchemaControlBasic::Exception &e)
    {
        if(e.GetNumber()==errorNumber) isOK = true;
    }

    return isOK;
}

bool TestxPLMsg::ControlBasicThrow()
{
    xPL::SchemaControlBasic scb;
    scb.SetDeviceName("Ctrl1");

    assert(true==TryControlBasic(xPL::SchemaControlBasic::controlType::unset, "", 0x0101));
    assert(true==TryControlBasic(xPL::SchemaControlBasic::controlType::balance, "255", 0x0102));
    assert(true==TryControlBasic(xPL::SchemaControlBasic::controlType::flag, "zzz", 0x0103));
    assert(true==TryControlBasic(xPL::SchemaControlBasic::controlType::infrared, "zzz", 0x0104));
    assert(true==TryControlBasic(xPL::SchemaControlBasic::controlType::input, "zzz", 0x0105));
    assert(true==TryControlBasic(xPL::SchemaControlBasic::controlType::macro, "zzz", 0x0106));
    assert(true==TryControlBasic(xPL::SchemaControlBasic::controlType::mute, "zzz", 0x0107));
    assert(true==TryControlBasic(xPL::SchemaControlBasic::controlType::output, "zzz", 0x0108));
    assert(true==TryControlBasic(xPL::SchemaControlBasic::controlType::variable, "zzz", 0x0109));
    assert(true==TryControlBasic(xPL::SchemaControlBasic::controlType::periodic, "zzz", 0x010A));
    assert(true==TryControlBasic(xPL::SchemaControlBasic::controlType::scheduled, "zzz", 0x0110));
    assert(true==TryControlBasic(xPL::SchemaControlBasic::controlType::slider, "-300", 0x0111));
    assert(true==TryControlBasic(xPL::SchemaControlBasic::controlType::timer, "zzz", 0x0112));

    return true;
}

bool TestxPLMsg::SchemaConfig()
{
    xPL::SchemaConfigEnd sce;
    assert("config"==sce.GetClass());
    assert("end"==sce.GetType());

    xPL::SchemaConfigBasic scb;
    assert("config"==scb.GetClass());
    assert("basic"==scb.GetType());

    xPL::SchemaConfigApp sca;
    assert("config"==sca.GetClass());
    assert("app"==sca.GetType());

    return true;
}

bool TestxPLMsg::SchemaSensor()
{
    xPL::SchemaSensorBasic ssb("sensor1", xPL::SchemaSensorTypeUtility::count, "13.2", "V");
    assert("sensor1"==ssb.GetValue("device"));
    assert("count"==ssb.GetValue("type"));
    assert(13.2F==ssb.GetCurrent());
    assert("V"==ssb.GetValue("unit"));

    ssb.SetDevice("sensorA", xPL::SchemaSensorTypeUtility::fan);
    assert("sensorA"==ssb.GetValue("device"));
    assert("fan"==ssb.GetValue("type"));

    xPL::SchemaSensorRequest ssr;
    ssr.SetDeviceName("sensor2");
    assert("sensor2"==ssr.GetValue("device"));
    ssr.SetDeviceType(xPL::SchemaSensorTypeUtility::generic);
    assert("generic"==ssr.GetValue("type"));
    ssr.SetDevice("sensorB", xPL::SchemaSensorTypeUtility::illuminance);
    assert("sensorB"==ssr.GetValue("device"));
    assert("illuminance"==ssr.GetValue("type"));

    return true;
}

bool TestxPLMsg::SchemaSensorType()
{
    assert("unset"==xPL::SchemaSensorTypeUtility::ToString(xPL::SchemaSensorTypeUtility::unset));
    assert("input"==xPL::SchemaSensorTypeUtility::ToString(xPL::SchemaSensorTypeUtility::input));
    assert("output"==xPL::SchemaSensorTypeUtility::ToString(xPL::SchemaSensorTypeUtility::output));
    assert("power"==xPL::SchemaSensorTypeUtility::ToString(xPL::SchemaSensorTypeUtility::power));
    assert("pressure"==xPL::SchemaSensorTypeUtility::ToString(xPL::SchemaSensorTypeUtility::pressure));
    assert("setpoint"==xPL::SchemaSensorTypeUtility::ToString(xPL::SchemaSensorTypeUtility::setpoint));
    assert("speed"==xPL::SchemaSensorTypeUtility::ToString(xPL::SchemaSensorTypeUtility::speed));
    assert("temp"==xPL::SchemaSensorTypeUtility::ToString(xPL::SchemaSensorTypeUtility::temp));
    assert("uv"==xPL::SchemaSensorTypeUtility::ToString(xPL::SchemaSensorTypeUtility::uv));
    assert("voltage"==xPL::SchemaSensorTypeUtility::ToString(xPL::SchemaSensorTypeUtility::voltage));
    assert("volume"==xPL::SchemaSensorTypeUtility::ToString(xPL::SchemaSensorTypeUtility::volume));
    assert("weight"==xPL::SchemaSensorTypeUtility::ToString(xPL::SchemaSensorTypeUtility::weight));

    return true;
}
