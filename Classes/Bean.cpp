//
//  Bean.cpp
//  PlantsVsZombies
//
//  Created by chaoyang805 on 16/4/1.
//
//

#include "Bean.hpp"
USING_NS_CC;
bool Bean::init() {
    if (!Sprite::initWithFile("wandou.png")) {
        return false;
    }
    setScale(0.3);
    setAnchorPoint(Vec2(0, 1));
    setContentSize(Size(90, 90));
    setPhysicsBody(PhysicsBody::createBox(getContentSize()));
    getPhysicsBody()->setContactTestBitmask(0x01);
    getPhysicsBody()->setCategoryBitmask(0x01);
    getPhysicsBody()->setCollisionBitmask(0x01);
    setTag(BEAN_TAG);
    schedule(schedule_selector(Bean::updatePosition), 0.04, kRepeatForever, 0);
    return true;
}

void Bean::updatePosition(float dt) {
    
    this->setPositionX(this->getPositionX() + 3);
    if (this->getPositionX() > Director::getInstance()->getVisibleSize().width) {
        unschedule(schedule_selector(Bean::updatePosition));
        removeFromParent();
    }
}

