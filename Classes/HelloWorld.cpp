#include "HelloWorld.h"
#include "Snake.h"

using namespace cocos2d;

bool HelloWorld::init()
{
  if (!CCLayer::init()){
    return false;
  }
  
  CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
  CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
 
  
  CCLabelTTF *pLabelNewGame = CCLabelTTF::create("New Game", "Rafa.ttf", 72);
  CCMenuItemLabel *pMenuItemNewGame = CCMenuItemLabel::create(pLabelNewGame, this, menu_selector(HelloWorld::menuNewGameCallback));
  pMenuItemNewGame->setPosition(ccp(origin.x + 200, origin.y+ 200));

  CCLabelTTF *pLabelExist = CCLabelTTF::create("Exist", "Rafa.ttf", 72);
  CCMenuItemLabel *pMenuItemExist = CCMenuItemLabel::create(pLabelExist, this, menu_selector(HelloWorld::menuCloseCallback));
  pMenuItemExist->setPosition(ccp(origin.x + 200, origin.y + 100));
  
  CCMenu *pMenu = CCMenu::create(pMenuItemNewGame, pMenuItemExist, NULL);
  pMenu->setPosition(CCPointZero);
  this->addChild(pMenu, 1);
  
  CCLabelTTF *pLabel = CCLabelTTF::create("Fireae", "Rafa_bold.ttf", 24);
  pLabel->setPosition(ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height - pLabel->getContentSize().height));
  
  this->addChild(pLabel);
  
  CCSprite *pSprite = CCSprite::create("HelloWorld.png");
  pSprite->setPosition(ccp(visibleSize.width/2+origin.x, origin.y + visibleSize.height/2));
  this->addChild(pSprite, 0);
  
  this->setTouchEnabled(true);
  return true;
}

void HelloWorld::menuNewGameCallback(CCObject *pSender)
{
    CCScene *pSnake = Snake::scene();
    CCDirector::sharedDirector()->replaceScene(pSnake);
}

void HelloWorld::menuCloseCallback(CCObject *pSender)
{
  CCDirector::sharedDirector()->end();
}

void HelloWorld::ccTouchesBegan(CCSet* pTouches, CCEvent *pEvent)
{
  CCTouch *touch = (CCTouch *)(*pTouches->begin());
  CCPoint pos = touch->getLocation();
  CCLog("%f, %f", pos.x, pos.y);
  
}

CCScene *HelloWorld::scene()
{
  CCScene *scene = CCScene::create();
  HelloWorld *layer = HelloWorld::create();
  scene->addChild(layer);
  return scene;
}
