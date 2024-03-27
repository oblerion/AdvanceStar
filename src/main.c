#include "raylib.h"
#include <stdio.h>

//#define CTYPE_EDIT0
//#define CTYPE_EDIT1
#define CTYPE_GAME

#include "Map.h"
struct smapteamtexture
{
	Texture2D lsttext[MAP_MAXTEAM];
	bool IsInit;
}_MapTeamTexture;


Texture2D _Map_remplaceColor(Texture2D sprc,Color incol,Color outcol)
{
	Image limg = LoadImageFromTexture(sprc);
	ImageColorReplace(&limg,incol,outcol);
	Texture2D ltexture = LoadTextureFromImage(limg);
	UnloadImage(limg);
	return ltexture;
}

Map Map_Init(const int pw,const int ph)
{
	Map map = {
		pw,
		ph,
		{BLUE,RED,GREEN,YELLOW}
	};

	MapCell mc = {TAG_NULL,TAG_NULL,TEAM_NULL};
	for(int i=0;i<ph;i++)
	for(int j=0;j<pw;j++)
	{
		for(int l=0;l<3;l++)
		{
			map.map[i*pw+j]=mc;
		}
	}
	return map;
}

TagMap Map_GetFloor(Map pmap,int px,int py)
{
	TagMap rtm = TAG_OUTSIDE;
	if( px>-1 && px<pmap.w &&
		py>-1 && py<pmap.h)
		rtm = pmap.map[py*pmap.w+px].floor;
	return rtm;
}

TagMap Map_Get(Map pmap,int px,int py)
{
	TagMap rtm = TAG_OUTSIDE;
	if( px>-1 && px<pmap.w &&
		py>-1 && py<pmap.h)
		rtm =  pmap.map[py*pmap.w+px].maptag;
	return rtm;
}

TeamId Map_GetTeam(Map pmap,int px,int py)
{
	int ir = TEAM_NULL;
	if( px>-1 && px<pmap.w &&
		py>-1 && py<pmap.h)
		ir = pmap.map[py*pmap.w+px].mapteam;
	return ir;
}
void Map_DelFloor(Map* pmap,int px,int py)
{
	pmap->map[py*pmap->w+px].floor=TAG_NULL;
}

void Map_Del(Map* pmap,int px,int py)
{
	pmap->map[py*pmap->w+px].maptag=TAG_NULL;
	pmap->map[py*pmap->w+px].mapteam = TEAM_NULL;
}

void Map_SetFloor(Map* pmap,int px,int py,TagMap itag)
{
	pmap->map[py*pmap->w+px].floor = itag;
}
void Map_Set(Map* pmap,int px,int py,TagMap itag,TeamId pteamid)
{
	pmap->map[py*pmap->w+px].maptag = itag;
	pmap->map[py*pmap->w+px].mapteam = pteamid;
}
bool Map_Move(Map* pmap,int px,int py,int px2,int py2)
{
	bool br=false;
	TagMap tm0 = Map_Get(*pmap,px,py);
	TagMap tm1 = Map_Get(*pmap,px2,py2);
	int iteam0 = Map_GetTeam(*pmap,px,py);

	if(	tm0 != TAG_NULL &&
		tm1 == TAG_NULL)
	{
		Map_Set(pmap,px2,py2,tm0,iteam0);
		Map_Del(pmap,px,py);
		br=true;
	}
	return br;
}
int Map_GetNbTeam(Map pmap)
{
	int ir = -1;
	for(int i=0;i<pmap.w*pmap.h;i++)
		if(pmap.map[i].mapteam>ir) ir = pmap.map[i].mapteam;
	return ir;
}

void Map_Draw(Map* pmap,int px,int py,SpriteSheet psprc)
{
	int stile = psprc.stile;
	int scale = psprc.scale;
	TagMap tfloor;
	TagMap tmap;
	TeamId iteam;

	for(int i=0;i<pmap->h;i++)
	for(int j=0;j<pmap->w;j++)
	{

		tfloor =  Map_GetFloor(*pmap,j,i);
		tmap = Map_Get(*pmap,j,i);
		iteam = Map_GetTeam(*pmap,j,i);

		if(tfloor!=TAG_NULL)
			SpriteSheet_DrawT(
				psprc,
				tfloor,
				px+j*stile*scale,
				py+i*stile*scale,
				0
			);

		if(tmap!=TAG_NULL)
			SpriteSheet_DrawTV(
				psprc,
				tmap,
				px+j*stile*scale,
				py+i*stile*scale,
				0,
				_MapTeamTexture.lsttext[iteam]
			);
	}
}
void Map_InitMapTeamTexture(SpriteSheet psprc,Map pmap)
{
	//color team generate
	Color colin = (Color){200,0,200,255};
	for(int i=0;i<MAP_MAXTEAM;i++)
	{
		_MapTeamTexture.lsttext[i] = _Map_remplaceColor(psprc.texture,colin,pmap.teamcolor[i]);
	}
}

Texture2D Map_GetMapTeamTexture(int pid)
{
	return _MapTeamTexture.lsttext[pid];
}

