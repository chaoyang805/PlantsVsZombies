//
//  GameController.cpp
//  PlantsVsZombies
//
//  Created by chaoyang805 on 16/4/5.
//
//

#include "GameController.hpp"
#include "SunFlower.hpp"

USING_NS_CC;

#define EMPTY_TYPE 0
#define SHOOTER_TYPE 1
#define FLOWER_TYPE 2
#define ZOMBIE_TYPE 3
GameController* GameController::create(MainGameScene* gameLayer,int row,int initialFlowerCount,int initialShooterCount) {
    
    GameController *pRet = new GameController();
    pRet->init(gameLayer,row, initialFlowerCount, initialShooterCount);
    pRet->autorelease();
    return pRet;
}

bool GameController::init(MainGameScene* gameLayer,int row,int initialFlowerCount,int initialShooterCount) {

    _row = row;
    _layer= gameLayer;
    // 初始化所有网格为零，表示不包含植物
    for (int i = 0; i < ROW_COUNT; i++) {
        for (int j = 0; j < COLUMN_COUNT; j++) {
            _grids[i][j] = 0;
        }
    }
    for (int i = 0; i < initialFlowerCount; i++) {
        addSunFlower(row, i);
    }
    for (int i = 0; i < initialShooterCount; i++) {
        addBeanShooter(row, initialFlowerCount + i);
    }
    
    randomZombie();
    return true;
}
void GameController::addBeanShooter(int row, int column) {
    if (plantExists(row, column)) {
        return;
    }
    auto shooter = BeanShooter::create();
    shooter->setPositionInGameView(row, column);
    shooter->_autoFire = true;
    _layer->addChild(shooter);
    _plants.insert(0, shooter);
    //将当前位置标记为有shooter
    _grids[row][column] = SHOOTER_TYPE;
}

void GameController::addBeanShooter(const cocos2d::Point &point){
    addBeanShooter(point.x, point.y);
}

void GameController::addZombie(int row, int column) {
    auto zombie = Zombie::create();
    zombie->setPositionInGameView(row, column);
    
    zombie->onZombieSuccess = [this](){
        ((MainGameScene*)_layer)->onZombieSuccess();
    };
    
    zombie->onZombieDead = [zombie,this](){
        _zombies.eraseObject(zombie);
    };
    
    _layer->addChild(zombie);
    _zombies.insert(0, zombie);
}

void GameController::addZombie(const cocos2d::Point &point) {
    addZombie(point.x, point.y);
}

void GameController::addSunFlower(int row, int column) {
    if (plantExists(row, column)) {
        return;
    }
    auto flower = SunFlower::create();
    flower->setPositionInGameView(row, column);
    flower->onSunTouched = [this](Sun* sun) {
        ((MainGameScene*)_layer)->onAddEnergy();
    };
    _layer->addChild(flower);
    _grids[row][column] = FLOWER_TYPE;
}

void GameController::addSunFlower(const cocos2d::Point &point) {
    addSunFlower(point.x, point.y);
}

void GameController::onZombieEatPlant(Zombie* zombie,Plant* plant) {
    zombie->_isMoving = false;
    plant->getHurt();
    
    plant->onDied = [zombie,this](bool dead) {
        if (dead) {
            zombie->_isMoving = true;
        }
    };
    
    zombie->onZombieDead = [zombie,plant,this](){
        plant->startRecovery();
        _zombies.eraseObject(zombie);
        if (this->isAllZombiesDead()) {
            ((BeanShooter*)plant)->_autoFire = false;
        }
    };
}
void GameController::onHitZombie(Zombie* zombie,Bean* bean) {
    zombie->getHurt();
    bean->removeFromParent();
}

void GameController::removePlantReference(int row, int column) {
    _grids[row][column] = EMPTY_TYPE;
}

bool GameController::plantExists(int row, int column) {
    return _grids[row][column] != EMPTY_TYPE;
}

bool GameController::isAllZombiesDead() {
    return _zombies.size() == 0;
}

void GameController::randomZombie() {
    _scheduler = Director::getInstance()->getScheduler();
    _scheduler->schedule(schedule_selector(GameController::addZombieRandomly), this, 1, false);
}
int updateCount = 0;
int randomTimer = random(20, 40);
void GameController::addZombieRandomly(float delta) {
    
    if (!_isScheduled) {
        return;
    }
    
    if (updateCount++ == randomTimer) {

        auto zombie = Zombie::create();
        zombie->setPositionInGameView(_row, 7);
        zombie->setPositionX(zombie->getPositionX() + 10);
        
        zombie->onZombieSuccess = [this](){
            ((MainGameScene*)_layer)->onZombieSuccess();
        };
        
        zombie->onZombieDead = [zombie,this](){
            _zombies.eraseObject(zombie);
        };
        if (_layer) {
            _layer->addChild(zombie);
            _zombies.insert(0, zombie);
        }
        updateCount = 0;
        randomTimer = random(20, 40);
    }
}
void GameController::stopAddZombie() {
    _isScheduled = false;
}