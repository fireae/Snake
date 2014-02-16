#include "AppDelegate.h"

#include "HelloWorld.h"
#include "Snake.h"
#include "PauseLayer.h"
#include "SimpleAudioEngine.h"

bool AppDelegate::applicationDidFinishLaunching()
{
  CCDirector *pDirector = CCDirector::sharedDirector();
  pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
  
  //TargetPlatform target = getTargetform();
  vector<string> paths;
  //paths.push_back("ipadhd");
  //CCFileUtils::sharedFileUtils()->setSearchPaths(paths);
  CCEGLView::sharedOpenGLView()->setDesignResolutionSize(960, 640, kResolutionNoBorder);
  
  //pDirector->setDisplayStats(true);
  pDirector->setAnimationInterval(1.0/60);

  CCScene *pScene = HelloWorld::scene(); //Snake::scene();
  pDirector->runWithScene(pScene);
  return true;
}

void AppDelegate::applicationDidEnterBackground()
{
  CCDirector::sharedDirector()->stopAnimation();
  CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
  CCSize size= CCDirector::sharedDirector()->getWinSize();
  
  CCRenderTexture *renderTexture = CCRenderTexture::create(size.width, size.height);
  renderTexture->retain();
  CCScene *s = CCDirector::sharedDirector()->getRunningScene();
  CCLog("%d", s->getTag());
  
  if (s->getTag() == 30)
  {
    renderTexture->begin();
    s->visit();
    renderTexture->end();
    CCScene *pause = PauseLayer::scene(renderTexture, true);
    pause->setTag(30+1);
    CCDirector::sharedDirector()->pushScene(pause);
    
  }
  else
  {
    CCLog("do nothing");
    
  }
}

void AppDelegate::applicationWillEnterForeground()
{
  CCDirector::sharedDirector()->startAnimation();
  CCDirector::sharedDirector()->startAnimation();
  int tag = CCDirector::sharedDirector()->getRunningScene()->getTag();

  switch (tag)
  {
  case 30:
	  CCLog("Tag = 30 do nothing");
	  break;
  case 31:
	  CCLog("Tag = 31 do nothing");
	  break;
  default:
	  CCLog("Tag = other do something");
	  CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	  break;
  }
}

