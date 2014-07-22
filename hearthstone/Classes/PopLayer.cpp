#include "PopLayer.h"

 

CCScene * PopScene::scene()

{
    CCScene * scene = NULL;
    do
    {
        scene = CCScene::create();
        PopScene * layer = PopScene::create();
        scene->addChild(layer);
    }
    while(0);
    return scene;
}

bool PopScene::init()
{
    bool bRet = false;
    do
	{
        CC_BREAK_IF(!CCLayer::init());
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        //设置这个层的背景图片，并且设置其位置为整个屏幕的中点
        CCSprite * background = CCSprite::create("duihuakuang.png");
        m_bgSprite = background;
        background->setPosition(ccp(winSize.width/2,winSize.height/2));
        this->addChild(background);
        //获得背景图片的大小
        CCSize contentSize = background->getContentSize();
        m_size = contentSize;
        //添加俩个菜单在这个层中
        CCMenuItemImage * item1 = CCMenuItemImage::create("queding1.png","queding1.png","",this,menu_selector(PopScene::yesButton));
        CCMenuItemImage * item2 = CCMenuItemImage::create("queding.png","queding.png","", this,menu_selector(PopScene::noButton));
        CCMenu * menu = CCMenu::create(item1,NULL,NULL);
        menu->alignItemsHorizontallyWithPadding(5);
        menu->setPosition(ccp(contentSize.width/2,contentSize.height/4));
        //kCCMenuHandlerPriority的值为-128，代表的是菜单按钮的触摸优先级
        //设置menu优先级，这里设置为普通menu的二倍减一，原因看下边
       // menu->setTouchPriority(kCCMenuHandlerPriority*2-1);
        background->addChild(menu);
        //设置题目和文本内容
        this->setTitle();
        this->setContent();
        this->setTouchEnabled(true);
        bRet = true;
    }
	while(0);
    return bRet;
}

bool PopScene::onTouchBegan(CCTouch * touch,CCEvent * pevent)
{
    return true;
}

//点击菜单按钮的时候调用的事件处理函数

void PopScene::yesButton(CCObject * object)
{
    this->removeFromParentAndCleanup(true);
}

 

void PopScene::noButton(CCObject * object)
{
    this->removeFromParentAndCleanup(true);
}

//设置这个层的题目

void PopScene::setTitle()
{
    CCLabelTTF * title = CCLabelTTF::create("Error:","",24);
    //CCLabelBMFont * title = CCLabelBMFont::create("Tips","bitmapFontChinese.fnt");
    title->setPosition(ccp(m_size.width/2,m_size.height-title->getContentSize().height/2));
    m_bgSprite->addChild(title);
}

//设置层的内容
void PopScene::setContent()
{
    CCLabelTTF * content = CCLabelTTF::create("login/register error\ncheck your username and password","",24);
    content->setPosition(ccp(m_size.width/2,m_size.height*3/5));
	content->setColor(Color3B::BLACK);
    //设置ttf的文本域
    content->setDimensions(CCSize(this->m_size.width-60,this->m_size.height-100));
    //设置ttf的水平对齐方式
    content->setHorizontalAlignment(kCCTextAlignmentLeft);
    m_bgSprite->addChild(content);
}
