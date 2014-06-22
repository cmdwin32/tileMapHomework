//
//  GameScene.h
//  tilemap
//
//  Created by king hin on 14-6-19.
//
//

#ifndef __tilemap__GameScene__
#define __tilemap__GameScene__

#include <iostream>
#include "cocos2d.h"
#include "MapManager.h"

class GameScene : public cocos2d::Scene {
    
    
public:
    GameScene();
    virtual ~GameScene();
    
    static GameScene * create();
    
    // 初始化
    virtual bool init() override;
    
    // 在场景创建的时候 调用
    virtual void onEnter() override;
    
    // 在场景释放的时候调用
    virtual void onExit() override;
    
    // 更新
    virtual void update(float dt) override;
private:
    
};



#endif /* defined(__tilemap__GameScene__) */
