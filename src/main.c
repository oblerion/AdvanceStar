#include "raylib.h"
#include <stdio.h>
#include "Map.h"
#include "SpriteSheet.h"
#include "MapEditor.h"

int main(void)
{

    // Initialization
    //--------------------------------------------------------------------------------------
	// float fraq = GetMonitorWidth(0)/GetMonitorHeight(0);
    const int screenWidth = 800; //GetMonitorWidth(0);
    const int screenHeight = 560;//GetMonitorHeight(0);
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    
    SpriteSheet ssprc = SpriteSheet_Init("./asset/titlesheet.png",16,4);
    SpriteSheet_SetTag(&ssprc,0,TAG_SAND0);
	SpriteSheet_SetTag(&ssprc,1,TAG_SAND1);
	
	SpriteSheet_SetTag(&ssprc,16,TAG_GRIS3);
	SpriteSheet_SetTag(&ssprc,17,TAG_GRIS2);
	SpriteSheet_SetTag(&ssprc,18,TAG_GRIS1);
	SpriteSheet_SetTag(&ssprc,19,TAG_GRIS0);
	
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
	
    Map map0 = Map_Init(5,5);
    Map_SetFloor(&map0,0,0,TAG_SAND0);
    Map_SetFloor(&map0,0,1,TAG_SAND1);
    Map_Set(&map0,0,0,TAG_BASE,1);
    Map_Set(&map0,0,1,TAG_BAR,0);

    MapEditor medit = MapEditor_Load(map0,ssprc);

   MapEditor_LoadSave(&medit,"map.dat");

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        ClearBackground(BLUE);

        MapEditor_Draw(&medit);
        EndDrawing();
    }
    
    MapEditor_Free(medit);
    SpriteSheet_Free(&ssprc);
    Map_Free(&map0);
	CloseWindow();        // Close window and OpenGL
	
    return 0;
}

