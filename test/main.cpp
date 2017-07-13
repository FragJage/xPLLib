#include <iostream>
#include "UnitTest/UnitTest.h"
#include "TestxPLDevice.h"
#include "TestxPLDevCfg.h"
#include "TestxPLMsg.h"

using namespace std;

int main()
{
  UnitTest unitTest;
  int ret = 0;


  try
  {
  	unitTest.addTestClass(new TestxPLDevice());
  	unitTest.addTestClass(new TestxPLDevCfg());
  	unitTest.addTestClass(new TestxPLMsg());
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