void Map_FreeMapTeamTexture()
{
	for(int i=0;i<MAP_MAXTEAM;i++)
	{
		UnloadTexture(_MapTeamTexture.lsttext[i]);
	}
}

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
    DataSpriteSheet ddsprc = dsprc;

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

int _SpriteSheet_getId(SpriteSheet pssprc, int itag)
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
	int idtile = _SpriteSheet_getId(ssprc,itag);
	if(idtile>-1)
	{
		SpriteSheet_Draw(ssprc,idtile,px,py,prot);
	}
}

void SpriteSheet_DrawTV(SpriteSheet ssprc, int itag,int px,int py,float prot,Texture2D vartext)
{
	const int pid = _SpriteSheet_getId(ssprc,itag);
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

#if defined(CTYPE_EDIT0) || defined(CTYPE_EDIT1)
#include "MapEditor.h"

MapEditor MapEditor_Init(SpriteSheet psprc)
{
    MapEditor medit = {
        Map_Init(64,64),
        psprc,
        SpriteSheet_GetTags(psprc),
        0,0,0,0
    };
    Map_InitMapTeamTexture(psprc,medit.map);
    return medit;
}

MapEditor MapEditor_Load(Map pmap,SpriteSheet psprc)
{
    MapEditor medit = {
        pmap,
        psprc,
        SpriteSheet_GetTags(psprc),
        0,0,0,0
    };
    Map_InitMapTeamTexture(psprc,medit.map);
    return medit;
}

void MapEditor_Draw(MapEditor* pmedit)
{
    int inbw = pmedit->map.w;
    int inbh = pmedit->map.h;
    int istile = pmedit->sprc.stile;
    int iscale = pmedit->sprc.scale;

    int imousex = (GetMouseX()-pmedit->offx)/(istile*iscale);
    int imousey = (GetMouseY()-pmedit->offy)/(istile*iscale);

    const int nbtag = SpriteSheet_GetNbTags(pmedit->sprc);
    TagMap ptag = pmedit->tags[pmedit->curant_tag];

    bool CanBePlace =
    !(
        (Tag_IsFloor(Map_GetFloor(pmedit->map,imousex,imousey)) && Tag_IsFloor(ptag)) ||
        (Tag_IsBuild(Map_Get(pmedit->map,imousex,imousey)) && Tag_IsBuild(ptag)) ||
        (Tag_IsEntity(Map_Get(pmedit->map,imousex,imousey)) && Tag_IsEntity(ptag))
    );

    // place/del element
    if( imousex>-1 && inbw > imousex &&
        imousey>-1 && inbh > imousey)
    {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CanBePlace)
        {
            if(Tag_IsFloor(ptag))
                Map_SetFloor(&pmedit->map,imousex,imousey,ptag);
            else
                Map_Set(&pmedit->map,imousex,imousey,ptag,pmedit->curant_team);
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            //for(int i=2;i>-1;i--)
            if(Map_Get(pmedit->map, imousex,imousey)!=TAG_NULL)
            {
                Map_Del(&pmedit->map,imousex,imousey);
            }
            else if(Map_GetFloor(pmedit->map,imousex,imousey)!=TAG_NULL)
            {
                Map_DelFloor(&pmedit->map,imousex,imousey);
            }
        }
    }
    else CanBePlace = false;
    // change tag
    if(GetMouseWheelMove()<0)
    {
        if(Tag_IsBuild(ptag) || Tag_IsEntity(ptag))
        {
            if(pmedit->curant_team<MAP_MAXTEAM-1)
                pmedit->curant_team++;
            else
                pmedit->curant_team=0;
        }
    }
    else if(GetMouseWheelMove()>0)
    {
        if(pmedit->curant_tag==nbtag-1)
            pmedit->curant_tag=0;
        else
            pmedit->curant_tag++;
    }
    // save map
    if(IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_S))
    {
        MapEditor_Save(*pmedit,"map.dat");
    }
    //draw
    Map_Draw(&pmedit->map,pmedit->offx,pmedit->offy,pmedit->sprc);
    SpriteSheet_DrawTV(pmedit->sprc,ptag,pmedit->offx+(imousex*iscale*istile),pmedit->offy+(imousey*iscale*istile),0,Map_GetMapTeamTexture(pmedit->curant_team));

    if(CanBePlace)
        DrawRectangleLines(
            pmedit->offx+(imousex*iscale*istile),
            pmedit->offy+(imousey*iscale*istile),
            iscale*istile,
            iscale*istile,
            GREEN);
    else
        DrawRectangleLines(
            pmedit->offx+(imousex*iscale*istile),
            pmedit->offy+(imousey*iscale*istile),
            iscale*istile,
            iscale*istile,
            RED);
}
void MapEditor_LoadSave(MapEditor* pmedit,const char* sfile)
{
    FILE* fic = fopen(sfile,"rb");
    if(fic!=NULL)
    {
        fread(&pmedit->map,sizeof(Map),1,fic);
        fclose(fic);
    }
}
void MapEditor_Save(MapEditor pmedit,const char* sfile)
{
    FILE* fic = fopen(sfile,"wb");
    fwrite(&pmedit.map,sizeof(Map),1,fic);
    fclose(fic);
}
void MapEditor_Free(MapEditor pmedit)
{
    MemFree(pmedit.tags);
    pmedit.tags=NULL;
    Map_FreeMapTeamTexture();
}

