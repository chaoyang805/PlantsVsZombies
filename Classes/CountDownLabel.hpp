//
//  CountDownLabel.hpp
//  PlantsVsZombies
//
//  Created by chaoyang805 on 16/4/8.
//
//

#ifndef CountDownLabel_hpp
#define CountDownLabel_hpp

#include <stdio.h>
#include "cocos2d.h"
class CountDownLabel :public cocos2d::Label {
public:
    typedef std::function<void()> onTimesUpCallback;
    typedef std::function<void()> onPreTimesUpCallback;
    virtual bool init(int totalTime);
    
    static CountDownLabel* create(int totalTime);
    
    void startCountDown();
    
    onTimesUpCallback onTimesUp;
    onPreTimesUpCallback onPreTimesUp;
private:
    int _totalTime;
    int _restTime;
    void countDown(float delta);
};


#endif /* CountDownLabel_hpp */
