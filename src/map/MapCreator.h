#ifndef MAPCREATOR_H
#define MAPCREATOR_H
#include "../BaseDefinitions.h"
#include "stdio.h"
#include "stdlib.h"
#include "string"
#include "string.h"
#include "random"
#include "fstream"
#include "iostream"
using namespace std;

string pic_path(int type);

string map_path(int layer);

string item_data_path(int layer);

class MapCreator
{
private:
    int map[64][64];
    int layer;
    void randomPoint(int&x,int&y);
    void spread(int x,int y,int type,int& max_spread);

public:
    // 设置layer层数
    MapCreator(int layer):layer(layer){};
    void createMap();

};

#endif // MAPCREATOR_H
