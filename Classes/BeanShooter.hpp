//
//  BeanShooter.hpp
//  PlantsVsZombies
//
//  Created by chaoyang805 on 16/4/5.
//  豌豆射手类
//

#ifndef BeanShooter_hpp
#define BeanShooter_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Plant.hpp"

class BeanShooter: public Plant {
public:
    bool _autoFire = false;
    
    virtual bool init();
    
    CREATE_FUNC(BeanShooter);
    
    void fire();
    void fireAtTime(float delta);
    
    void getHurt();
    
    virtual void removeFromParent();
    
    bool shouldAutoFire();
    
private:
    int getRow();
    
};
#endif /* BeanShooter_hpp */
