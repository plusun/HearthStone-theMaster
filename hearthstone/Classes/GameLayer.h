#ifndef __GAMELAYER_SCENE_H__
#define __GAMELAYER_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "logic/player.h"

USING_NS_CC;
USING_NS_CC_EXT; 

class GameLayer : public cocos2d::Layer
{
public:
	bool init();
	GameLayer():
		b(new Battlefield()),
		d1(new deck()),
		d2(new deck()),
		player1(d1, b, true),
		player2(d2, b, false)
	{
	}
	Battlefield *b;
	deck *d1, *d2;
	Player player1;
	Player player2;
	
	static cocos2d::Scene* createScene();
	CREATE_FUNC(GameLayer);

	void cardMenuCallback(Object* pSender);
	void endMenuCallback(Object* pSender);
	void timeCallback(float ct);
	void card_move(Player &player1);

	
	virtual bool onTouchBegan(Touch *touch, Event *unused_event); 
    virtual void onTouchMoved(Touch *touch, Event *unused_event); 
    virtual void onTouchEnded(Touch *touch, Event *unused_event); 
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);

private:
	

};

#endif


