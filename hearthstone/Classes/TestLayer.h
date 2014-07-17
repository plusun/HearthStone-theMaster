#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "string.h"

using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;

class TestLayer :
	public CCLayer, public EditBoxDelegate
{
public:
	TestLayer(void);
	~TestLayer(void);

	static cocos2d::Scene* createScene();
	CREATE_FUNC(TestLayer);

	virtual bool init();

	EditBox* uEditBox;
	EditBox* pEditBox;

	void editBoxEditingDidBegin(EditBox *editBox);

	void editBoxEditingDidEnd(EditBox *editBox);

	void editBoxReturn(EditBox *editBox);

	void editBoxTextChanged(EditBox *editBox, const std::string &text);

	void btncallback1(CCObject* pSender);

	void btncallback2(CCObject* pSender);

};

