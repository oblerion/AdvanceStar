#pragma once

#include <stdio.h>
#include "Map.h"
#include "SpriteSheet.h"

struct smapeditor
{
    Map map;
    SpriteSheet sprc;
    int* tags;
    int curant_tag;
    int offx;
    int offy;
};
typedef struct smapeditor MapEditor;

MapEditor MapEditor_Init(SpriteSheet psprc);
MapEditor MapEditor_Load(Map pmap,SpriteSheet psprc);
void MapEditor_Draw(MapEditor* pmedit);
void MapEditor_LoadSave(MapEditor* pmedit,const char* sfile);
void MapEditor_Save(MapEditor pmedit,const char* sfile);
void MapEditor_Free(MapEditor pmedit);

