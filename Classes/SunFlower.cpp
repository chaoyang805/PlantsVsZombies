//
//  SunFlower.cpp
//  PlantsVsZombies
//
//  Created by chaoyang805 on 16/4/1.
//
//

#include "SunFlower.hpp"
#include "FlashTool.hpp"
#include "Sun.hpp"
USING_NS_CC;
bool SunFlower::init() {
    if (!Plant::init()) {
        return false;
    }
    Size flowerSize = Size(73, 74);
    
    runAction(RepeatForever::create(FlashTool::animateFromeImages("sunflower", ".png", 0.3, 18, flowerSize)));
    setContentSize(flowerSize);
    setScale(0.8);
    setAnchorPoint(Vec2(0,0));
    setPhysicsBody(PhysicsBody::createBox(flowerSize));
    getPhysicsBody()->setDynamic(false);
    getPhysicsBody()->setRotationEnable(false);
    getPhysicsBody()->setContactTestBitmask(PLANT_BITMASK);
    getPhysicsBody()->setCategoryBitmask(PLANT_CATEGORY);
    getPhysicsBody()->setCollisionBitmask(PLANT_COLLISION);
    setTag(PLANT_TAG);
    schedule(schedule_selector(SunFlower::produceSun), 10);
    
    return true;
}

void SunFlower::produceSun(float delta) {
    
    
    // 产生阳光
    auto sun = Sun::create();
    float positionX = this->getPositionX() + this->getContentSize().width * getScaleX() * 0.3;
    float positionY = this->getPositionY() + this->getContentSize().height * getScaleY() * 0.4;
    
    Vec2 position = Vec2(positionX, positionY);
    
    sun->setPosition(position);
    this->getParent()->addChild(sun);

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [this,sun](Touch* t,Event* e) {
        
        if(sun->getBoundingBox().containsPoint(t->getLocation())) {
            sun->removeFromParent();
            this->onSunTouched(sun);
        }
        
        return true;
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, sun);
    
}

