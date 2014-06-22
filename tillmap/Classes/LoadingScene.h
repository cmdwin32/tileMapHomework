//
//  LoadingScene.h
//  tillmap
//
//  Created by king hin on 14-6-18.
//
//

#ifndef __tillmap__LoadingScene__
#define __tillmap__LoadingScene__

#include <iostream>
#include "cocos2d.h"
#include "CCProgressLayer.h"
#include "MapLoadable.h"
class LoadingScene : public cocos2d::Scene {
    
public:
    static LoadingScene * create();
    
    LoadingScene();
    virtual ~LoadingScene();
    // 重载init方法初始化进度条层 
    virtual bool init() override;
    virtual void onEnter() override;
protected:
    CCProgressLayer * _layer ; // 显示加载进度条的层
private:
    void LoadedFinish(); // 完成全部加载
};


#endif /* defined(__tillmap__LoadingScene__) */
