//
//  MainGameScene.cpp
//  PlantsVsZombies
//
//  Created by chaoyang805 on 16/3/31.
//
//

#include "MainGameScene.hpp"
#include "GameOverScene.hpp"
USING_NS_CC;

Scene* MainGameScene::createScene() {
    auto scene = Scene::createWithPhysics();
    //        scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0,0));
    auto layer = MainGameScene::create();
    scene->addChild(layer);
    
    return scene;
}
void MainGameScene::initializeGameScene() {
    _controllers.clear();
    _controllers.insert(0, GameController::create(this, 0,1,1));
    _controllers.insert(1, GameController::create(this, 1,0,0));
    _controllers.insert(2, GameController::create(this, 2,0,0));
    _controllers.insert(3, GameController::create(this, 3,0,0));
}

bool MainGameScene::init() {
    if (!Layer::init()) {
        return false;
    }
    _visibleSize = Director::getInstance()->getVisibleSize();
    auto background = GrassGround::create("background.png");
    addChild(background);
    
    // 添加计时器
    addGameTimer();
    
    // 添加阳光计数的label
    addEnergyLabel();

    // 添加植物的按钮
    addButtons();
    
    // 初始化游戏控制器
    initializeGameScene();
    
    // 添加碰撞监听
    addHitListener();
    
    // 添加触摸监听
    addTouchListener();

    return true;
}

