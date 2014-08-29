#include "ReplayLayer.h"

USING_NS_CC;

#define MAXCARD 5
#define MAXMINION 5
#define WINSIZE_W 960
#define WINSIZE_H 640
#define SPACING 100

//int GameLayer::operator_position = 0;
//int GameLayer::battlefield_position  = 0;
//bool GameLayer::is_first_turn = true;
//int GameLayer::minion1_position = 0;
//int GameLayer::minion2_position = 0;

Scene* ReplayLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ReplayLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


bool ReplayLayer::init()
{
	if ( !Layer::init() )
    {
        return false;
    }

    setTouchEnabled(false);

	CCSize winSize=CCDirector::sharedDirector()->getWinSize();//get window size

	/*init player*/
	init_img();
	player1.is_first = true;
	is_first_turn = false;
	CCLOG("init complete!");

	/* background */
	Sprite* bgSp = Sprite::create("gamelayer.png");
    bgSp->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    bgSp->setScaleX(winSize.width/1440);
    bgSp->setScaleY(winSize.height/900);
    this->addChild(bgSp,0,0);

	/* button */
	auto cardMenuItem=MenuItemImage::create("chupai.png","chupai.png",CC_CALLBACK_1(ReplayLayer::cardMenuCallback, this, &player1, &operator_position ,&battlefield_position));
	cardMenuItem->setPosition(Point(winSize.width / 2+390, winSize.height / 2-220));
	auto cardMenu=Menu::create(cardMenuItem,NULL);
	cardMenu->setPosition(Point::ZERO); 
	this->addChild(cardMenu,1);

	auto endMenuItem=MenuItemImage::create("huihejieshu.png","huihejieshu.png",CC_CALLBACK_1(ReplayLayer::endMenuCallback, this , &player1, &player2 ,&operator_position , &battlefield_position));
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
	stat_label.setPosition(ccp(winSize.width *1/10, winSize.height *18/20) );  
	this->addChild(&stat_label, 1); 

	/* hero */
	Hero* tmp1 = new Hero(30);
	player1._battlefield->_hero[0] = tmp1;
	player1._battlefield->_hero[0]->Sprite_card = Sprite::create("lieren1.png",Rect(0,0,90,128));
	player1._battlefield->_hero[0]->Sprite_card->setPosition(Point(860+45,140+64));
	this->addChild(player1._battlefield->_hero[0]->Sprite_card);
	bh_add_touchListener(&player1, 0);
	Hero* tmp2 = new Hero(30);
	player1._battlefield->_hero[1] = tmp2;
	player1._battlefield->_hero[1]->Sprite_card = Sprite::create("lieren1.png",Rect(0,0,90,128));
	player1._battlefield->_hero[1]->Sprite_card->setPosition(Point(860+45,340+64));
	this->addChild(player1._battlefield->_hero[1]->Sprite_card);
	bh_add_touchListener(&player1, 1);



	{
		player1.turn();
		refresh_mana();
		CCLOG("first_hand init complete!");
		/* init the handcard */
		//for(int i = 0 ; i < player1._handcard._card.size(); i++)
		//{
		//	Card* tmp_sprite = NumberToCard(player1._handcard._card[i],player1._battlefield,0);
		//	sprite_vec.push_back(tmp_sprite);
		//	tmp_sprite->Sprite_card = Sprite::create(NumberToFilename(player1._handcard._card[i]));//we should use the file path
		//	tmp_sprite->Sprite_card->setPosition(Point(SPACING + SPACING * i, winSize.height / 2-260));
		//	this->addChild(tmp_sprite->Sprite_card);		
		//}

		/* create the event listenr to the sprite*/
		
		//auto touchListener = EventListenerTouchOneByOne::create();
		//touchListener->setSwallowTouches(true);
		//touchListener->onTouchBegan = CC_CALLBACK_2(ReplayLayer::onTouchBegan, this);
		//touchListener->onTouchMoved = CC_CALLBACK_2(ReplayLayer::onTouchMoved, this);
		//touchListener->onTouchEnded = CC_CALLBACK_2(ReplayLayer::onTouchEnded, this);
	
		//_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, sprite_vec[0]->Sprite_card);
		//for(int i = 1 ; i < player1._handcard._card.size() ;i++)
		//{
		//	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(),sprite_vec[i]->Sprite_card);
		//}

		//for(int i  = 0 ; i < player1._handcard._card.size() ; i++)
		//{
		//	cl.draw_card(player1._handcard._card[i]);
		//	Sleep(200);
		//}
	}

	std::thread wait(ReplayLayer::replay, this, &player1 , &player2);
	wait.detach();

    return true;

}

