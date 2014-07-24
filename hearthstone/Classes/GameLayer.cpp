#include "GameLayer.h"

USING_NS_CC;

#define MAXCARD 5
#define MAXMINION 5
#define WINSIZE_W 960
#define WINSIZE_H 640
#define SPACING 100

int GameLayer::operator_position = 0;
int GameLayer::battlefield_position  = 0;
bool GameLayer::is_first_turn = true;
int GameLayer::minion1_position = 0;
int GameLayer::minion2_position = 0;

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
	init_img();
	player1.is_first = Is_First;
	player1.init();
	//player2.init();
	is_first_turn = !Is_First;

	/* background */
	Sprite* bgSp = Sprite::create("gamelayer.png");
    bgSp->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    bgSp->setScaleX(winSize.width/1440);
    bgSp->setScaleY(winSize.height/900);
    this->addChild(bgSp,0,0);

	/* button */
	auto cardMenuItem=MenuItemImage::create("chupai.png","chupai.png",CC_CALLBACK_1(GameLayer::cardMenuCallback, this, &player1, &operator_position ,&battlefield_position));
	cardMenuItem->setPosition(Point(winSize.width / 2+390, winSize.height / 2-220));
	auto cardMenu=Menu::create(cardMenuItem,NULL);
	cardMenu->setPosition(Point::ZERO); 
	this->addChild(cardMenu,1);

	auto endMenuItem=MenuItemImage::create("huihejieshu.png","huihejieshu.png",CC_CALLBACK_1(GameLayer::endMenuCallback, this , &player1, &player2 ,&operator_position , &battlefield_position));
	endMenuItem->setPosition(Point(winSize.width / 2+390, winSize.height / 2-275));
	auto endMenu=Menu::create(endMenuItem,NULL);
	endMenu->setPosition(Point::ZERO); 
	this->addChild(endMenu,1);
  
	/* turn label */
	turn_label.create("stat_label",  "Arial", 60);
	turn_label.setString("Your turn");
	turn_label.setFontSize(20);
	turn_label.retain();
	turn_label.setVisible(true); 
	turn_label.setPosition(ccp(winSize.width *9/10, winSize.height *19/20) );  
	this->addChild(&turn_label, 1); 

	/* mana label */
	mana_label.create("mana_label",  "Arial", 60);
	mana_label.setString("mana : 0/0");
	mana_label.setFontSize(20);
	mana_label.retain();
	mana_label.setVisible(true); 
	mana_label.setPosition(ccp(winSize.width *9/10, winSize.height *18/20) );  
	this->addChild(&mana_label, 1); 
 

	/* stat label */
	stat_label.create("stat_label",  "Arial", 60);
	stat_label.setFontSize(20);
	stat_label.retain();
	stat_label.setVisible(false); 
	stat_label.setPosition(ccp(winSize.width *9/10, winSize.height *15/20) );  
	this->addChild(&stat_label, 1); 

	if(player1.is_first)
	{
		player1.turn();
		player1.draw();
		refresh_mana();

		/* init the handcard */
		for(int i = 0 ; i < player1._handcard._card.size(); i++)
		{
			Card* tmp_sprite = NumberToCard(player1._handcard._card[i]);
			sprite_vec.push_back(tmp_sprite);
			tmp_sprite->Sprite_card = Sprite::create(NumberToFilename(player1._handcard._card[i]));//we should use the file path
			tmp_sprite->Sprite_card->setPosition(Point(SPACING + SPACING * i, winSize.height / 2-260));
			this->addChild(tmp_sprite->Sprite_card);		
		}

		/* create the event listenr to the sprite*/
		
		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->setSwallowTouches(true);
		touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
		touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, sprite_vec[0]->Sprite_card);
		for(int i = 1 ; i < player1._handcard._card.size() ;i++)
		{
			_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(),sprite_vec[i]->Sprite_card);
		}

		for(int i  = 0 ; i < player1._handcard._card.size() ; i++)
		{
			cl.draw_card(player1._handcard._card[i]);
			Sleep(200);
		}
	}
	else
	{
		/* init the handcard */
		refresh_turn();
		player2.turn();
		setTouchEnabled(false);
		for(int i = 0 ; i < player1._handcard._card.size(); i++)
		{
			Card* tmp_sprite = NumberToCard(player1._handcard._card[i]);
			sprite_vec.push_back(tmp_sprite);
			tmp_sprite->Sprite_card = Sprite::create(NumberToFilename(player1._handcard._card[i]));//we should use the file path
			tmp_sprite->Sprite_card->setPosition(Point(SPACING + SPACING * i, winSize.height / 2-260));
			this->addChild(tmp_sprite->Sprite_card);		
		}

		/* create the event listenr to the sprite*/
		
		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->setSwallowTouches(true);
		touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
		touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, sprite_vec[0]->Sprite_card);
		for(int i = 1 ; i < player1._handcard._card.size() ;i++)
		{
			_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(),sprite_vec[i]->Sprite_card);
		}

		std::thread wait(GameLayer::wait_message, this, &player1 , &player2);
		wait.detach();
	}
	
    return true;

}

