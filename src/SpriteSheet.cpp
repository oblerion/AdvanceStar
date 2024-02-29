#include "SpriteSheet.hpp"


SpriteSheet SpriteSheet_Init(const char* fstr,int psize,int pscale)
{
	Texture2D ltexture = LoadTexture(fstr);
	SpriteSheet ssprc={
		ltexture.height/psize,
		ltexture.width/psize,
		psize,
		pscale
	};
	
	ssprc.texture = ltexture;
	ssprc.mapid = (char**)MemAlloc(sizeof(char*)*ssprc.nbw*ssprc.nbh);
	ssprc.maptile = (Rectangle*)MemAlloc(sizeof(Rectangle)*ssprc.nbw*ssprc.nbh);
	
	for(int i=0;i<ssprc.nbh;i++)
	for(int j=0;j<ssprc.nbw;j++)
	{
		ssprc.mapid[i*ssprc.nbw+j] = (char*)MemAlloc(SPRITESHEET_MAXTAGLENGHT);
		ssprc.mapid[i*ssprc.nbw+j][0] = '\0';
		ssprc.maptile[i*ssprc.nbw+j] = (Rectangle){
			(float)(j*ssprc.stile),
			(float)(i*ssprc.stile),
			(float)(ssprc.stile),
			(float)(ssprc.stile)
		};
	}
	
	return ssprc;
}

SpriteSheet SpriteSheet_Load(DataSpriteSheet dsprc)
{
	SpriteSheet sprc;
	
	return sprc;
}

void SpriteSheet_SetTag(SpriteSheet* ssprc, int pid,const char* pstag)
{
	if( pid>-1 && 
		pid<ssprc->nbw*ssprc->nbh && 
		TextLength(pstag) < SPRITESHEET_MAXTAGLENGHT)
			TextCopy(ssprc->mapid[pid],pstag);
}

void SpriteSheet_Draw(SpriteSheet ssprc, int pid,int px,int py,float prot)
{
	if(pid>-1 && pid<ssprc.nbw*ssprc.nbh)
	{
		float realsize = (float)ssprc.stile*ssprc.scale;
		Rectangle rd = {
			(float)px+(realsize*0.5f),
			(float)py+(realsize*0.5f),
			(float)realsize,
			(float)realsize
		};
		Vector2 vo = {realsize*0.5f,realsize*0.5f};
		DrawTexturePro(ssprc.texture,ssprc.maptile[pid],rd,vo,prot,WHITE);
	}
}

int _getId(SpriteSheet pssprc, const char* pstag)
{
	int ir = -1;
	for(int i=0;i<pssprc.nbh*pssprc.nbw;i++)
	{
		if(TextIsEqual(pstag,pssprc.mapid[i])) 
		{
			ir=i;
			break;
		}
	}	
	return ir;	
}

void SpriteSheet_DrawT(SpriteSheet ssprc, const char* pstag,int px,int py,float prot)
{
	int idtile = _getId(ssprc,pstag);
	if(idtile>-1)
	{
		SpriteSheet_Draw(ssprc,idtile,px,py,prot);
	}
}

DataSpriteSheet SpriteSheet_Save(SpriteSheet ssprc)
{
	DataSpriteSheet dataspritesheet = {
		ssprc.nbw,
		ssprc.nbh,
		ssprc.stile,
		ssprc.scale
	};
	for(int i=0;i<ssprc.nbh*ssprc.nbw;i++)
	{
		TextCopy(dataspritesheet.mapid[i],ssprc.mapid[i]);
		dataspritesheet.maptile[i]=ssprc.maptile[i];
	}
	Image img = LoadImageFromTexture(ssprc.texture);
	Color* cols = LoadImageColors(img);
	
	dataspritesheet.texture.width=img.width;
	dataspritesheet.texture.height=img.height;
	dataspritesheet.texture.mipmaps=img.mipmaps;
	dataspritesheet.texture.format=img.format;
	
	for(int i=0;i<img.width*img.height;i++)
	{
		dataspritesheet.texture.data[i]=cols[i];
	}
	
	UnloadImageColors(cols);
	UnloadImage(img);
	return dataspritesheet;
}

void SpriteSheet_Free(SpriteSheet* ssprc)
{
	if(ssprc!=NULL)
	{
		for(int i=0;i<ssprc->nbh;i++)
		for(int j=0;j<ssprc->nbw;j++)
		{
			MemFree(ssprc->mapid[i*ssprc->nbw+j]);
		}
		UnloadTexture(ssprc->texture);
		MemFree(ssprc->maptile);
		MemFree(ssprc->mapid);
		ssprc = NULL;
	}
}
