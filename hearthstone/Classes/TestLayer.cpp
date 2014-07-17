#include "TestLayer.h"

Scene* TestLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TestLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

TestLayer::TestLayer(void)
{
}


TestLayer::~TestLayer(void)
{
}

bool TestLayer::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		/* background */
		CCSize winSize=CCDirector::sharedDirector()->getWinSize();//get window size
		Sprite* bgSp = Sprite::create("storybg.png");
		bgSp->setPosition(ccp(winSize.width / 2, winSize.height / 2));
		bgSp->setScaleX(winSize.width/1920);
		bgSp->setScaleY(winSize.height/1200);
		this->addChild(bgSp,0,0);


		CCSize visibleSize=CCDirector::sharedDirector()->getVisibleSize();

		uEditBox = EditBox::create(CCSizeMake(200,40), Scale9Sprite::create("login_edit_normal.9.png"));
		uEditBox->setPosition(ccp(visibleSize.width/2, visibleSize.height*3/4));
		uEditBox->setFontColor(ccRED);
		uEditBox->setPlaceHolder("username:");
		uEditBox->setMaxLength(8);
		uEditBox->setInputFlag(EditBox::InputFlag::SENSITIVE);
		uEditBox->setInputMode(EditBox::InputMode::ANY);
		uEditBox->setReturnType(EditBox::KeyboardReturnType::DONE);
	    uEditBox->setDelegate(this);
		addChild(uEditBox);


		pEditBox = EditBox::create(CCSizeMake(200,40), Scale9Sprite::create("login_edit_normal.9.png"));
		pEditBox->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
		pEditBox->setFontColor(ccRED);
		pEditBox->setPlaceHolder("password:");
		pEditBox->setMaxLength(8);
		


		//      kEditBoxInputModeAny:         开启任何文本的输入键盘,包括换行
		//      kEditBoxInputModeEmailAddr:   开启 邮件地址 输入类型键盘
		//      kEditBoxInputModeNumeric:     开启 数字符号 输入类型键盘
		//      kEditBoxInputModePhoneNumber: 开启 电话号码 输入类型键盘
		//      kEditBoxInputModeUrl:         开启 URL 输入类型键盘
		//      kEditBoxInputModeDecimal:     开启 数字 输入类型键盘，允许小数点
		//      kEditBoxInputModeSingleLine:  开启任何文本的输入键盘,不包括换行
		pEditBox->setInputMode(EditBox::InputMode::ANY);

		//kEditBoxInputFlagPassword:				密码形式输入
		//kEditBoxInputFlagSensitive:				敏感数据输入、存储输入方案且预测自动完成
		//kEditBoxInputFlagInitialCapsWord:			每个单词首字母大写,并且伴有提示
		//kEditBoxInputFlagInitialCapsSentence:		第一句首字母大写,并且伴有提示
		//kEditBoxInputFlagInitialCapsAllCharacters:所有字符自动大写
		pEditBox->setInputFlag(EditBox::InputFlag::PASSWORD);

		//      kKeyboardReturnTypeDefault:  默认使用键盘return 类型
		//      kKeyboardReturnTypeDone:     默认使用键盘return类型为“Done”字样
		//      kKeyboardReturnTypeSend:     默认使用键盘return类型为“Send”字样	
		//      kKeyboardReturnTypeSearch:   默认使用键盘return类型为“Search”字样
		//      kKeyboardReturnTypeGo:       默认使用键盘return类型为“Go”字样
		pEditBox->setReturnType(EditBox::KeyboardReturnType::DONE);
	    pEditBox->setDelegate(this);
		addChild(pEditBox);

		Scale9Sprite* confirm1=Scale9Sprite::create("login.png");
		confirm1->setContentSize(CCSizeMake(140,57));
		Scale9Sprite* confirm2=Scale9Sprite::create("register.png");
		confirm2->setContentSize(CCSizeMake(140,57));
		CCMenuItemSprite* menuitem1=CCMenuItemSprite::create(confirm1, confirm1, nullptr, CC_CALLBACK_1(TestLayer::btncallback1,this));
		CCMenuItemSprite* menuitem2=CCMenuItemSprite::create(confirm2, confirm2, nullptr, CC_CALLBACK_1(TestLayer::btncallback2,this));
		CCMenu* menu1=CCMenu::create(menuitem1,NULL);
		CCMenu* menu2=CCMenu::create(menuitem2,NULL);
		menu1->setPosition(visibleSize.width*2/5,visibleSize.height/4);
		menu2->setPosition(visibleSize.width*3/5,visibleSize.height/4);
		this->addChild(menu1);
		this->addChild(menu2);

		bRet=true;

	} while (0);
	return bRet;
}

void TestLayer::editBoxEditingDidBegin(EditBox *editBox)
{
	CCLOG("start edit");
}
void TestLayer::editBoxEditingDidEnd(EditBox *editBox)
{
	CCLOG("end edit");
}
void TestLayer::editBoxReturn(EditBox *editBox)
{
	CCLOG("editbox return");
}
void TestLayer::editBoxTextChanged(EditBox *editBox, const std::string &text)
{
	CCLOG("text changed");
}

void TestLayer::btncallback1( CCObject* pSender )
{
	//login
	CCLOG("%s,%s",uEditBox->getText(),pEditBox->getText());
	//TODO
	string tmp1 = uEditBox->getText();
	string tmp2 = pEditBox->getText();
}

void TestLayer::btncallback2( CCObject* pSender )
{
	//register
	CCLOG("%s,%s",uEditBox->getText(),pEditBox->getText());
	//TODO
}