/* 每回合出牌后调用的回调函数*/
void GameLayer::cardMenuCallback(Object* pSender, Player * player1,int *operator_position,int *battlefield_position )
{
	if(sprite_vec[*operator_position]->_type ==  MINION)
	{
				
		if	( player1->use(*operator_position ,* battlefield_position) )
		{
			/* release the sprite of the handcard */
			this->removeChild(sprite_vec[*operator_position]->Sprite_card,true);
			/*maybe we need send some mes to server*/
			int tmp_pos  = update_battlefiled(player1 , 0 ,operator_position , battlefield_position);
			sprite_vec.erase(sprite_vec.begin() + *operator_position);
			cl.use_card(*operator_position , tmp_pos);
			/*restore the hand card*/
			if(player1->_handcard._card.size() > 1)
			{
				for(int i  = (* operator_position); i < player1->_handcard._card.size(); i++ )
				{
					sprite_vec[i]->Sprite_card -> setPosition(Point(SPACING + SPACING * i, WINSIZE_H / 2-260));
				}
			}
		}
		/*if we can not use the card , we should restore the position of the card*/
		else
		{
			sprite_vec[*operator_position]->Sprite_card->setPosition(Point(SPACING +SPACING * *operator_position , WINSIZE_H / 2-260));
		}
	}
	refresh_mana();
}


/* 每回合结束回合后调用的回调函数*/
void GameLayer::endMenuCallback(Object* pSender, Player * p1,Player * p2 , int * operator_position ,int * battlefield_position)
{
	setTouchEnabled(false);
	cl.end_turn();
	p1->over();
	p2->turn();
	refresh_turn();
	std::thread wait(GameLayer::wait_message, this, p1 , p2);
	wait.detach();
}

/* 更新战场随从的信息 */
int GameLayer::update_battlefiled(Player * p1 ,int side ,int * operator_position ,int * battlefield_position)
{
		int tmp_pos = 0;
		if(* battlefield_position >  p1->_battlefield->_minion[side].size() -1 )
		{
			tmp_pos = p1->_battlefield->_minion[side].size() - 1 ;
		}
		else
		{
			tmp_pos = *battlefield_position ;
		}
		
		/* add new minion the battlefield */
		
		//p1->_battlefield->_minion[side][tmp_pos] = find_minion(p1->_battlefield->_minion[side][tmp_pos]->no);
		string str = CharacterToFilename(p1->_battlefield->_minion[side][tmp_pos]);
		p1->_battlefield->_minion[side][tmp_pos]->Sprite_card = Sprite::create(str,Rect(0,0,90,128));
		Point p = Point(60 + SPACING * tmp_pos + 45 , side * 200 + 140 + 64 );
		p1->_battlefield->_minion[side][tmp_pos]->Sprite_card->setPosition(Point(60 + SPACING * tmp_pos + 45 , side * 200 + 140 + 64 ));
		this->addChild(p1->_battlefield->_minion[side][tmp_pos]->Sprite_card);
		b_add_touchListener(p1 ,side , operator_position , battlefield_position , tmp_pos);
		
		for(int i  = tmp_pos + 1 ; i <  p1->_battlefield->_minion[side].size(); i++)
		{
			if(p1->_battlefield->_minion[side][i] != NULL)
			{
				p1->_battlefield->_minion[side][i - 1 ]->Sprite_card->setPosition(Point(60 + SPACING *(i - 1) + 45 , side * 200  + 140 + 64 ));
			}
		}

		return tmp_pos;
}


