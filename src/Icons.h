#pragma once
#include "SpriteSheet.h"

enum eidicons
{
    ICON_CRIS,
    ICON_GAS
};
typedef enum eidicons IdIcons;

void Icons_Init();
void Icons_Draw(IdIcons id,int x,int y);
void Icons_Free();
