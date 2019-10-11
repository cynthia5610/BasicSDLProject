/**
* This code is to create a menu
* Name: Cynthia Ha
* Date: January 30, 2018
**/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <cstring>
#include <iostream>
#include <sstream>

//Screen dimension constants
const int SWIDTH = 640;
const int SHEIGHT = 480;

using namespace std;

bool init();
bool loadMedia();
void close();

//SDL_window/surface...
SDL_Window* window = NULL;
Mix_Chunk* sound = NULL;
SDL_Renderer* render = NULL;
SDL_Surface* surface = NULL;
SDL_Texture* texture = NULL;
SDL_Texture* overlap = NULL;

bool init()
{
	bool success = true;

	TTF_Init();
	if( SDL_Init(SDL_INIT_EVERYTHING) < 0 )
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		//Creating Window
		SDL_Window *window = SDL_CreateWindow("Things&Stuff", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SWIDTH, SHEIGHT, 0);
		if (window == NULL) 
		{
        	std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        	success = false;
    	}
    	else
    	{
    		int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) )
            {
                std::cout << "SDL_image Error:" << IMG_GetError() << std::endl;
                success = false;
            }

    		//Creating Renderer
			render = SDL_CreateRenderer(window, -1, 0);
    		if (render == NULL) 
    		{
        		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        		success = false;
    		}

    		if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 0, 2048 ) < 0 )
			{
					std::cout << "SDL_mixer Error:" << Mix_GetError() << std::endl;
					success = false;
			}
    	}
    }
	return success;
}

bool loadMedia()
{
	bool success = true;

    sound = Mix_LoadWAV( "music/high.wav" );
	if( sound == NULL )
	{
		std::cout << "SDL_Mixer Error: " << Mix_GetError() << std::endl;
		success = false;
	}

    return success;
}

void close()
{
   	SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    Mix_FreeChunk( sound );

	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}


int main(int argc, char* args[])
{
	if( !init() )
	{
		std::cout << "Failed to initialize!" << std::endl;
	}
	else
	{
		if( !loadMedia() )
		{
			std::cout << "Failed to load media!" << std::endl;
		}
		else
		{
			bool quit = false;

			SDL_Event e;

			int x = 0;
			int y = 0;

			SDL_SetRenderDrawColor(render, 0,0,255,255);
  		 	SDL_RenderClear(render);
  		 	SDL_RenderPresent(render);

  		 	TTF_Font * font = TTF_OpenFont("arial.ttf", 50);
    		SDL_Color black = {0, 0, 0};
    		SDL_Color white = {255,255,255};
  		 	SDL_SetRenderDrawColor(render,255,255,255,255);


    		surface = TTF_RenderText_Solid(font, "Click!", white);
    		texture = SDL_CreateTextureFromSurface(render, surface);

			SDL_Rect click;
    		click.x = (SWIDTH/4)-40;    
    		click.y = (SHEIGHT/2)+40;    
    		click.w = 80;  
    		click.h = 80;   

    		SDL_RenderDrawRect(render, &click);
    		SDL_RenderCopy(render, texture, NULL, &click);
    		
    		surface = TTF_RenderText_Solid(font, "Click!!", white);
    		texture = SDL_CreateTextureFromSurface(render, surface);

    		SDL_Rect animate;
    		animate.x = (SWIDTH/1.5);    
    		animate.y = (SHEIGHT/2)+40;    
    		animate.w = 80;  
    		animate.h = 80;  

    		SDL_RenderDrawRect(render, &animate);
    		SDL_RenderCopy(render, texture, NULL, &animate);

    		SDL_RenderPresent(render);

			while( !quit )
			{
				while( SDL_PollEvent( &e ) != 0 )
				{
					SDL_GetMouseState(&x, &y);

					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					else if (x >= click.x && x <= click.x + click.w && y >= click.y && y <= click.y + click.h) 
					{

						if (e.type == SDL_MOUSEBUTTONUP)
						{
							if (e.button.button == SDL_BUTTON_LEFT)
							{
								Mix_PlayChannel(-1, sound, 0 );
								SDL_Delay(100);
								close();
								quit = true;
							}	
						}
					}
					else if (x >= animate.x && x <= animate.x + animate.w && y >= animate.y && y <= animate.y + animate.h) 
					{

						if (e.type == SDL_MOUSEBUTTONUP)
						{
							if (e.button.button == SDL_BUTTON_LEFT)
							{
								Mix_PlayChannel(-1, sound, 0 );
							}	
						}
					}
				}
			}
		}
	}
	string stuff = "";
	std::cout << "\nInput the name of the robots file." << std::endl;
	std::cin >> stuff;
	// CALL his code
	std::cout << stuff << std::endl;

	return 0;
}