//
//  LevelScene.h
//  SanGuoYingJie
//
//  Created by Steven.Xc.Tian.
//
//

#ifndef __SanGuoYingJie__LevelScene__
#define __SanGuoYingJie__LevelScene__

#include "cocos2d.h"

class TKMap;

class LevelScene : public cocos2d::Layer {
//    friend class MapHelper;
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    CREATE_FUNC(LevelScene);
    
    virtual bool init() override;
    
private:
    TKMap *_tkmap; //
    
    std::vector<cocos2d::Point> _solution;
    
    void move(const cocos2d::Point &tileCoord);
    
    void justdoit();
};

#endif /* defined(__SanGuoYingJie__LevelScene__) */