void ReplayLayer:: update_handcard(Player* p1 ,int num)
{
	int size_card = p1->_handcard._card.size();
	for(int i = num ; i > 0 ; i--)
	{
		Card* tmp_sprite;
		if(player1.is_first)
			tmp_sprite = NumberToCard(p1->_handcard._card[size_card - i],p1->_battlefield,0);
		else
			tmp_sprite = NumberToCard(p1->_handcard._card[size_card - i],p1->_battlefield,1);
		sprite_vec.push_back(tmp_sprite);
		string str = NumberToFilename(player1._handcard._card[size_card - i]);
		tmp_sprite->Sprite_card = Sprite::create(str,Rect(0,0,90,128));
		tmp_sprite->Sprite_card->setPosition(Point(SPACING + SPACING * ( size_card - i ), WINSIZE_H / 2-260));
		//h_add_touchListener(p1 ,&operator_position ,&battlefield_position ,size_card - i);
		this->addChild(tmp_sprite->Sprite_card);
	}
}


vector<int> ReplayLayer::torecv(char* s, char c)
{
	vector<int> vi;
	vi.clear();
	if (s[1] == '1')
		vi.push_back(1);
	else
		vi.push_back(2);
	char buf[100];
	char str[100];
	memset(str,0,sizeof(str)); 
	memset(buf,0,sizeof(buf)); 
	int head = 0;
	int tail = 0;
	for (int i = 3; i < strlen(s); i++)
	{
		if (s[i] == c)
		{
			vi.push_back(atoi(str));
			memset(str,0,sizeof(str)); 
		}
		else
		{
			sprintf_s(buf,"%c",s[i],1);
			strcat_s(str, 100, buf);
		}
	}
	return vi;
}

void ReplayLayer::replay(ReplayLayer * g,Player * player1 , Player * player2)
{
	int _card_position;
	int _position;
	int _side;
	int _target;
	int _minion1;
	int _minion2;
	int _card;
	int tmp;

	ifstream file("log.txt");
	char* buf = new char[100];
	while (!file.eof() )  
	{  
		file.getline (buf,100);  
		if (file.fail())
			break;
		vector<int> vi = g->torecv(buf);

		switch (vi[1])
		{
			case 6:
				if (vi[0] == 2)
				{
					if (vi[2] == 1)
						tmp = 2;//TODO: you lose
					else
					if (vi[2] == 2)
						tmp = 1;//TODO: you win
					else
						tmp = 3;//TODO: draw
					g->end_game(tmp);
				}
				else
				{
					if (vi[2] == 1)
						tmp = 1;//TODO: you lose
					else
					if (vi[2] == 2)
						tmp = 2;//TODO: you win
					else
						tmp = 3;//TODO: draw
					g->end_game(tmp);
				}
				//TODO:此时回收此线程
				return ;
			case 4:					//Done
				//TODO: player2.endturn()
				if (vi[0] == 1)
				{
					player1->over();
					player2->turn();
					g->refresh_turn();
				}
				else
				{
					player2->over();
					player1->turn();
					g->refresh_mana();
					g->refresh_turn();
				}
				break;
			case 1:					//Done
				_card_position = vi[2];
				_position = vi[3];
				_side = vi[4];
				_target = vi[5];
				//TODO: player2.use(_card_position, _position, _side, _target);
				if (vi[0] == 1)
				{
					g->cardMenuCallback(NULL,player1,&_card_position,&_position);
				}
				else
				{
					if(player2->use(_card_position, _position))
						g->update_battlefiled(player2 , 1 ,&_card_position , &_position );
				}
				break;
			case 2:					//Done
				_minion1 = vi[2];
				_minion2 = vi[3];
				if (vi[0] == 1)
					g->attack(0, _minion1, _minion2);
				else
					g->attack(1, _minion1, _minion2);
				break;
			case 8:					//Done
				_card = vi[2];
				if (vi[0] == 1)
				{
					player1->_handcard.draw_card(_card);
					g->update_handcard(player1,1);
				}
				else
				{
					player2->_handcard.draw_card(_card);
					goto done;
					//g->update_handcard(player2,1);
				}
				break;
			default:
				;//TODO: error,should never reach here
		}
		Sleep(1000);
done:
		;
	}
}