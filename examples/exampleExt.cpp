#include <iostream>
#include "exampleExt.h"

using namespace std;

extern bool stop;

exampleExt::exampleExt()
{
    m_CountReceive = 0;
}

exampleExt::~exampleExt()
{
}

bool exampleExt::MsgAnswer(SchemaObject& msg)
{
    m_CountReceive++;
    cout << "===============================" << endl;
    cout << "Identifier : " << msg.GetMsgTypeStr() << endl;
    cout << "Class : " << msg.GetClass() << endl;
    cout << "Type : " << msg.GetType() << endl;

    if(m_CountReceive==3) stop=true;

    return true;
}
