//
//  MapObjects.cpp
//  tilemap
//
//  Created by king hin on 14-6-21.
//
//

#include "MapObjects.h"
#include <string.h>

#define FILE_NAME_SIZE 512
char _filename[FILE_NAME_SIZE];

MapObj::MapObj():
_index({-1,-1}),
_sp(NULL),
_is_using(false),
_batchnode_name("")
{

}

MapObj::~MapObj(){
    
}

MapObj * MapObj::create()
{
    return new MapObj();
}

bool MapObj::isUsing(Vec4 showing_rect)
{
 
    bool res = _is_using;
    if (_is_using) {
        // 如果不在正在显示的范围内则判断为无用 
        if (_index.x < showing_rect.x || _index.x > showing_rect.z || _index.y < showing_rect.y || _index.y > showing_rect.w ){
            res = false;
        }
    }
    return res;
}

Node * MapObj::use(Vec2 index,MapInfo * info){
    if (_is_using) {
        return NULL;
    }
    _is_using = true;
    _index = index;
    
    int _tmp_x = _index.x;
    int _tmp_y = info->getTileCountY() - 1 - _index.y;
    
    int _tmp_x_d = _tmp_x / info->getTilePerArea();
    int _tmp_y_d = _tmp_y / info->getTilePerArea();
    
    int area = _tmp_x_d + _tmp_y_d * info->getTileAreaCount() +1 ; // 地域
    
    _tmp_x = _tmp_x - _tmp_x_d * info->getTilePerArea();
    _tmp_y = _tmp_y - _tmp_y_d * info->getTilePerArea();
    
    _tmp_x_d = _tmp_x / info->getTilePerFeild();
    _tmp_y_d = _tmp_y / info->getTilePerFeild();
    
    int feild = _tmp_x_d + _tmp_y_d * info->getTileFeildCount() + 1; // 场景
    
    _tmp_x = _tmp_x - _tmp_x_d * info->getTilePerFeild();
    _tmp_y = _tmp_y - _tmp_y_d * info->getTilePerFeild();
    
    int map_index = _tmp_x + _tmp_y * info->getTileIndexCount() + 1; // 索引
    
    // 生成大图索引
    memset(_filename, 0, FILE_NAME_SIZE);
    sprintf(_filename, "map_%d_%d.plist",area,feild);
    _batchnode_name = _filename;
    // 生成小图文件名
    memset(_filename, 0, FILE_NAME_SIZE);
    sprintf(_filename, "map_%02d_%02d_%02d.png",area,feild,map_index);
    SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(_filename);
    if (!frame) {
        cout << "area : " <<area << " : " << feild << " : " << map_index << endl;
    }
    // 如果已经创建的sp则直接设置frame 否则创建一个新的sp
    if(_sp){
        std::string f = _filename;
        
        if (frame->getTexture()->getName() != _sp->getTexture()->getName()) {
            // 如果不是同一个大图的，那就这能重新创建了 
            _sp->removeFromParentAndCleanup(true);
            _sp = Sprite::createWithSpriteFrame(frame);
            _sp->setAnchorPoint(Vec2::ZERO);
        }
        else{
            _sp->setSpriteFrame(frame);
        }
    }
    else{
        _sp = Sprite::createWithSpriteFrame(frame);
        _sp->setAnchorPoint(Vec2::ZERO);
    }
    
    _sp->setPosition(Vec2(index.x * info->getTileWidth(), index.y * info->getTileHeight()));
    return _sp;
}

void MapObj::unUse(bool cleanup){
    if (_is_using) {
        _is_using = false;
        _index = {-1,-1};
        _batchnode_name = "";
        if(cleanup){
            _sp->removeFromParentAndCleanup(true);
            _sp = NULL;
        }
    }
}

Vec2 MapObj::getIndex()
{
    return _index;
}

Node * MapObj::getNode(){
    return _sp;
}

std::string MapObj::getBatchNodeName(){
    return _batchnode_name;
}
