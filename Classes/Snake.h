#ifndef _SNAKE_H
#define _SNAKE_H

#include "cocos2d.h"
#include <string>
#include <vector>
using namespace std;
using namespace cocos2d;

enum ObjectType{
    BEAN_RED,
    BEAN_GREEN,
    BEAN_YELLOW,
    BEAN_BLUE,
    SNAKE_HEAD,
    SNAKE_TAIL,
    SNAKE_BODY
};
    
typedef struct _Object{
    int x;
    int y;
    ObjectType type;
    CCSprite *sprite;

    _Object(int _x, int _y, ObjectType _type, CCSprite *_sprite)
    {
        x = _x;
        y = _y;
        type = _type;
        sprite = _sprite;
    }
    
}Object;

enum Direction{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

const string csSnakeBody = "body.png";
const string csSnakeHead = "head.png";
const string csSnakeTail = "body.png";
const string csWall = "wall.png";
const string csLife = "life.png";
const string csBgMusic = "bg.wav";
const string csEatMusic = "eat.wav";
const string csDeadMusic = "end.wav";
const string csHitWallMusic = "ha.wav";
const string csLevelUpMusic = "levelup.wav";
const unsigned int BLOCK_WIDTH = 32;
const unsigned int BLOCK_HEIGHT = 32;
const string csSnakeHeadUp = "head_up.png";
const string csSnakeHeadDown = "head_down.png";
const string csSnakeHeadLeft = "head_left.png";
const string csSnakeHeadRight = "head_right.png";

class Snake : public cocos2d::CCLayer
{
 public:
    Snake(){m_nSpan = 32; m_nGameSpeed = 500; m_Direction = UP; m_nLife = 3;
        m_pBg = NULL; m_bGameOver = false; m_pLevel = NULL; m_nLevel=1; }
    ~Snake(){}

    virtual bool init();
    static cocos2d::CCScene *scene();	
    
    bool initBackground();
    bool initSnake();
    bool initLife();
    bool initBean();
    bool initWall();
    bool initLevel();
    
    void menuOnMenuCallback(CCObject *pSender);
    //void menuCloseCallback(CCObject *pSender);
    //void menuNewGameCallback(CCObject *pSender);
    
    virtual bool ccTouchBegan(CCTouch *pTouches, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouches, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouches, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher(void);
    CREATE_FUNC(Snake);

    void step(float dt);
 private:
    list<Object> m_listSnake;            // 蛇体精灵
    vector<Object> m_vecBean;            // 豆子精灵
    vector<CCSprite *> m_vecLifeSprites;  // 血量 精灵
    vector<CCSprite *> m_vecWallSprites;  // 墙壁精灵
    CCSprite *m_pBg;   // 背景 精灵

    int m_nBeanCount; // 豆子数量， random
    int m_nSpan;            // 方块的宽度
    
    CCPoint m_ptTouched;    // 第一次按的点，用于判断运动方向
    Direction m_Direction;  // 运动方向 上下左右
    int m_nLife;      // 血量
    int m_nLevel;      // 等级
    CCLabelTTF *m_pLevel;
    int m_nGameSpeed; // 游戏速度

    unsigned int m_nIndexX;  // 格子的数量， x， 30
    unsigned int m_nIndexY;  // 格子的数量 ， y 20
    bool m_bGameOver;
   
};

#endif // _SNAKE_H
