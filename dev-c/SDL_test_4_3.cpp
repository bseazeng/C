#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>//引用SDL库
#include <SDL_image.h>//引用SDL_image库

int main(int argc,char* argv[])//完成的mian函数定义
{
	SDL_Event event;
	
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow(
                                          "SDL Tutorial1",//窗口标题
         SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,//窗口位置
                                          1240,1240,//窗口大小
                                    SDL_WINDOW_RESIZABLE//以窗口模式显示
                                          );
    SDL_Rect rect;
    rect.x = 100;
    rect.y = 100;

    SDL_Surface* surface = SDL_GetWindowSurface(window);//获得画布
    SDL_Surface* image = IMG_Load("image.png");//采用image加载png格式图片
    

	while (1)
	{
		SDL_WaitEvent(&event);

		if (SDL_QUIT == event.type)
		{
			break;
		}
		
		SDL_BlitSurface(image,NULL,surface,&rect);//实现将贴图贴至画布上
		SDL_UpdateWindowSurface(window);//更新画布
		SDL_Delay(1000);
	}
    

    SDL_FreeSurface(image);//释放贴图
    SDL_FreeSurface(surface);//释放画布
    SDL_Delay(3000);//延迟3秒
    SDL_DestroyWindow(window);//销毁画布对象
    SDL_Quit();//退出SDL

    return 0;
}
