#ifndef _POP_LAYER_H_

#define _POP_LAYER_H_

#include "cocos2d.h"



using namespace cocos2d;

 

class PopScene : public CCLayer

{

public:

    static CCScene * scene();

    bool init();

    CREATE_FUNC(PopScene);

private:

    //ע�ᴥ���¼���ʵ��ccTouchBegan()����

   // void registerWithTouchDispatcher();

    bool onTouchBegan(CCTouch * touch,CCEvent * pevent);

    //�ڵ����ĶԻ����ϼ�������ť�����µĺ����Ƕ�Ӧ�İ�ť�Ĵ����¼�

    void yesButton(CCObject * object);

    void noButton(CCObject * object);

    //���öԻ����title

    void setTitle();

    //���öԻ�����ı�����

    void setContent();

    //m_size������ǶԻ��򱳾��Ĵ�С

    CCSize m_size;

    //�Ի���ı�������

    CCSprite * m_bgSprite;

};
#endif
