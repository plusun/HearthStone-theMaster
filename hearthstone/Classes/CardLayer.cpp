#include "CardLayer.h"

int CardLayer::NumOfPage = 0;
int CardLayer::NumOfCard = 0;

Scene* CardLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = CardLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool CardLayer::init()
{
	if ( !Layer::init() )
    {
        return false;
    }

    setTouchEnabled(true);

	CCSize winSize=CCDirector::sharedDirector()->getWinSize();//get window size


	/* background */
	Sprite* bgSp = Sprite::create("card.png");
    bgSp->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    bgSp->setScaleX(winSize.width/1024);
    bgSp->setScaleY(winSize.height/610);
    this->addChild(bgSp,0,0);

	auto cardMenuItem=MenuItemImage::create("qianyiye.png","qianyiye.png",CC_CALLBACK_1(CardLayer::NextMenuCallback, this));
	cardMenuItem->setPosition(Point( 250, winSize.height / 2-275));
	auto cardMenu=Menu::create(cardMenuItem,NULL);
	cardMenu->setPosition(Point::ZERO); 
	this->addChild(cardMenu,1);

	auto endMenuItem=MenuItemImage::create("houyiye.png","houyiye.png",CC_CALLBACK_1(CardLayer::PrevMenuCallback, this));
	endMenuItem->setPosition(Point(400, winSize.height / 2-275));
	auto endMenu=Menu::create(endMenuItem,NULL);
	endMenu->setPosition(Point::ZERO); 
	this->addChild(endMenu,1);

	
	auto doneMenuItem=MenuItemImage::create("wancheng.png","wancheng.png",CC_CALLBACK_1(CardLayer::finishMenuCallback, this));
	doneMenuItem->setPosition(Point(600, winSize.height / 2-275));
	auto doneMenu=Menu::create(doneMenuItem,NULL);
	doneMenu->setPosition(Point::ZERO); 
	this->addChild(doneMenu,1);


	auto backMenuItem=MenuItemImage::create("fanhui.png","fanhui.png",CC_CALLBACK_1(CardLayer::backMenuCallback, this));
	backMenuItem->setPosition(Point(720, winSize.height / 2-275));
	auto backMenu=Menu::create(backMenuItem,NULL);
	backMenu->setPosition(Point::ZERO); 
	this->addChild(backMenu,1);


	LabelOfPage.create("label_of_page",  "Arial", 20);
	LabelOfPage.setFontSize(25);
	LabelOfPage.setVisible(true); 
	LabelOfPage.setPosition(100, winSize.height / 2-275);
	this->addChild(&LabelOfPage,1);
	ChangePage(NumOfPage);

	auto _mouseListener = EventListenerMouse::create();
    _mouseListener->onMouseDown = CC_CALLBACK_1(CardLayer::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

	UpdateImg(NumOfPage);
	scheduleOnce(schedule_selector(CardLayer::_init), 0.1f);

}

void CardLayer::NextMenuCallback(Object* pSender)
{
	if(NumOfPage != MaxPage)
		NumOfPage ++ ;
	ChangePage(NumOfPage);
	removeImg();
	UpdateImg(NumOfPage);
}

void CardLayer::PrevMenuCallback(Object* pSender)
{

	if(NumOfPage != MinPage)
		NumOfPage -- ;
	ChangePage(NumOfPage);
	removeImg();
	UpdateImg(NumOfPage);
}

void CardLayer::finishMenuCallback(Object* pSender)
{
	if (finish())
		backMenuCallback(pSender);
	else
	{
		string str = "Need 30 cards,\nYou now have " + convertInt(vi.size());
		str += " card(s)";
		label.setString(str);
		label.setVisible(true); 
		scheduleOnce(schedule_selector(CardLayer::label_hide), 3.0f);
	}
}

void CardLayer::label_hide(float f)
{
	label.setVisible(false);
}

void CardLayer::backMenuCallback(Object* pSender)
{
		CCTransitionScene * reScene = NULL;
		CCScene * s = LoginScene::createScene();
		float t = 1.2f;
		reScene = CCTransitionProgressHorizontal ::create(t , s);
		CCDirector::sharedDirector()->replaceScene(reScene);
}

void CardLayer::ChangePage(int NumOfPage)
{
	string str1 = to_string(NumOfPage);
	string str2 = to_string(MaxPage);
	string str = "Page: ";
	str += str1;
	str += "/";
	str += str2;

	LabelOfPage.setString(str);
}

void CardLayer::UpdateImg(int NumOfPage)
{
	int i = 0;
	int j = 0;
	int k = NumOfPage * 10 ;
	int pos1;
	string str1;
	for(i ; i < FirstLineOfImg && k  < MaxImg ; i++)
	{
		pos1 = k  + 1;
		str1 = to_string(pos1);
		str1 = str1 + ".png";
		Img[i] = Sprite::create(str1);
		Img[i]->setPosition(Point(100 + i * 100 ,550));
		this->addChild(Img[i]);
		k++;
	}
	for(i ; i < SecondLineOfImg && k  < MaxImg ; i++)
	{
		pos1 = k + 1;
		str1 = to_string(pos1);
		str1 = str1 + ".png";
		Img[i] = Sprite::create(str1);
		Img[i]->setPosition(Point(100 +  j * 100 ,400));
		this->addChild(Img[i]);
		j++;
		k++;
	}
}

void CardLayer::removeImg()
{
	for(int i  = 0 ; i < 10 ; i++)
		this->removeChild(Img[i],true);
}

void CardLayer::_init(float f)
{
	vi.clear();
	ifstream file("deck.txt",ios::in);
	while (!file.eof())
	{
		int tmp;
		file >> tmp;
		if (file.fail())
			break;
		vi.push_back(tmp);
	}
	file.close();


	for (int i = 0; i < _amount; i++)
	{
		sp[i] = Sprite::create("a0.png");
		sp[i]->setPosition(Point(850,610-i*20));
		this->addChild(sp[i]);
	}

	refresh_pic();
	label.create("label",  "Arial", 60);
	label.setPosition(ccp(WINSIZE_W /2, WINSIZE_H /2) );  
	label.setFontSize(40);
	label.setVisible(false);
	this->addChild(&label, 1); 
}

void CardLayer::add_card(int n)
{
	if (vi.size() < _amount)
	{
		int c = 0;
		while (c < vi.size() && vi[c] < n)
			c++;
		vi.insert(vi.begin() + c, n);
	}
	refresh_pic();
}

void CardLayer::del_card(int n)
{
	if (n < vi.size())
		vi.erase(vi.begin() + n);
	else
		return;
	refresh_pic();
}

bool CardLayer::finish()
{
	if (vi.size() != _amount)
		return false;
	ofstream file("deck.txt",ios::out);
	for (int i = 0; i < vi.size(); i++)
		file << vi[i] << " ";
	file.close();
	return true;
}

void CardLayer::refresh_pic()
{
	for (int i = 0; i < vi.size(); i++)
	{
		string name = "a" + convertInt(vi[i]) + ".png";
		CCTexture2D * text2d = CCTextureCache::sharedTextureCache()->addImage(name);
		sp[i]->setTexture(text2d);
	}
	for (int i = vi.size(); i < _amount; i++)
	{
		string name = "a0.png";
		CCTexture2D * text2d = CCTextureCache::sharedTextureCache()->addImage(name);
		sp[i]->setTexture(text2d);
	}
}

void CardLayer::onMouseDown(Event *event)
{
	EventMouse* e = (EventMouse*)event;
	CCLOG("%d,%d",(int)e->getCursorX(),-(int)(e->getCursorY()));
	if ((int) e->getCursorX() > 55 && (int) e->getCursorX() < 545)
	{
		if(((int) e->getCursorX() % 100) > 55 || ( ( (int)e->getCursorX() % 100 ) < 45 ) )
		{
			if( (-(int)e->getCursorY()) > 26 && (  (-(int)e->getCursorY())  < 154 ) )
			{
				int tmp = (e->getCursorX() - 45 ) / 100 + NumOfPage * 10;
				if(tmp < MaxImg)
					NumOfCard = tmp + 1;
				else
					NumOfCard = -1;
			}
			else if ( (-(int)e->getCursorY()) > 176 && (  (-(int)e->getCursorY())  < 304 ) ) 
			{
				int tmp = (e->getCursorX() - 45 ) / 100 + NumOfPage * 10 + 5;
				if(tmp < MaxImg)
					NumOfCard = tmp + 1;
				else
					NumOfCard = -1;
			}
			else 
				NumOfCard = -1;
		}
		else
			NumOfCard = -1;
		CCLOG("%d" , NumOfCard);
		if (NumOfCard != -1)
			add_card(NumOfCard);
	}
	{
		int x = (int) e->getCursorX();
		int y = -(int)e->getCursorY();
		int n = -1;
		if (x > 798 && x < 908)
			for (int i = 0; i < vi.size(); i++)
				if (y >= 21 + i * 20 && y <= 36 + i * 20)
				{
					n = i;
					break;
				}
		if (n != -1)
			del_card(n);
	}

}; 

