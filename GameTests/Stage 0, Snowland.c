#include "..\Suprannua\Definitions.h" //All the enums, structs and variables the framework and script needs to know.
#include "..\Suprannua\GameScript.h" //Script and asset functions.
#include "..\Suprannua\2DCamera.h" //Camera functions.
#include "..\Suprannua\AI.h" //Artificial Intelligence of agents.
#include "..\Suprannua\Input.h"
#include "..\Suprannua\Compute.h" //All algorithms and physics calculations.
#include "..\Suprannua\Editor.h" //Functions used for data manipulation in game script.

///////////////////////////////////
//Custom code for Game Data, Logic, AI, Inputs
///////////////////////////////////

//Global variables
char gameTitle[64]          = SOFTWARE VERSION "[Stage 0, Snowland]";
double dpadSensitivity      = 30;
double cameraScrollSpeed    = 0.5;

Rect worldMap               = {200,60};

double friction             = 0.4;
double platformGravity      = 50.0;

bool isGamePaused           = false;


void initGameData()
{
        camera_resolution(100);
        camera_target(camera2D.viewport.width/2, camera2D.viewport.height/2);

        edit_create(BOX, BACKGROUND, 0, 0, worldMap.width - 0.01, worldMap.height - 0.01, worldMap.width/2,
                    worldMap.height/2, 135, 206, 250);
        edit_create(BOX, PLATFORM, 0, 0, worldMap.width - 0.01, 3.0, worldMap.width/2, 1.6, 83, 21, 21);
        edit_create(BOX, PLATFORM, 0, 0, worldMap.width - 0.01, 3.0, worldMap.width/2, 3, 255, 255, 255);
        edit_create(POLYGON, ENTITY, 6, 3.0, 0, 0, 5, 30, 255, 0, 0);
        for(i = 1; i < 20; i++)
        {
            edit_create(POLYGON, ENTITY, 8, 0.5, 0, 0, 0, 0, 255, 255, 255);
            edit_change(POLYGON, i, YVELOCITY, -5.0);
        }
}

void runGameScript()
{
    compute_translate();
    compute_rotate();
    compute_limitBoundary();
    compute_detectPlatformCollision();

    compute_gravitate(POLYGON, 0, DOWN);
    compute_roll(POLYGON, 0);
    camera_follow(POLYGON, 0, true, false);
    camera_limit(0, worldMap.width, 0, worldMap.height);

    for(i = 1; i < 20; i++)
        if(polygon[i].centre.yPosition < 6)
            edit_move(POLYGON, i, polygon[i].centre.xPosition, worldMap.height - 1);
}

//Controller
void readInput()
{
    if(!isGamePaused)
    {
        if(input_isPressed('w'))
        {
            for(i = 0; i < MAX_BOXES; i++)
            {
                if(compute_isOnPlatform(POLYGON, 0, i))
                    edit_change(POLYGON, 0, YVELOCITY, 40 + box[i].properties.yVelocity); //Jumping
            }
        }

        if(input_isPressed('a'))
            edit_change(POLYGON, 0, XVELOCITY, -1 * dpadSensitivity);

        if(input_isPressed('s'))
        {
            for(i = 0; i < MAX_BOXES; i++)
            {
                if(compute_isTouchingUnderPlatform(POLYGON, 0, i))
                    edit_change(POLYGON, 0, YVELOCITY, -40 + box[i].properties.yVelocity);
            }
        }

        if(input_isPressed('d'))
            edit_change(POLYGON, 0, XVELOCITY, dpadSensitivity);

        ////////////////
        //Camera
        ////////////////
        if(input_isPressed('i'))
            camera_scroll(0.0, cameraScrollSpeed);

        if(input_isPressed('j'))
            camera_scroll(-1 * cameraScrollSpeed, 0.0);

        if(input_isPressed('k'))
            camera_scroll(0.0, - 1 * cameraScrollSpeed);

        if(input_isPressed('l'))
            camera_scroll(cameraScrollSpeed, 0.0);
    }
}

