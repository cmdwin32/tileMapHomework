//
//  LoadableObj.cpp
//  HelloCpp
//
//  Created by CK on 14-6-5.
//
//

#include "LoadableObj.h"
// LoadableObj

LoadableObj::LoadableObj():
_target(NULL),
_callback_func(NULL)
{

}

LoadableObj::~LoadableObj(){
    
}

void LoadableObj::setCallBackFunc(cocos2d::CCObject *target, SEL_CallFuncO callback_func){
    _target = target;
    _callback_func = callback_func;
}

void LoadableObj::load(){

}

void LoadableObj::loadedCallBack(cocos2d::Texture2D *obj){
    if (_target && _callback_func) {
        (_target->*_callback_func)(obj);
    }
}

// PLISTLoadableObj

void LoadableObj::loadedFaild(float d){
    
}

PLISTLoadableObj::PLISTLoadableObj():
_filename("")
{

}

PLISTLoadableObj::~PLISTLoadableObj(){

}

PLISTLoadableObj * PLISTLoadableObj::createWithFileName(std::string filename){
    PLISTLoadableObj * obj = new PLISTLoadableObj();
    obj->setFileName(filename);
    std::string path = obj->_filename;
    size_t startPos = path.find_last_of(".");
    std::string texturePath = path.erase(startPos);
    texturePath = texturePath.append(".plist");
    obj->setPlist(texturePath);
    
    return obj;
}

PLISTLoadableObj * PLISTLoadableObj::createWithFileNameAndPlist(std::string filename, std::string plist){
    PLISTLoadableObj * obj = new PLISTLoadableObj();
    obj->setFileName(filename);
    obj->setPlist(plist);
    
    return obj;
}

void PLISTLoadableObj::setFileName(std::string filename){
    _filename = filename;
}

void PLISTLoadableObj::setPlist(std::string plist){
    _plist = plist;
}

void PLISTLoadableObj::load(){
    
    Director::getInstance()->getScheduler()->scheduleSelector(schedule_selector(PLISTLoadableObj::loadedFaild), this, 5, false);
    TextureCache::sharedTextureCache()->addImageAsync(_filename.c_str(), [this](Texture2D* tex)->void{this->loadedCallBack(tex);});
}

void PLISTLoadableObj::loadedCallBack(cocos2d::Texture2D *obj){
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(PLISTLoadableObj::loadedFaild), this);
    CCTexture2D * tx = dynamic_cast<CCTexture2D*>(obj);
    if (tx) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(_plist.c_str(), tx);
    }
    LoadableObj::loadedCallBack(obj);
}

void PLISTLoadableObj::loadedFaild(float d){
    LoadableObj::loadedFaild(d);
    char err_msg[256];
    sprintf(err_msg, "%s load faild",_filename.c_str());
    CCAssert(true,err_msg);
}

// IMGLoadableObj

IMGLoadableObj::IMGLoadableObj():
_filename("")
{
    
}

IMGLoadableObj::~IMGLoadableObj(){

}

IMGLoadableObj * IMGLoadableObj::createWithFileName(std::string filename){
    IMGLoadableObj * obj = new IMGLoadableObj();
    obj->setFileName(filename);
    return obj;
}

void IMGLoadableObj::setFileName(std::string filename){
    _filename = filename;
}

void IMGLoadableObj::load(){
    CCDirector::getInstance()->getScheduler()->scheduleSelector(schedule_selector(IMGLoadableObj::loadedFaild), this, 5, false);
    CCTextureCache::getInstance()->addImageAsync(_filename.c_str(),[this](Texture2D* tex)->void{this->loadedCallBack(tex);}) ;
}

void IMGLoadableObj::loadedCallBack(cocos2d::Texture2D *obj){
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(IMGLoadableObj::loadedFaild), this);
    LoadableObj::loadedCallBack(obj);
}

void IMGLoadableObj::loadedFaild(float d){
    LoadableObj::loadedFaild(d);
    char err_msg[256];
    sprintf(err_msg, "%s load faild",_filename.c_str());
    CCAssert(true,err_msg);
}

