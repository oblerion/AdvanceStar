#include "Map.h"
Map Map_Init(const int pw,const int ph)
{
	Map map = {
		pw,
		ph,
		{{-1}},
		{BLUE,RED,GREEN,YELLOW}
	};

	for(int i=0;i<ph;i++)
	for(int j=0;j<pw;j++)
	{
		for(int l=0;l<3;l++)
		{
			map.lmap[i*pw+j][l]=TAG_NULL;
		}
	}

	MapTeamTexture.IsInit=false;
	return map;
}

TagMap Map_Get(Map pmap,int px,int py,int pz)
{
	return pmap.lmap[py*pmap.w+px][pz];
}

void Map_Del(Map* pmap,int px,int py,int pz)
{
	pmap->lmap[py*pmap->w+px][pz]=TAG_NULL;
	if(pz>0) pmap->lteam[py*pmap->w+px][pz-1] = -1;
}

void Map_SetFloor(Map* pmap,int px,int py,TagMap itag)
{
	pmap->lmap[py*pmap->w+px][0] = itag;
}
void Map_Set(Map* pmap,int px,int py,TagMap itag, int pteamid)
{
	int lid = -1;
	if(Tag_IsBuild(itag)) lid = 1;
	else if(Tag_IsEntity(itag)) lid = 2;

	if(lid != -1)
	{
		pmap->lmap[py*pmap->w+px][lid]=itag;
		pmap->lteam[py*pmap->w+px][lid-1] = pteamid;
	}
}
int Map_GetNbTeam(Map pmap)
{
	int ir = -1;
	for(int i=0;i<pmap.w*pmap.h;i++)
	for(int j=0;j<2;j++)
	{
		int lteamnb = pmap.lteam[i][j];
		if(lteamnb>ir) ir = lteamnb;
	}
	return ir+1;
}
Texture2D _remplaceColor(Texture2D sprc,Color incol,Color outcol)
{
	Image limg = LoadImageFromTexture(sprc);
	ImageColorReplace(&limg,incol,outcol);
	Texture2D ltexture = LoadTextureFromImage(limg);
	UnloadImage(limg);
	return ltexture;
}
void Map_Draw(Map* pmap,int px,int py,SpriteSheet psprc)
{
	if(!MapTeamTexture.IsInit)
	{//color team generate
		const int nbteam = Map_GetNbTeam(*pmap);
		Color colin = (Color){200,0,200,255};
		for(int i=0;i<nbteam;i++)
		{
			MapTeamTexture.lsttext[i] = _remplaceColor(psprc.texture,colin,pmap->teamcolor[i]);
		}
		MapTeamTexture.IsInit=true;
	}
	int stile = psprc.stile;
	int scale = psprc.scale;
	for(int i=0;i<pmap->h;i++)
	for(int j=0;j<pmap->w;j++)
	{
		for(int l=0;l<3;l++)
		{
			if(pmap->lmap[i*pmap->w+j][l]!=TAG_NULL)
			{
				if(l==0)
				{
					SpriteSheet_DrawT(
						psprc,
						pmap->lmap[i*pmap->w+j][l],
						px+j*stile*scale,
						py+i*stile*scale,
						0
					);
				}
				else
				{
					SpriteSheet_DrawTV(
						psprc,
						pmap->lmap[i*pmap->w+j][l],
						px+j*stile*scale,
						py+i*stile*scale,
						0,
						MapTeamTexture.lsttext[pmap->lteam[i*pmap->w+j][l-1]]
					);
				}
			}
		}
	}
}

void Map_Free(Map* pmap)
{

	const int nbteam = Map_GetNbTeam(*pmap);
	for(int i=0;i<nbteam;i++)
	{
		UnloadTexture(MapTeamTexture.lsttext[i]);
	}
}

