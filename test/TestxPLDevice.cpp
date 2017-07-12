#include "TestxPLDevice.h"

using namespace std;

TestxPLDevice::TestxPLDevice() : TestClass("xPLDevice", this)
{
	addTest("Initialisation", &TestxPLDevice::Initialisation);
	addTest("SetAppName", &TestxPLDevice::SetAppName);
	addTest("Instance", &TestxPLDevice::Instance);
	addTest("HBeatConfig", &TestxPLDevice::HBeatConfig);
	addTest("GroupsFeature", &TestxPLDevice::GroupsFeature);
	addTest("FiltersFeature", &TestxPLDevice::FiltersFeature);
	addTest("WaitRecv", &TestxPLDevice::WaitRecv);
}

TestxPLDevice::~TestxPLDevice()
{
}

bool TestxPLDevice::Initialisation()
{
    string msg;
    xPL::SchemaObject sch;

    xPL::xPLDevice dev1;
    dev1.Initialisation("fragxpl", "test", "def1");
    dev1.Open();
    msg = SimpleSockUDP::GetLastSend(10);
    sch.Parse(msg);
    assert("fragxpl-test.def1"==sch.GetSource());
    dev1.Close();
    msg = SimpleSockUDP::GetLastSend(10);       //Pass hbeat.end

    xPL::xPLDevice dev2("fragxpl", "test");
    dev2.Open();
    msg = SimpleSockUDP::GetLastSend(10);
    sch.Parse(msg);
    assert("fragxpl-test.default"==sch.GetSource());
    dev2.Close();
    msg = SimpleSockUDP::GetLastSend(10);       //Pass hbeat.end


    xPL::xPLDevice dev3("fragxpl", "test", "def3");
    dev3.Open();
    msg = SimpleSockUDP::GetLastSend(10);
    sch.Parse(msg);
    assert("fragxpl-test.def3"==sch.GetSource());
    dev3.Close();
    msg = SimpleSockUDP::GetLastSend(10);       //Pass hbeat.end

    return true;
}

bool TestxPLDevice::SetAppName()
{
    string msg;
    xPL::SchemaObject sch;

    xPL::xPLDevice dev("fragxpl", "test");
    dev.SetAppName("MyTest", "1.0");
    dev.Open();
    msg = SimpleSockUDP::GetLastSend(10);
    sch.Parse(msg);
    assert("MyTest"==sch.GetValue("appname"));
    assert("1.0"==sch.GetValue("version"));
    dev.Close();
    msg = SimpleSockUDP::GetLastSend(10);       //Pass hbeat.end

    return true;
}

bool TestxPLDevice::Instance()
{
    string msg;
    xPL::SchemaObject sch;

    xPL::xPLDevice dev("fragxpl", "test");
    dev.SetInstance("MyInstance");
    dev.Open();
    msg = SimpleSockUDP::GetLastSend(10);
    sch.Parse(msg);
    assert("fragxpl-test.MyInstance"==sch.GetSource());
    assert("MyInstance"==dev.GetInstance());
    dev.SetInstance("MyInstance");              //Increase code coverage
    assert("MyInstance"==dev.GetInstance());
    dev.Close();
    msg = SimpleSockUDP::GetLastSend(10);       //Pass hbeat.end

    return true;
}

