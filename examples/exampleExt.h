#include <cassert>
#include "xPLLib/xPLDevice.h"
#include "xPLLib/Schemas/SchemaObject.h"

using namespace std;
using namespace xPL;

class exampleExt : public xPLDevice::IExtension
{
public:
    exampleExt();
    ~exampleExt();

    bool MsgAnswer(SchemaObject& msg);

private:
    int m_CountReceive;
};
