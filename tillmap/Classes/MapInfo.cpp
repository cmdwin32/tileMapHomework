//
//  MapInfo.cpp
//  tilemap
//
//  Created by king hin on 14-6-21.
//
//

#include "MapInfo.h"

MapInfo::MapInfo():
_tile_count_y(0),
_tile_count_x(0),
_tile_height(0),
_tile_width(0),
_map_tile_per_feild(0),
_map_tile_per_area(0)
{
    
}

MapInfo::~MapInfo()
{

}


MapInfo * MapInfo::createWithData(JsonData &  _jdata)
{
    MapInfo * info = new MapInfo();
    if (info&&info->initWithData(_jdata)) {
        
    }
    else{
        if (info) {
            delete info;
            info = NULL;
        }
    }
    return info;
}

bool MapInfo::initWithData(JsonData &  _jdata)
{
    bool res = false;
    _tile_width = _jdata["map_info"]["tile_width"].getIntValue();
    _tile_height = _jdata["map_info"]["tile_height"].getIntValue();
    _tile_count_x = _jdata["map_info"]["tile_count_x"].getIntValue();
    _tile_count_y = _jdata["map_info"]["tile_count_y"].getIntValue();
    
    _map_tile_area_count = _jdata["map_info"]["area_count"].getIntValue();
    _map_tile_feild_count = _jdata["map_info"]["feild_count"].getIntValue();

    _map_tile_per_area = _tile_count_x / _map_tile_area_count;
    _map_tile_per_feild = _map_tile_per_area / _map_tile_feild_count;
    _map_tile_index_count = _map_tile_per_feild;
    
    _map_height = _tile_height * _tile_count_y;
    _map_width = _tile_width * _tile_count_x;
    
    res = true;
    return res;
}

int MapInfo::getMapWidth()
{
    return _map_width;
}

int MapInfo::getMapHeight()
{
    return _map_height;
}

int MapInfo::getTileCountX()
{
    return _tile_count_x;
}

int MapInfo::getTileCountY()
{
    return _tile_count_y;
}

int MapInfo::getTileHeight()
{
    return _tile_height;
}

int MapInfo::getTileWidth()
{
    return _tile_width;
}

int MapInfo::getTilePerArea()
{
    return _map_tile_per_area;
}

int MapInfo::getTilePerFeild()
{
    return _map_tile_per_feild;
}

int MapInfo::getTileAreaCount()
{
    return _map_tile_area_count;
}

int MapInfo::getTileFeildCount()
{
    return _map_tile_feild_count;
}

int MapInfo::getTileIndexCount()
{
    return _map_tile_index_count;
}



