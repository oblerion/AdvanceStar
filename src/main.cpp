#include "raylib.h"
#include "Map.hpp"
#include "SpriteSheet.hpp"

int main(void)
{

    // Initialization
    //--------------------------------------------------------------------------------------
   // float fraq = GetMonitorWidth(0)/GetMonitorHeight(0);
    const int screenWidth = 800; //GetMonitorWidth(0);
    const int screenHeight = 560;//GetMonitorHeight(0);
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    
    SpriteSheet ssprc = SpriteSheet_Init("asset/32bitjam.png",16,4);
    SpriteSheet_SetTag(&ssprc,0,"ship");
	SpriteSheet_SetTag(&ssprc,1,"ship2");

    Map tmap(5,5,ssprc);
    tmap.SetFloor(0,0,"ship");
	tmap.SetFloor(1,0,"ship2");

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //if(IsKeyDown(KEY_S))
       
        BeginDrawing();
        ClearBackground(BLUE);
        tmap.Draw(0,0);
        EndDrawing();
    }
    
    SpriteSheet_Free(&ssprc);
	CloseWindow();        // Close window and OpenGL
	
    return 0;
}

