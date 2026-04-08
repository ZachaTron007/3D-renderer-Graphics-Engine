//libraries
#include <SDL2/SDL.h>
#include <iostream>

//header files
#include "../GameLogic/objects.hpp"
#include "../global.hpp"
#include "input.hpp"


SDL_Event event;

const int quitGame = SDL_SCANCODE_Q;

const int forward = SDL_SCANCODE_W;
const int backward = SDL_SCANCODE_S;
const int right = SDL_SCANCODE_D;
const int left = SDL_SCANCODE_A;
const int up = SDL_SCANCODE_SPACE;
const int down = SDL_SCANCODE_TAB;

const int lookLeft = SDL_SCANCODE_LEFT;
const int lookRight = SDL_SCANCODE_RIGHT;
const int lookUp = SDL_SCANCODE_UP;
const int lookDown = SDL_SCANCODE_DOWN;
const int lookZ = SDL_SCANCODE_COMMA;
const int lookZe = SDL_SCANCODE_PERIOD;
const Uint8* keystates = SDL_GetKeyboardState(NULL);

void I_CheckEventStatus(){
    
    //Switch checking what event happende
    while(SDL_PollEvent(&event) != 0){
    }
    
    if(keystates[quitGame]) G_QuitGame();
    
    if(keystates[forward])  O_MoveForward(1);
    if(keystates[backward]) O_MoveForward(-1);
    if(keystates[right])    O_MoveSideways(1);
    if(keystates[left])     O_MoveSideways(-1);
    if(keystates[up])       O_MoveUp(-1);
    if(keystates[down])     O_MoveUp(1);

    if(keystates[lookLeft])  O_MoveYAngle(1);
    if(keystates[lookRight]) O_MoveYAngle(-1);
    if(keystates[lookUp])    O_MoveXAngle(1);
    if(keystates[lookDown]) O_MoveXAngle(-1);
    if(keystates[lookZ])    O_MoveZAngle(1);
    if(keystates[lookZe]) O_MoveZAngle(-1);
}