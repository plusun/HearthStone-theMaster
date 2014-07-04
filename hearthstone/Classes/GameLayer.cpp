#include "GameLayer.h"

USING_NS_CC;


Scene* GameLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool GameLayer::init()
{
	if ( !Layer::init() )
    {
        return false;
    }

    setTouchEnabled(true);

	CCSize winSize=CCDirector::sharedDirector()->getWinSize();//get window size

	/* background */
	 Sprite* bgSp = Sprite::create("gamelayer.png");
    bgSp->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    bgSp->setScaleX(winSize.width/1440);
    bgSp->setScaleY(winSize.height/900);
    this->addChild(bgSp,0,0);

	
 
	/* button */
	auto LoginMenuItem=MenuItemImage::create("chupai.png","chupai.png",CC_CALLBACK_1(GameLayer::cardMenuCallback,this));
	LoginMenuItem->setPosition(Point(winSize.width / 2+390, winSize.height / 2-220));
	auto starMenu=Menu::create(LoginMenuItem,NULL);
	starMenu->setPosition(Point::ZERO); 
	this->addChild(starMenu,1);

	auto exitMenuItem=MenuItemImage::create("huihejieshu.png","huihejieshu.png",CC_CALLBACK_1(GameLayer::endMenuCallback,this));
	exitMenuItem->setPosition(Point(winSize.width / 2+390, winSize.height / 2-275));
	auto exitMenu=Menu::create(exitMenuItem,NULL);
	exitMenu->setPosition(Point::ZERO); 
	this->addChild(exitMenu,1);
  

	/* time progress */
	CCSprite *s2=CCSprite::create("time2.png");     
	s2->setPosition(ccp(winSize.width / 2+390, winSize.height / 2-100));    
	addChild(s2,0);    
	CCSprite *s=CCSprite::create("time1.png");    
	CCProgressTimer *pt=CCProgressTimer::create(s);    
	pt->setPosition(ccp(winSize.width / 2+390, winSize.height / 2-100));    
	pt->setType(cocos2d::CCProgressTimerType(kCCProgressTimerTypeBar));
	pt->setBarChangeRate(ccp(1, 0));
	this->addChild(pt,1);    
	CCProgressTo *t=CCProgressTo::create(60,100);    
	pt->runAction(CCRepeatForever::create(t));

	/* time label */
	CCLabelTTF* pLabel = CCLabelTTF::create("Time", "Arial", 30);//要显示的内容，字体，字号    
	pLabel->setPosition(ccp(winSize.width / 2+390, winSize.height / 2-150));  
	this->addChild(pLabel, 1);  

	/*init player*/
	if( player1.is_first == true )
	{
		player1._handcard.amount = 3;
	}
	else
	{
		player1._handcard.amount = 4;
	}
	/*draw card*/

	if(player1._handcard.amount = 3)
	{
		player1._handcard._card[0].Sprite_card = Sprite::create("time2.png");
		player1._handcard._card[0].Sprite_card -> setPosition(Point(winSize.width / 2+10, winSize.height / 2-275));

	}


	this->schedule(schedule_selector(GameLayer::timeCallback), 10.0f);
    return true;

}

/* 每回合出牌后调用的回调函数*/
void GameLayer::cardMenuCallback(Object* pSender)
{

}


/* 每回合结束回合后调用的回调函数*/
void GameLayer::endMenuCallback(Object* pSender)
{

}

void GameLayer::timeCallback(float ct)
{

}