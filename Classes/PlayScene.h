#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

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
    cocos2d::ui::LoadingBar* loadingBar;

    float progression;

    std::uniform_real_distribution<float> distributionX;
    std::uniform_real_distribution<float> distributionY;

    CREATE_FUNC(PlayScene);
};

#endif // __PLAY_SCENE_H__
