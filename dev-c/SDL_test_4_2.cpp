#include <SDL.h>        
#include <SDL_image.h>
#include <stdio.h>

int main(int argc, char ** argv)
{
	bool quit = false;
	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);


	SDL_Window * window = SDL_CreateWindow("SDL2 Displaying Image",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600,800, SDL_WINDOW_RESIZABLE);
		
	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderClear(renderer);
	

	#if 1
	SDL_Surface * image = IMG_Load("IMG_1246.jpg");
	#else
	SDL_Surface * image = IMG_Load("image.png");
	#endif
	if(NULL == image)
	{
			printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			return 1;
	}
	
	//SDL_Rect src_box={0,0,0,0};
	SDL_Rect box={0,0,100,120};
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
		SDL_RenderCopy(renderer, texture, NULL, &box);
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
