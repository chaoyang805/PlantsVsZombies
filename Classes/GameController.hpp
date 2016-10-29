//
//  GameController.hpp
//  PlantsVsZombies
//
//  Created by chaoyang805 on 16/4/5.
//
//

#pragma once

#include <stdio.h>
#include "cocos2d.h"
#include "Zombie.hpp"
#include "Bean.hpp"
#include "Plant.hpp"
#include "BeanShooter.hpp"
#include "MainGameScene.hpp"

#define ROW_COUNT 4
#define COLUMN_COUNT 8
#define GRID_WIDTH (Director::getInstance()->getVisibleSize().width - 43)/COLUMN_COUNT
#define GRID_HEIGHT (Director::getInstance()->getVisibleSize().height - 53)/ROW_COUNT


USING_NS_CC;
// 防止头文件重复引入
class MainGameScene;
class GameController: public cocos2d::Ref {
public:
    static GameController* create(MainGameScene* gameLayer,int row,int initialFlowerCount,int initialShooterCount);
    
    bool init(MainGameScene* gameLayer,int row,int initialFlowerCount,int initialShooterCount);
    /**
     *  在指定的行和列添加豌豆射手
     *
     *  @param row    要添加的行
     *  @param column 要添加的列
     *  @see addBeanShooter(const cocos2d::Point &point);
     */
    void addBeanShooter(int row,int column);
    /**
     *  在指定的点添加豌豆射手
     *
     *  @param point 要添加的位置
     *  @see addBeanShooter(int row,int column);
     */
    void addBeanShooter(const cocos2d::Point &point);
    /**
     *  在指定的行和列添加僵尸
     *
     *  @param row    要添加的行
     *  @param column 要添加的列
     *  @see addZombie(const cocos2d::Point &point);
     */
    void addZombie(int row,int column);
    /**
     *  在指定的点添加僵尸
     *
     *  @param point 要添加的位置
     *  @see addZombie(int row,int column);
     */
    void addZombie(const cocos2d::Point &point);
    /**
     *  在指定的点添加向日葵
     *
     *  @param scene
     *  @param row    要添加的行
     *  @param column 要添加的列
     */
    void addSunFlower(int row,int column);
    
    /**
     *  在指定的点添加向日葵
     *
     *  @param point  要添加的位置
     */
    void addSunFlower(const cocos2d::Point &point);
    
    /**
     ***  当僵尸碰到植物时执行
     *
     *  @param zombie 僵尸
     *  @param plant  植物
     */
    void onZombieEatPlant(Zombie* zombie,Plant* plant);
    
    /**
     *  当僵尸被豌豆击中时执行
     *
     *  @param zombie 僵尸
     *  @param bean   豌豆
     */
    void onHitZombie(Zombie* zombie,Bean* bean);
    /**
     *  从grids中移除plant的位置记录
     *
     *  @param row    行
     *  @param column 列
     */
    void removePlantReference(int row,int column);
    /**
     *  特定位置是否已经存在植物了
     *
     *  @param row    行
     *  @param column 列
     *
     *  @return 如果存在，返回true
     */
    bool plantExists(int row,int column);
    /**
     *  是否所有僵尸都死了
     *
     *  @return 返回是否所有僵尸都死了
     */
    bool isAllZombiesDead();
    
    void stopAddZombie();

private:
    /**
     *  记录游戏场景网格中所有的位置是否存在植物
     */
    int _grids[ROW_COUNT][COLUMN_COUNT];
    Scheduler *_scheduler;
    void randomZombie();
    
    void addZombieRandomly(float delta);
    
    bool _isScheduled = true;
    int _row = 0;
    cocos2d::Layer* _layer;
    cocos2d::Vector<Zombie*> _zombies;
    cocos2d::Vector<Plant*> _plants;
    
    
};

//#endif /* GameController_hpp */
