//
//  Zombie.cpp
//  PlantsVsZombies
//
//  Created by chaoyang805 on 16/3/31.
//
//

#include "Zombie.hpp"
#include <string>
#include "FlashTool.hpp"
#include "GameController.hpp"
USING_NS_CC;
bool Zombie::init() {
    if (!Sprite::init()) {
        return false;
    }
    
    Size zombieSize = Size(85, 145);

    runAction(RepeatForever::create(FlashTool::animateFromeImages("zombie", ".png", 0.3, 14, 10, 18, 85, 145)));
    setContentSize(zombieSize);
    setAnchorPoint(Vec2(0, 0));
    setScale(0.4, 0.4);
    
    setPhysicsBody(PhysicsBody::createBox(getContentSize()));
    getPhysicsBody()->setRotationEnable(false);
    getPhysicsBody()->setContactTestBitmask(ZOMBIE_BITMASK);
    getPhysicsBody()->setCollisionBitmask(ZOMBIE_COLLISION_BITMASK);
    
    setTag(ZOMBIE_TAG);
    return true;
}

void Zombie::update(float delta){
    if(_isMoving) {
        setPositionX(getPositionX() - 0.1);
        if (getPositionX() <= -getContentSize().width * getScale()) {
            unscheduleUpdate();
            removeFromParent();
            this->onZombieSuccess();
        }
    }
}

void Zombie::getHurt() {
    
    life--;
    if (life <= 0) {
        if (onZombieDead != NULL) {
            onZombieDead();
        }
        unscheduleUpdate();
        removeFromParent();
    }
}

void Zombie::setPositionInGameView(int row, int column) {
    _row = row;
    _column = column;
    setPosition(GRID_WIDTH * column, GRID_HEIGHT * row);
}

