#include "TestxPLExtSensors.h"

using namespace std;

TestxPLExtSensors::TestxPLExtSensors() : TestClass("Sensors", this), m_xPLDevice("fragxpl", "test", "default"), m_Sensors(&m_xPLDevice)
{
	addTest("AddMessage1", &TestxPLExtSensors::AddMessage1);
	addTest("AddMessage2", &TestxPLExtSensors::AddMessage2);
	addTest("AddMessage3", &TestxPLExtSensors::AddMessage3);
	addTest("AddMessage4", &TestxPLExtSensors::AddMessage4);
	addTest("AddSensorMessage1", &TestxPLExtSensors::AddSensorMessage1);
	addTest("AddSensorMessage2", &TestxPLExtSensors::AddSensorMessage2);
	addTest("GetMessage", &TestxPLExtSensors::GetMessage);
	addTest("ModifyMessage", &TestxPLExtSensors::ModifyMessage);
	addTest("MsgAnswer", &TestxPLExtSensors::MsgAnswer);
	addTest("RemoveMessage", &TestxPLExtSensors::RemoveMessage);
	addTest("RemoveAllMessages", &TestxPLExtSensors::RemoveAllMessages);

	m_xPLDevice.AddExtension(&m_Sensors);
    m_xPLDevice.Open();
    SimpleSockUDP::GetLastSend(10);       //Pass config.app on start
}

TestxPLExtSensors::~TestxPLExtSensors()
{
    m_xPLDevice.Close();
    SimpleSockUDP::GetLastSend(10);       //Pass hbeat.end
}

bool TestxPLExtSensors::AddMessage1()
{
    static xPL::SchemaSensorBasic sb;
    xPL::SchemaObject sch;
    string msg;

    sb.SetDeviceName("sensorOne");
    sb.SetDeviceType(xPL::SchemaSensorTypeUtility::battery);
    sb.SetCurrent(12);
    sb.SetUnit("V");

    m_Sensors.AddMessage(&sb);
    msg = SimpleSockUDP::GetLastSend(10);
    sch.Parse(msg);

    assert("sensor"==sch.GetClass());
    assert("basic"==sch.GetType());
    assert("sensorOne"==sch.GetValue("device"));
    assert("battery"==sch.GetValue("type"));
    assert("12"==sch.GetValue("current"));
    assert("V"==sch.GetValue("unit"));

    return true;
}

bool TestxPLExtSensors::AddMessage2()
{
    static xPL::SchemaSensorBasic sb("sensorTwo", xPL::SchemaSensorTypeUtility::current);
    xPL::SchemaObject sch;
    string msg;

    sb.SetCurrent(5);
    sb.SetUnit("A");

    m_Sensors.AddMessage(&sb);
    msg = SimpleSockUDP::GetLastSend(10);
    sch.Parse(msg);

    assert("sensor"==sch.GetClass());
    assert("basic"==sch.GetType());
    assert("sensorTwo"==sch.GetValue("device"));
    assert("current"==sch.GetValue("type"));
    assert("5"==sch.GetValue("current"));
    assert("A"==sch.GetValue("unit"));

    return true;
}

bool TestxPLExtSensors::AddMessage3()
{
    static xPL::SchemaSensorBasic sb("sensorThree", xPL::SchemaSensorTypeUtility::direction, "west");
    xPL::SchemaObject sch;
    string msg;

    m_Sensors.AddMessage(&sb);
    msg = SimpleSockUDP::GetLastSend(10);
    sch.Parse(msg);

    assert("sensor"==sch.GetClass());
    assert("basic"==sch.GetType());
    assert("sensorThree"==sch.GetValue("device"));
    assert("direction"==sch.GetValue("type"));
    assert("west"==sch.GetValue("current"));

    return true;
}

