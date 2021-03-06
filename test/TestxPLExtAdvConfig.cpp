#include "TestxPLExtAdvConfig.h"

using namespace std;

TestxPLExtAdvConfig::TestxPLExtAdvConfig() : TestClass("AdvanceConfig", this), m_xPLDevice("fragxpl", "test", "default"), m_AdvanceConfig(&m_xPLDevice)
{
	addTest("Initialisation", &TestxPLExtAdvConfig::Initialisation);
	addTest("List", &TestxPLExtAdvConfig::List);
    addTest("Current", &TestxPLExtAdvConfig::Current);
    addTest("LoadConfig", &TestxPLExtAdvConfig::LoadConfig);
    addTest("Request", &TestxPLExtAdvConfig::Request);
    addTest("RequestSingle", &TestxPLExtAdvConfig::RequestSingle);
    addTest("Delete", &TestxPLExtAdvConfig::Delete);
    addTest("NoResponse", &TestxPLExtAdvConfig::NoResponse);
    addTest("AddConfig", &TestxPLExtAdvConfig::AddConfig);
    addTest("DeleteConfig", &TestxPLExtAdvConfig::DeleteConfig);

	m_xPLDevice.AddExtension(&m_AdvanceConfig);
    m_xPLDevice.Open();
    SimpleSockUDP::GetLastSend(10);       //Pass config.app on start
}

TestxPLExtAdvConfig::~TestxPLExtAdvConfig()
{
    m_xPLDevice.Close();
    SimpleSockUDP::GetLastSend(10);       //Pass hbeat.end
}

bool TestxPLExtAdvConfig::Initialisation()
{
    m_AdvanceConfig.AddFormat("configname", xPL::AdvanceConfig::ParamType::STRING, xPL::AdvanceConfig::ParamList::NONE);
    m_AdvanceConfig.AddFormat("output", xPL::AdvanceConfig::ParamType::DEVICE, xPL::AdvanceConfig::ParamList::NONE);
    m_AdvanceConfig.AddFormat("myinteger", xPL::AdvanceConfig::ParamType::INTEGER, xPL::AdvanceConfig::ParamList::NONE);
    m_AdvanceConfig.AddFormat("myfloat", xPL::AdvanceConfig::ParamType::FLOAT, xPL::AdvanceConfig::ParamList::NONE);
    m_AdvanceConfig.AddFormat("mybool", xPL::AdvanceConfig::ParamType::BOOLEAN, xPL::AdvanceConfig::ParamList::NONE);

    m_Config1["configname"] = "deviceA";
    m_Config1["output"] = "fragxpl-other.default:devA";
    m_Config1["myinteger"] = "1";
    m_Config2["configname"] = "deviceB";
    m_Config2["output"] = "fragxpl-other.default:devB";
    m_Config2["myinteger"] = "2";

    return true;
}

bool TestxPLExtAdvConfig::List()
{
    xPL::SchemaAdvanceConfigListRequest aclr;
    xPL::SchemaObject sch;
    string msg;

    aclr.Check();
    aclr.SetSource("fragxpl-other.default");
    aclr.TargetAddress.SetAddress("fragxpl-test.default");
    m_AdvanceConfig.MsgAnswer(aclr);
    msg = SimpleSockUDP::GetLastSend(10);
    sch.Parse(msg);

    assert("advanceconfig"==sch.GetClass());
    assert("list"==sch.GetType());
    assert("string"==sch.GetValue("configname"));
    assert("device"==sch.GetValue("output"));

    return true;
}

bool TestxPLExtAdvConfig::Current()
{
    xPL::SchemaObject sch1(xPL::ISchema::cmnd, "advanceconfig", "request");
    xPL::SchemaObject sch2(xPL::ISchema::cmnd, "advanceconfig", "request");

    sch1.SetSource("fragxpl-other.default");
    sch1.TargetAddress.SetAddress("fragxpl-test.default");
    sch1.AddValue("configname", "test1");
    sch1.AddValue("output", "fragxpl-other.default:testA");
    m_AdvanceConfig.MsgAnswer(sch1);

    sch2.SetSource("fragxpl-other.default");
    sch2.TargetAddress.SetAddress("fragxpl-test.default");
    sch2.AddValue("configname", "test2");
    sch2.AddValue("output", "fragxpl-other.default:testB");
    m_AdvanceConfig.MsgAnswer(sch2);

    return true;
}

bool TestxPLExtAdvConfig::LoadConfig()
{
    m_xPLDevice.LoadConfig();
    return Current();
}

bool TestxPLExtAdvConfig::Request()
{
    xPL::SchemaAdvanceConfigCurrentCmnd sacc;
    xPL::SchemaObject sch;
    string msg;

    sacc.Check();
    sacc.SetSource("fragxpl-other.default");
    sacc.TargetAddress.SetAddress("fragxpl-test.default");
    m_AdvanceConfig.MsgAnswer(sacc);

    msg = SimpleSockUDP::GetLastSend(10);
    sch.Parse(msg);
    assert("advanceconfig"==sch.GetClass());
    assert("current"==sch.GetType());
    assert("test1"==sch.GetValue("configname"));
    assert("fragxpl-other.default:testA"==sch.GetValue("output"));

    msg = SimpleSockUDP::GetLastSend(10);
    sch.Parse(msg);
    assert("advanceconfig"==sch.GetClass());
    assert("current"==sch.GetType());
    assert("test2"==sch.GetValue("configname"));

    return true;
}

