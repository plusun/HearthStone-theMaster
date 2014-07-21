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
        //���������ı���ͼƬ������������λ��Ϊ������Ļ���е�
        CCSprite * background = CCSprite::create("duihuakuang.png");
        m_bgSprite = background;
        background->setPosition(ccp(winSize.width/2,winSize.height/2));
        this->addChild(background);
        //��ñ���ͼƬ�Ĵ�С
        CCSize contentSize = background->getContentSize();
        m_size = contentSize;
        //��������˵����������
        CCMenuItemImage * item1 = CCMenuItemImage::create("queding1.png","queding1.png","",this,menu_selector(PopScene::yesButton));
        CCMenuItemImage * item2 = CCMenuItemImage::create("queding.png","queding.png","", this,menu_selector(PopScene::noButton));
        CCMenu * menu = CCMenu::create(item1,NULL,NULL);
        menu->alignItemsHorizontallyWithPadding(5);
        menu->setPosition(ccp(contentSize.width/2,contentSize.height/4));
        //kCCMenuHandlerPriority��ֵΪ-128��������ǲ˵���ť�Ĵ������ȼ�
        //����menu���ȼ�����������Ϊ��ͨmenu�Ķ�����һ��ԭ���±�
       // menu->setTouchPriority(kCCMenuHandlerPriority*2-1);
        background->addChild(menu);
        //������Ŀ���ı�����
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

//����˵���ť��ʱ����õ��¼�������

void PopScene::yesButton(CCObject * object)
{
    this->removeFromParentAndCleanup(true);
}

 

void PopScene::noButton(CCObject * object)
{
    this->removeFromParentAndCleanup(true);
}

//������������Ŀ

void PopScene::setTitle()
{
    CCLabelTTF * title = CCLabelTTF::create("Error:","",24);
    //CCLabelBMFont * title = CCLabelBMFont::create("Tips","bitmapFontChinese.fnt");
    title->setPosition(ccp(m_size.width/2,m_size.height-title->getContentSize().height/2));
    m_bgSprite->addChild(title);
}

//���ò������
void PopScene::setContent()
{
    CCLabelTTF * content = CCLabelTTF::create("login/register error\ncheck your username and password","",24);
    content->setPosition(ccp(m_size.width/2,m_size.height*3/5));
	content->setColor(Color3B::BLACK);
    //����ttf���ı���
    content->setDimensions(CCSize(this->m_size.width-60,this->m_size.height-100));
    //����ttf��ˮƽ���뷽ʽ
    content->setHorizontalAlignment(kCCTextAlignmentLeft);
    m_bgSprite->addChild(content);
}
