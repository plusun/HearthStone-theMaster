#include "GameLayer.h"

USING_NS_CC;

#define MAXCARD 5
#define MAXMINION 5

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

	/*init player*/
	player1.init();
	static int operator_position = 0;
	static int battlefield_position = 0;

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
	auto cardMenuItem=MenuItemImage::create("chupai.png","chupai.png",CC_CALLBACK_1(GameLayer::cardMenuCallback, this, &player1, &ai, &operator_position ,&battlefield_position));
	cardMenuItem->setPosition(Point(winSize.width / 2+390, winSize.height / 2-220));
	auto cardMenu=Menu::create(cardMenuItem,NULL);
	cardMenu->setPosition(Point::ZERO); 
	this->addChild(cardMenu,1);

	auto endMenuItem=MenuItemImage::create("huihejieshu.png","huihejieshu.png",CC_CALLBACK_1(GameLayer::endMenuCallback, this , &player1 ,&ai ,&operator_position , &battlefield_position));
	endMenuItem->setPosition(Point(winSize.width / 2+390, winSize.height / 2-275));
	auto endMenu=Menu::create(endMenuItem,NULL);
	endMenu->setPosition(Point::ZERO); 
	this->addChild(endMenu,1);
  

	/* time label */
	CCLabelTTF* pLabel = CCLabelTTF::create("Time", "Arial", 30);//Ҫ��ʾ�����ݣ����壬�ֺ�    
	pLabel->setPosition(ccp(winSize.width / 2+390, winSize.height / 2-150));  
	this->addChild(pLabel, 1);  

	
	
	/* init the handcard */
	//for(int i = 0 ; i < player1._handcard._card.size(); i++)
	//{
		NumberToCard(player1._handcard._card[0])->Sprite_card = Sprite::create("218.png");//we should use the file path
		NumberToCard(player1._handcard._card[0])->Sprite_card -> setPosition(Point(100 + 100 * 0, winSize.height / 2-260));
		this->addChild(NumberToCard(player1._handcard._card[0])->Sprite_card);
		NumberToCard(player1._handcard._card[1])->Sprite_card = Sprite::create("256.png");//we should use the file path
		NumberToCard(player1._handcard._card[1])->Sprite_card -> setPosition(Point(100 + 100 * 1, winSize.height / 2-260));
		this->addChild(NumberToCard(player1._handcard._card[1])->Sprite_card);
		NumberToCard(player1._handcard._card[2])->Sprite_card = Sprite::create("231.png");//we should use the file path
		NumberToCard(player1._handcard._card[2])->Sprite_card -> setPosition(Point(100 + 100 * 2, winSize.height / 2-260));
		this->addChild(NumberToCard(player1._handcard._card[2])->Sprite_card);
	//}
	

	/* create the event listenr to the sprite*/
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(false);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this,&operator_position);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this, &player1 ,&operator_position ,&battlefield_position);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, NumberToCard(player1._handcard._card[0])->Sprite_card);
	for(int i = 1 ; i < player1._handcard._card.size() ;i++)
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), NumberToCard(player1._handcard._card[i])->Sprite_card);
	
    return true;

}

/* ÿ�غϳ��ƺ���õĻص�����*/
void GameLayer::cardMenuCallback(Object* pSender, Player * player1 ,AI * player2 ,int *operator_position,int *battlefield_position )
{
	if(NumberToCard(player1->_handcard._card[*operator_position])->_type ==  MINION)
			{
				/* release the sprite of the handcard */
				this->removeChild(NumberToCard(player1->_handcard._card[*operator_position])->Sprite_card,true);
				
				if	( player1->use(*operator_position ,* battlefield_position) )
				{
					/*maybe we need send some mes to server*/
					update_battlefiled(player1 , 0 ,operator_position , battlefield_position);
				}
				/*if we can not use the card , we should restore the position of the card*/
				else
				{
					NumberToCard(player1->_handcard._card[*operator_position])->Sprite_card = Sprite::create("218.png");//we should use the file path
					NumberToCard(player1->_handcard._card[*operator_position])->Sprite_card -> setPosition(Point(100 +100 * *operator_position , 640 / 2-260));
					this->addChild(NumberToCard(player1->_handcard._card[*operator_position])->Sprite_card);
					
					for(int i  = (* operator_position) + 1; i < player1->_handcard._card.size(); i++ )
					{
						NumberToCard(player1->_handcard._card[i])->Sprite_card -> setPosition(Point(100 + 100 * i, 640 / 2-260));
					}
				}
			}

}


/* ÿ�غϽ����غϺ���õĻص�����*/
void GameLayer::endMenuCallback(Object* pSender, Player * p1 , AI * p2 , int * operator_position ,int * battlefield_position)
{
	p1->over();
	p2->play();
	//update_battlefiled(p1,operator_position, battlefield_position );
	p1->turn();
	update_handcard(p1);
}

