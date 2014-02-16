#include "Snake.h"
#include "SimpleAudioEngine.h"
#include "GameOverScene.h"
#include "GlobalValue.h"
#include "PauseLayer.h"
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace cocos2d;
using namespace std;

bool Snake::initBackground()
{
     // 清空界面
    // clear bg
    if (m_pBg != NULL)
        this->removeChild(m_pBg, true);
    
    CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();
    CCLog("wx %f ,wy %f", winSize.width, winSize.height);
    m_nIndexX = ((int)winSize.width)/BLOCK_WIDTH;
    m_nIndexY = ((int)winSize.height)/BLOCK_HEIGHT;
    CCLog("x, %d, y %d", m_nIndexX, m_nIndexY);
    do{
        m_pBg = CCSprite::create("bg.jpg");
        CC_BREAK_IF(!m_pBg);
        m_pBg->setAnchorPoint(ccp(0, 0));
        m_pBg->setPosition(ccp(0, 0));
        this->addChild(m_pBg);
        
    }while(0);
    
    CCLabelTTF *pMenuLabel = CCLabelTTF::create("Menu", "Rafa.ttf", 32);
    pMenuLabel->setColor(ccBLACK);
    CCMenuItemLabel *pMenuLabelItem = CCMenuItemLabel::create(pMenuLabel, this, menu_selector(Snake::menuOnMenuCallback));
    pMenuLabelItem->setPosition(ccp((m_nIndexX-2) *m_nSpan+ 16, (m_nIndexY)*m_nSpan+16));
    CCMenu *pMenu = CCMenu::create(pMenuLabelItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    return true;
}

bool Snake::initSnake()
{
    
    // clear snake
    list<Object>::iterator itSnake = m_listSnake.begin();
    for (itSnake = m_listSnake.begin(); itSnake != m_listSnake.end(); itSnake++)
    {
        Object &obj = *itSnake;
        if (obj.sprite != NULL)
        {
            this->removeChild(obj.sprite, true);
        }
    }
    m_listSnake.clear();
    
    // add snake
    CCSprite *snakeHead = CCSprite::create(csSnakeTail.c_str());
    snakeHead->setPosition(ccp(10*m_nSpan+ m_nSpan/2, 11*m_nSpan + m_nSpan/2));
    this->addChild(snakeHead);
    Object objSnakeHead(10, 11, SNAKE_TAIL, snakeHead);
    m_listSnake.push_back(objSnakeHead);
    
    for (unsigned int i = 10; i >= 8; i--)
    {
        CCSprite *snakeBody = CCSprite::create(csSnakeBody.c_str());
        snakeBody->setPosition(ccp(10 * m_nSpan + m_nSpan/2, i *m_nSpan + m_nSpan/2));
        this->addChild(snakeBody);

        Object obj(10, i, SNAKE_BODY, snakeBody);        
        m_listSnake.push_back(obj);
        
    }
    
    CCSprite *snakeTail = CCSprite::create(csSnakeHeadUp.c_str());
    snakeHead->setPosition(ccp(10*m_nSpan + m_nSpan/2, 7*m_nSpan + m_nSpan/2));
    this->addChild(snakeTail);

    Object objSnakeTail(10, 7, SNAKE_HEAD, snakeTail);
    m_listSnake.push_back(objSnakeTail);
    
    m_Direction = UP;
    return true;
}

bool Snake::initWall()
{
    
    // clear wall
    for (unsigned int i = 0; i < m_vecWallSprites.size(); i++)
    {
        CCSprite * pSprite = m_vecWallSprites.at(i);
        if (pSprite != NULL)
        {
            this->removeChild(pSprite, true);
        }
    }
    m_vecWallSprites.clear();
    
    // add wall
    for (unsigned int i = 0; i <= m_nIndexX; i++)
    {
        CCSprite *wall = CCSprite::create(csWall.c_str());
        wall->setPosition(ccp(i*m_nSpan + m_nSpan/2, 1*m_nSpan + m_nSpan/2));
        this->addChild(wall);
         
        CCSprite *wall1 = CCSprite::create(csWall.c_str());
        wall1->setPosition(ccp(i*m_nSpan + m_nSpan/2, (m_nIndexY)*m_nSpan + m_nSpan/2));
        this->addChild(wall1);
        
        m_vecWallSprites.push_back(wall);
        m_vecWallSprites.push_back(wall1);
    }
    
    for (unsigned int i = 0; i <= m_nIndexY; i++)
    {
        CCSprite *wall = CCSprite::create(csWall.c_str());
        wall->setPosition(ccp(0*m_nSpan + m_nSpan/2, i*m_nSpan + m_nSpan/2));
        this->addChild(wall);
        
        CCSprite *wall1 = CCSprite::create(csWall.c_str());
        wall1->setPosition(ccp((m_nIndexX-1)*m_nSpan + m_nSpan/2, i*m_nSpan + m_nSpan/2));
        this->addChild(wall1);

        m_vecWallSprites.push_back(wall);
        m_vecWallSprites.push_back(wall1);
    }
    
    return true;
}

bool Snake::initLife()
{
    // clear life
    for (unsigned int i = 0; i < m_vecLifeSprites.size(); i++)
    {
        CCSprite *pLife = m_vecLifeSprites.at(i);
        if (pLife != NULL)
        {
            this->removeChild(pLife, true);
        }
    }
    m_vecLifeSprites.clear();
    // add life
    for (int i = 0; i < m_nLife; i++)
    {
        CCSprite *life = CCSprite::create(csLife.c_str());
        life->setPosition(ccp((i+1)*(m_nSpan+10) + 64, m_nIndexY*m_nSpan + 16));
        m_vecLifeSprites.push_back(life);
        this->addChild(life);
    }
    return true;
}

bool Snake::initBean()
{
    vector<Object>::iterator itBean;
    for (itBean = m_vecBean.begin(); itBean != m_vecBean.end(); itBean++)
    {
        Object &bean = *itBean;
        if (bean.sprite != NULL)
        {
            this->removeChild(bean.sprite, true);
        }
    }
    m_vecBean.clear();
    
    // add bean
    srand(unsigned(time(0)));
    m_nBeanCount = rand()%(3) + 1;
    for (int i = 0; i < m_nBeanCount; i++)
    {
        int x = rand()%(m_nIndexX - 3) + 2;
        int y = rand()%(m_nIndexY - 3) + 2;
        int type = rand()%6 + 1;
        char fruitName[30];
        sprintf(fruitName, "fruit%d.png", type);
        CCSprite *bean = CCSprite::create(fruitName);
        
        bean->setPosition(ccp(x * m_nSpan + m_nSpan/2, y * m_nSpan + m_nSpan/2));
        this->addChild(bean);
        Object obj(x, y, (ObjectType)type, bean);
        m_vecBean.push_back(obj);
    }

    return true;
}


bool Snake::initLevel()
{
    if (m_pLevel != NULL)
    {
        this->removeChild(m_pLevel);
    }

    char szLevel[50];
    sprintf(szLevel, "Level : %d" ,m_nLevel);
    m_pLevel = CCLabelTTF::create(szLevel, "Rafa.ttf", 32);
    m_pLevel->setPosition(ccp(5*(m_nSpan+10) + 64, m_nIndexY*m_nSpan + 16));
    m_pLevel->setColor(ccGREEN);
    this->addChild(m_pLevel, 1);
    return true;
}

bool Snake::init(){
    if (!CCLayer::init())
        return false;
    initBackground();
    initWall();
    initSnake();
    initBean();
    initLife();
    initLevel();
    
    this->schedule(schedule_selector(Snake::step), (float)m_nGameSpeed/(float)1000);
    this->setTouchEnabled(true);
    // add bg music
    if (GlobalValue::sharedValue()->m_bMusicOn)
      CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(csBgMusic.c_str(), true);
    this->setTag(1000);
    return  true;
}

CCScene *Snake::scene()
{
    CCScene *scene = NULL;
    // do{
        scene = CCScene::create();
        Snake *pSnake = Snake::create();
        scene->addChild(pSnake);
        // }while(0);
    return scene;
}


void Snake::step(float dt)
{
    CCLog("dir： %d", (int) m_Direction);
    // game over?
    if (m_bGameOver)
    {
        return;
    }
    
    // dead?
    if (m_listSnake.empty())
    {
        m_nLife--;
        initSnake();
        initLife();
        initBean();
        if (m_nLife <= 0)
        {
            m_nLife = 0;
            m_bGameOver = true;
	    if (GlobalValue::sharedValue()->m_bMusicOn)
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(csDeadMusic.c_str());
            CCScene *pGameOverScene = GameOverScene::scene();
            CCDirector::sharedDirector()->replaceScene(pGameOverScene);
            CCLog("Game Over!");
            return ;
        }

        //return;
    }
    
    // 清空snake 的sprite
    list<Object>::iterator itSnake = m_listSnake.begin();
    for (itSnake = m_listSnake.begin(); itSnake != m_listSnake.end(); itSnake++)
    {
      Object objSnake = *itSnake;
      CCSprite *sprite = objSnake.sprite;
      if (sprite != NULL)
      {
          this->removeChild(sprite, true);
      }
      
    }

    // eat bean
    // get snake head
    Object &curSnakeHead = m_listSnake.front();
    int x = curSnakeHead.x;
    int y = curSnakeHead.y;
    
    if (m_Direction == UP)
    {
        y++;
    }
    else if (m_Direction == DOWN)
    {
        y--;
    }
    else if (m_Direction == LEFT)
    {
        x--;
    }
    else if (m_Direction == RIGHT)
    {
        x++;
    }
    curSnakeHead.type = SNAKE_BODY; //这个位置的由蛇头变为蛇身

    // 测试是否碰上身体
    if (m_listSnake.size() >= 1)
    {
        itSnake = m_listSnake.begin();
        //itSnake++; 从第二个开始
        for (itSnake++; itSnake != m_listSnake.end(); itSnake++)
        {
            Object objSnake = *itSnake;
            int xTmp = objSnake.x;
            int yTmp = objSnake.y;
            if (x == xTmp && y == yTmp)
            {
		if (GlobalValue::sharedValue()->m_bMusicOn)
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(csHitWallMusic.c_str());
                m_nLife --;
                if (m_nLife <= 0)
                {
                    m_nLife = 0;
                    m_bGameOver= true;
		    if (GlobalValue::sharedValue()->m_bMusicOn)
                    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(csDeadMusic.c_str());
                    return;
                }

                // 重新开始新游戏
                initSnake();
                initLife();
                initBean();
                return;
            }
      
        }
    }
    
    
    // 添加新的蛇头
    Object objSnakeHead(x, y, SNAKE_HEAD, NULL);
    m_listSnake.push_front(objSnakeHead);
    
    do {
    // 碰壁
	if ((unsigned int) objSnakeHead.x == 0 || (unsigned int)objSnakeHead.y == 1 ||
        (unsigned int)objSnakeHead.x == m_nIndexX -1  || (unsigned int)objSnakeHead.y == m_nIndexY)
	{
	  if (GlobalValue::sharedValue()->m_bMusicOn)
	    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(csHitWallMusic.c_str());
	  if (!m_listSnake.empty())
	    m_listSnake.pop_front();
	}

	// 取蛇头
	// 吃豆子
	bool bEatBean = 0;
	vector<Object>::iterator itBean = m_vecBean.begin();
	for (itBean = m_vecBean.begin(); itBean != m_vecBean.end();)
	{
	    Object objBean = *itBean;
	    CCLog("bean x: %d, y %d", objBean.x , objBean.y);
	    if (((int)objBean.x == (int)objSnakeHead.x) && ((int)objBean.y == (int)objSnakeHead.y))
	    {
            itBean = m_vecBean.erase(itBean);
            this->removeChild(objBean.sprite, true);
            bEatBean = true;
            CCLog("eat bean");
	    if (GlobalValue::sharedValue()->m_bMusicOn)
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(csEatMusic.c_str());
	    }
	    else
	    {
            itBean ++;
	    }
	}
	
	if (!bEatBean)
	{
	    m_listSnake.pop_back();
	}
    
    if ( !m_listSnake.empty())
    {
        Object &objSnakeTail = m_listSnake.back();
        objSnakeTail.type = SNAKE_TAIL;
    }
	
	CCLog("snake list: %d", m_listSnake.size());
    }while(0);
    // 
    itSnake = m_listSnake.begin();
    for (itSnake = m_listSnake.begin(); itSnake != m_listSnake.end(); itSnake++)
    {
        Object &objSnake = *itSnake;
        CCSprite *sprite= NULL;
        int x = objSnake.x;
        int y = objSnake.y;
        switch(objSnake.type)
        {
        case SNAKE_HEAD:
            if (m_Direction == UP)
            {
                sprite = CCSprite::create(csSnakeHeadUp.c_str());
            }
            else if(m_Direction == DOWN)
            {
                sprite = CCSprite::create(csSnakeHeadDown.c_str());
            }
            else if(m_Direction == LEFT)
            {
                sprite = CCSprite::create(csSnakeHeadLeft.c_str());
            }
            else
            {
                sprite = CCSprite::create(csSnakeHeadRight.c_str());
            }
            //sprite = CCSprite::create(csSnakeHead.c_str());
            break;
        case SNAKE_BODY:
            sprite = CCSprite::create(csSnakeBody.c_str());
            break;
        case SNAKE_TAIL:
            sprite = CCSprite::create(csSnakeTail.c_str());
            break;
        default:
            break;
	  
        }
        objSnake.sprite = sprite;
        sprite->setPosition(ccp(x*m_nSpan + 16, y*m_nSpan + 16));
        this->addChild(sprite);
	
	
	CCLog("x :%d , y :%d, type :%d \n", objSnake.x, objSnake.y, (int)objSnake.type);
    }

    if (m_vecBean.size() <= 0)
    {
        initBean();
    }
    if (m_listSnake.size() > (unsigned int)((m_nLevel + 1)*5))
    {
        m_nLevel++;
        if (m_nGameSpeed > 50)
        {
            m_nGameSpeed = 500 - 50*m_nLevel;
            this->schedule(schedule_selector(Snake::step), (float)m_nGameSpeed/(float)1000);
        }
        initLevel();
	if (GlobalValue::sharedValue()->m_bMusicOn)
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(csLevelUpMusic.c_str());
    }
   

    CCLog("speed %d", m_nGameSpeed);
}

bool Snake::ccTouchBegan(CCTouch *pTouches, CCEvent *pEvent)
{
    m_ptTouched = this->convertTouchToNodeSpace(pTouches);
    return true;
}

void Snake::ccTouchMoved(CCTouch *pTouches, CCEvent *pEvent)
{
    
}

void Snake::ccTouchEnded(CCTouch *pTouches, CCEvent *pEvent)
{
    CCPoint pt = this->convertTouchToNodeSpace(pTouches);
    int x = m_ptTouched.x - pt.x;
    int y = m_ptTouched.y - pt.y;
   
    if ((abs(x) > abs(y)) && m_Direction != RIGHT && m_Direction != LEFT)
    {
        m_Direction = RIGHT;
        if (x >= 0)
            m_Direction = LEFT;
    }
    if ((abs(x) <= abs(y)) && m_Direction != UP && m_Direction != DOWN)
    {
        m_Direction = UP;
        if (y >= 0)
            m_Direction = DOWN;
    }
}

void Snake::registerWithTouchDispatcher(void)
{
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}
        
void Snake::menuOnMenuCallback(CCObject *pSender)
{
  CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
  CCSize size= CCDirector::sharedDirector()->getWinSize();

  CCRenderTexture *renderTexture = CCRenderTexture::create(size.width, size.height);
  renderTexture->retain();
  CCScene *s = CCDirector::sharedDirector()->getRunningScene();
 
  renderTexture->begin();
  s->visit();
  renderTexture->end();
  CCScene *pause = PauseLayer::scene(renderTexture, true);
  CCDirector::sharedDirector()->pushScene(pause);
 
}
/*
void Snake::menuNewGameCallback(CCObject *pSender)
{
    m_nGameSpeed = 1000;
    m_Direction = UP;
    m_nLife = 3;
    m_bGameOver = false;
    m_nLevel = 1;

    this->cleanup();
    initBackground();
    initSnake();
    initLife();
    initBean();
    initWall();
    initLevel();
    
}
*/

