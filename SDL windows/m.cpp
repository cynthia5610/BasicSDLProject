/*
 File: Generic.cpp
 Author: Micah A Church
 Created on October 18, 2017, 2:14am
*/
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


#include <iostream>
#include <cstring>
#include <string>

using namespace std;
/*
Makes a window in SDL2 for every and outputs either a 1 or 0 pertaining to the user either clicking on yes or no
Input: Two strings, one for the title of the window and the other for the message displayed
Output: Boolean value that the person who called the function can use.
*/
bool main(int argc, char* args[]) {

    bool quit = false;
    bool ans;
    int x,y;
        
        SDL_Init(SDL_INIT_EVERYTHING);
        TTF_Init();
        
    SDL_Event event;
    SDL_Window *window;
    window = SDL_CreateWindow(
        "Death", 
        SDL_WINDOWPOS_UNDEFINED, //Starting x coordinate for window
        SDL_WINDOWPOS_UNDEFINED, //Starting y coordinate for window
        640,                     //Width of the window
        480,                     //Height of the window
        0                        //Flags
        );
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0,0,255,255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    TTF_Font * font = TTF_OpenFont("arial.ttf", 50);
    SDL_Color black = {0, 0, 0};
    SDL_Color white = {255,255,255};
    SDL_SetRenderDrawColor(renderer,0,0,0,255);

    SDL_Surface * surface = TTF_RenderText_Solid(font, "Sup", white);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surface);
    
    /*
     Create a text box rectangle for the question
    */
    SDL_Rect Message_rect;
    Message_rect.x = 0;  //controls the rect's x coordinate  
    Message_rect.y = 220;    //controls the rect's y coordinte
    Message_rect.w = 640;  //controls the width of the rect
    Message_rect.h = 50;   //controls the height of the rect
    
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

    surface = TTF_RenderText_Solid(font, "yes", white);
    Message = SDL_CreateTextureFromSurface(renderer, surface);
    /*
    Create a Yes button to return a 1 to the call 
    */
    SDL_Rect Yes_rect; //create a rectangle to hold a message
    Yes_rect.x = 80;  //controls the rect's x coordinate 
    Yes_rect.y = 400;    //controls the rect's y coordinte
    Yes_rect.w = 50;  //controls the width of the rect
    Yes_rect.h = 20;   //controls the height of the rect
    SDL_RenderCopy(renderer, Message, NULL, &Yes_rect);

    
    //SDL_RenderFillRect(renderer, &Yes_rect);

    /*
     Create a no button to return a 0
    */
    SDL_Rect No_rect; //create a rectangle to hold a message
    No_rect.x = 500;  //controls the rect's x coordinate 
    No_rect.y = 400;    //controls the rect's y coordinte
    No_rect.w = 50;  //controls the width of the rect
    No_rect.h = 20;   //controls the height of the rect
    SDL_RenderCopy(renderer, Message, NULL, &No_rect);
    SDL_RenderPresent(renderer);

    while (!quit){
       SDL_WaitEvent(&event);
            SDL_GetMouseState(&x, &y);//set x and y to where the mouses coordinates are
                //SDL_RenderPresent(renderer);

            if (x >= Yes_rect.x && x <= Yes_rect.x + Yes_rect.w && y >= Yes_rect.y && y <= Yes_rect.y + Yes_rect.h)
            /*
            Checks if the pointer is inside the area of the rect, 
            Checks if the mouse's x-coordinate is greater than the origin but less than the origin plus
            width
            */
            {
                //SDL_SetTextureColorMod(Message, 255, 0, 0);//Changes the color if the mouse is over the button 
                //SDL_RenderPresent(renderer);
                if (event.type == SDL_MOUSEBUTTONUP)//on mouse release
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        ans = true;
                        quit = true;
                    }

            }
                        
            else if (x >= No_rect.x && x <= No_rect.x + No_rect.w && y >= No_rect.y && y <= No_rect.y + No_rect.h) 
            /*
            Checks if the pointer is inside the area of the rect, 
            Checks if the mouse's x-coordinate is greater than the origin but less than the origin plus
            width
            */
            {
                //SDL_SetTextureColorMod(Message, 255, 0, 128);//Changes the color if the mouse is over the button
                                
                if (event.type == SDL_MOUSEBUTTONUP)//on mouse release
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        ans = false;
                        quit = true;
                    }

            }
            else if (event.type == SDL_QUIT)
                quit = true;
    }
    SDL_Quit();
    
    return 0;
} 