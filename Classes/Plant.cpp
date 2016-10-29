//
//  Plant.cpp
//  PlantsVsZombies
//
//  Created by chaoyang805 on 16/3/31.
//
//

#include "Plant.hpp"
#include "FlashTool.hpp"
#include "Bean.hpp"
#include "GameController.hpp"

bool Plant::init() {
    if (!Sprite::init()) {
        return false;
    }
    return true;
}

void Plant::getHurt() {
    schedule(schedule_selector(Plant::dropBlood), _dropBloodInterval / ++_hitCount);
}

void Plant::dropBlood(float delta) {
    life--;
    if (life <= 0) {
        ((MainGameScene*)getParent())->gameControllerAtRow(_row)->removePlantReference(_row,_column);
        onDied(true);
        removeFromParent();
    }
}

void Plant::startRecovery() {
    
    if(--_hitCount == 0)
        unschedule(schedule_selector(Plant::dropBlood));
    else
        schedule(schedule_selector(Plant::dropBlood), _dropBloodInterval / _hitCount);
}

void Plant::onExit() {
    unschedule(schedule_selector(Plant::dropBlood));
    Node::onExit();
}

void Plant::removeFromParent() {
    unschedule(schedule_selector(Plant::dropBlood));
    Sprite::removeFromParent();
}

void Plant::setPositionInGameView(int row, int column) {
    _row = row;
    _column = column;
    setPosition(GRID_WIDTH * column, GRID_HEIGHT * row);
}

