#ifndef __REPLAYLAYER_SCENE_H__
#define __REPLAYLAYER_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "logic/player.h"
#include "logic/client.h"
#include "GameLayer.h"

using namespace std;

USING_NS_CC;
USING_NS_CC_EXT; 

extern client cl;
extern bool Is_First;

class ReplayLayer : public GameLayer
{
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(ReplayLayer);

	bool init();

	vector<int> torecv(char* s, char c = '/');
	static void replay(ReplayLayer *,Player * , Player *);
	void update_handcard(Player* p1 ,int num);
};


#endif