/* 更新杀敌后战场全部最新信息 */
void GameLayer::update_battlefiled_all(bool visible)
{
	for (int i = 0; i < player1._battlefield->_minion[0].size(); i++)
	{
		if (visible)
		{
			player1._battlefield->_minion[0][i]->Sprite_card->setOpacity(255);
			player1._battlefield->_minion[0][i]->Sprite_card->setPosition(60+100*i+45,140+64);
		}
		else
			player1._battlefield->_minion[0][i]->Sprite_card->setOpacity(0);
	}
	for (int i = 0; i < player2._battlefield->_minion[1].size(); i++)
	{
		if (visible)
		{
			player2._battlefield->_minion[1][i]->Sprite_card->setPosition(60+100*i+45,340+64);
			player2._battlefield->_minion[1][i]->Sprite_card->setOpacity(255);
		}
		else
			player2._battlefield->_minion[1][i]->Sprite_card->setOpacity(0);
	}
}

/* side方m1进攻对方m2的后台和前台包装函数 */
void GameLayer::attack(int side, int m1, int m2)
{
	update_battlefiled_all(false);
	player1._battlefield->attack(player1._battlefield->_minion[side][m1],player2._battlefield->_minion[1-side][m2]);
	player1._battlefield->checkAndDead();
	update_battlefiled_all(true);
}

/* 更新手牌的信息 */
void GameLayer:: update_handcard(Player* p1 ,int num)
{
	int size_card = p1->_handcard._card.size();
	for(int i = num ; i > 0 ; i--)
	{
		Card* tmp_sprite = NumberToCard(p1->_handcard._card[size_card - i]);
		sprite_vec.push_back(tmp_sprite);
		string str = NumberToFilename(player1._handcard._card[size_card - i]);
		tmp_sprite->Sprite_card = Sprite::create(str,Rect(0,0,90,128));
		tmp_sprite->Sprite_card->setPosition(Point(SPACING + SPACING * ( size_card - i ), WINSIZE_H / 2-260));
		h_add_touchListener(p1 ,&operator_position ,&battlefield_position ,size_card - i);
		this->addChild(tmp_sprite->Sprite_card);
	}
}

/* 更新法力水晶显示 */
void GameLayer::refresh_mana()
{
	int cur = player1._mana._cur_mana;
	int max = player1._mana._max_mana;
	string str1 = to_string(cur);
	string str2 = to_string(max);
	string str = "mana : ";
	str += str1;
	str +=  "/";
	str += str2;

	mana_label.setString(str);

}

/* 更新随从信息 */
void GameLayer::refresh_stat(Character* m, Touch* touch)
{
	string str = "";
	string str1 = "attack : ";
	str1 += to_string(m->attack());
	str1 += "\n";
	str += str1;
	str1 = "current health : ";
	str1 += to_string(m->health());
	str1 += "\n";
	str += str1;
	str1 = "max health : ";
	str1 += to_string(m->maxHealth());
	str1 += "\n";
	str += str1;
	str1 = "can attack : ";
	str1 += m->canAttack() ? "true" : "false";
	str1 += "\n";
	str += str1;
	stat_label.setString(str);
	stat_label.setVisible(true);

	CCPoint point = touch->getLocation(); 
	stat_label.setPosition(point);
	stat_label.setOpacity(200);
	//CCMoveTo *move = CCMoveTo::create(1, point); //创建一个Action  
	//stat_label.runAction(move);//执行这个Action 
	scheduleOnce(schedule_selector(GameLayer::stat_hide), 3.0f);
}

