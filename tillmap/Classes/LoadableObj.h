//
//  LoadableObj.h
//  HelloCpp
//
//  Created by CK on 14-6-5.
//
//

#ifndef __HelloCpp__LoadableObj__
#define __HelloCpp__LoadableObj__

#include <string>
#include "cocos2d.h"
#include <pthread.h>
USING_NS_CC;
/**
 * 为可加载对象提供异步加载接口
 */
class LoadableObj : public CCObject{
    
public:
    LoadableObj();
    virtual ~LoadableObj();
    
    void setCallBackFunc(CCObject * target,SEL_CallFuncO);
    virtual void load();
    virtual void loadedCallBack(Texture2D * obj);
    virtual void loadedFaild(float d);
    
protected:
    CCObject * _target;
    SEL_CallFuncO _callback_func;
    
};

/**
 * plist 大图资源预加载
 */
class PLISTLoadableObj : public LoadableObj {
    
public:
    PLISTLoadableObj();
    virtual ~PLISTLoadableObj();
    
    /**
     * 根据文件名创建一个Plist加载对象 
     */
    static PLISTLoadableObj * createWithFileName(std::string filename);
    
    static PLISTLoadableObj * createWithFileNameAndPlist(std::string filename,std::string plist);
    
    /**
     * 设置需要加载的文件名
     */
    void setFileName(std::string file_name);
    /**
     * 设置plist文件名 
     */
    void setPlist(std::string plist);
    
    virtual void load();
    virtual void loadedCallBack(Texture2D * obj);
    virtual void loadedFaild(float d);
protected:
    std::string _filename;
    std::string _plist;
};

/**
 * 单独图片缓存
 */
class IMGLoadableObj : public LoadableObj {
    
public:
    IMGLoadableObj();
    virtual ~IMGLoadableObj();
    
    /**
     * 根据需要加载的图片名称加载图片
     */
    static IMGLoadableObj * createWithFileName(std::string filename);
    
    /**
     * 设置需要加载的文件名
     */
    void setFileName(std::string filename);
    
    
    virtual void load();
    virtual void loadedCallBack(Texture2D * obj);
    virtual void loadedFaild(float d);
protected:
    std::string _filename;
    
};


#endif /* defined(__HelloCpp__LoadableObj__) */
