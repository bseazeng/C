#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>//����SDL��
#include <SDL_image.h>//����SDL_image��

int main(int argc,char* argv[])//��ɵ�mian��������
{
	SDL_Event event;
	
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow(
                                          "SDL Tutorial1",//���ڱ���
         SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,//����λ��
                                          1240,1240,//���ڴ�С
                                    SDL_WINDOW_RESIZABLE//�Դ���ģʽ��ʾ
                                          );
    SDL_Rect rect;
    rect.x = 100;
    rect.y = 100;

    SDL_Surface* surface = SDL_GetWindowSurface(window);//��û���
    SDL_Surface* image = IMG_Load("image.png");//����image����png��ʽͼƬ
    

	while (1)
	{
		SDL_WaitEvent(&event);

		if (SDL_QUIT == event.type)
		{
			break;
		}
		
		SDL_BlitSurface(image,NULL,surface,&rect);//ʵ�ֽ���ͼ����������
		SDL_UpdateWindowSurface(window);//���»���
		SDL_Delay(1000);
	}
    

    SDL_FreeSurface(image);//�ͷ���ͼ
    SDL_FreeSurface(surface);//�ͷŻ���
    SDL_Delay(3000);//�ӳ�3��
    SDL_DestroyWindow(window);//���ٻ�������
    SDL_Quit();//�˳�SDL

    return 0;
}
