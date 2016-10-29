//
//  MainGameScene.hpp
//  PlantsVsZombies
//
//  Created by chaoyang805 on 16/3/31.
//
//

#pragma once

#include <stdio.h>
#include "cocos2d.h"
#include "GrassGround.hpp"
#include "Plant.hpp"
#include "Zombie.hpp"
#include "SunFlower.hpp"
#include "Bean.hpp"
#include "Sun.hpp"
#include "BeanShooter.hpp"
#include "GameController.hpp"
#include "ui/CocosGUI.h"
#include "extensions/cocos-ext.h"
#include "CountDownLabel.hpp"
class GameController;
class MainGameScene: public cocos2d::Layer {
public:
    
    static cocos2d::Scene* createScene();
    virtual bool init();

    CREATE_FUNC(MainGameScene);
    
    void onAddEnergy();
    
    void onDropEnergy();
    
    void onZombieSuccess();
    
    void onExit();
    
    int _energies = 10;
    
    cocos2d::Map<int, GameController*> _controllers;
    
    bool checkSuccess();
    
    GameController* gameControllerAtRow(int row);
    
private:
    
    void initializeGameScene();
    void addHitListener();
    
    void addTouchListener();
    
    void addButtons();
    
    void addGameTimer();
    
    void addEnergyLabel();
    
    void onGameEnd(bool success);
    
    bool isSuccess();
    
    void updateEnergyLabel();
private:
    cocos2d::Size _visibleSize;
    
    cocos2d::ui::Button *flowerButton;
    
    cocos2d::ui::Button *shooterButton;
    
    cocos2d::Label* _energyLabel;
    
    CountDownLabel* _timerLabel;
    
    bool _addFlower = false;
    
    bool _addShooter = false;
};


//#endif /* MainGameScene_hpp */
