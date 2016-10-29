//
//  Bean.hpp
//  PlantsVsZombies
//
//  Created by chaoyang805 on 16/4/1.
//
//

#ifndef Bean_hpp
#define Bean_hpp

#include <stdio.h>
#include "cocos2d.h"
#define BEAN_TAG 300
class Bean: public cocos2d::Sprite {
    
    
public:
    virtual bool init();
    
    CREATE_FUNC(Bean);
    
    void updatePosition(float dt);
    
//    void update(float dt);
};
#endif /* Bean_hpp */
