#include "CardLayer.h"

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

	Sprite* cardSp = Sprite::create("card_select.png");
    cardSp->setPosition(ccp(winSize.width / 2 - 90 , winSize.height / 2 + 20));
    cardSp->setScaleX(winSize.width/1200);
    cardSp->setScaleY(winSize.height/800);
    this->addChild(cardSp,0,0);
}