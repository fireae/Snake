#include "PauseLayer.h"
#include "SimpleAudioEngine.h"
#include "Snake.h"
#include "GlobalValue.h"

bool PauseLayer::init()
{
  if (!CCLayer::init())
    return false;
  
  CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
  
  CCLabelTTF *pLabelPause = CCLabelTTF::create("Pause ...", "Rafa.ttf", 48);
  pLabelPause->setPosition(ccp(winSize.width/2, winSize.height/5*4+32));
  this->addChild(pLabelPause);
  
  CCLabelTTF *pLabelContinue = CCLabelTTF::create("Continue", "Rafa.ttf", 48);
  CCMenuItemLabel *pMenuItemContinue = CCMenuItemLabel::create(pLabelContinue, this, 
					menu_selector(PauseLayer::menuItemContinueCallback));
  pMenuItemContinue->setPosition(ccp(winSize.width/2, winSize.height/5*3+32));
  
  char szMusic[30];
  if (GlobalValue::sharedValue()->m_bMusicOn)
    sprintf(szMusic, "Music Off");
  else
    sprintf(szMusic, "Music On");
  
  CCLabelTTF *pLabelMusic = CCLabelTTF::create(szMusic, "Rafa.ttf", 48);
  CCMenuItemLabel *pMenuItemMusic = CCMenuItemLabel::create(pLabelMusic, this, 
					menu_selector(PauseLayer::menuItemMusicCallback));
  
  pMenuItemMusic->setPosition(ccp(winSize.width/2, winSize.height/5*2+32));
  
  CCLabelTTF *pLabelExist = CCLabelTTF::create("Exist", "Rafa.ttf", 48);
  CCMenuItemLabel *pMenuItemExist = CCMenuItemLabel::create(pLabelExist, this, 
					menu_selector(PauseLayer::menuItemCloseCallback));
  
  pMenuItemExist->setPosition(ccp(winSize.width/2, winSize.height/5*1+32));
  
  
  CCMenu *pMenu = CCMenu::create(pMenuItemContinue, pMenuItemMusic, pMenuItemExist, NULL);
  pMenu->setPosition(CCPointZero);
  this->addChild(pMenu);
  
  return true;
  
}

CCScene *PauseLayer::scene(CCRenderTexture *sqr, bool isFlip)
{
  CCScene *scene = CCScene::create();
  CCSize size = CCDirector::sharedDirector()->getWinSize();
  
  CCSprite *_spr = CCSprite::createWithTexture(sqr->getSprite()->getTexture());
  _spr->setPosition(ccp(size.width/2, size.height/2));
  _spr->setFlipY(isFlip);
  _spr->setColor(ccGRAY);
  scene->addChild(_spr);
  
  PauseLayer *layer = PauseLayer::create();
  scene->addChild(layer);
  
  return scene;
}

CCScene *PauseLayer::scene()
{
  CCScene *scene = CCScene::create();
  PauseLayer *layer = PauseLayer::create();
  scene->addChild(layer);
  
  return scene;
}


void PauseLayer::menuItemContinueCallback(CCObject *pSender)
{
   if (GlobalValue::sharedValue()->m_bMusicOn)
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
  else
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
  
  CCDirector::sharedDirector()->popScene();
  
}

void PauseLayer::menuItemMusicCallback(CCObject *pSender)
{
  GlobalValue::sharedValue()->m_bMusicOn = !(GlobalValue::sharedValue()->m_bMusicOn);
  if (GlobalValue::sharedValue()->m_bMusicOn)
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
  else
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
  //CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
  CCDirector::sharedDirector()->popScene();
  
}

void PauseLayer::menuItemCloseCallback(CCObject *pSender)
{
  CCDirector::sharedDirector()->end();
  
}