/* 隐藏stat */
void GameLayer::stat_hide(float f)
{
	stat_label.setVisible(false);
}

/* 更新谁的回合 */
void GameLayer::refresh_turn()
{
	if (turn_label.getString() == "Your turn")
		turn_label.setString("Opponent's turn");
	else
		turn_label.setString("Your turn");
}

/* 将战场中需要监听的对象加入监听 */
bool GameLayer:: b_add_touchListener(Player * p1,int side , int * operator_pos ,int * battlefield_pos ,int tmp_pos)
{
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::b_onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::b_onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::b_onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,  p1->_battlefield->_minion[side][tmp_pos]->Sprite_card);
	return true;
}

/* 将手牌中需要监听的对象加入监听 */
bool GameLayer:: h_add_touchListener(Player * p1, int * operator_pos ,int * battlefield_pos ,int tmp_pos)
{
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,  sprite_vec[tmp_pos]->Sprite_card);
	return true;
}

void GameLayer::timeCallback(float c)
{
	//wait_message(&player1, &player2);
}

bool GameLayer::onTouchBegan(Touch *touch, Event *event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	Node * b=  event->getCurrentTarget();
	Point a = target->getPosition();
	Point touchPoint  =  touch->getLocation();
	Point locationInNode = target->convertToNodeSpace(touchPoint);
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);
	/* Limited range of touch */
	if(touch->getLocation().y < 124)
	{
		/* get the position of the card that we are operatoring*/
		if(((int) touch->getLocation().x % 100) > 55 || ( ( (int)(touch->getLocation()).x % 100 ) < 45 ))
			{
				int tmp = ( touch->getLocation().x - 45 ) / 100;
				operator_position = tmp;
			}
	    if (rect.containsPoint(locationInNode))
			{
				target->setOpacity(180);
				return true;
			}
	}
	return false;
};

void  GameLayer::onTouchMoved(Touch *touch, Event *event)
{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		target->setPosition(target->getPosition() + touch->getDelta());
}; 

void GameLayer::onTouchEnded(Touch *touch, Event *event)
{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = touch->getLocation();

		Rect rect1 = Rect(60,140,90,128);
		Rect rect2 = Rect(160,140,90,128);
		Rect rect3 = Rect(260,140,90,128);
		Rect rect4 = Rect(360,140,90,128);
		Rect rect5 = Rect(460,140,90,128);
		Rect rect6 = Rect(560,140,90,128);
		Rect rect7 = Rect(660,140,90,128);
		bool f = true;

		/* ugly code */
		if (rect1.containsPoint(locationInNode))
		{
			target->setOpacity(255);
			target->setPosition(60+45,140+64);
			battlefield_position = 0;
			
			
		}
		else if(rect2.containsPoint(locationInNode))
		{
			target->setOpacity(255);
			target->setPosition(160+45,140+64);
			battlefield_position = 1;
			
		}
		else if(rect3.containsPoint(locationInNode))
		{
			target->setOpacity(255);
			target->setPosition(260+45,140+64);
			battlefield_position = 2;
		}
		else if(rect4.containsPoint(locationInNode))
		{
			target->setOpacity(255);
			target->setPosition(360+45,140+64);
			battlefield_position = 3;
			
		}
		else if(rect5.containsPoint(locationInNode))
		{
			target->setOpacity(255);
			target->setPosition(460+45,140+64);
			battlefield_position = 4;
			
		}
		else if(rect6.containsPoint(locationInNode))
		{
			target->setOpacity(255);
			target->setPosition(560+45,140+64);
			battlefield_position = 5;
			
		}
		else if(rect7.containsPoint(locationInNode))
		{
			target->setOpacity(255);
			target->setPosition(660+45,140+64);
			battlefield_position = 6;
			
		}
		else
		{
			target->setOpacity(255);
			target->setPosition(Point(SPACING + SPACING * (operator_position) , 640 / 2-260));
			f = false;
		}
}; 

