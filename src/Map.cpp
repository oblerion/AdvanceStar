#include "Map.hpp"



Map::Map(const int pw, const int ph, SpriteSheet psprc)
{
	lspr = psprc;
	w = pw;
	h = ph;
	for(int i=0;i<ph;i++)
	for(int j=0;j<pw;j++)
	{
		for(int l=0;l<3;l++)
			lmap[i*w+j][l] = "";
	}
}
Map::Map(DataMap psmap,SpriteSheet psprc)
{
	Map(psmap.w,psmap.h,psprc);
	for(int i=0;i<psmap.h;i++)
	for(int j=0;j<psmap.w;j++)
	{
		for(int l=0;l<3;l++)
			lmap[i*psmap.w+j][l]=psmap.smap[i*psmap.w+j][l];
	}
}
Map::~Map()
{
	for(int i=0;i<h;i++)
	for(int j=0;j<w;j++)
	{
		for(int l=0;l<3;l++) lmap[i*w+j][l].clear();
	}
}
int Map::GetW()
{
	return w;
}
int Map::GetH()
{
	return h;
}
std::string Map::Get(int x,int y,int z)
{
	return lmap[y*w+x][z];
}
void Map::SetFloor(int x,int y,std::string pstag)
{
	lmap[y*w+x][0] = pstag;
}

void Map::SetBuidy(int x,int y,std::string pstag)
{
	lmap[y*w+x][1] = pstag;
}

void Map::SetEntity(int x,int y,std::string pstag)
{
	lmap[y*w+x][2] = pstag;
}

void Map::Draw(int px,int py)
{
	int stile = lspr.stile;
	int scale = lspr.scale;
	for(int i=0;i<h;i++)
	for(int j=0;j<w;j++)
	{
		for(int l=0;l<3;l++)
		if(lmap[i*w+j][l]!="")
		{
			SpriteSheet_DrawT(
				lspr,
				lmap[i*w+j][l].c_str(),
				px+j*stile*scale,
				py+i*stile*scale,
				0
			);
		}
	}
}
DataMap Map::Save()
{
	DataMap datamap={w,h};
	for(int i=0;i<datamap.h;i++)
	for(int j=0;j<datamap.w;j++)
	{
		for(int l=0;l<3;l++)
			TextCopy(
				datamap.smap[i*datamap.w+j][l],
				lmap[i*datamap.w+j][l].c_str()
			);
	}
	return datamap;
}
