#ifndef __GAMELAYER_SCENE_H__
#define __GAMELAYER_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "logic/player.h"
#include "logic/client.h"

using namespace std;

USING_NS_CC;
USING_NS_CC_EXT; 

extern client cl;
extern bool Is_First;

class GameLayer : public cocos2d::Layer
{
public:
	bool init();
	GameLayer():
		b(new Battlefield()),
		d1(new deck()),
		d2(new deck()),
		player1(d1, b, true, 0),
		player2(d2, b, false, 1)
	{
	}
	Battlefield *b;
	deck *d1, *d2;
	Player player1;
	Player player2;
	static bool is_first_turn;

	vector<Card * >sprite_vec;
	vector<MinionCard *>minion_vec;
	static int operator_position;
	static int battlefield_position;
	static int minion1_position;
	static int minion2_position;
	LabelTTF mana_label;
	LabelTTF stat_label;
	LabelTTF turn_label;

	static cocos2d::Scene* createScene();
	CREATE_FUNC(GameLayer);

	void cardMenuCallback(Object* pSender, Player * player1, int *, int *);
	void endMenuCallback(Object* pSender , Player * p1 ,Player * p2, int *,int *);
	void timeCallback(float ct);
	int update_battlefiled(Player* p1 ,int ,int * ,int *);
	void update_battlefiled_all(bool);
	void attack(int side, int m1, int m2);
	void update_handcard(Player* p1 ,int );
	void refresh_mana();
	void refresh_stat(Character* m, Touch* touch);
	void stat_hide(float f);
	void refresh_turn();
	bool b_add_touchListener(Player *,int ,int *,int *, int);
	bool h_add_touchListener(Player *,int *,int *, int);
	static void wait_message(GameLayer *,Player * , Player *);
	Minion * find_minion(int);
	void init_img();
	
	virtual bool onTouchBegan(Touch *touch, Event *unused_event); 
    virtual void onTouchMoved(Touch *touch, Event *unused_event); 
    virtual void onTouchEnded(Touch *touch, Event *unused_event); 

	virtual bool b_onTouchBegan(Touch *touch, Event *unused_event); 
    virtual void b_onTouchMoved(Touch *touch, Event *unused_event); 
    virtual void b_onTouchEnded(Touch *touch, Event *unused_event); 

private:
	

};


#endif


