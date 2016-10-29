//
//  Plant.hpp
//  PlantsVsZombies
//
//  Created by chaoyang805 on 16/3/31.
//
//

#ifndef Plant_hpp
#define Plant_hpp

#include <stdio.h>
#include "cocos2d.h"
#define PLANT_BITMASK 0x10
#define PLANT_TAG 200
#define PLANT_CATEGORY 0x01
#define PLANT_COLLISION 0x10
class Plant: public cocos2d::Sprite {
public:
    /// 植物的生命值
    int life = 7;
    
    virtual bool init();
    
    CREATE_FUNC(Plant);
    /**
     *  被僵尸碰到，开始掉血
     */
    void getHurt();
    /**
     *  掉血函数
     *
     *  @param delta 时间间隔
     */
    void dropBlood(float delta);
    
    std::function<void(bool isDead)> onDied;
    
    virtual void onExit();
    
    void removeFromParent();
    /**
     *  设置植物在游戏场景中的位置
     *
     *  @param row    行
     *  @param column 列
     */
    void setPositionInGameView(int row,int column);
    /**
     *  开始恢复
     */
    void startRecovery();
    
    int _row;
    
    int _column;
    
private:
    /**
     *  被僵尸袭击的次数，被一个僵尸袭击为1，两个为2
     */
    int _hitCount = 0;
    float _dropBloodInterval = 0.5;
};
#endif /* Plant_hpp */