/* ����ս����ӵ���Ϣ */
void GameLayer::update_battlefiled(Player * p1 ,int side ,int * operator_position ,int * battlefield_position)
{
	int tmp_pos = 0;
	if(side  == 0)
	{
		if(* battlefield_position >  p1->_battlefield->_minion[0].size() -1 )
		{
			tmp_pos = p1->_battlefield->_minion[0].size() - 1 ;
		}
		else
		{
			tmp_pos = *battlefield_position ;
		}
		
		/* add new minion the battlefield */
		p1->_battlefield->_minion[side][tmp_pos]->Sprite_card = Sprite::create("218.png");
		p1->_battlefield->_minion[side][tmp_pos]->Sprite_card->setPosition(Point(60 + 100 * tmp_pos + 45 , 140 +64 ));
		this->addChild(p1->_battlefield->_minion[side][tmp_pos]->Sprite_card);
		add_touchListener(p1 ,0 , operator_position , battlefield_position , tmp_pos);
		
		for(int i  = tmp_pos + 1 ; i <  p1->_battlefield->_minion[0].size(); i++)
		{
			if(p1->_battlefield->_minion[side][i] != NULL)
			{
				p1->_battlefield->_minion[side][i - 1 ]->Sprite_card->setPosition(Point(60 + 100 *(i - 1) + 45 , 140 +64 ));
			}
		}
	}
}
/* �������Ƶ���Ϣ */

void GameLayer:: update_handcard(Player* p1)
{
	NumberToCard(p1->_handcard._card[p1->_handcard._card.size() - 1])->Sprite_card = Sprite::create("218.png");
    NumberToCard(p1->_handcard._card[p1->_handcard._card.size() - 1])->Sprite_card -> setPosition(Point(100 +100 * p1->_handcard._card.size() , 640 / 2-260));
    this->addChild( NumberToCard(p1->_handcard._card[ p1->_handcard._card.size() - 1])->Sprite_card);
}


/* ����Ҫ�����Ķ��������� */
bool GameLayer:: add_touchListener(Player * p1,int side , int * operator_pos ,int * battlefield_pos ,int tmp_pos)
{
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(false);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this, operator_pos);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this, p1 ,operator_pos , battlefield_pos);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,  p1->_battlefield->_minion[side][tmp_pos]->Sprite_card);
	return true;
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
	/* Limited range of touch */
	if(touch->getLocation().y < 540)
	{
		/* get the position of the card that we are operatoring*/
		if(((int) touch->getLocation().x % 100) > 60 || ( ( (int)(touch->getLocation()).x % 100 ) <40 ))
			{
				int tmp = ( touch->getLocation().x - 40 ) / 100;
				*postion = tmp;
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

void GameLayer:: onTouchEnded(Touch *touch, Event *event , Player * player1 , int * operator_position , int * battlefield_position)
{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = touch->getLocation();

		Rect rect1 = Rect(60,140,90,128);
		Rect rect2 = Rect(160,140,90,128);
		Rect rect3 = Rect(260,140,90,128);
		Rect rect4 = Rect(360,140,90,128);
		Rect rect5 = Rect(460,140,90,128);
		Rect rect6 = Rect(560,140,90,128);


		/* ugly code */
		if (rect1.containsPoint(locationInNode))
		{
			target->setOpacity(255);
			target->setPosition(60+45,140+64);
			* battlefield_position = 0;
			
			
		}
		else if(rect2.containsPoint(locationInNode))
		{
			target->setOpacity(255);
			target->setPosition(160+45,140+64);
			* battlefield_position = 1;
			
		}
		else if(rect3.containsPoint(locationInNode))
		{
			target->setOpacity(255);
			target->setPosition(260+45,140+64);
			* battlefield_position = 2;
		}
		else if(rect4.containsPoint(locationInNode))
		{
			target->setOpacity(255);
			target->setPosition(360+45,140+64);
			* battlefield_position = 3;
			
		}
		else if(rect5.containsPoint(locationInNode))
		{
			target->setOpacity(255);
			target->setPosition(460+45,140+64);
			* battlefield_position = 4;
			
		}
		else if(rect6.containsPoint(locationInNode))
		{
			target->setOpacity(255);
			target->setPosition(560+45,140+64);
			* battlefield_position = 5;
			
		}
		else
		{
			target->setOpacity(255);
			target->setPosition(Point(100 + 100 * ( *operator_position) , 640 / 2-260));
		}

		/* restore the handcard*/
		if(player1->_handcard._card.size() > 1)
		{
			for(int i  = (* operator_position) + 1; i < player1->_handcard._card.size(); i++ )
			{
				NumberToCard(player1->_handcard._card[i])->Sprite_card -> setPosition(Point(100 * i, 640 / 2-260));
			}
		}



}; 
void GameLayer:: onTouchCancelled(Touch *touch, Event *unused_event){};