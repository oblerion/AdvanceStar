#pragma once
#include <stdio.h>
#include <math.h>
#include "Map.h"
#include "SpriteSheet.h"
#include "Icons.h"

#define GAME_CRISCOST_VCS 25
#define GAME_CRISCOST_BASE 150
#define GAME_CRISCOST_BAR 100
#define GAME_CRISCOST_RAF 50

#define GAME_PACOST_BASE 3
#define GAME_PACOST_BAR 2
#define GAME_PACOST_RAF 2

struct sresource
{
    int team_cris[MAP_MAXTEAM];//count for team
    int team_gas[MAP_MAXTEAM];
    int onmap[MAP_MAXSIZE];
};
typedef struct sresource MapResource;

struct sturn
{
    int turnid;//team id to play
    int turnnb;//turn number
    int onmap[MAP_MAXSIZE];//pts action on map
};
typedef struct sturn MapTurn;

struct sgame
{
    Map map;
    MapResource mapres;
    MapTurn mapturn;
    int maphp[MAP_MAXSIZE];
};
typedef struct sgame Game;

Game Game_Load(const char* sfile,SpriteSheet psprc);
bool Game_MoveEntity(Game* pgame,int px,int py,int px2,int py2);
void Game_VCSBuildBase(Game* pgame,int vcs_x,int vcs_y,int base_x,int base_y);
void Game_VCSBuildBar(Game* pgame,int vcs_x,int vcs_y,int bar_x,int bar_y);
void Game_VCSBuildRaf(Game* pgame,int vcs_x,int vcs_y,int raff_x,int raff_y);
void Game_VCSCollectCris(Game* pgame,int vcs_x,int vcs_y,int cris_x,int cris_y);
void Game_VCSCollectGas(Game* pgame,int vcs_x,int vcs_y,int gas_x,int gas_y);
void Game_BaseCreateVCS(Game* pgame,int px,int py);
void Game_BarCreateMarine(Game* pgame,int px,int py);
void Game_Draw(Game* pgame, SpriteSheet psprc);
void Game_Free();
