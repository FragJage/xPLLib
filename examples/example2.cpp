/***********************************************************************************************/
/**                                                                                           **/
/** EXAMPLE 2                                                                                 **/
/**                                                                                           **/
/** Simple xPL application                                                                    **/
/**                                                                                           **/
/***********************************************************************************************/

#include <iostream>
#include "xPLLib/xPLDevice.h"
#include "exampleExt.h"

using namespace std;
using namespace xPL;

bool stop;

int main()
{
    xPLDevice myDevice;
    exampleExt myExtention;

    myDevice.Initialisation("fragxpl", "example", "default");
    myDevice.SetAppName("xPL Example", "0.9.0.0");
    myDevice.SetAnswerAllMsg(true);
    myDevice.AddExtension(&myExtention);

    stop = false;
    myDevice.Open();

    while(!stop)
        myDevice.WaitRecv(500);

    myDevice.Close();

    return 0;
}