void MainGameScene::addHitListener() {
    auto listener = EventListenerPhysicsContact::create();
    listener->onContactBegin = [this](PhysicsContact& contact){
        
        auto shapeA = contact.getShapeA()->getBody()->getNode();
        auto shapeB = contact.getShapeB()->getBody()->getNode();
        
        if (shapeA == NULL || shapeB == NULL) {
            return false;
        }
        int row = shapeA->getPositionY() / GRID_HEIGHT;
        GameController* controller = _controllers.at(row);
        if (controller == NULL) {
            return false;
        }
        // 僵尸100 和 豌豆300 碰撞
        if (shapeA->getTag() == BEAN_TAG && shapeB->getTag() == ZOMBIE_TAG) {
            
            controller->onHitZombie((Zombie*)shapeB, (Bean*)shapeA);
            return true;
        }
        
        if(shapeA->getTag() == 100 && shapeB->getTag() == 300) {
            
            controller->onHitZombie((Zombie*)shapeA, (Bean*)shapeB);
            return true;
        }
        
        // 僵尸100和植物200 碰撞
        if (shapeA->getTag() == 200 && shapeB->getTag() == 100) {
            
            controller->onZombieEatPlant((Zombie*)shapeB, (Plant*)shapeA);
            return true;
        }
        
        if (shapeA->getTag() == 100 && shapeB->getTag() == 200) {
            
            controller->onZombieEatPlant((Zombie*)shapeA, (Plant*)shapeB);
            return true;
        }
        return false;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
    
}

void MainGameScene::addTouchListener() {
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [this](Touch* t,Event* e) {
        // 两个按钮禁用了，说明阳光不够，直接返回
        if (!shooterButton->isEnabled() || !flowerButton->isEnabled()) {
            return false;
        }
        Vec2 location = t->getLocation();
        int width = GRID_WIDTH;
        int height = GRID_HEIGHT;
        int row = location.y / height;
        int column = location.x / width;
        
        if (_addFlower) {
            if (row < ROW_COUNT){
                this->gameControllerAtRow(row)->addSunFlower(row, column);
                this->onDropEnergy();
            }
            flowerButton->setScale(flowerButton->getScale() - 0.1);
            _addFlower = false;
            return true;
        }
        if (_addShooter) {
            if (row < ROW_COUNT){
                this->gameControllerAtRow(row)->addBeanShooter(row, column);
                this->onDropEnergy();
            }
            shooterButton->setScale(shooterButton->getScale() - 0.1);
            _addShooter = false;
            return true;
        }
        
        if (flowerButton->getBoundingBox().containsPoint(t->getLocation())) {
            flowerButton->setScale(flowerButton->getScale() + 0.1);
            _addFlower = true;
            return true;
        }
        if (shooterButton->getBoundingBox().containsPoint(t->getLocation())) {
            shooterButton->setScale(shooterButton->getScale() + 0.1);
            _addShooter = true;
            return true;
        }
        _addShooter = false;
        _addFlower = false;
        return false;
    };
    touchListener->onTouchEnded = [this](Touch* t,Event* e){
        Vec2 location = t->getLocation();
        
        if (_addFlower && flowerButton->getBoundingBox().containsPoint(t->getLocation())) {
            return;
        }
        if (_addShooter && shooterButton->getBoundingBox().containsPoint(t->getLocation())) {
            return;
        }
        
        int width = GRID_WIDTH;
        int height = GRID_HEIGHT;
        int row = location.y / height;
        int column = location.x / width;
        
        if (_addFlower) {
            if (row < ROW_COUNT && column < COLUMN_COUNT){
                this->gameControllerAtRow(row)->addSunFlower(row, column);
                this->onDropEnergy();
            }
            flowerButton->setScale(flowerButton->getScale() - 0.1);
        }
        if (_addShooter) {
            if (row < ROW_COUNT && column < COLUMN_COUNT){
                this->gameControllerAtRow(row)->addBeanShooter(row, column);
                this->onDropEnergy();
            }
            shooterButton->setScale(shooterButton->getScale() - 0.1);
        }
        
        _addFlower = false;
        _addShooter = false;
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void MainGameScene::addGameTimer() {
    _timerLabel = CountDownLabel::create(120);
    _timerLabel->setPosition(Vec2(0, _visibleSize.height));
    _timerLabel->onTimesUp = [this](){
        onGameEnd(checkSuccess());
        
    };
    _timerLabel->onPreTimesUp = [this](){
        // 游戏结束前停止添加僵尸到界面上
        for (auto iterator = this->_controllers.begin(); iterator != this->_controllers.end(); iterator++) {
            (*iterator).second->stopAddZombie();
        }
    };
    addChild(_timerLabel);
    _timerLabel->startCountDown();
}

void MainGameScene::addEnergyLabel() {
    _energyLabel = Label::create();
    _energyLabel->setTextColor(Color4B::BLACK);
    _energyLabel->setSystemFontSize(30);
    _energyLabel->setAnchorPoint(Vec2(0,1));
    _energyLabel->setPosition(this->_timerLabel->getContentSize().width + 15, _visibleSize.height);
    
    updateEnergyLabel();
    addChild(_energyLabel);

}

void MainGameScene::addButtons() {
    flowerButton = cocos2d::ui::Button::create("sunflower.png");
    this->addChild(flowerButton);
    flowerButton->setScale(0.5);
    flowerButton->setAnchorPoint(Vec2(0, 0));
    flowerButton->cocos2d::Node::setPosition(_visibleSize.width - flowerButton->getContentSize().width * flowerButton->getScale() - 10, _visibleSize.height - flowerButton->getContentSize().height * flowerButton->getScale() - 10);
    flowerButton->setTouchEnabled(false);
    
    
    shooterButton = cocos2d::ui::Button::create("plant1.png");
    this->addChild(shooterButton);
    shooterButton->setScale(0.55);
    shooterButton->setAnchorPoint(Vec2(0, 0));
    shooterButton->setPosition(
                               Vec2(_visibleSize.width - flowerButton->getContentSize().width * flowerButton->getScale() - shooterButton->getContentSize().width * shooterButton->getScale() - 20,
                                    _visibleSize.height - shooterButton->getContentSize().height * shooterButton->getScale() - 10));
    shooterButton->setTouchEnabled(false);
}


GameController* MainGameScene::gameControllerAtRow(int row) {
    return _controllers.at(row);
}

void MainGameScene::onAddEnergy() {
    _energies += 5;
    flowerButton->setEnabled(true);
    flowerButton->setBright(true);
    shooterButton->setEnabled(true);
    shooterButton->setBright(true);
    updateEnergyLabel();
}

void MainGameScene::onDropEnergy() {
    if (_energies > 0) {
        _energies -= 5;
        if(_energies <= 0){
            flowerButton->setEnabled(false);
            flowerButton->setBright(false);
            shooterButton->setEnabled(false);
            shooterButton->setBright(false);
        }
    }
    updateEnergyLabel();
}

void MainGameScene::updateEnergyLabel() {
    if (_energyLabel) {
        std::stringstream energyCount;
        energyCount << "Sun:" << _energies;
        _energyLabel->setString(energyCount.str());
    }
}

void MainGameScene::onZombieSuccess() {
    onGameEnd(false);
}

void MainGameScene::onExit() {
    unscheduleAllCallbacks();
    removeAllChildren();
    Layer::onExit();
}

bool MainGameScene::checkSuccess() {
    for (auto iterator = _controllers.begin(); iterator != _controllers.end(); iterator++) {
        if(!(*iterator).second->isAllZombiesDead()){
            log("you lose");
            return false;
        }
    }
    log(" zombie dead");
    return true;
}

void MainGameScene::onGameEnd(bool success) {
    for (auto iterator = _controllers.begin(); iterator != _controllers.end(); iterator++) {
        (*iterator).second->stopAddZombie();
    }
    Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
    Director::getInstance()->replaceScene(GameOverScene::createScene(success));
}

