#ifndef PAUSELAYER_H
#define PAUSELAYER_H

#include "cocos2d.h"

using namespace cocos2d;

class PauseLayer : public cocos2d::CCLayer
{
public:
  PauseLayer(){}
  ~PauseLayer(){}
  
  virtual bool init();
  static CCScene * scene(CCRenderTexture *sr, bool isFlip);
  static CCScene *scene();
  void menuItemContinueCallback(CCObject *pSender);
  void menuItemCloseCallback(CCObject *pSender);
  void menuItemMusicCallback(CCObject *pSender);
  
  CREATE_FUNC(PauseLayer);
  
};

#endif // PAUSELAYER_H