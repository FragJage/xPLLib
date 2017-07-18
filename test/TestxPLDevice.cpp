#include "TestxPLDevice.h"
#include "xPLLib/Address.h"

using namespace std;

TestxPLDevice::TestxPLDevice() : TestClass("xPLDevice", this)
{
	addTest("Initialisation", &TestxPLDevice::Initialisation);
	addTest("InitException", &TestxPLDevice::InitException);
	addTest("SetAppName", &TestxPLDevice::SetAppName);
	addTest("Instance", &TestxPLDevice::Instance);
	addTest("HBeatConfig", &TestxPLDevice::HBeatConfig);
	addTest("GroupsFeature", &TestxPLDevice::GroupsFeature);
	addTest("FiltersFeature", &TestxPLDevice::FiltersFeature);
	addTest("WaitRecv", &TestxPLDevice::WaitRecv);
	addTest("MsgAnswer", &TestxPLDevice::MsgAnswer);
	addTest("LogCoverage", &TestxPLDevice::LogCoverage);
	addTest("TCPPort", &TestxPLDevice::TCPPort);
	addTest("isDevice", &TestxPLDevice::isDevice);

    if(remove("test.tmp")==0)
        cout << termcolor::yellow << "Remove old log file" << endl << termcolor::grey;
}

TestxPLDevice::~TestxPLDevice()
{
    if(remove("test.tmp")!=0)
        cout << termcolor::red << "Unable to remove log file" << endl << termcolor::grey;
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

bool TestxPLDevice::TryInit(const string& vendor, const string& device, const string& instance, int errorNumber)
{
    xPL::xPLDevice dev;
    bool isOK;


    dev.SetLogDestination("test.tmp");
    isOK = false;
    try
    {
        dev.Initialisation(vendor, device, instance);
    }
    catch(const xPL::Address::Exception &e)
    {
        if(e.GetNumber()==errorNumber) isOK = true;
    }

    return isOK;
}

bool TestxPLDevice::InitException()
{
    assert(true==TryInit("frag.xpl", "test", "def", 0x0101));
    assert(true==TryInit("fragxpltoolong", "test", "def", 0x0104));
    assert(true==TryInit("fragxpl", "test-1", "def", 0x0102));
    assert(true==TryInit("fragxpl", "testtoolong", "def", 0x0105));
    assert(true==TryInit("fragxpl", "test", "default.1", 0x0103));
    assert(true==TryInit("fragxpl", "test", "defaultverytoolong", 0x0106));

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

bool TestxPLDevice::TryInstance(const string& instance, int errorNumber)
{
    xPL::xPLDevice dev;
    bool isOK;


    dev.SetLogDestination("test.tmp");
    isOK = false;
    try
    {
        dev.SetInstance(instance);
    }
    catch(const xPL::Address::Exception &e)
    {
        if(e.GetNumber()==errorNumber) isOK = true;
    }

    return isOK;

}

bool TestxPLDevice::Instance()
{
    string msg;
    xPL::SchemaObject sch;
    xPL::xPLDevice dev("fragxpl", "test");

    assert(true==TryInstance("instance-1", 0x0103));
    assert(true==TryInstance("verylongdefaultinstance", 0x0106));

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


    dev.Open();
    msg = SimpleSockUDP::GetLastSend(10);       //Pass config.app on start

    msg = hbr.ToMessage("fragxpl-other.default", "fragxpl-test.default");
    SimpleSockUDP::SetNextRecv(msg);
    dev.WaitRecv(10);
    msg = SimpleSockUDP::GetLastSend(10);
    sch.Parse(msg);
    assert("fragxpl-test.default"==sch.GetSource());
    assert("fragxpl-other.default"==sch.TargetAddress.ToString());
    assert(xPL::ISchema::stat==sch.GetMsgType());

    assert(false==dev.WaitRecv(5));
    SimpleSockUDP::SetNextRecv("malformatedxplmessage");
    assert(false==dev.WaitRecv(5));

    dev.Close();
    msg = SimpleSockUDP::GetLastSend(10);       //Pass hbeat.end

    return true;
}

bool TestxPLDevice::MsgAnswer()
{
    xPL::xPLDevice dev("fragxpl", "test");
    xPL::SchemaObject sch1;
    string msg;

    dev.Open();
    msg = SimpleSockUDP::GetLastSend(10);       //Pass config.app on start

    msg = sch1.ToMessage("fragxpl-other.default", "fragxpl-test.default");
    SimpleSockUDP::SetNextRecv(msg);
    dev.WaitRecv(5);
    msg = SimpleSockUDP::GetLastSend(1);
    assert(""==msg);

    sch1.SetMsgType(xPL::ISchema::cmnd);
    sch1.SetClass("hbeat");
    sch1.SetType("app");
    msg = sch1.ToMessage("fragxpl-other.default", "fragxpl-test.default");
    SimpleSockUDP::SetNextRecv(msg);
    dev.WaitRecv(5);
    msg = SimpleSockUDP::GetLastSend(1);
    assert(""==msg);

    sch1.SetType("request");
    msg = sch1.ToMessage("fragxpl-other.default", "fragxpl-test.default");
    SimpleSockUDP::SetNextRecv(msg);
    dev.WaitRecv(5);
    msg = SimpleSockUDP::GetLastSend(1);
    assert(""==msg);

    return true;
}

bool TestxPLDevice::LogCoverage()
{
    xPL::xPLDevice dev("fragxpl", "test");

    dev.SetLogFunction("LogCoverage");
    dev.SetLogDestination("cout");
    dev.SetLogDestination("clog");
    dev.SetLogDestination("test.tmp");

    for(int i=1; i<9; i++) dev.SetLogLevel(i);

    dev.SetConfigFileName("config");

    return true;
}

bool TestxPLDevice::TCPPort()
{
    xPL::xPLDevice dev("fragxpl", "test");

    dev.SetNetworkInterface("eth0");
    dev.SetAnswerAllMsg(true);

    dev.Open();
    SimpleSockUDP::GetLastSend(10);       //Pass config.app on start
    assert(3865==dev.GetTCPPort());
    dev.Close();
    SimpleSockUDP::GetLastSend(10);       //Pass hbeat.end

    SimpleSockUDP::SetPortInUse(3865);
    try
    {
        dev.Open();
    }
    catch(const SimpleSock::Exception &e)
    {
    }

    SimpleSockUDP::GetLastSend(10);       //Pass config.app on start
    assert(49152==dev.GetTCPPort());

    dev.Close();
    SimpleSockUDP::GetLastSend(10);       //Pass hbeat.end

    return true;
}

bool TestxPLDevice::isDevice()
{
    xPL::xPLDevice dev("fragxpl", "test");

    assert(false==dev.isDevice("fragxplother.default:roomtemp"));
    assert(false==dev.isDevice("fragxpl-otherdefault:roomtemp"));
    assert(false==dev.isDevice("fragxpl-other.defaultroomtemp"));
    assert(true==dev.isDevice("fragxpl-other.default:roomtemp"));

    return true;
}
