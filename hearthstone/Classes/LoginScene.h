#ifndef __LOGINSCENE_SCENE_H__
#define __LOGINSCENE_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameLayer.h"
#include "CardLayer.h"

USING_NS_CC;
USING_NS_CC_EXT; 

extern client cl;
extern bool Is_First;

class LoginScene : public cocos2d::Layer
{
public:
	bool init();
	LoginScene():m_iCurMsgIndex(0){};
	static cocos2d::Scene* createScene();
	CREATE_FUNC(LoginScene);

	void GameMenuCallback(Object* pSender);
	void exitMenuCallback(Object* pSender);
	void cardMenuCallback(Object* pSender);
private:
	int m_iCurMsgIndex;//no useful

};

#endif