#include "MapEditor.h"

MapEditor MapEditor_Init(SpriteSheet psprc)
{
    MapEditor medit = {
        Map_Init(64,64),
        psprc,
        SpriteSheet_GetTags(psprc),
        0,0,0
    };
    return medit;
}

MapEditor MapEditor_Load(Map pmap,SpriteSheet psprc)
{
    MapEditor medit = {
        pmap,
        psprc,
        SpriteSheet_GetTags(psprc),
        0,0,0
    };
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
        (Tag_IsFloor(Map_Get(pmedit->map,imousex,imousey,0)) && Tag_IsFloor(ptag)) ||
        (Tag_IsBuild(Map_Get(pmedit->map,imousex,imousey,1)) && Tag_IsBuild(ptag)) ||
        (Tag_IsEntity(Map_Get(pmedit->map,imousex,imousey,2)) && Tag_IsEntity(ptag))
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
                Map_Set(&pmedit->map,imousex,imousey,ptag,0);
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            for(int i=2;i>-1;i--)
            if(Map_Get(pmedit->map, imousex,imousey,i)!=TAG_NULL)
            {
                    Map_Del(&pmedit->map,imousex,imousey,i);
                break;
            }
        }
    }
    else CanBePlace = false;
    // change tag
    if(GetMouseWheelMove()<0)
    {
        if(pmedit->curant_tag>0)
            pmedit->curant_tag--;
        else
            pmedit->curant_tag=nbtag-1;
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
    Map_Draw(&pmedit->map,pmedit->offx,pmedit->offy,pmedit->sprc);
    SpriteSheet_DrawT(pmedit->sprc,ptag,pmedit->offx+(imousex*iscale*istile),pmedit->offy+(imousey*iscale*istile),0);
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
    //const int nbtag = SpriteSheet_GetNbTags(pmedit.sprc);
    // for(int i=0;i<nbtag;i++)
    // {
    //     MemFree(pmedit.tags[i]);
    //     pmedit.tags[i]=NULL;
    // }
    MemFree(pmedit.tags);
    pmedit.tags=NULL;
}