bool TestxPLDevice::HBeatConfig()
{
    string msg;
    xPL::SchemaObject sch;
    xPL::xPLDevice dev1("fragxpl", "test1");
    xPL::xPLDevice dev2("fragxpl", "test2");
    xPL::xPLDevice dev3("fragxpl", "test3");

    dev1.SetHeartBeatInterval(6);
    dev1.SetHeartBeatType(xPL::xPLDevice::HeartBeatType::HeartBeatBASIC);
    dev1.Open();
    msg = SimpleSockUDP::GetLastSend(10);
    sch.Parse(msg);
    assert("hbeat"==sch.GetClass());
    assert("basic"==sch.GetType());
    assert("6"==sch.GetValue("interval"));
    assert(xPL::xPLDevice::HeartBeatType::HeartBeatBASIC==dev1.GetHeartBeatType());
    dev1.Close();
    msg = SimpleSockUDP::GetLastSend(10);       //Pass hbeat.end

    dev2.SetHeartBeatInterval(4);
    dev2.SetHeartBeatType(xPL::xPLDevice::HeartBeatType::ConfigBASIC);
    dev2.Open();
    msg = SimpleSockUDP::GetLastSend(10);
    sch.Parse(msg);
    assert("5"==sch.GetValue("interval"));
    assert(xPL::xPLDevice::HeartBeatType::ConfigBASIC==dev2.GetHeartBeatType());
    dev2.Close();
    msg = SimpleSockUDP::GetLastSend(10);       //Pass hbeat.end

    dev3.SetHeartBeatInterval(31);
    dev3.SetHeartBeatType(xPL::xPLDevice::HeartBeatType::HeartBeatAPP);
    dev3.Open();
    msg = SimpleSockUDP::GetLastSend(10);
    sch.Parse(msg);
    assert("30"==sch.GetValue("interval"));
    assert(xPL::xPLDevice::HeartBeatType::HeartBeatAPP==dev3.GetHeartBeatType());
    dev3.Close();
    msg = SimpleSockUDP::GetLastSend(10);       //Pass hbeat.end

    return true;
}

bool TestxPLDevice::GroupsFeature()
{
    set<string> groups;
    xPL::xPLDevice dev("fragxpl", "test");
    xPL::SchemaObject sch(xPL::ISchema::MsgType::trig, "sensor", "basic");

    sch.SetTarget("fragxpl-other.default");
    assert(false==dev.MsgForMe(sch));

    groups.insert("xpl-group.bedroom");
    groups.insert("xpl-group.livingroom");
    dev.SetGroups(groups);

    sch.SetTarget("fragxpl-other.default");
    assert(false==dev.MsgForMe(sch));
    sch.SetTarget("xpl-group.otherroom");
    assert(false==dev.MsgForMe(sch));
    sch.SetTarget("xpl-group.bedroom");
    assert(true==dev.MsgForMe(sch));

    return true;
}

bool TestxPLDevice::FiltersFeature()
{
    set<string> filters;
    xPL::xPLDevice dev("fragxpl", "test");
    xPL::SchemaObject sch1(xPL::ISchema::MsgType::trig, "sensor", "basic");
    sch1.SetSource("fragxpl-test.default");
    sch1.SetTarget("*");
    xPL::SchemaObject sch2(xPL::ISchema::MsgType::cmnd, "control", "basic");
    sch2.SetSource("fragxpl-test.default");
    sch2.SetTarget("*");


    assert(true==dev.MsgForMe(sch1));

    filters.insert("xpl-cmnd.remote.basic.fragxpl.test.default");
    filters.insert("xpl-cmnd.control.advance.fragxpl.test.default");
    filters.insert("xpl-cmnd.control.basic.xpl.test.default");
    filters.insert("xpl-cmnd.control.basic.fragxpl.onewire.default");
    filters.insert("xpl-cmnd.control.basic.fragxpl.test.def2");
    filters.insert("xpl-trig.sensor.basic.fragxpl.test.default");
    dev.SetFilters(filters);

    assert(true==dev.MsgForMe(sch1));
    assert(false==dev.MsgForMe(sch2));

    return true;
}

bool TestxPLDevice::WaitRecv()
{
    xPL::xPLDevice dev("fragxpl", "test");
    xPL::SchemaHbeatRequest hbr;
    xPL::SchemaObject sch;
    string msg;

    msg = hbr.ToMessage("fragxpl-other.default", "fragxpl-test.default");
    SimpleSockUDP::SetNextRecv(msg);

    dev.Open();
    dev.WaitRecv(10);
    msg = SimpleSockUDP::GetLastSend(10);
    sch.Parse(msg);
    assert("fragxpl-test.default"==sch.GetSource());
    assert(xPL::ISchema::stat==sch.GetMsgType());
    dev.Close();
    msg = SimpleSockUDP::GetLastSend(10);       //Pass hbeat.end

    return true;
}