bool TestxPLExtSensors::AddMessage4()
{
    static xPL::SchemaSensorBasic sb("sensorFour", xPL::SchemaSensorTypeUtility::distance, 50, "m");
    xPL::SchemaObject sch;
    string msg;

    m_Sensors.AddMessage(&sb);
    msg = SimpleSockUDP::GetLastSend(10);
    sch.Parse(msg);

    assert("sensor"==sch.GetClass());
    assert("basic"==sch.GetType());
    assert("sensorFour"==sch.GetValue("device"));
    assert("distance"==sch.GetValue("type"));
    assert("50"==sch.GetValue("current"));
    assert("m"==sch.GetValue("unit"));

    return true;
}

bool TestxPLExtSensors::AddSensorMessage1()
{
    xPL::SchemaObject sch;
    string msg;

    m_Sensors.AddSensorMessage("sensorFive", xPL::SchemaSensorTypeUtility::energy, 50);
    msg = SimpleSockUDP::GetLastSend(10);
    sch.Parse(msg);

    assert("sensor"==sch.GetClass());
    assert("basic"==sch.GetType());
    assert("sensorFive"==sch.GetValue("device"));
    assert("energy"==sch.GetValue("type"));
    assert("50"==sch.GetValue("current"));

    return true;
}

bool TestxPLExtSensors::AddSensorMessage2()
{
    xPL::SchemaObject sch;
    string msg;

    m_Sensors.AddSensorMessage("sensorSix", xPL::SchemaSensorTypeUtility::humidity, 50);
    msg = SimpleSockUDP::GetLastSend(10);
    sch.Parse(msg);

    assert("sensor"==sch.GetClass());
    assert("basic"==sch.GetType());
    assert("sensorSix"==sch.GetValue("device"));
    assert("humidity"==sch.GetValue("type"));
    assert("50"==sch.GetValue("current"));

    return true;
}

bool TestxPLExtSensors::GetMessage()
{
    xPL::SchemaObject* sch;

    sch = m_Sensors.GetMessage("sensorFour");
    assert(nullptr != sch);
    assert("sensorFour"==sch->GetValue("device"));
    assert("distance"==sch->GetValue("type"));
    assert("50"==sch->GetValue("current"));
    return true;
}

bool TestxPLExtSensors::ModifyMessage()
{
    xPL::SchemaObject sch;
    string msg;

    m_Sensors.ModifyMessage("sensorFive", "TEST", "input");
    msg = SimpleSockUDP::GetLastSend(10);
    sch.Parse(msg);

    assert("sensor"==sch.GetClass());
    assert("basic"==sch.GetType());
    assert("sensorFive"==sch.GetValue("device"));
    assert("input"==sch.GetValue("type"));
    assert("TEST"==sch.GetValue("current"));

    return true;
}
bool TestxPLExtSensors::MsgAnswer()
{
    xPL::SchemaSensorRequest ssr;
    xPL::SchemaObject sch;
    string msg;

    ssr.AddValue("device", "sensorThree");
    msg = ssr.ToMessage("fragxpl-other.default", "fragxpl-test.default");
    SimpleSockUDP::SetNextRecv(msg);
    m_xPLDevice.WaitRecv(10);
    msg = SimpleSockUDP::GetLastSend(10);
    sch.Parse(msg);

    assert("sensor"==sch.GetClass());
    assert("basic"==sch.GetType());
    assert("sensorThree"==sch.GetValue("device"));
    assert("direction"==sch.GetValue("type"));
    assert("west"==sch.GetValue("current"));

    return true;
}
bool TestxPLExtSensors::RemoveMessage()
{
    xPL::SchemaObject* sch;
    m_Sensors.RemoveMessage("sensorFive");

    sch = m_Sensors.GetMessage("sensorFive");
    assert(nullptr == sch);

    return true;
}
bool TestxPLExtSensors::RemoveAllMessages()
{
    xPL::SchemaObject* sch;
    m_Sensors.RemoveAllMessages();

    sch = m_Sensors.GetMessage("sensorOne");
    assert(nullptr == sch);

    sch = m_Sensors.GetMessage("sensorSix");
    assert(nullptr == sch);

    return true;
}
