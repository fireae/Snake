#ifndef __HELLOWORLD_H
#define __HELLOWORLD_H

#include "cocos2d.h"
using namespace cocos2d;
using namespace std;

class HelloWorld : public CCLayer
{
 public:
  virtual bool init();
  static cocos2d::CCScene *scene();
  void menuCloseCallback(CCObject *pSender);
  void menuNewGameCallback(CCObject *pSender);
  void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
  CREATE_FUNC(HelloWorld);
};
#endif
