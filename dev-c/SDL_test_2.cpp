//ʹ�� SDL �� ��׼ IO
#include <SDL.h>
#include <stdio.h>

//������Ļ�ߴ糣��
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main_2( int argc, char* args[] )
{
    //��Ҫ��Ⱦ�Ĵ���
    SDL_Window* window = NULL;

    //���ں��е�surface
    SDL_Surface* screenSurface = NULL;

    //��ʼ��SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        //���� window
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
               else
        {
            //��ȡ window surface
            screenSurface = SDL_GetWindowSurface( window );

            //�ð�ɫ���surface
            SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );

            //����surface
            SDL_UpdateWindowSurface( window );

            //�ӳ�����
            SDL_Delay( 2000 );
        }
    }
    //���� window
    SDL_DestroyWindow( window );

    //�˳� SDL subsystems
    SDL_Quit();

    return 0;
}
