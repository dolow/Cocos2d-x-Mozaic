#include "HelloWorldScene.h"
#include "MozaicTo.h"
#include "FilterMozaic.h"

using namespace cocos2d;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
    if (!Layer::init()) return false;
    
    Sprite* bg = Sprite::create("bg.jpg");
    bg->setAnchorPoint(Vec2::ZERO);
    bg->setPosition(Vec2::ZERO);
    bg->setScale(2.0f);
    this->addChild(bg, 1);
    
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("obj.plist");
    
    Sprite* ken = Sprite::createWithSpriteFrame(cache->getSpriteFrameByName("ken_1.png"));
    ken->setAnchorPoint(Vec2::ZERO);
    ken->setPosition(Vec2(100.0f, 10.0f));
    ken->setScale(3.5f);
    this->addChild(ken, 2);
    
    Sprite* ken2 = Sprite::createWithSpriteFrame(cache->getSpriteFrameByName("ken_4.png"));
    ken2->setAnchorPoint(Vec2::ZERO);
    ken2->setPosition(Vec2(300.0f, 40.0f));
    ken2->setScale(3.5f);
    ken2->setFlippedX(true);
    this->addChild(ken2, 2);
    
    FilterMozaic* mozaic = FilterMozaic::createWithTarget(ken2, cocos2d::Size(5.0f, 5.0f));
    mozaic->setAnchorPoint(ken2->getAnchorPoint());
    mozaic->setPosition(ken2->getPosition());
    mozaic->setScale(ken2->getScale());
    mozaic->setVisible(false);
    this->addChild(mozaic, 3);
    
    
    Animation* anim = Animation::create();
    anim->setDelayPerUnit(0.1f);
    anim->setLoops(-1);
    for (int i = 1; i <= 7; i++)
        anim->addSpriteFrame(cache->getSpriteFrameByName("ken_" + std::to_string(i) + ".png"));
    
    ken->runAction(Animate::create(anim));
    ken->runAction(RepeatForever::create(Sequence::createWithTwoActions(
        DelayTime::create(0.2f),
        JumpBy::create(0.5f, Vec2::ZERO, 80.0f, 1)
    )));
    
    MenuItemLabel* button = MenuItemLabel::create(Label::createWithSystemFont("RUN", "Arial", 30), [this, ken, ken2, mozaic](Ref*){
        ken->runAction(MozaicTo::create(10.0f, cocos2d::Size(5.0f, 5.0f)));
        ken2->setVisible(false);
        mozaic->setVisible(true);
    });
    button->setAnchorPoint(Vec2(1.0f, 0.0f));
    button->setPosition(Vec2(Director::getInstance()->getVisibleSize().width, 0.0f));
    
    Menu* menu = Menu::create(button, nullptr);
    menu->ignoreAnchorPointForPosition(false);
    menu->setAnchorPoint(Vec2::ZERO);
    menu->setPosition(Vec2::ZERO);
    menu->setContentSize(Director::getInstance()->getVisibleSize());
    this->addChild(menu, 10);
    
    return true;
}