#elif defined(CTYPE_GAME)
#include "Icons.h"

struct sicons
{
    SpriteSheet sprc;
}Icons;

void Icons_Init()
{
    Icons.sprc=SpriteSheet_Init("./asset/titlesheet.png",8,2);
    SpriteSheet_SetTag(&Icons.sprc,80,ICON_CRIS);
    SpriteSheet_SetTag(&Icons.sprc,81,ICON_GAS);
}
void Icons_Draw(IdIcons id,int x,int y)
{
    SpriteSheet_DrawT(Icons.sprc,id,x,y,0);
}
void Icons_Free()
{
    SpriteSheet_Free(&Icons.sprc);
}

#include "Game.h"

struct sgamecursor
{
    int x;
    int y;
    int lastx;
    int lasty;
    int offx;
    int offy;
    TagMap floor;
    TagMap map;
    TeamId team;
}_Game_GameCursor;

void _Game_GameCursor_Update(Game* pgame,SpriteSheet psprc)
{
    int istile = psprc.stile;
    int iscale = psprc.scale;
    int imousex = (GetMouseX()-_Game_GameCursor.offx)/(istile*iscale);
    int imousey = (GetMouseY()-_Game_GameCursor.offy)/(istile*iscale);

    _Game_GameCursor.x = imousex;
    _Game_GameCursor.y = imousey;
    _Game_GameCursor.floor = Map_GetFloor(pgame->map,imousex,imousey);
    _Game_GameCursor.map = Map_Get(pgame->map,imousex,imousey);
    _Game_GameCursor.team = Map_GetTeam(pgame->map,imousex,imousey);
}

#define _Game_GameCursor_IfUnSelect() (_Game_GameCursor.lastx==-1 && _Game_GameCursor.lasty==-1)
#define _Game_GameCursor_IfSelect() (_Game_GameCursor.lastx>-1 && _Game_GameCursor.lasty>-1)

void _Game_GameCursor_UnSelect()
{
    _Game_GameCursor.lastx=-1;
    _Game_GameCursor.lasty=-1;
}
void _Game_GameCursor_Select()
{
    _Game_GameCursor.lastx=_Game_GameCursor.x;
    _Game_GameCursor.lasty=_Game_GameCursor.y;
}

bool _Game_GameCursor_IsInGame(Game* pgame)
{
    bool rb = false;
    if( _Game_GameCursor.x>-1 &&
        _Game_GameCursor.x<pgame->map.w &&
        _Game_GameCursor.y>-1 &&
        _Game_GameCursor.y<pgame->map.h) rb=true;
    return rb;
}
#define _Game_COLLIDE(x,y,w,h,x2,y2,w2,h2) (x+w>x2 && x<x2+w2 && y+h>y2 && y2+h2>y)
#define _Game_DIST(x,x2,y,y2) (abs(x-x2)+abs(y-y2))
bool _Game_UIBUTTON(int px,int py,const char* pname,int fontsize,Color color)
{
    bool lbool = false;
    const int width = MeasureText(pname,fontsize)+8;
    const int height = fontsize+4;
    Color lcol = color;
    if(_Game_COLLIDE(GetMouseX(),GetMouseY(),10,10,px-4,py-2,width,height))
    {
        lcol.a = 50;
        if(IsMouseButtonPressed(0)) lbool = true;
    }
    DrawRectangle(px-4,py-2,width,height,GRAY);
    DrawRectangleLines(px-4,py-2,width,height,lcol);
    DrawText(pname,px,py,fontsize,lcol);
    return lbool;
}


void _Game_Resource_MapSet(Game* pgame,int px,int py,int nb)
{
    pgame->mapres.onmap[py*pgame->map.w+px]=nb;
}
int _Game_Resource_MapGet(Game* pgame,int px,int py)
{
    return pgame->mapres.onmap[py*pgame->map.w+px];
}
bool _Game_Resource_IfCostCris(Game* pgame,TeamId iteam,int nb)
{
    bool rb=false;
    if(pgame->mapres.team_cris[iteam]>=nb)
        rb=true;
    return rb;
}
bool _Game_Resource_IfCostGas(Game* pgame,TeamId iteam,int nb)
{
    bool rb=false;
    if(pgame->mapres.team_gas[iteam]>=nb)
        rb=true;
    return rb;
}
void _Game_Resource_MapInit(Game* pgame)
{
    Map pmap = pgame->map;
    for(int y=0;y<pmap.h;y++)
    for(int x=0;x<pmap.w;x++)
    {
        switch(Map_Get(pmap,x,y))
        {
            case TAG_CRIS3:
            case TAG_GAS3:
                _Game_Resource_MapSet(pgame,x,y,200);
            break;
            case TAG_CRIS2:
            case TAG_GAS2:
                _Game_Resource_MapSet(pgame,x,y,150);
            break;
            case TAG_CRIS1:
            case TAG_GAS1:
                _Game_Resource_MapSet(pgame,x,y,100);
            break;
            case TAG_CRIS0:
            case TAG_GAS0:
                _Game_Resource_MapSet(pgame,x,y,50);
            break;
            default:
                _Game_Resource_MapSet(pgame,x,y,0);
        }
    }
}