bool TestxPLExtAdvConfig::RequestSingle()
{
    xPL::SchemaObject sch1(xPL::ISchema::cmnd, "advanceconfig", "request");

    sch1.SetSource("fragxpl-other.default");
    sch1.TargetAddress.SetAddress("fragxpl-test.default");
    sch1.AddValue("configname", "test3");
    sch1.AddValue("output", "fragxpl-other.default:testC");
    m_AdvanceConfig.MsgAnswer(sch1);


    xPL::SchemaAdvanceConfigCurrentCmnd sacc;
    xPL::SchemaObject sch;
    string msg;

    sacc.SetSource("fragxpl-other.default");
    sacc.TargetAddress.SetAddress("fragxpl-test.default");
    sacc.AddValue("configname", "test2");
    m_AdvanceConfig.MsgAnswer(sacc);

    msg = SimpleSockUDP::GetLastSend(10);
    sch.Parse(msg);
    assert("advanceconfig"==sch.GetClass());
    assert("current"==sch.GetType());
    assert("test2"==sch.GetValue("configname"));
    assert("fragxpl-other.default:testB"==sch.GetValue("output"));

    return true;
}

bool TestxPLExtAdvConfig::Delete()
{
    xPL::SchemaAdvanceConfigCurrentCmnd sacc1;
    xPL::SchemaAdvanceConfigCurrentCmnd sacc2;

    sacc1.SetSource("fragxpl-other.default");
    sacc1.TargetAddress.SetAddress("fragxpl-test.default");
    sacc1.SetValue("command", "delete");
    sacc1.AddValue("configname", "test2");
    m_AdvanceConfig.MsgAnswer(sacc1);

    xPL::SchemaAdvanceConfigCurrentCmnd sacc;
    xPL::SchemaObject sch;
    string msg;

    sacc.SetSource("fragxpl-other.default");
    sacc.TargetAddress.SetAddress("fragxpl-test.default");
    m_AdvanceConfig.MsgAnswer(sacc);

    msg = SimpleSockUDP::GetLastSend(10);
    sch.Parse(msg);
    assert("advanceconfig"==sch.GetClass());
    assert("current"==sch.GetType());
    assert("test1"==sch.GetValue("configname"));

    msg = SimpleSockUDP::GetLastSend(10);
    sch.Parse(msg);
    assert("advanceconfig"==sch.GetClass());
    assert("current"==sch.GetType());
    assert("test3"==sch.GetValue("configname"));

    sacc2.SetSource("fragxpl-other.default");
    sacc2.TargetAddress.SetAddress("fragxpl-test.default");
    sacc2.SetValue("command", "delete");
    m_AdvanceConfig.MsgAnswer(sacc2);

    return true;
}

bool TestxPLExtAdvConfig::NoResponse()
{
    xPL::SchemaObject sch1;
    string msg;

    m_AdvanceConfig.MsgAnswer(sch1);
    msg = SimpleSockUDP::GetLastSend(5);
    assert(""==msg);

    sch1.SetMsgType(xPL::ISchema::cmnd);
    m_AdvanceConfig.MsgAnswer(sch1);
    msg = SimpleSockUDP::GetLastSend(5);
    assert(""==msg);

    sch1.SetClass("advanceconfig");
    m_AdvanceConfig.MsgAnswer(sch1);
    msg = SimpleSockUDP::GetLastSend(5);
    assert(""==msg);

    sch1.SetType("list");
    m_AdvanceConfig.MsgAnswer(sch1);
    msg = SimpleSockUDP::GetLastSend(5);
    assert(""==msg);

    sch1.SetType("current");
    m_AdvanceConfig.MsgAnswer(sch1);
    msg = SimpleSockUDP::GetLastSend(5);
    assert(""==msg);

    sch1.SetValue("command", "request");
    sch1.SetValue("configname", "zzzzzzz");
    m_AdvanceConfig.MsgAnswer(sch1);
    msg = SimpleSockUDP::GetLastSend(5);
    assert(""==msg);

    sch1.SetType("zzzzzz");
    m_AdvanceConfig.MsgAnswer(sch1);
    msg = SimpleSockUDP::GetLastSend(5);
    assert(""==msg);

    return true;
}

bool TestxPLExtAdvConfig::AddConfig()
{
    map<string, string>* config;

    m_AdvanceConfig.AddConfig(m_Config1);
    m_AdvanceConfig.AddConfig(m_Config2);

    config = m_AdvanceConfig.GetConfig(0);
    assert(nullptr!=config);
    assert("deviceA"==(*config)["configname"]);
    assert("fragxpl-other.default:devA"==(*config)["output"]);
    assert("1"==(*config)["myinteger"]);

    config = m_AdvanceConfig.GetConfig("deviceB");
    assert(nullptr!=config);
    assert("deviceB"==(*config)["configname"]);
    assert("fragxpl-other.default:devB"==(*config)["output"]);
    assert("2"==(*config)["myinteger"]);

    return true;
}

bool TestxPLExtAdvConfig::DeleteConfig()
{
    map<string, string>* config;

    m_AdvanceConfig.DelConfig("deviceB");
    config = m_AdvanceConfig.GetConfig("deviceB");
    assert(nullptr==config);

    m_AdvanceConfig.DelConfig(0);
    config = m_AdvanceConfig.GetConfig(0);
    assert(nullptr==config);

    return true;
}
