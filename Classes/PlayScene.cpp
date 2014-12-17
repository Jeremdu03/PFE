#include "PlayScene.h"
#include "MainMenuScene.h"
#include <random>

std::random_device rdev{};
std::minstd_rand Engine{rdev()};
USING_NS_CC;

static int pressNumber;
static bool isIn;


Scene* PlayScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = PlayScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PlayScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    pressNumber = 0;
    isIn = false;
    progression = 0;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    pressButton = MenuItemImage::create("press_normal.png", "press_normal.png", CC_CALLBACK_1(PlayScene::modifyPressLabel, this));

    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(PlayScene::goBack, this));

    pressButton->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    pressButton->setOpacity(0.f);
    pressButton->setEnabled(false);

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));


    auto menu = Menu::create(pressButton, closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    distributionX = std::uniform_real_distribution<float> (pressButton->getContentSize().width/2, Director::getInstance()->getVisibleSize().width - pressButton->getContentSize().width/2);
    distributionY = std::uniform_real_distribution<float> (pressButton->getContentSize().height/2, Director::getInstance()->getVisibleSize().height - pressButton->getContentSize().height/2);

    pressLabel = Label::createWithTTF(std::to_string(pressNumber), "fonts/Marker Felt.ttf", 36);

    // position the label on the center of the screen
    pressLabel->setPosition(Vec2(origin.x + visibleSize.width*3/4,
                            origin.y + visibleSize.height - pressLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pressLabel, 1);

    loadingBar = cocos2d::ui::LoadingBar::create("loading_bar.png", progression);

    loadingBar->setPosition(Vec2(origin.x + loadingBar->getContentSize().width / 2.0f,origin.y + visibleSize.height - loadingBar->getContentSize().height / 2.0f + loadingBar->getContentSize().height / 4.0f));
    this->addChild(loadingBar);

    buttonFadeIn(pressButton);

    return true;
}

void PlayScene::goBack(Ref* pSender)
{
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void PlayScene::modifyPressLabel(Ref* pSender)
{
	pressNumber ++;
	pressLabel->setString(std::to_string(pressNumber));
	/*if(1)
	{*/
		pressButton->stopAllActions();
		buttonFadeOutWithDelay(pressButton, 0.0f);
	//}
	if(progression < 100)
		progression += 5;

    loadingBar->setPercent(progression);
}

void PlayScene::buttonFadeIn(cocos2d::MenuItemImage* image)
{
	isIn = true;
	image->runAction(Sequence::create(DelayTime::create(0.5f), CallFunc::create(std::bind(&PlayScene::buttonLock, this, image, true)), FadeIn::create(1.0f), CallFunc::create(std::bind(&PlayScene::buttonFadeOut, this, image)), NULL));
}

void PlayScene::buttonFadeOut(cocos2d::MenuItemImage* image)
{
	isIn = false;
	image->runAction(Sequence::create(DelayTime::create(1), FadeOut::create(0.5f), CallFunc::create(std::bind(&PlayScene::buttonFadeIn, this, image)), CallFunc::create(std::bind(&PlayScene::buttonLock, this, image, false)), NULL));
}

void PlayScene::buttonFadeInWithDelay(cocos2d::MenuItemImage* image, float delay)
{
	isIn = true;
	image->runAction(Sequence::create(DelayTime::create(delay), CallFunc::create(std::bind(&PlayScene::buttonLock, this, image, true)), FadeIn::create(1.0f), CallFunc::create(std::bind(&PlayScene::buttonFadeOut, this, image)), NULL));
}

void PlayScene::buttonFadeOutWithDelay(cocos2d::MenuItemImage* image, float delay)
{
	isIn = false;
	image->runAction(Sequence::create(DelayTime::create(delay), CallFunc::create(std::bind(&PlayScene::buttonLock, this, pressButton, false)), FadeOut::create(0.5f), CallFunc::create(std::bind(&PlayScene::buttonFadeIn, this, image)), NULL));
}

void PlayScene::buttonLock(MenuItemImage* image, bool lock)
{
	image->setEnabled(lock);
	if(lock)
	{
		image->setPosition(distributionX(Engine), distributionY(Engine));
	}
}
