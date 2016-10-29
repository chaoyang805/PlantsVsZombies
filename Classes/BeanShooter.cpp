//
//  BeanShooter.cpp
//  PlantsVsZombies
//
//  Created by chaoyang805 on 16/4/5.
//
//

#include "BeanShooter.hpp"
#include "Bean.hpp"
#include "FlashTool.hpp"
#include "MainGameScene.hpp"
USING_NS_CC;
bool BeanShooter::init() {
    if (!Plant::init()) {
        return false;
    }
    runAction(RepeatForever::create(FlashTool::readJsonSpriteSheet("plant.json", 0.4)));
    Size plantSize = Size(71, 71);
    setContentSize(plantSize);
    setAnchorPoint(Vec2(0, 0));
    setScale(0.8);
    setPhysicsBody(PhysicsBody::createBox(plantSize));
    getPhysicsBody()->setContactTestBitmask(PLANT_BITMASK);
    getPhysicsBody()->setCategoryBitmask(PLANT_CATEGORY);
    getPhysicsBody()->setCollisionBitmask(PLANT_COLLISION);
    getPhysicsBody()->setRotationEnable(false);
    getPhysicsBody()->setDynamic(false);
    
    setTag(PLANT_TAG);
    schedule(schedule_selector(BeanShooter::fireAtTime), 2);
    return true;
}

void BeanShooter::fireAtTime(float delta) {
    
    if (shouldAutoFire()) {
        fire();
    }
}

bool BeanShooter::shouldAutoFire() {
    MainGameScene* parent = (MainGameScene*)getParent();
    return !parent->gameControllerAtRow(getRow())->isAllZombiesDead();
}

void BeanShooter::fire() {
    
    auto bean = Bean::create();
    Vec2 position = Vec2(getPositionX() + getContentSize().width * getScale(),
                         getPositionY() + getContentSize().height * getScale());
    bean->setPosition(Vec2(position));
    
    this->getParent()->addChild(bean);
}

int BeanShooter::getRow() {
    return _row;
}

void BeanShooter::removeFromParent() {
    unschedule(schedule_selector(BeanShooter::fireAtTime));
    Plant::removeFromParent();
}