#pragma once

#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

#define SPRITESHEET_MAXTAGLENGHT 50
#define SPRITESHEET_MAXTAGNB 256
#define SPRITESHEET_MAXSTILE 64

//save image
struct sdataimage
{
	Color data[SPRITESHEET_MAXSTILE*SPRITESHEET_MAXSTILE*SPRITESHEET_MAXTAGNB];
	int width;
	int height;
	int mipmaps;
	int format;
};
typedef struct sdataimage DataImage;
//save spritesheet
struct sdataspritesheet
{
	int nbw;
	int nbh;
	int stile;
	int scale;
	int mapid[SPRITESHEET_MAXTAGNB];
	Rectangle maptile[SPRITESHEET_MAXTAGNB];
	DataImage texture;
};
typedef struct sdataspritesheet DataSpriteSheet;
//draw spritesheet
struct sspritesheet
{
	int nbw;
	int nbh;
	int stile;
	int scale;
	int* mapid;
	Rectangle* maptile;
	Texture2D texture;
};
typedef struct sspritesheet SpriteSheet;
SpriteSheet SpriteSheet_Init(const char* fstr,int psize,int pscale);
SpriteSheet SpriteSheet_Load(DataSpriteSheet dsprc);//todo
void SpriteSheet_SetTag(SpriteSheet* ssprc, int pid,int itag);
int SpriteSheet_GetTag(SpriteSheet ssprc,int pid);
void SpriteSheet_Draw(SpriteSheet ssprc, int pid,int px,int py,float prot);
void SpriteSheet_DrawT(SpriteSheet ssprc, int itag,int px,int py,float prot);
void SpriteSheet_DrawTV(SpriteSheet ssprc, int itag,int px,int py,float prot,Texture2D vartext);
DataSpriteSheet SpriteSheet_Save(SpriteSheet ssprc);
int SpriteSheet_GetNbTags(SpriteSheet psprc);
int* SpriteSheet_GetTags(SpriteSheet psprc);
int* SpriteSheet_GetTagsId(SpriteSheet psprc);
void SpriteSheet_Free(SpriteSheet* ssprc);