bool _Game_Resource_MapCollectCris(Game* pgame,int vcs_x,int vcs_y,int cris_x,int cris_y)
{
    //collect after second click
    bool rb=false;
    int dist = _Game_DIST(vcs_x,cris_x,vcs_y,cris_y);
    if( dist == 1 && _Game_GameCursor_IfSelect())
    {
        TagMap tm_last = Map_Get(pgame->map,vcs_x,vcs_y);
        TagMap tm = Map_Get(pgame->map,cris_x,cris_y);
        if(tm_last==TAG_VCS && Tag_IsResource(tm))
        {
            int nbcollect = 20;
            int nbres = _Game_Resource_MapGet(pgame,cris_x,cris_y);
            _Game_Resource_MapSet(pgame,cris_x,cris_y,nbres-nbcollect);
            TeamId iteam_vcs =  Map_GetTeam(
                pgame->map,
                _Game_GameCursor.lastx,
                _Game_GameCursor.lasty
            );

            pgame->mapres.team_cris[iteam_vcs]+=nbcollect;
            rb=true;
        }
    }
    return rb;
}

bool _Game_Resource_MapCollectGas(Game* pgame,int vcs_x,int vcs_y,int gas_x,int gas_y)
{
    //collect after second click
    bool rb=false;
    int dist = _Game_DIST(vcs_x,gas_x,vcs_y,gas_y);
    if( dist == 1 && _Game_GameCursor_IfSelect())
    {
        TagMap tm_last = Map_Get(pgame->map,vcs_x,vcs_y);
        if(tm_last==TAG_VCS && _Game_GameCursor.map==TAG_RAF1)
        {
            int nbcollect = 5;
            int nbres = _Game_Resource_MapGet(pgame,gas_x,gas_y);
            _Game_Resource_MapSet(pgame,gas_x,gas_y,nbres-nbcollect);
            TeamId iteam_vcs =  Map_GetTeam(
                pgame->map,
                vcs_x,
                vcs_y
            );

            pgame->mapres.team_gas[iteam_vcs]+=nbcollect;
            rb=true;
        }
    }
    return rb;
}
void _Game_Resource_TeamInit(Game* pgame,const int nc,const int ng)
{
    for(int i=0;i<MAP_MAXTEAM;i++)
    {
        pgame->mapres.team_cris[i]=nc;
        pgame->mapres.team_gas[i]=ng;
    }
}
bool _Game_Resource_CostCris(Game* pgame,TeamId iteam, int nb)
{
    bool br = false;
    if(IsTeam(iteam) && nb<=pgame->mapres.team_cris[iteam])
    {
        pgame->mapres.team_cris[iteam]-=nb;
        br=true;
    }
    return br;
}
bool _Game_Resource_CostGas(Game* pgame,TeamId iteam, int nb)
{
    bool br = false;
    if(IsTeam(iteam) && nb<=pgame->mapres.team_gas[iteam])
    {
        pgame->mapres.team_gas[iteam]-=nb;
        br=true;
    }
    return br;
}


int _Game_Turn_Get(Game pgame,int x,int y)
{
    return pgame.mapturn.onmap[y*pgame.map.w+x];
}
void _Game_Turn_Set(Game* pgame,int x,int y,int nb)
{
    pgame->mapturn.onmap[y*pgame->map.w+x]=nb;
}
bool _Game_Turn_IfCost(Game* pgame,int x,int y,int nb)
{
    bool rb = false;
    if(_Game_Turn_Get(*pgame,x,y)>=nb)
        rb=true;
    return rb;
}
void _Game_Turn_Init(Game* pgame)
{
    pgame->mapturn.turnid=0;
    pgame->mapturn.turnnb=0;
    for(int j=0;j<pgame->map.h;j++)
    for(int i=0;i<pgame->map.w;i++)
        _Game_Turn_Set(pgame,i,j,0);
}

void _Game_Turn_Reset(Game* pgame)
{
    for(int j=0;j<pgame->map.h;j++)
    for(int i=0;i<pgame->map.w;i++)
        _Game_Turn_Set(pgame,i,j,0);
}
void _Game_Turn_Next(Game* pgame)
{
    _Game_Turn_Reset(pgame);
    if(pgame->mapturn.turnid+1>Map_GetNbTeam(pgame->map))
    {
        pgame->mapturn.turnid=0;
        pgame->mapturn.turnnb++;
    }
    else
        pgame->mapturn.turnid++;

    for(int i=0;i<pgame->map.h;i++)
    for(int j=0;j<pgame->map.w;j++)
    {
        TeamId tid = Map_GetTeam(pgame->map,j,i);
        if(tid==pgame->mapturn.turnid)
        switch(Map_Get(pgame->map,j,i))
        {
            case TAG_VCS:
                _Game_Turn_Set(pgame,j,i,3);
            break;
            case TAG_BASE:
                _Game_Turn_Set(pgame,j,i,1);
            break;
            case TAG_BAR:
                _Game_Turn_Set(pgame,j,i,1);
            break;
            default:;
        }
    }

}
bool _Game_Turn_Cost(Game* pgame,int px,int py,int nb)
{
    bool rb = false;
    int tnb = _Game_Turn_Get(*pgame,px,py);
    if(tnb>=nb)
    {
        _Game_Turn_Set(pgame,px,py,tnb-nb);
        rb=true;
    }
    return rb;
}
void _Game_Turn_Move(Game* pgame,int px,int py,int px2,int py2)
{
    int tnb = _Game_Turn_Get(*pgame,px,py);
    _Game_Turn_Set(pgame,px2,py2,tnb);
    _Game_Turn_Set(pgame,px,py,0);
}

