//
//  MapLoadable.cpp
//  tilemap
//
//  Created by king hin on 14-6-21.
//
//

#include "MapLoadable.h"
#include "MapCache.h"

MapLoadable::MapLoadable(){

}

MapLoadable::~MapLoadable(){
    
}

MapLoadable * MapLoadable::createWithFileName(std::string filename){
    MapLoadable * loadable = new MapLoadable();
    if (loadable) {
        loadable->setFileName(filename);
        std::string path = loadable->_filename;
        size_t startPos = path.find_last_of(".");
        std::string texturePath = path.erase(startPos);
        texturePath = texturePath.append(".plist");
        loadable->setPlist(texturePath);
        
    }
    return loadable;
}

MapLoadable * MapLoadable::createWithFileNameAndPlist(std::string filename, std::string plist){
    MapLoadable * loadable = new MapLoadable();
    if (loadable) {
        loadable->setFileName(filename);
        loadable->setPlist(plist);
    }
    return loadable;
}

void MapLoadable::loadedCallBack(cocos2d::Texture2D *obj){
    CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(PLISTLoadableObj::loadedFaild), this);
    CCTexture2D * tx = dynamic_cast<CCTexture2D*>(obj);
    if (tx) {
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(_plist.c_str(), tx);
    }
    SpriteBatchNode * node = SpriteBatchNode::createWithTexture(obj);
    MapCache::getInstance()->addBatchNode(_plist, node);
    LoadableObj::loadedCallBack(obj);
}