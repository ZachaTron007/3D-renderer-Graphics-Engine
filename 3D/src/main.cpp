//libraries
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <ctime>

//header files
#include "global.hpp"
#include "Rendering/rendering.hpp"
#include "Shapes/shapes.hpp"
#include "GameLogic/objects.hpp"
#include "Input/input.hpp"

//make run
double G_RadianToAngle(double rad){ return rad * (180/M_PI); }
bool running = true;
void G_QuitGame(){ running = false; }

double deltaTime;
int fps;
double G_GetDeltaTime(){ return deltaTime; }

int main(){
    SDL_Init(SDL_INIT_EVERYTHING);
    R_StartDisplay();
    O_GenerateObjects();

    while(running){
        clock_t time = clock();   
        R_RunDisplay();
        I_CheckEventStatus();
        //running = false;


        time = clock() - time;
        deltaTime = double(time)/CLOCKS_PER_SEC;
        fps = 1/deltaTime;
        //std::cout<<fps<<std::endl;
    }



}