void _Game_Hp_Set(Game* pgame,int px,int py,int nb)
{
    pgame->maphp[py*pgame->map.w+px]=nb;
}

int _Game_Hp_Get(Game* pgame,int px,int py)
{
    return pgame->maphp[py*pgame->map.w+px];
}

void _Game_UI_Cursor(SpriteSheet sprc)
{
    int lw = sprc.stile*sprc.scale;
    int lx = _Game_GameCursor.offx+(_Game_GameCursor.x*lw);
    int ly = _Game_GameCursor.offy+(_Game_GameCursor.y*lw);
    DrawRectangleLines(lx,ly,lw,lw,WHITE);
}
void _Game_UI_Select(SpriteSheet sprc)
{
    const int offset = 20;
    const int lw = sprc.stile*sprc.scale;
    const int lx = _Game_GameCursor.offx+(_Game_GameCursor.lastx*lw)+offset/2;
    const int ly = _Game_GameCursor.offy+(_Game_GameCursor.lasty*lw)+offset/2;

    if(_Game_GameCursor_IfSelect())
        DrawRectangleLines(lx,ly,lw-offset,lw-offset,WHITE);
}
void _Game_UI_Resource(Game pgame,int px,int py,TeamId piteam)
{
    const char* text_cris = TextFormat("%4d ",
        pgame.mapres.team_cris[piteam]);
    const int off_x1 = MeasureText(text_cris,20);
    const char* text_gas = TextFormat("%4d ",
        pgame.mapres.team_gas[piteam]);
    const int off_x2 = MeasureText(text_gas,20);
    DrawText(text_cris,px,py,20,BLACK);
    Icons_Draw(ICON_CRIS,px+off_x1,py);
    DrawText(text_gas,px,py+20,20,BLACK);
    Icons_Draw(ICON_GAS,px+off_x2,py+20);
}

void _Game_UI_Turn(Game* pgame,int px,int py)
{
    const int idturn = pgame->mapturn.turnid;
    const char* sstr = TextFormat("team | turn %d",
    pgame->mapturn.turnnb);
    DrawRectangle(px,py,MeasureText("team",20),20,pgame->map.teamcolor[idturn]);
    DrawText(sstr,px,py,20,BLACK);
}

