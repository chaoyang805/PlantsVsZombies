//
//  Zombie.hpp
//  PlantsVsZombies
//
//  Created by chaoyang805 on 16/3/31.
//
//

#ifndef Zombie_hpp
#define Zombie_hpp

#include <stdio.h>
#include "cocos2d.h"
#define ZOMBIE_TAG 100
#define ZOMBIE_BITMASK 0x11
#define ZOMBIE_COLLISION_BITMASK 0x10

class Zombie: public cocos2d::Sprite {
public:
    typedef std::function<void()> ZombieSuccessCallback;
    typedef std::function<void()> ZombieDeadCallback;
    virtual bool init();
    
    CREATE_FUNC(Zombie);

    void update(float delta);
    
    /// 僵尸是否前进
    bool _isMoving = true;
    
    void getHurt();
    void setPositionInGameView(int row,int column);
    /**
     *  僵尸的默认生命值
     */
    int life = 10;
    
    ZombieSuccessCallback onZombieSuccess;
    ZombieDeadCallback onZombieDead;
private:
    int _row;
    int _column;
};
#endif /* Zombie_hpp */
