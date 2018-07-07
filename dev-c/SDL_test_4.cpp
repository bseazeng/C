#include <stdio.h>
//引入SDL头文件
#include <SDL.h>        
//显式bmp之外的图片需要用到sdl_image库，需要单独引入头文件
#include <SDL_image.h>

#define bool int
#define false 0
#define true (!false)

int main(int argc, char ** argv)
{
    bool quit = false;
    SDL_Event event;

     //SDL初始化，这里只显示图片，所以只初始化VIDEO系统，更多的支持查看官方文档
    SDL_Init(SDL_INIT_VIDEO);
    //为了显示png图片，额外使用了图片库，所以要单独初始化
    IMG_Init(IMG_INIT_JPG); 

    //建立SDL窗口
    SDL_Window * window = SDL_CreateWindow("Marriage Image",
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    //渲染层
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    //如果只是显示一张bmp图片，使用sdl内置的功能即可
    //SDL_Surface * image = SDL_LoadBMP("only_support_BMP.bmp");
    //因为要显示png图片，所以使用了外部库，sdl_image库当前支持jpg/png/webp/tiff图片格式
    SDL_Surface * image = IMG_Load("IMG_1246.jpg");
    //载入的图片生成SDL贴图材质
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
 
    while (!quit)
    {//主消息循环
        SDL_WaitEvent(&event);
 
        switch (event.type)
        {   //用户从菜单要求退出程序
            case SDL_QUIT:
                quit = true;
                break;
        }
 
       //如果指定显示位置使用下面注释起来的两句
        SDL_Rect dstrect = { 5, 5, 320, 240 };
        SDL_RenderCopy(renderer, texture, NULL, &dstrect);
        //把贴图材质复制到渲染器
        //SDL_RenderCopy(renderer, texture, NULL, NULL);
        //显示出来
        SDL_RenderPresent(renderer);
    }
     //典型的三明治结构，清理各项资源
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    //退出image库
    IMG_Quit();
    //退出SDL
    SDL_Quit();
 
    return 0;
}