void _Game_UI_PA(Game* pgame,SpriteSheet psprc)
{
    const int offset = 12;
    const int lw = psprc.stile*psprc.scale;
    const int idturn = pgame->mapturn.turnid;
    for(int j=0;j<pgame->map.h;j++)
    for(int i=0;i<pgame->map.w;i++)
    {
        TagMap tm = Map_Get(pgame->map,i,j);
        if(Map_GetTeam(pgame->map,i,j)==idturn &&
           !Tag_IsResource(tm) &&
           tm!=TAG_RAF1 &&
           tm!=TAG_RAF0
        )
        {
            const char* cstr = TextFormat("%2d PA",_Game_Turn_Get(*pgame, i,j));
            DrawRectangle(offset*2+(i*lw),(j+1)*lw,MeasureText(cstr,18)+2,18,BLACK);
            DrawText(cstr,offset*2+(i*lw),(j+1)*lw,18,WHITE);
        }
    }

}
void _Game_UI_MenuVCS(Game* pgame,SpriteSheet psprc)
{
    const int lw = psprc.stile*psprc.scale;
    const int dist = _Game_DIST(_Game_GameCursor.lastx,_Game_GameCursor.x,_Game_GameCursor.lasty,_Game_GameCursor.y);

    int vcs_pa = _Game_Turn_Get(*pgame,_Game_GameCursor.lastx,_Game_GameCursor.lasty);
    if(Map_Get(pgame->map,_Game_GameCursor.lastx,_Game_GameCursor.lasty)==TAG_VCS && vcs_pa>0
    )
    {
        // TeamId iteam = Map_GetTeam(pgame->map,_Game_GameCursor.lastx,_Game_GameCursor.lasty);
        TagMap tdest = Map_Get(pgame->map,_Game_GameCursor.x,_Game_GameCursor.y);
        if(tdest==TAG_NULL)
        {
            if(vcs_pa>0)
            if(_Game_UIBUTTON((lw/2)+_Game_GameCursor.x*lw,_Game_GameCursor.offy+_Game_GameCursor.y*lw,"move",16,BLACK))
                if(Game_MoveEntity(pgame,
                    _Game_GameCursor.lastx,
                    _Game_GameCursor.lasty,
                    _Game_GameCursor.x,
                    _Game_GameCursor.y)) _Game_GameCursor_UnSelect();
            if(vcs_pa==3 && dist==1)
            if(_Game_UIBUTTON((lw/2)+_Game_GameCursor.x*lw,21+_Game_GameCursor.offy+_Game_GameCursor.y*lw,"build base",16,BLACK)
            )
                Game_VCSBuildBase(pgame,
                    _Game_GameCursor.lastx,
                    _Game_GameCursor.lasty,
                    _Game_GameCursor.x,
                    _Game_GameCursor.y);
            if(vcs_pa>1 && dist==1)
            if(_Game_UIBUTTON((lw/2)+_Game_GameCursor.x*lw,42+_Game_GameCursor.offy+_Game_GameCursor.y*lw,"build bar",16,BLACK))
            {
                Game_VCSBuildBar(pgame,
                    _Game_GameCursor.lastx,
                    _Game_GameCursor.lasty,
                    _Game_GameCursor.x,
                    _Game_GameCursor.y);
            }

        }
        else if(dist==1)
        {
            switch(tdest)
            {
                case TAG_CRIS0:
                case TAG_CRIS1:
                case TAG_CRIS2:
                case TAG_CRIS3:
                    if(vcs_pa>0)
                    if(_Game_UIBUTTON((lw/2)+_Game_GameCursor.x*lw,_Game_GameCursor.offy+_Game_GameCursor.y*lw,"collect",16,BLACK))
                        Game_VCSCollectCris(pgame,
                            _Game_GameCursor.lastx,
                            _Game_GameCursor.lasty,
                            _Game_GameCursor.x,
                            _Game_GameCursor.y);
                break;
                case TAG_GAS0:
                case TAG_GAS1:
                case TAG_GAS2:
                case TAG_GAS3:
                    if(_Game_UIBUTTON((lw/2)+_Game_GameCursor.x*lw,_Game_GameCursor.offy+_Game_GameCursor.y*lw,"build raff",16,BLACK))
                        Game_VCSBuildRaf(pgame,
                            _Game_GameCursor.lastx,
                            _Game_GameCursor.lasty,
                            _Game_GameCursor.x,
                            _Game_GameCursor.y);
                break;
                case TAG_RAF1:
                        if(_Game_UIBUTTON((lw/2)+_Game_GameCursor.x*lw,_Game_GameCursor.offy+_Game_GameCursor.y*lw,"collect",16,BLACK)) //puts("collect");
                        Game_VCSCollectGas(pgame,
                            _Game_GameCursor.lastx,
                            _Game_GameCursor.lasty,
                            _Game_GameCursor.x,
                            _Game_GameCursor.y);
                break;
                default:;
            }
        }
    }
}

void _Game_UI_MenuBase(Game* pgame,SpriteSheet psprc)
{
    const int lw = psprc.stile*psprc.scale;
    //const int dist = _Game_DIST(_Game_GameCursor.lastx,_Game_GameCursor.x,_Game_GameCursor.lasty,_Game_GameCursor.y);
    int base_pa = _Game_Turn_Get(*pgame,_Game_GameCursor.x,_Game_GameCursor.y);
    if(Map_Get(pgame->map,_Game_GameCursor.x,_Game_GameCursor.y)==TAG_BASE && _Game_GameCursor_IfUnSelect())
    {
        if(base_pa>0)
        if(_Game_UIBUTTON((lw/2)+_Game_GameCursor.x*lw,_Game_GameCursor.offy+_Game_GameCursor.y*lw,"build VCS",16,BLACK))
         {
             if(_Game_Turn_Cost(pgame,
                        _Game_GameCursor.x,
                        _Game_GameCursor.y,1))
             Game_BaseCreateVCS(pgame,_Game_GameCursor.x,_Game_GameCursor.y);
         }
    }

}

void _Game_UI_MenuBar(Game* pgame,SpriteSheet psprc)
{
    const int lw = psprc.stile*psprc.scale;
    //const int dist = _Game_DIST(_Game_GameCursor.lastx,_Game_GameCursor.x,_Game_GameCursor.lasty,_Game_GameCursor.y);
    int bar_pa = _Game_Turn_Get(*pgame,_Game_GameCursor.x,_Game_GameCursor.y);
    if(Map_Get(pgame->map,_Game_GameCursor.x,_Game_GameCursor.y)==TAG_BAR && _Game_GameCursor_IfUnSelect())
    {
        if(bar_pa>0)
        if(_Game_UIBUTTON((lw/2)+_Game_GameCursor.x*lw,_Game_GameCursor.offy+_Game_GameCursor.y*lw,"create marine",16,BLACK))
        if(_Game_Turn_Cost(pgame,
            _Game_GameCursor.x,
            _Game_GameCursor.y,1))
        {
            Game_BarCreateMarine(pgame,
                                 _Game_GameCursor.x,
                                 _Game_GameCursor.y);
        }
    }
}

void _Game_UI_ButtonTurn(Game* pgame,int px,int py)
{
    if(_Game_UIBUTTON(px,py,"next turn",18,BLACK))
    {
        _Game_Turn_Next(pgame);
    }
}


