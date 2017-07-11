#include "TestxPLMsg.h"

using namespace std;

TestxPLMsg::TestxPLMsg() : TestClass("xPLMsg", this)
{
	//addTest("SetCalcul", &TestCalcul::SetCalcul);
}

TestxPLMsg::~TestxPLMsg()
{
}

/*
bool TestxPLMsg::SetCalcul()
{
    Calcul myCalculSimple;
    Calcul myCalcul("EvaluateNight", "fragxpl-fictif.default:night", "output", "fragxpl-owfs.default:brightness<10");

    assert(""==myCalculSimple.m_Name);
    assert("EvaluateNight"==myCalcul.m_Name);
    assert("fragxpl-fictif.default:night"==myCalcul.m_CanonicDevice);
    assert("output"==myCalcul.m_TypeStr);
    assert("fragxpl-owfs.default:brightness<10"==myCalcul.m_Formula);
    assert("fragxpl-fictif.default"==myCalcul.m_ModuleName);
    assert("night"==myCalcul.m_DeviceName);
    assert(xPL::SchemaControlBasic::output==myCalcul.m_TypeEnum);

    return true;
}
*/
