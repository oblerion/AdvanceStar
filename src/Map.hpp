#pragma once
#include <string>
//#include "stdio.h"
#include "SpriteSheet.hpp"

//---------------------- map ------------------------------
#define MAP_MAXSIZE 64*64
#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif
//save map
struct data_map
{
	int w;
	int h;
	char smap[MAP_MAXSIZE][3][SPRITESHEET_MAXTAGLENGHT];
};
typedef struct data_map DataMap;
#ifdef __cplusplus
}
#endif

// draw map
class Map
{
	int w;
	int h;
	std::string lmap[MAP_MAXSIZE][3];
	SpriteSheet lspr;
public:
    Map(const int pw,const int ph,SpriteSheet psprc);
	Map(DataMap psmap,SpriteSheet psprc);
	~Map();
	int GetW();
	int GetH();
	std::string Get(int x,int y,int z);
    void SetFloor(int x,int y,std::string pstag);
    void SetBuidy(int x,int y,std::string pstag);
    void SetEntity(int x,int y,std::string pstag);
    void Draw(int px,int py);
	DataMap Save();
};