Game Game_Load(const char* sfile,SpriteSheet psprc)
{
    Game lgame={0};
    FILE* fic = fopen(sfile,"rb");
    if(fic!=NULL)
    {
        fread(&lgame.map,sizeof(Map),1,fic);
        fclose(fic);
    }
    _Game_GameCursor.offy=20;
    _Game_GameCursor_UnSelect();
    _Game_Resource_TeamInit(&lgame,50,50);
    _Game_Resource_MapInit(&lgame);
    _Game_Turn_Init(&lgame);
    Map_InitMapTeamTexture(psprc,lgame.map);
    return lgame;
}

bool Game_MoveEntity(Game* pgame,int px,int py,int px2,int py2)
{
    bool rb = false;
    int dist = _Game_DIST(px,px2,py,py2);
    if( _Game_Turn_Cost(pgame,px,py,dist) &&
        Map_Move(&pgame->map,px,py,px2,py2))
    {
        rb=true;
        _Game_Turn_Move(pgame,px,py,px2,py2);
        //_Game_GameCursor_UnSelect();
    }

    return rb;
}

bool _Game_CreateEntity(Game* pgame,int px,int py,TagMap tag)
{
    bool rb = false;
    const int lpos[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
    TeamId iteam = Map_GetTeam(pgame->map,px,py);
    for(int i=0;i<4;i++)
    {
        if(Map_Get(pgame->map,px+lpos[i][0],py+lpos[i][1])==TAG_NULL)
        {
            Map_Set(&pgame->map,
                    px+lpos[i][0],
                    py+lpos[i][1],
                    tag,
                    iteam);
            rb=true;
            break;
        }
    }
    return rb;
}
void Game_BaseCreateVCS(Game* pgame,int px,int py)
{
    TeamId iteam = Map_GetTeam(pgame->map,px,py);
    TagMap tm = Map_Get(pgame->map,px,py);
    if(_Game_GameCursor_IfUnSelect() &&
        tm==TAG_BASE &&
        _Game_Resource_IfCostCris(pgame,iteam,GAME_CRISCOST_VCS)
    )
    {
        _Game_Resource_CostCris(pgame,iteam,GAME_CRISCOST_VCS);
        _Game_CreateEntity(pgame,px,py,TAG_VCS);
    }
}
void Game_BarCreateMarine(Game* pgame,int px,int py)
{
    TeamId iteam = Map_GetTeam(pgame->map,px,py);
    TagMap tm = Map_Get(pgame->map,px,py);
    if( tm==TAG_BAR &&
        _Game_GameCursor_IfUnSelect() &&
        _Game_Resource_IfCostCris(pgame,iteam,50)
    )
    {
        _Game_Resource_CostCris(pgame,iteam,50);
        _Game_CreateEntity(pgame,px,py,TAG_MARINE);
    }
}
void Game_VCSBuildBase(Game* pgame,int vcs_x,int vcs_y,int base_x,int base_y)
{
    TeamId iteam = Map_GetTeam(pgame->map,vcs_x,vcs_y);
    if(_Game_Turn_IfCost(pgame,vcs_x,vcs_y,GAME_PACOST_BASE) &&
        _Game_Resource_IfCostCris(pgame,iteam,GAME_CRISCOST_BASE)
    )
    {
        _Game_Turn_Cost(pgame,_Game_GameCursor.lastx,_Game_GameCursor.lasty,GAME_PACOST_BASE);
        _Game_Resource_CostCris(pgame,iteam,GAME_CRISCOST_BASE);
        Map_Set(&pgame->map,base_x,base_y,TAG_BASE,iteam);
    }

}
void Game_VCSBuildBar(Game* pgame,int vcs_x,int vcs_y,int bar_x,int bar_y)
{
    TeamId iteam = Map_GetTeam(pgame->map,vcs_x,vcs_y);
    if(_Game_Turn_IfCost(pgame,vcs_x,vcs_y,GAME_PACOST_BAR) &&
        _Game_Resource_IfCostCris(pgame,iteam,GAME_CRISCOST_BAR))
    {
        _Game_Turn_Cost(pgame,vcs_x,vcs_y,GAME_PACOST_BAR);
        _Game_Resource_CostCris(pgame,iteam,GAME_CRISCOST_BAR);
        Map_Set(&pgame->map,bar_x,bar_y,TAG_BAR,iteam);
    }
}
void Game_VCSBuildRaf(Game* pgame,int vcs_x,int vcs_y,int raff_x,int raff_y)
{
    TeamId iteam = Map_GetTeam(pgame->map,vcs_x,vcs_y);
    if( _Game_Turn_IfCost(pgame,vcs_x,vcs_y,GAME_PACOST_RAF) &&
        _Game_Resource_IfCostCris(pgame,iteam,GAME_CRISCOST_RAF))
    {
        _Game_Turn_Cost(pgame,vcs_x,vcs_y,GAME_PACOST_RAF);
        _Game_Resource_CostCris(pgame,iteam,GAME_CRISCOST_RAF);
        Map_Set(&pgame->map,raff_x,raff_y,TAG_RAF1,iteam);
    }
}
void Game_VCSCollectCris(Game* pgame,int vcs_x,int vcs_y,int cris_x,int cris_y)
{
    if(_Game_Turn_IfCost(pgame,vcs_x,vcs_y,1))
    {
        _Game_Turn_Cost(pgame,vcs_x,vcs_y,1);
        _Game_Resource_MapCollectCris(pgame,vcs_x,vcs_y,cris_x,cris_y);
    }
}
void Game_VCSCollectGas(Game* pgame,int vcs_x,int vcs_y,int gas_x,int gas_y)
{
    if(_Game_Turn_IfCost(pgame,vcs_x,vcs_y,1))
    {
        _Game_Turn_Cost(pgame,vcs_x,vcs_y,1);
        _Game_Resource_MapCollectGas(pgame,vcs_x,vcs_y,gas_x,gas_y);
    }

}
void Game_Draw(Game* pgame,SpriteSheet psprc)
{
    _Game_GameCursor_Update(pgame,psprc);

    Map_Draw(&pgame->map,_Game_GameCursor.offx,_Game_GameCursor.offy,psprc);
    if(_Game_GameCursor_IsInGame(pgame))
    {
        if(IsMouseButtonPressed(0))
        {
            if( Tag_IsEntity(_Game_GameCursor.map) &&
                _Game_GameCursor_IfUnSelect())
            {
                _Game_GameCursor_Select();
            }
        }
        _Game_UI_Cursor(psprc);
        _Game_UI_MenuVCS(pgame,psprc);
        _Game_UI_MenuBase(pgame,psprc);
        _Game_UI_MenuBar(pgame,psprc);
    }
    if( IsMouseButtonPressed(1))
    {
        _Game_GameCursor_UnSelect();
    }
    _Game_UI_ButtonTurn(pgame,400,100);
    _Game_UI_Select(psprc);
    _Game_UI_Resource(*pgame,400,30,TEAM1);
    _Game_UI_Turn(pgame,400,70);
    _Game_UI_PA(pgame,psprc);

}

void Game_Free()
{
    Map_FreeMapTeamTexture();
}

#endif

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
	// float fraq = GetMonitorWidth(0)/GetMonitorHeight(0);
    const int screenWidth = 800; //GetMonitorWidth(0);
    const int screenHeight = 560;//GetMonitorHeight(0);
    InitWindow(screenWidth, screenHeight, "AdvanceStar");
    
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
#if defined(CTYPE_GAME)
    Icons_Init();
#endif

    SpriteSheet ssprc = SpriteSheet_Init("asset/titlesheet.png",16,4);
    SpriteSheet_SetTag(&ssprc,0,TAG_SAND0);
	SpriteSheet_SetTag(&ssprc,1,TAG_SAND1);
	
	SpriteSheet_SetTag(&ssprc,16,TAG_CRIS3);
	SpriteSheet_SetTag(&ssprc,17,TAG_CRIS2);
	SpriteSheet_SetTag(&ssprc,18,TAG_CRIS1);
	SpriteSheet_SetTag(&ssprc,19,TAG_CRIS0);
	
	SpriteSheet_SetTag(&ssprc,20,TAG_GAS3);
	SpriteSheet_SetTag(&ssprc,21,TAG_GAS2);
	SpriteSheet_SetTag(&ssprc,22,TAG_GAS1);
	SpriteSheet_SetTag(&ssprc,23,TAG_GAS0);
	
	SpriteSheet_SetTag(&ssprc,32,TAG_BASE);
	SpriteSheet_SetTag(&ssprc,33,TAG_RAF1);
	SpriteSheet_SetTag(&ssprc,34,TAG_RAF0);
	SpriteSheet_SetTag(&ssprc,35,TAG_BAR);
	
	SpriteSheet_SetTag(&ssprc,48,TAG_VCS);
	SpriteSheet_SetTag(&ssprc,49,TAG_MARINE);


    #ifdef CTYPE_EDIT0
        Map map0 = Map_Init(3,3);
        Map_SetFloor(&map0,0,0,TAG_SAND0);
        Map_SetFloor(&map0,0,1,TAG_SAND1);
        Map_Set(&map0,0,0,TAG_BASE,1);
        Map_Set(&map0,0,1,TAG_BAR,0);

        MapEditor medit = MapEditor_Load(map0,ssprc);
    #elif defined CTYPE_EDIT1
        MapEditor medit = MapEditor_Init(ssprc);
        MapEditor_LoadSave(&medit,"map.dat");
    #elif defined CTYPE_GAME
        Game game = Game_Load("asset/map.dat",ssprc);
    #endif

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        #if defined(CTYPE_EDIT0) || defined(CTYPE_EDIT1)
            MapEditor_Draw(&medit);
        #elif defined CTYPE_GAME
            Game_Draw(&game,ssprc);
        #endif

        EndDrawing();
    }

    #if defined(CTYPE_EDIT0) || defined(CTYPE_EDIT1)
        MapEditor_Free(medit);
    #elif defined CTYPE_GAME
        Game_Free();
    #endif

    SpriteSheet_Free(&ssprc);
    #if defined(CTYPE_GAME)
        Icons_Free();
    #endif
	CloseWindow();        // Close window and OpenGL
	
    return 0;
}

