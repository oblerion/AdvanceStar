#pragma once
#include "SpriteSheet.h"
#include "raylib.h"
//---------------------- team id -------------------------
enum eteamid
{
	TEAM_NULL=-1,
	TEAM0,
	TEAM1,
	TEAM2,
	TEAM3
};
typedef enum eteamid TeamId;
#define IsTeam(idteam) (idteam>TEAM_NULL && idteam<=TEAM3)
//---------------------- tag map -------------------------
enum etagmap
{
	TAG_OUTSIDE=-2,
	TAG_NULL,
	// --- floor
	TAG_SAND0,
	TAG_SAND1,
	// --- build
	TAG_CRIS0,
	TAG_CRIS1,
	TAG_CRIS2,
	TAG_CRIS3,

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
#define Tag_IsBuild(ptag) (ptag>=TAG_CRIS0 && ptag<=TAG_BAR)
#define Tag_IsEntity(ptag) (ptag>=TAG_VCS && ptag<=TAG_MARINE)
#define Tag_IsResource(ptag) (ptag>=TAG_CRIS0 && ptag<=TAG_GAS3)

//---------------------- map ------------------------------
#define MAP_MAXSIZE 64*64
#define MAP_MAXTEAM 4
struct smapcell
{
	TagMap floor;
	TagMap maptag;
	TeamId mapteam;
};
typedef struct smapcell MapCell;
//map
struct smap
{
	int w;
	int h;
	Color teamcolor[MAP_MAXTEAM];
	MapCell map[MAP_MAXSIZE];
};
typedef struct smap Map;

Map Map_Init(const int pw,const int ph);
TagMap Map_GetFloor(Map pmap,int px,int py);
TagMap Map_Get(Map pmap,int px,int py);
TeamId Map_GetTeam(Map pmap,int px,int py);
void Map_DelFloor(Map* pmap,int px,int py);
void Map_Del(Map* pmap,int px,int py);
void Map_SetFloor(Map* pmap,int px,int py,TagMap itag);
void Map_Set(Map* pmap,int px,int py,TagMap itag,TeamId pteamid);
bool Map_Move(Map* pmap,int px,int py,int px2,int py2);
int Map_GetNbTeam(Map pmap);
void Map_Draw(Map* pmap,int px,int py,SpriteSheet psprc);

void Map_InitMapTeamTexture(SpriteSheet psprc,Map pmap);
Texture2D Map_GetMapTeamTexture(int pid);
void Map_FreeMapTeamTexture();
