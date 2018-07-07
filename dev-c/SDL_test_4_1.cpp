#include <SDL.h>        
#include <SDL_image.h>
#include <stdio.h>

int main(int argc, char ** argv)
{
	bool quit = false;
	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window * window = SDL_CreateWindow("SDL2 Displaying Image",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
		
	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
	
	#if 1
	SDL_Surface * image = SDL_LoadBMP("IMG_1246.jpg");
	#else
	SDL_Surface * image = IMG_Load("image.png");
	if(NULL == image)
	{
			printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	#endif
	
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);

	while (!quit)
	{
		SDL_WaitEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}
		
		#if 0
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		
		#else
		SDL_Rect dstrect = { 5, 5, 320, 240 };
		SDL_RenderCopy(renderer, texture, NULL, &dstrect);
		#endif
		
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(image);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}
