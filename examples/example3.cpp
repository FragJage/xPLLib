/***********************************************************************************************/
/**                                                                                           **/
/** EXAMPLE 3                                                                                 **/
/**                                                                                           **/
/** Simple xPL application                                                                    **/
/**                                                                                           **/
/***********************************************************************************************/

#include <iostream>
#include "xPLLib/xPLDevice.h"

using namespace std;
using namespace xPL;

bool stop;

int main()
{
    xPLDevice myDevice;

    myDevice.Initialisation("fragxpl", "example", "default");
    myDevice.SetAppName("xPL Example3", "0.9.0.0");
    myDevice.SetAnswerAllMsg(true);


    return 0;
}
