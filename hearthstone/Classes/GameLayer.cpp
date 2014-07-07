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

	/* time progress */
	CCSprite *s2=CCSprite::create("time2.png");     
	s2->setPosition(ccp(winSize.width / 2+390, winSize.height / 2-100));    
	this->addChild(s2,0);    
	CCSprite *s=CCSprite::create("time1.png");    
	CCProgressTimer *pt=CCProgressTimer::create(s);    
	pt->setPosition(ccp(winSize.width / 2+390, winSize.height / 2-100));    
	pt->setType(cocos2d::CCProgressTimerType(kCCProgressTimerTypeBar));
	pt->setBarChangeRate(ccp(1, 0));
	this->addChild(pt,1);    
	CCProgressTo *t=CCProgressTo::create(60,100);    
	pt->runAction(CCRepeatForever::create(t));

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
  

	/* time label */
	CCLabelTTF* pLabel = CCLabelTTF::create("Time", "Arial", 30);//要显示的内容，字体，字号    
	pLabel->setPosition(ccp(winSize.width / 2+390, winSize.height / 2-150));  
	this->addChild(pLabel, 1);  

	/*init player*/
	player1.init();
	/*draw card*/

	for(int i = 0 ; i < player1._handcard._card.size(); i++)
	{
		NumberToCard(player1._handcard._card[i])->Sprite_card = Sprite::create("218.png");
		NumberToCard(player1._handcard._card[i])->Sprite_card -> setPosition(Point(100 + 100 * i, winSize.height / 2-260));
		this->addChild(NumberToCard(player1._handcard._card[i])->Sprite_card);
	}
	
	card_move(player1);
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

void GameLayer::card_move(Player &player1)
{
	auto listener1 = EventListenerTouchOneByOne::create();//创建一个触摸监听
	listener1->setSwallowTouches(true); //设置是否想下传递触摸
	
 
	//通过 lambda 表达式 直接实现触摸事件的回掉方法
	listener1->onTouchBegan = [](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
    
		if (rect.containsPoint(locationInNode))
		{
			target->setOpacity(180);
			return true;
		}
		return false;
	};
 
	listener1->onTouchMoved = [](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		target->setPosition(target->getPosition() + touch->getDelta());
	};
 
	listener1->onTouchEnded = [=](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = touch->getLocation();
		Rect rect1 = Rect(60,140,90,128);
		if (rect1.containsPoint(locationInNode))
		{
			target->setOpacity(255);
			target->setPosition(60+45,140+64);
		}
		else
		{
			target->setPosition(Point(100 + 100 *  player1._handcard._card.size() , 640 / 2-260));
		}
	};
 
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, NumberToCard(player1._handcard._card[1])->Sprite_card);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), NumberToCard(player1._handcard._card[2])->Sprite_card);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), NumberToCard(player1._handcard._card[0])->Sprite_card);

}

 bool GameLayer:: onTouchBegan(Touch *touch, Event *unused_event)
{
	AllocConsole(); freopen("CONIN$", "r", stdin);
 freopen("CONOUT$", "w", stdout); freopen("CONOUT$", "w", stderr);
	 CCLOG("touch menu");  
        return true; 
};
void GameLayer:: onTouchMoved(Touch *touch, Event *unused_event)
{
}; 
void GameLayer:: onTouchEnded(Touch *touch, Event *unused_event){}; 
void GameLayer:: onTouchCancelled(Touch *touch, Event *unused_event){};