#include "GameLayer.h"

USING_NS_CC;

#define MAXCARD 5

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
	auto cardMenuItem=MenuItemImage::create("chupai.png","chupai.png",CC_CALLBACK_1(GameLayer::cardMenuCallback, this, &player1));
	cardMenuItem->setPosition(Point(winSize.width / 2+390, winSize.height / 2-220));
	auto cardMenu=Menu::create(cardMenuItem,NULL);
	cardMenu->setPosition(Point::ZERO); 
	this->addChild(cardMenu,1);

	auto endMenuItem=MenuItemImage::create("huihejieshu.png","huihejieshu.png",CC_CALLBACK_1(GameLayer::endMenuCallback, this));
	endMenuItem->setPosition(Point(winSize.width / 2+390, winSize.height / 2-275));
	auto endMenu=Menu::create(endMenuItem,NULL);
	endMenu->setPosition(Point::ZERO); 
	this->addChild(endMenu,1);
  

	/* time label */
	CCLabelTTF* pLabel = CCLabelTTF::create("Time", "Arial", 30);//要显示的内容，字体，字号    
	pLabel->setPosition(ccp(winSize.width / 2+390, winSize.height / 2-150));  
	this->addChild(pLabel, 1);  

	/*init player*/
	player1.init();
	static int operator_position = 0;
	/*draw card*/

	player1.draw();
	for(int i = 0 ; i < player1._handcard._card.size(); i++)
	{
		NumberToCard(player1._handcard._card[i])->Sprite_card = Sprite::create("218.png");
		NumberToCard(player1._handcard._card[i])->Sprite_card -> setPosition(Point(100 + 100 * i, winSize.height / 2-260));
		this->addChild(NumberToCard(player1._handcard._card[i])->Sprite_card);
	}
	
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(false);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this,&operator_position);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this, &player1 , &operator_position);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, NumberToCard(player1._handcard._card[0])->Sprite_card);
	for(int i = 1 ; i < player1._handcard._card.size() ;i++)
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), NumberToCard(player1._handcard._card[i])->Sprite_card);
	
    return true;

}

/* 每回合出牌后调用的回调函数*/
void GameLayer::cardMenuCallback(Object* pSender, Player * player1)
{

}


/* 每回合结束回合后调用的回调函数*/
void GameLayer::endMenuCallback(Object* pSender)
{

}

void GameLayer::timeCallback(float ct)
{

}



 bool GameLayer:: onTouchBegan(Touch *touch, Event *event , int* postion)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if(touch->getLocation().y < 140)
		{
			if(((int) touch->getLocation().x % 100) > 60 || ( ( (int)(touch->getLocation()).x % 100 ) <40 ))
			{
				int tmp = ( touch->getLocation().x - 40 ) / 100;
				*postion = 1;
			}
			if (rect.containsPoint(locationInNode))
			{
				target->setOpacity(180);
				return true;
			}
		}
		return false;
};

void  GameLayer:: onTouchMoved(Touch *touch, Event *event)
{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		target->setPosition(target->getPosition() + touch->getDelta());
}; 

void GameLayer:: onTouchEnded(Touch *touch, Event *event , Player * player1, int* operator_position )
{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = touch->getLocation();

		Rect rect1 = Rect(60,140,90,128);
		Rect rect2 = Rect(160,140,90,128);
		Rect rect3 = Rect(260,140,90,128);
		Rect rect4 = Rect(360,140,90,128);
		Rect rect5 = Rect(460,140,90,128);
		Rect rect6 = Rect(560,140,90,128);

		/*get the operator position */

		if (rect1.containsPoint(locationInNode))
		{
			target->setOpacity(255);
			target->setPosition(60+45,140+64);
			if(NumberToCard(player1->_handcard._card[*operator_position])->_type ==  MINION)
			{
				player1->use(*operator_position);
			}
		}
		else if(rect2.containsPoint(locationInNode))
		{
			target->setOpacity(255);
			target->setPosition(160+45,140+64);
			if(NumberToCard(player1->_handcard._card[*operator_position])->_type ==  MINION)
			{
				player1->use(*operator_position);
			}
		}
		else if(rect3.containsPoint(locationInNode))
		{
			target->setOpacity(255);
			target->setPosition(260+45,140+64);
			if(NumberToCard(player1->_handcard._card[*operator_position])->_type ==  MINION)
			{
				player1->use(*operator_position);
			}
		}
		else if(rect4.containsPoint(locationInNode))
		{
			target->setOpacity(255);
			target->setPosition(360+45,140+64);
			if(NumberToCard(player1->_handcard._card[*operator_position])->_type ==  MINION)
			{
				player1->use(*operator_position);
			}
		}
		else if(rect5.containsPoint(locationInNode))
		{
			target->setOpacity(255);
			target->setPosition(460+45,140+64);
			if(NumberToCard(player1->_handcard._card[*operator_position])->_type ==  MINION)
			{
				player1->use(*operator_position);
			}
		}
		else if(rect6.containsPoint(locationInNode))
		{
			target->setOpacity(255);
			target->setPosition(560+45,140+64);
			if(NumberToCard(player1->_handcard._card[*operator_position])->_type ==  MINION)
			{
				player1->use(*operator_position);
			}
		}
		else
		{
			target->setPosition(Point(100 + 100 *  player1->_handcard._card.size() , 640 / 2-260));
		}


}; 
void GameLayer:: onTouchCancelled(Touch *touch, Event *unused_event){};