bool GameLayer::b_onTouchBegan(Touch *touch, Event *event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	Node * b=  event->getCurrentTarget();
	Point a = target->getPosition();
	Point touchPoint  =  touch->getLocation();
	Point locationInNode = target->convertToNodeSpace(touchPoint);
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);
	/* Limited range of touch */
	if(  140 < touch->getLocation().y && touch->getLocation().y < 268)
	{
		int tmp;
		/* get the position of the card that we are operatoring*/
		if(((int) touch->getLocation().x % 100) > 60 || ( ( (int)(touch->getLocation()).x % 100 ) <50 ))
			{
				tmp = ( touch->getLocation().x - 50 ) / 100;
				minion1_position = tmp;
			}
	    if (rect.containsPoint(locationInNode))
			{
				refresh_stat(player1._battlefield->_minion[0][tmp],touch);
				return true;
			}
	}
	if(  340 < touch->getLocation().y && touch->getLocation().y < 468)
	{
		minion1_position = -1;
		int tmp;
		/* get the position of the card that we are operatoring*/
		if(((int) touch->getLocation().x % 100) > 60 || ( ( (int)(touch->getLocation()).x % 100 ) < 50 ))
			{
				tmp = ( touch->getLocation().x - 50 ) / 100;
			}
	    if (rect.containsPoint(locationInNode))
			{
				refresh_stat(player2._battlefield->_minion[1][tmp],touch);
				return true;
			}
	}

	minion1_position = -1;
	return false;
};

void  GameLayer::b_onTouchMoved(Touch *touch, Event *event)
{
	//	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	//	target->setPosition(target->getPosition() + touch->getDelta());
}; 

void GameLayer::b_onTouchEnded(Touch *touch, Event *event)
{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = touch->getLocation();

		Rect rect1 = Rect(60,340,90,128);
		Rect rect2 = Rect(160,340,90,128);
		Rect rect3 = Rect(260,340,90,128);
		Rect rect4 = Rect(360,340,90,128);
		Rect rect5 = Rect(460,340,90,128);
		Rect rect6 = Rect(560,340,90,128);
		Rect rect7 = Rect(660,340,90,128);
		bool f = true;

		/* ugly code */
		if (rect1.containsPoint(locationInNode) && player1._battlefield->_minion[1].size() > 0)
		{
			minion2_position = 0;
		}
		else if(rect2.containsPoint(locationInNode) && player1._battlefield->_minion[1].size() > 1)
		{
			minion2_position = 1;
		}
		else if(rect3.containsPoint(locationInNode) && player1._battlefield->_minion[1].size() > 2)
		{
			minion2_position = 2;
		}
		else if(rect4.containsPoint(locationInNode) && player1._battlefield->_minion[1].size() > 3)
		{
			minion2_position = 3;
			
		}
		else if(rect5.containsPoint(locationInNode) && player1._battlefield->_minion[1].size() > 4)
		{
			minion2_position = 4;
			
		}
		else if(rect6.containsPoint(locationInNode) && player1._battlefield->_minion[1].size() > 5)
		{
			minion2_position = 5;
			
		}
		else if(rect7.containsPoint(locationInNode) && player1._battlefield->_minion[1].size() > 6)
		{
			minion2_position = 6;
		}
		else
		{
			minion2_position = -1;
		}

		if (minion1_position >= 0 && minion2_position >= 0)
		{
			//TODO: minion1 attack minion2
			if (player1._battlefield->_minion[0][minion1_position]->canAttack())
			{
				attack(0, minion1_position, minion2_position);
				cl.attack(minion1_position, minion2_position);
			}

		}
}; 

