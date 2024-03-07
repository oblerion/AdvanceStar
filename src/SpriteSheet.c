#include "SpriteSheet.h"

SpriteSheet SpriteSheet_Init(const char* fstr,int psize,int pscale)
{
	Texture2D ltexture = LoadTexture(fstr);
	SpriteSheet ssprc={
		ltexture.width/psize,
		ltexture.height/psize,
		psize,
		pscale
	};
	
	ssprc.texture = ltexture;
	ssprc.mapid = (int*)MemAlloc(sizeof(int)*ssprc.nbw*ssprc.nbh);
	ssprc.maptile = (Rectangle*)MemAlloc(sizeof(Rectangle)*ssprc.nbw*ssprc.nbh);
	
	for(int i=0;i<ssprc.nbh;i++)
	for(int j=0;j<ssprc.nbw;j++)
	{
		ssprc.mapid[i*ssprc.nbw+j] = -1;
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
	SpriteSheet sprc={0};
	
	return sprc;
}

void SpriteSheet_SetTag(SpriteSheet* ssprc, int pid,int itag)
{
	if( pid>-1 && pid<ssprc->nbw*ssprc->nbh)
		ssprc->mapid[pid]=itag;
}

int SpriteSheet_GetTag(SpriteSheet ssprc,int pid)
{
	int ri = -1;
	if(pid>-1 && pid<SPRITESHEET_MAXTAGNB)
		ri = ssprc.mapid[pid];
	return ri;
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

int _getId(SpriteSheet pssprc, int itag)
{
	int ir = -1;
	for(int i=0;i<pssprc.nbh*pssprc.nbw;i++)
	{
		if(itag==pssprc.mapid[i])
		{
			ir=i;
			break;
		}
	}	
	return ir;	
}

void SpriteSheet_DrawT(SpriteSheet ssprc, int itag,int px,int py,float prot)
{
	int idtile = _getId(ssprc,itag);
	if(idtile>-1)
	{
		SpriteSheet_Draw(ssprc,idtile,px,py,prot);
	}
}

void SpriteSheet_DrawTV(SpriteSheet ssprc, int itag,int px,int py,float prot,Texture2D vartext)
{
	const int pid = _getId(ssprc,itag);
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
		DrawTexturePro(vartext,ssprc.maptile[pid],rd,vo,prot,WHITE);
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
		dataspritesheet.mapid[i]=ssprc.mapid[i];
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
int SpriteSheet_GetNbTags(SpriteSheet psprc)
{
	int ir = 0;
	for(int i=0;i<psprc.nbh;i++)
	for(int j=0;j<psprc.nbw;j++)
	{
		if(psprc.mapid[i*psprc.nbw+j]>-1) ir++;
	}
	return ir;
}
int* SpriteSheet_GetTags(SpriteSheet psprc)
{//need free return
	int tipos = 0;
	int* tags = 0;
	tags = (int*)MemAlloc(sizeof(int)*psprc.nbh*psprc.nbw);

	for(int i=0;i<psprc.nbh;i++)
	for(int j=0;j<psprc.nbw;j++)
	{
		int ltag = psprc.mapid[i*psprc.nbw+j];
		if(ltag>-1)
		{
			tags[tipos] = ltag;
			tipos++;
		}
	}
	return tags;
}
int* SpriteSheet_GetTagsId(SpriteSheet psprc)
{//need free return
	int tipos = 0;
	int* ptri = NULL;
	ptri = (int*)MemAlloc(sizeof(int)*psprc.nbh*psprc.nbw);
	int lid;
	for(int i=0;i<psprc.nbh;i++)
	for(int j=0;j<psprc.nbw;j++)
	{
		lid = psprc.mapid[i*psprc.nbw+j];
		if(lid>-1)
		{
			ptri[tipos]=lid;
			tipos++;
		}
	}
	return ptri;
}

void SpriteSheet_Free(SpriteSheet* ssprc)
{
	if(ssprc!=NULL)
	{
		UnloadTexture(ssprc->texture);
		MemFree(ssprc->maptile);
		ssprc->maptile=0;
		MemFree(ssprc->mapid);
		ssprc->mapid=0;
		ssprc = 0;
	}
}
