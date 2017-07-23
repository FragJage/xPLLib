#ifndef __linux__
//    #include <winsock2.h>       //Make sur winsock2.h is include before windows.h
#endif
#include <iostream>
#include "TestxPLDevice.h"
#include "TestxPLDevCfg.h"
#include "TestxPLExtAdvConfig.h"
#include "TestxPLExtSensors.h"
#include "TestxPLMsg.h"
#include "TestxPLAddress.h"
#include "UnitTest/UnitTest.h"

using namespace std;

int main()
{
  UnitTest unitTest;
  int ret = 0;


  try
  {
  	unitTest.addTestClass(new TestxPLDevice());
  	unitTest.addTestClass(new TestxPLDevCfg());
  	unitTest.addTestClass(new TestxPLExtAdvConfig());
  	unitTest.addTestClass(new TestxPLExtSensors());
  	unitTest.addTestClass(new TestxPLMsg());
  	unitTest.addTestClass(new TestxPLAddress());
  }
  catch(const exception &e)
  {
      unitTest.displayError(e.what());
      ret = -1;
  }

  if(ret!=-1)
    if(!unitTest.run()) ret = 1;

	return ret;
}