void GameLayer::wait_message(GameLayer * g,Player * player1 , Player * player2)
{

	int _card_position;
	int _position;
	int _side;
	int _target;
	int _minion1;
	int _minion2;
	int _card;
	while (1)
	{
		vector<int> vi = cl.opponent_turn();
		switch (vi[0])
		{
			case 6:
				if (vi[1] == '1')
					;//TODO: you lose
				else
				if (vi[1] == '2')
					;//TODO: you win
				else
					;//TODO: draw
				break;
			case 4:
				//TODO: player2.endturn()
				g->setTouchEnabled(true);
				player2->over();
				player1->turn();
				player1->draw();
				g->update_handcard(player1 , 1);
				g->refresh_mana();
				g->refresh_turn();
				if (is_first_turn)
				{
					is_first_turn = false;
					for(int i  = 0 ; i < player1->_handcard._card.size() ; i++)
					{
						cl.draw_card(player1->_handcard._card[i]);
						Sleep(200);
					}
				}
				else
					cl.draw_card(player1->_handcard._card[player1->_handcard._card.size()-1]);
				return;
			case 1:
				_card_position = vi[1];
				_position = vi[2];
				_side = vi[3];
				_target = vi[4];
				//TODO: player2.use(_card_position, _position, _side, _target);
				if(player2->use(_card_position, _position))
					g->update_battlefiled(player2 , 1 ,&_card_position , &_position );
				break;
			case 2:
				_minion1 = vi[1];
				_minion2 = vi[2];
				//TODO: battlefield[1][_minion2] attack battlefield[0][_minion1];
				g->attack(1, _minion1, _minion2);
				break;
			case 8:
				_card = vi[1];
				//TODO: player2.handcard.draw(_card);
				player2->_handcard.draw_card(_card);
				break;
			default:
				;//TODO: error,should never reach here
		}
		
	}
}

void GameLayer::init_img()
{
	for(int i = 0 ; i < player1._deck->_amount; i++ )
	{
		Card* tmp_sprite = NumberToCard(player1._deck->_card[i]);
		sprite_vec.push_back(tmp_sprite);
		tmp_sprite->Sprite_card = Sprite::create(NumberToFilename(player1._deck->_card[i]));
	}
	sprite_vec.clear();
	/*
	for(int j = 1; j <= MAXCARDNO; j++)
	{
		for(int k = 0 ; k < 30 ; k++)
		{
			MinionCard* tmp_sprite =(MinionCard *) NumberToCard(j);
			tmp_sprite->_minion->Sprite_card= Sprite::create(CharacterToFilename(tmp_sprite->_minion));
			minion_vec.push_back(tmp_sprite);
		}
	}
	*/
	
	int m = 0;
	for(int k = 0 ; k < 9 ; k++)
	{
		player2.turn();
		player2.draw();
	}
		for(int  j = 0 ; j < 30 ; j++)
	{
		player2.turn();
		player2.draw();
		if(player2.use(0,j))
		{
			string str = CharacterToFilename(player2._battlefield->_minion[1][j]);
			Sprite * Sprite_card = Sprite::create(CharacterToFilename(player2._battlefield->_minion[1][j])); 
			if(player2._battlefield->_minion[1].size() == 10)
			{
				player2._battlefield->_minion[1].clear();
				j = -1;
			}
			m++;
		}
		if(m == 30)
		{
			player2._battlefield->_minion[1].clear();
			player2._deck->_amount =30;
			player2._handcard._card.clear();
			player2._mana._max_mana = 0;
			player2._mana._cur_mana = 0;
			break;
		}
	}
}

Minion * GameLayer::find_minion(int no)
{
	Minion * tmp_minion ;
	for(int i = 0 ; i < minion_vec.size() ; i++)
	{
		if(no == minion_vec[i]->_minion->no)
		{
			tmp_minion = minion_vec[i]->_minion;
			minion_vec.erase(minion_vec.begin() + i);
			return tmp_minion;
		}

	}
	return NULL;
}