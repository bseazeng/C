#include <stdio.h>
//����SDLͷ�ļ�
#include <SDL.h>        
//��ʽbmp֮���ͼƬ��Ҫ�õ�sdl_image�⣬��Ҫ��������ͷ�ļ�
#include <SDL_image.h>

#define bool int
#define false 0
#define true (!false)

int main(int argc, char ** argv)
{
    bool quit = false;
    SDL_Event event;

     //SDL��ʼ��������ֻ��ʾͼƬ������ֻ��ʼ��VIDEOϵͳ�������֧�ֲ鿴�ٷ��ĵ�
    SDL_Init(SDL_INIT_VIDEO);
    //Ϊ����ʾpngͼƬ������ʹ����ͼƬ�⣬����Ҫ������ʼ��
    IMG_Init(IMG_INIT_JPG); 

    //����SDL����
    SDL_Window * window = SDL_CreateWindow("Marriage Image",
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    //��Ⱦ��
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    //���ֻ����ʾһ��bmpͼƬ��ʹ��sdl���õĹ��ܼ���
    //SDL_Surface * image = SDL_LoadBMP("only_support_BMP.bmp");
    //��ΪҪ��ʾpngͼƬ������ʹ�����ⲿ�⣬sdl_image�⵱ǰ֧��jpg/png/webp/tiffͼƬ��ʽ
    SDL_Surface * image = IMG_Load("IMG_1246.jpg");
    //�����ͼƬ����SDL��ͼ����
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
 
    while (!quit)
    {//����Ϣѭ��
        SDL_WaitEvent(&event);
 
        switch (event.type)
        {   //�û��Ӳ˵�Ҫ���˳�����
            case SDL_QUIT:
                quit = true;
                break;
        }
 
       //���ָ����ʾλ��ʹ������ע������������
        SDL_Rect dstrect = { 5, 5, 320, 240 };
        SDL_RenderCopy(renderer, texture, NULL, &dstrect);
        //����ͼ���ʸ��Ƶ���Ⱦ��
        //SDL_RenderCopy(renderer, texture, NULL, NULL);
        //��ʾ����
        SDL_RenderPresent(renderer);
    }
     //���͵������νṹ�����������Դ
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    //�˳�image��
    IMG_Quit();
    //�˳�SDL
    SDL_Quit();
 
    return 0;
}
