//
//  CCProgressLayer.h
//  HelloCpp
//
//  Created by CK on 14-6-5.
//
//

#ifndef __HelloCpp__CCProgressLayer__
#define __HelloCpp__CCProgressLayer__

#include <iostream>
#include "cocos2d.h"
#include <vector>
#include "LoadableObj.h"
USING_NS_CC;
using namespace std;
class CCProgressLayer : public CCLayer {
    
public:
    
    CCProgressLayer();
    
    virtual ~CCProgressLayer();
    
    static CCProgressLayer * createWithResouceList(vector<LoadableObj*> resouce_list);
    
    void startLoad();
    
    virtual bool init();
    
//    virtual void update(float dt);
    /**
     *  设置当前进度
     */
    void setProgressRate(float progress_rate);
    
    void loadingCallBack(CCObject * obj);
    
    /**
     * 获得当前的进度
     */
    float getProgressRate();
    /**
     * 加载结束
     */
    void LoadingFinished();
    /**
     * 线主线程调用结束
     */
    void LoadingFinishedThread( float dt );
    /**
     * 加载出错
     */
    void LoadingErr(bool ignore);
    /**
     * 设置完成回调函数
     */
    void setSuccessCallBack(CCObject* target,SEL_CallFunc func);
    /**
     * 释放加载对象 
     */
    void reset();
    
protected:
    void loadOneResource( float dt ); // 加载一个资源
    int _res_index;
    CCProgressTimer * _progress_sp; // 进度条显示对象
    CCProgressTimer * _progress_str; // loading 文字 
    float _progress_rate; // 当前的进度
    vector<LoadableObj*> _resouce_list;
    CCMenuItemSprite * m_bg;
    
    CCObject * _success_target;
    SEL_CallFunc _success_func;
    
};
#endif /* defined(__HelloCpp__CCProgressLayer__) */
