#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "cocos2d.h"

class PlayScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void goBack(Ref* pSender);

    void modifyPressLabel(Ref* pSender);

    void buttonFadeIn(cocos2d::MenuItemImage* image);
    void buttonFadeOut(cocos2d::MenuItemImage* image);
    void buttonFadeInWithDelay(cocos2d::MenuItemImage* image, float delay);
    void buttonFadeOutWithDelay(cocos2d::MenuItemImage* image, float delay);

    void buttonLock(cocos2d::MenuItemImage* image, bool lock);



private:
    cocos2d::Label* pressLabel;
    cocos2d::MenuItemImage* pressButton;

    CREATE_FUNC(PlayScene);
};

#endif // __PLAY_SCENE_H__
