//
//  FlashTool.hpp
//  PlantsVsZombies
//
//  Created by chaoyang805 on 16/3/31.
//
//

#ifndef FlashTool_hpp
#define FlashTool_hpp

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;
class FlashTool {
public:
    static Animate* readJsonSpriteSheet(const std::string jsonFile, float interval);
    /**
     *  通过一系列图片创建动画
     *
     *  @param baseImageName 图片命名格式为image1.png image2.png ... 下标从1开始，baseImageName表示图片名称中的image
     *  @param extensionName 扩展名类型，例如：.png .jpg
     *  @param delayUnit     图片切换的间隔
     *  @param imageCount    图片数量
     *  @param width         图片的宽度，像素
     *  @param height        图片的高度，像素
     *
     *  @return 返回Animate动画指针
     */
    static Animate* animateFromeImages(const std::string baseImageName,const std::string extensionName,float delayUnit,int imageCount,int width,int height);
    /**
     *  通过一系列图片创建动画
     *
     *  @param baseImageName 图片命名格式为image1.png image2.png ... 下标从1开始，baseImageName表示图片名称中的image
     *  @param extensionName 扩展名类型，例如：.png .jpg
     *  @param delayUnit     图片切换的间隔
     *  @param imageCount    图片数量
     *  @param imageSize     图片的尺寸
     *
     *  @return 返回Animate动画指针
     */
    static Animate* animateFromeImages(const std::string baseImageName,const std::string extensionName,float delayUnit,int imageCount,Size imageSize);
    
    static Animate* animateFromeImages(const std::string baseImageName,const std::string extensionName,float delayUnit,int imageCount,int offsetX,int offsetY,int width,int height);
};
#endif /* FlashTool_hpp */
