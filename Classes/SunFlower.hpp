//
//  SunFlower.hpp
//  PlantsVsZombies
//
//  Created by chaoyang805 on 16/4/1.
//
//

#ifndef SunFlower_hpp
#define SunFlower_hpp

#include <stdio.h>
#include "Plant.hpp"
#include "Sun.hpp"

class SunFlower: public Plant{
    
public:
    typedef std::function<void(Sun* sun)> SunTouchCallback;
    virtual bool init();
    
    CREATE_FUNC(SunFlower);
    /**
     *  产生阳光
     */
    void produceSun(float delta);
    SunTouchCallback onSunTouched;

};
#endif /* SunFlower_hpp */
