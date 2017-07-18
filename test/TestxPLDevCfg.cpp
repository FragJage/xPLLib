#include "TestxPLDevCfg.h"

using namespace std;

TestxPLDevCfg::TestxPLDevCfg() : TestClass("TestxPLDevCfg", this), m_xPLDevice("fragxpl", "test", "default")
{
	addTest("GetConfigList", &TestxPLDevCfg::GetConfigList);
	addTest("SetConfig", &TestxPLDevCfg::SetConfig);
	addTest("GetCurrentConfig", &TestxPLDevCfg::GetCurrentConfig);
	addTest("LoadConfig", &TestxPLDevCfg::LoadConfig);
	addTest("GetConfigItem", &TestxPLDevCfg::GetConfigItem);
	addTest("RemoveConfig", &TestxPLDevCfg::RemoveConfig);

    m_xPLDevice.Open();
    SimpleSockUDP::GetLastSend(10);       //Pass config.app on start
}

TestxPLDevCfg::~TestxPLDevCfg()
{
    m_xPLDevice.Close();
    SimpleSockUDP::GetLastSend(10);       //Pass hbeat.end
}

bool TestxPLDevCfg::GetConfigList()
{
    xPL::SchemaConfigListRequest sclr;
    xPL::SchemaObject sch;
    string msg;


    m_xPLDevice.AddBasicConfig("port", xPL::ConfigItem::Option, "1234");
    m_xPLDevice.AddBasicConfig("grp", xPL::ConfigItem::Option, 2);

    msg = sclr.ToMessage("fragxpl-other.default", "fragxpl-test.default");
    SimpleSockUDP::SetNextRecv(msg);
    m_xPLDevice.WaitRecv(10);
    msg = SimpleSockUDP::GetLastSend(10);
    sch.Parse(msg);

    if(sch.GetType()=="app")
    {
        msg = SimpleSockUDP::GetLastSend(10);
        sch.Parse(msg);
    }

    assert("config"==sch.GetClass());
    assert("list"==sch.GetType());
    assert("loglevel"==sch.GetValue("reconf", 3));
    assert("port"==sch.GetValue("option", 4));
    assert("grp[2]"==sch.GetValue("option", 5));
    assert("network"==sch.GetValue("config"));

    return true;
}

bool TestxPLDevCfg::SetConfig()
{
    xPL::SchemaObject sclc(xPL::ISchema::cmnd, "config", "response");
    xPL::SchemaObject sch;
    string msg;

    sclc.AddValue("port", "5555");
    sclc.AddValue("logmodule", "xPLLib");
    sclc.AddValue("group", "xpl-group.bedroom");
    sclc.AddValue("group", "xpl-group.livingroom");

    msg = sclc.ToMessage("fragxpl-other.default", "fragxpl-test.default");
    SimpleSockUDP::SetNextRecv(msg);
    m_xPLDevice.WaitRecv(10);

    return true;
}

bool TestxPLDevCfg::GetCurrentConfig()
{
    xPL::SchemaConfigCurrentRequest sccr;
    xPL::SchemaObject sch;
    string msg;

    msg = sccr.ToMessage("fragxpl-other.default", "fragxpl-test.default");
    SimpleSockUDP::SetNextRecv(msg);
    m_xPLDevice.WaitRecv(10);
    msg = SimpleSockUDP::GetLastSend(10);
    sch.Parse(msg);

    assert("config"==sch.GetClass());
    assert("current"==sch.GetType());
    assert("5"==sch.GetValue("interval"));
    assert("xPLLib"==sch.GetValue("logmodule"));
    assert("5555"==sch.GetValue("port"));
    assert("xpl-group.livingroom"==sch.GetValue("group", 1));

    return true;
}

bool TestxPLDevCfg::LoadConfig()
{
    m_xPLDevice.LoadConfig();
    return GetCurrentConfig();
}

bool TestxPLDevCfg::GetConfigItem()
{
    xPL::ConfigItem *item;
    xPL::SchemaConfigCurrentRequest sccr;
    xPL::SchemaObject sch;
    string msg;

    item = m_xPLDevice.GetConfigItem("grp");
    assert(nullptr!=item);

    item->SetValue("1111");
    item->SetValue(1, "2222");

    msg = sccr.ToMessage("fragxpl-other.default", "fragxpl-test.default");
    SimpleSockUDP::SetNextRecv(msg);
    m_xPLDevice.WaitRecv(10);
    msg = SimpleSockUDP::GetLastSend(10);
    sch.Parse(msg);

    assert("config"==sch.GetClass());
    assert("current"==sch.GetType());
    assert("1111"==sch.GetValue("grp"));
    assert("1111"==sch.GetValue("grp", 0));
    assert("2222"==sch.GetValue("grp", 1));

    return true;
}

bool TestxPLDevCfg::RemoveConfig()
{
    xPL::SchemaConfigListRequest sclr;
    xPL::SchemaObject sch;
    string msg;

    m_xPLDevice.RemoveBasicConfig("port");
    msg = sclr.ToMessage("fragxpl-other.default", "fragxpl-test.default");
    SimpleSockUDP::SetNextRecv(msg);
    m_xPLDevice.WaitRecv(10);
    msg = SimpleSockUDP::GetLastSend(10);
    sch.Parse(msg);

    if(sch.GetType()=="app")
    {
        msg = SimpleSockUDP::GetLastSend(10);
        sch.Parse(msg);
    }

    assert("config"==sch.GetClass());
    assert("list"==sch.GetType());
    assert("port"!=sch.GetValue("option", 4));
    return true;
}
