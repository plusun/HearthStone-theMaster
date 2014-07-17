#include "LoginScene.h"

USING_NS_CC;

Scene* LoginScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LoginScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool LoginScene::init()
{
	if ( !Layer::init() )
    {
        return false;
    }

	m_iCurMsgIndex=0;
    setTouchEnabled(true);

	CCSize winSize=CCDirector::sharedDirector()->getWinSize();//get window size

	/* background */
	 Sprite* bgSp = Sprite::create("storybg.png");
    bgSp->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    bgSp->setScaleX(winSize.width/1920);
    bgSp->setScaleY(winSize.height/1200);
    this->addChild(bgSp,0,0);

	
 
	//button

	//login button 
	auto LoginMenuItem=MenuItemImage::create("denglu.png","denglu.png",CC_CALLBACK_1(LoginScene::LoginMenuCallback,this));
	LoginMenuItem->setPosition(Point(winSize.width / 2, winSize.height / 2-135));
	auto starMenu=Menu::create(LoginMenuItem,NULL);
	starMenu->setPosition(Point::ZERO); //menu锚点默认为（0,0），此时把menu位置也设为(0,0)，所以menu的左下角位于屏幕的左下角
	this->addChild(starMenu,1);


	//card button
	auto cardMenuItem=MenuItemImage::create("kapai.png","kapai.png",CC_CALLBACK_1(LoginScene::cardMenuCallback,this));
	cardMenuItem->setPosition(Point(winSize.width / 2, winSize.height / 2-200));
	auto cardMenu=Menu::create(cardMenuItem,NULL);
	cardMenu->setPosition(Point::ZERO); //menu锚点默认为（0,0），此时把menu位置也设为(0,0)，所以menu的左下角位于屏幕的左下角
	this->addChild(cardMenu,1);
	 
	//exit button
	auto exitMenuItem=MenuItemImage::create("exit.png","exit.png",CC_CALLBACK_1(LoginScene::exitMenuCallback,this));
	exitMenuItem->setPosition(Point(winSize.width / 2, winSize.height / 2-265));
	auto exitMenu=Menu::create(exitMenuItem,NULL);
	exitMenu->setPosition(Point::ZERO); //menu锚点默认为（0,0），此时把menu位置也设为(0,0)，所以menu的左下角位于屏幕的左下角
	this->addChild(exitMenu,1);


    return true;

}

//callback -- login
void LoginScene::LoginMenuCallback(Object* pSender)
{
	CCTransitionScene * reScene = NULL;
	CCScene * s = GameLayer::createScene();
    float t = 1.2f;
    reScene = CCTransitionProgressHorizontal  ::create(t , s);
	CCDirector::sharedDirector()->replaceScene(reScene);
}

void LoginScene::cardMenuCallback(Object* pSender)
{
	CCTransitionScene * reScene = NULL;
	CCScene * s = CardLayer::createScene();
    float t = 1.2f;
    reScene = CCTransitionProgressHorizontal  ::create(t , s);
	CCDirector::sharedDirector()->replaceScene(reScene);
}

//callback -- exit
void LoginScene::exitMenuCallback(Object* pSender)
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}