#ifndef __CARDLAYER_H__
#define __CARDLAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "logic/player.h"
#include "./logic/basic.h"
#include "LoginScene.h"
#include <vector>
#include <iostream>
#include <fstream>

#define _amount 30
#define MaxPage 4
#define MinPage 0
#define MaxImg 19
#define WINSIZE_W 960
#define WINSIZE_H 640
#define FirstLineOfImg 5
#define SecondLineOfImg 10

USING_NS_CC;
USING_NS_CC_EXT; 

using namespace std;

class CardLayer : public cocos2d::Layer
{
public:
	bool init();

	static cocos2d::Scene* createScene();
	CREATE_FUNC(CardLayer);

	static int NumOfPage;
	static int NumOfCard;

	LabelTTF LabelOfPage;
	LabelTTF label;
	Sprite * Img[10];
	vector<int> vi;
	Sprite* sp[_amount];

	void PrevMenuCallback(Object* pSender);
	void NextMenuCallback(Object* pSender);
	void finishMenuCallback(Object* pSender);
	void backMenuCallback(Object* pSender);

	void ChangePage(int );
	void UpdateImg(int );
	void removeImg();
	void _init(float f);
	void add_card(int n);
	void del_card(int n);
	bool finish();
	void refresh_pic();
	void label_hide(float f);

    virtual void onMouseDown(Event *event);  
};
#endif