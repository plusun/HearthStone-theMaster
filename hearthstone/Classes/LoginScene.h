#ifndef __LOGINSCENE_SCENE_H__
#define __LOGINSCENE_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameLayer.h"


USING_NS_CC;
USING_NS_CC_EXT; 

class LoginScene : public cocos2d::Layer
{
public:
	bool init();
	LoginScene():m_iCurMsgIndex(0){};
	static cocos2d::Scene* createScene();
	CREATE_FUNC(LoginScene);

	void LoginMenuCallback(Object* pSender);
	void exitMenuCallback(Object* pSender);
private:
	int m_iCurMsgIndex;//no useful

};

#endif