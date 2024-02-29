#pragma once
#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

#include "raylib.h"
#include <stdlib.h>

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
	char mapid[SPRITESHEET_MAXTAGNB][SPRITESHEET_MAXTAGLENGHT];
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
	
	char** mapid;
	Rectangle* maptile;
	Texture2D texture;
};
typedef struct sspritesheet SpriteSheet;
SpriteSheet SpriteSheet_Init(const char* fstr,int psize,int pscale);
SpriteSheet SpriteSheet_Load(DataSpriteSheet dsprc);//todo
void SpriteSheet_SetTag(SpriteSheet* ssprc, int pid,const char* pstag);
void SpriteSheet_Draw(SpriteSheet ssprc, int pid,int px,int py,float prot);
void SpriteSheet_DrawT(SpriteSheet ssprc, const char* pstag,int px,int py,float prot);
DataSpriteSheet SpriteSheet_Save(SpriteSheet ssprc);
void SpriteSheet_Free(SpriteSheet* ssprc);

#ifdef __cplusplus
}
#endif
