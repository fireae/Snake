#include "GlobalValue.h"
#include <iostream>
using namespace std;

GlobalValue *GlobalValue::pValue= NULL;
GlobalValue *GlobalValue::sharedValue()
{
  if (pValue == NULL)
    pValue = new GlobalValue();
  return pValue;
}

