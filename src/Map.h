#pragma once
#include "SpriteSheet.h"
#include "raylib.h"
//---------------------- tag map -------------------------
enum etagmap
{
	TAG_NULL=-1,
	// --- floor
	TAG_SAND0,
	TAG_SAND1,
	// --- build
	TAG_GRIS0,
	TAG_GRIS1,
	TAG_GRIS2,
	TAG_GRIS3,

	TAG_GAS0,
	TAG_GAS1,
	TAG_GAS2,
	TAG_GAS3,

	TAG_BASE,
	TAG_RAF1,
	TAG_RAF0,
	TAG_BAR,
	// --- entity
	TAG_VCS,
	TAG_MARINE
};
typedef enum etagmap TagMap;
#define Tag_IsFloor(ptag) (ptag>=TAG_SAND0 && ptag<=TAG_SAND1)
#define Tag_IsBuild(ptag) (ptag>=TAG_GRIS0 && ptag<=TAG_BAR)
#define Tag_IsEntity(ptag) (ptag>=TAG_VCS && ptag<=TAG_MARINE)

//---------------------- map ------------------------------
#define MAP_MAXSIZE 64*64
#define MAP_MAXTEAM 4
//map
struct smap
{
	int w;
	int h;
	int lteam[MAP_MAXSIZE][3];
	Color teamcolor[MAP_MAXTEAM];
	TagMap lmap[MAP_MAXSIZE][4];
};
typedef struct smap Map;

struct smapteamtexture
{
	Texture2D lsttext[MAP_MAXTEAM];
	bool IsInit;
} static MapTeamTexture;


Map Map_Init(const int pw,const int ph);
TagMap Map_Get(Map pmap,int px,int py,int pz);
void Map_Del(Map* pmap,int px,int py,int pz);
void Map_SetFloor(Map* pmap,int px,int py,TagMap itag);
void Map_Set(Map* pmap,int px,int py,TagMap itag, int pteamid);
int Map_GetNbTeam(Map pmap);
void Map_Draw(Map* pmap,int px,int py,SpriteSheet psprc);
void Map_Free(Map* pmap);
