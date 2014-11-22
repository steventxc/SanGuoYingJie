//
//  LevelHelper.h
//  SanGuoYingJie
//
//  Created by Steven.Xc.Tian.
//
//

#ifndef __SanGuoYingJie__LevelHelper__
#define __SanGuoYingJie__LevelHelper__

#include "cocos2d.h"

class Roles;
class TKMap;
class LevelScene;

class LevelHelper : public cocos2d::Ref
{
public:
    
    static LevelHelper * create(LevelScene *scene, const std::string& tmxFile);
    
    
    std::vector<cocos2d::Point> getMovingRange(Roles *selected);
    
protected:
    LevelHelper(LevelScene *scene);
    ~LevelHelper();
    
    bool init(const std::string& tmxFile);
    
private:
    LevelScene *_mLevelScene;
    TKMap *_mTKMap;
};

#endif /* defined(__SanGuoYingJie__LevelHelper__) */
