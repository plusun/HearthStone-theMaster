#ifndef __CARDLAYER_H__
#define __CARDLAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT; 

class CardLayer : public cocos2d::Layer
{
public:
	bool init();

	static cocos2d::Scene* createScene();
	CREATE_FUNC(CardLayer);
};
#endif