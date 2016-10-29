//
//  FlashTool.cpp
//  PlantsVsZombies
//
//  Created by chaoyang805 on 16/3/31.
//
//

#include "FlashTool.hpp"
#include "json/document.h"
Animate* FlashTool::readJsonSpriteSheet(const std::string jsonFile, float interval) {
    rapidjson::Document doc;
    std::string fileContent = FileUtils::getInstance()->getStringFromFile(jsonFile);
    fileContent.erase(0, fileContent.find_first_of('{'));
    
    doc.Parse<0>(fileContent.c_str());
    std::string imgFileName = doc["meta"]["image"].GetString();
    
    auto &frames = doc["frames"];
    auto sfc = SpriteFrameCache::getInstance();
    
    Vector<AnimationFrame*> animFrames;
    for (auto m = frames.MemberBegin(); m != frames.MemberEnd(); m++) {
        auto frameName = m->name.GetString();
        auto &frameProperties = m->value["frame"];
        auto &spriteSourceSize = m->value["spriteSourceSize"];
        
        auto sf = sfc->getSpriteFrameByName(frameName);
        if (!sf) {

            sf = SpriteFrame::create(imgFileName, Rect(frameProperties["x"].GetInt(), frameProperties["y"].GetInt(),frameProperties["w"].GetInt(), frameProperties["h"].GetInt()),m->value["rotated"].GetBool(),Vec2(spriteSourceSize["x"].GetInt(),spriteSourceSize["y"].GetInt()),Size(spriteSourceSize["w"].GetInt(),spriteSourceSize["h"].GetInt()));
            sfc->addSpriteFrame(sf, frameName);
        }
        animFrames.pushBack(AnimationFrame::create(sf, interval, ValueMapNull));
    }
    Animation* animation = Animation::create(animFrames, interval);
    return Animate::create(animation);
}

Animate* FlashTool::animateFromeImages(const std::string baseImageName, const std::string extensionName, float delayUnit, int imageCount,int width,int height) {
    auto sfc = SpriteFrameCache::getInstance();
    
    Vector<AnimationFrame*> animFrames;
    for (int i = 1; i < imageCount + 1; i++) {
        std::stringstream frameName;
        frameName << baseImageName << i << extensionName;
        auto sf = sfc->getSpriteFrameByName(frameName.str());
        if(!sf) {
            sf = SpriteFrame::create(frameName.str(), Rect(0, 0, width, height));
            sfc->addSpriteFrame(sf, frameName.str());
        }
        animFrames.pushBack(AnimationFrame::create(sf, delayUnit, ValueMapNull));
    }
    Animation *animation  = Animation::create(animFrames, delayUnit);
    return Animate::create(animation);

}

Animate* FlashTool::animateFromeImages(const std::string baseImageName, const std::string extensionName, float delayUnit, int imageCount, cocos2d::Size imageSize) {
    return FlashTool::animateFromeImages(baseImageName, extensionName, delayUnit, imageCount, imageSize.width, imageSize.height);
}

Animate* FlashTool::animateFromeImages(const std::string baseImageName, const std::string extensionName, float delayUnit, int imageCount, int offsetX, int offsetY, int width, int height) {
    
    
    auto sfc = SpriteFrameCache::getInstance();
    
    Vector<AnimationFrame*> animFrames;
    for (int i = 1; i < imageCount + 1; i++) {
        std::stringstream frameName;
        frameName << baseImageName << i << extensionName;
        auto sf = sfc->getSpriteFrameByName(frameName.str());
        if(!sf) {
            sf = SpriteFrame::create(frameName.str(), Rect(offsetX, offsetY, width, height), false, Vec2(0, 0), Size(width, height));
            sfc->addSpriteFrame(sf, frameName.str());
        }
        animFrames.pushBack(AnimationFrame::create(sf, delayUnit, ValueMapNull));
    }
    Animation *animation  = Animation::create(animFrames, delayUnit);
    return Animate::create(animation);
}
