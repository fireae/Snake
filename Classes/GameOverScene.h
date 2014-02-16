#ifndef _GAMEOVERSCENE_H_
#define _GAMEOVERSCENE_H_
#include "cocos2d.h"
using namespace cocos2d;
using namespace std;

class GameOverScene : public cocos2d::CCLayer
{
 public:
    GameOverScene(){}
    ~GameOverScene(){}

    static CCScene *scene();
    virtual bool init();
    bool initMenu();
    void menuCloseCallback(CCObject *pSender);
    void menuNewGameCallback(CCObject *pSender);
    CREATE_FUNC(GameOverScene);

 private:
    CCLabelTTF *m_pLabelGameOver;
    CCLabelTTF *m_pLabelClose;
    CCLabelTTF *m_pLabelNewGame;
    CCMenuItemLabel *m_pNewGameLabelItem;
    CCMenuItemLabel *m_pCloseItem;
    CCMenu *m_pMenu;
};

#endif //_GAMEOVERSCENE_H_
