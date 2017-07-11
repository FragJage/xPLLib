#include "TestxPLDevice.h"

using namespace std;

TestxPLDevice::TestxPLDevice() : TestClass("xPLDevice", this)
{
	addTest("Initialisation", &TestxPLDevice::Initialisation);
	addTest("SetAppName", &TestxPLDevice::SetAppName);
	addTest("Instance", &TestxPLDevice::Instance);
	addTest("HBeatConfig", &TestxPLDevice::HBeatConfig);
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
    dev2.Open();
    msg = SimpleSockUDP::GetLastSend(10);
    sch.Parse(msg);
    assert("5"==sch.GetValue("interval"));
    dev2.Close();
    msg = SimpleSockUDP::GetLastSend(10);       //Pass hbeat.end

    return true;
}
