#include <SDL/SDL.h>
#include <Kos_SDL.h>
int main (int argc,char *argv[])
{
    /*初始化并载入文件*/
    Kos_SDL_Init(640,480,"Kos_SDL example");
    SDL_Surface * image =Kos_Load_Image("./test_1.jpg");
    SDL_Surface * person=IMG_Load("./person.png");
    /*Blit到屏幕表面*/
    Kos_BlitToScreen(0,0,image,NULL);
    Kos_BlitToScreen(0,0,person,NULL);
    Kos_FlipScreen();
    /*关闭前保持画面存在*/
    bool isexit=false;
    while (isexit==false)
    {
        while (SDL_PollEvent(&Kos_SDL_NowEvent))
        {
            if (Kos_SDL_NowEvent.type==SDL_QUIT)
            {
                isexit=true;
            }
        }
    }
    /*清理工作*/
    SDL_FreeSurface(image);
    Kos_Clean_Up();
    return 0;
}
