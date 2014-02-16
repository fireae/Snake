#include "GameOverScene.h"
#include "Snake.h"

bool GameOverScene::initMenu()
{
    CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
    CCLog("wx %f ,wy %f", winSize.width, winSize.height);
    int m_nIndexX = ((int)winSize.width)/32;
    int m_nIndexY = ((int)winSize.height)/32;
    int m_nSpan = 32;
    if (m_pLabelGameOver != NULL)
       this->removeChild(m_pLabelGameOver, true);
    m_pLabelGameOver = CCLabelTTF::create("Game Over", "Rafa.ttf", 72);
    m_pLabelGameOver->setPosition(ccp(m_nIndexX/2*m_nSpan - 36, m_nIndexY/5*4*m_nSpan));
    this->addChild(m_pLabelGameOver);
    if (m_pMenu != NULL)
        this->removeChild(m_pMenu, true);
    m_pLabelNewGame = CCLabelTTF::create("New Game", "Rafa.ttf", 72);
     //m_pLabelNewGame->setPosition(ccp(m_nIndexX/2*m_nSpan - 36, m_nIndexY/5*3*m_nSpan));
    m_pLabelClose = CCLabelTTF::create("Close", "Rafa.ttf", 72);
     //m_pLabelClose->setPosition(ccp(m_nIndexX/2*m_nSpan - 36, m_nIndexY/5*2*m_nSpan));
    m_pNewGameLabelItem = CCMenuItemLabel::create(m_pLabelNewGame, this,
                                                                  menu_selector(GameOverScene::menuNewGameCallback));
    m_pNewGameLabelItem->setPosition(ccp(m_nIndexX/2*m_nSpan - 36, m_nIndexY/5*3*m_nSpan));
    m_pCloseItem = CCMenuItemLabel::create(m_pLabelClose, this,
                                                          menu_selector(GameOverScene::menuCloseCallback));
    m_pCloseItem->setPosition(ccp(m_nIndexX/2*m_nSpan - 36, m_nIndexY/5*2*m_nSpan));
    m_pMenu = CCMenu::create(m_pNewGameLabelItem, m_pCloseItem, NULL);
    m_pMenu->setPosition(CCPointZero);
    this->addChild(m_pMenu, 1);
    return true;      
}


bool GameOverScene::init()
{
    if (!CCLayer::init())
        return false;

    initMenu();
    return true;
}

CCScene *GameOverScene::scene()
{
  CCScene *scene = CCScene::create();
  GameOverScene *pGameOver = GameOverScene::create();
  scene->addChild(pGameOver);
  return scene;
  
}
void GameOverScene::menuCloseCallback(CCObject *pSender)
{
    CCDirector::sharedDirector()->end();
}

void GameOverScene::menuNewGameCallback(CCObject *pSender)
{
    CCScene *pSnake = Snake::scene();
    CCDirector::sharedDirector()->replaceScene(pSnake);
}
