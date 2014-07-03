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

	m_iCurMsgIndex=0;
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
	starMenu->setPosition(Point::ZERO); //menuê��Ĭ��Ϊ��0,0������ʱ��menuλ��Ҳ��Ϊ(0,0)������menu�����½�λ����Ļ�����½�
	this->addChild(starMenu,1);

	auto exitMenuItem=MenuItemImage::create("huihejieshu.png","huihejieshu.png",CC_CALLBACK_1(GameLayer::endMenuCallback,this));
	exitMenuItem->setPosition(Point(winSize.width / 2+390, winSize.height / 2-275));
	auto exitMenu=Menu::create(exitMenuItem,NULL);
	exitMenu->setPosition(Point::ZERO); //menuê��Ĭ��Ϊ��0,0������ʱ��menuλ��Ҳ��Ϊ(0,0)������menu�����½�λ����Ļ�����½�
	this->addChild(exitMenu,1);

	this->schedule(schedule_selector(GameLayer::timeCallback), 10.0f);
    return true;

}

/* ÿ�غϳ��ƺ���õĻص�����*/
void GameLayer::cardMenuCallback(Object* pSender)
{

}


/* ÿ�غϽ����غϺ���õĻص�����*/
void GameLayer::endMenuCallback(Object* pSender)
{

}

void GameLayer::timeCallback(float ct)
{
	 
}