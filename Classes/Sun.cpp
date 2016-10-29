//
//  Sun.cpp
//  PlantsVsZombies
//
//  Created by chaoyang805 on 16/4/2.
//
//

#include "Sun.hpp"
#include "FlashTool.hpp"
USING_NS_CC;
bool Sun::init() {
    if (!Sprite::init()) {
        return false;
    }
    
    runAction(RepeatForever::create(FlashTool::animateFromeImages("sun", ".png", 0.3, 4, 0, 0, 296, 296)));
    Size sunSize = Size(296, 296);
    setContentSize(sunSize);
    setScale(0.1, 0.1);
    setAnchorPoint(Vec2(0, 0));
//    setPhysicsBody(PhysicsBody::createBox(sunSize));
    _visibleSize = Director::getInstance()->getVisibleSize();
    _velocityX = random(0.0, 2.0);
    schedule(schedule_selector(Sun::scheduleMove), 0.05);
    return true;
}

void Sun::scheduleMove(float delta) {
    this->setPositionX(getPositionX() + _velocityX);
    this->setPositionY(getPositionY() + _velocityY);
    
    if (getPositionX() <= 0 || getPositionY() <=0 ||
        getPositionY() >= _visibleSize.height || getPositionX() >= _visibleSize.width) {
        unschedule(schedule_selector(Sun::scheduleMove));
        removeFromParent();
    }

    
}

