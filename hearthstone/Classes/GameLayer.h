#ifndef __GAMELAYER_SCENE_H__
#define __GAMELAYER_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"


USING_NS_CC;
USING_NS_CC_EXT; 

class GameLayer : public cocos2d::Layer
{
public:
	bool init();
	GameLayer():m_iCurMsgIndex(0){};
	static cocos2d::Scene* createScene();
	CREATE_FUNC(GameLayer);

	void cardMenuCallback(Object* pSender);
	void endMenuCallback(Object* pSender);
	void timeCallback(float ct);

private:
	int m_iCurMsgIndex;

};

#endif