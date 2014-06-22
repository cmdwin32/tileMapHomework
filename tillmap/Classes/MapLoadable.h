//
//  MapLoadable.h
//  tilemap
//
//  Created by king hin on 14-6-21.
//
//

#ifndef __tilemap__MapLoadable__
#define __tilemap__MapLoadable__

#include <iostream>
#include "LoadableObj.h"

class MapLoadable : public PLISTLoadableObj{
public:
    /**
     * 根据文件名创建一个Plist加载对象
     */
    static MapLoadable * createWithFileName(std::string filename);
    
    static MapLoadable * createWithFileNameAndPlist(std::string filename,std::string plist);
    
    MapLoadable();
    virtual ~MapLoadable();
    
    // 重写完成函数 出去添加纹理缓存外，还要生成一个batchNode
    virtual void loadedCallBack(cocos2d::Texture2D *obj) override;
};

#endif /* defined(__tilemap__MapLoadable__) */
