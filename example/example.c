#include <SDL/SDL.h>
#include <Kos_SDL.h>
int main (int argc,char *argv[])
{
    /*初始化并载入文件*/
    Kos_SDL_Init(640,480,"Kos_SDL example");
    SDL_Surface * warning=IMG_Load("./warning.png");//警告
    SDL_Surface * image =Kos_Load_Image("./test_1.jpg");//背景
    SDL_Surface * person=IMG_Load("./person.png");//人物
    SDL_Surface * box=IMG_Load("./box.png");//对话框
    SDL_Surface * loadbutton=IMG_Load("load.png");//加载按钮
    SDL_Surface * savebutton=IMG_Load("save.png");//保存按钮
    SDL_Surface * skipbutton=IMG_Load("skip.png");//跳过按钮
    SDL_Surface * systembutton=IMG_Load("system.png");//系统按钮
    Kos_Set_DefaultFont("./DroidSans.ttf");//默认字体
    TTF_Font * heiti=Kos_Load_Font("./heiti.ttf",20);//中文字体
    /*渲染文字*/
    SDL_Color textcolor={255,255,255};
    SDL_Surface * text=Kos_Render_UTF8Text(heiti,"我能吞下玻璃而不伤身体",textcolor);
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
            /*Blit到屏幕表面*/
            Kos_Set_ScreenColor(0xFF,0xFF,0xFF);
            Kos_BlitToScreen(0,0,image,NULL);
            Kos_BlitToScreen(0,0,person,NULL);
            Kos_BlitToScreen(0,Kos_SCREEN_HEIGHT-box->h,box,NULL);
            Kos_BlitToScreen((Kos_SCREEN_WIDTH-warning->w)/2,0,warning,NULL);
            Kos_BlitToScreen(Kos_SCREEN_WIDTH-systembutton->w-10,Kos_SCREEN_HEIGHT-systembutton->h-10,systembutton,NULL);
            Kos_BlitToScreen(Kos_SCREEN_WIDTH-skipbutton->w-10,Kos_SCREEN_HEIGHT-skipbutton->h*2-20,skipbutton,NULL);
            Kos_BlitToScreen(Kos_SCREEN_WIDTH-loadbutton->w-10,Kos_SCREEN_HEIGHT-loadbutton->h*3-30,loadbutton,NULL);
            Kos_BlitToScreen(Kos_SCREEN_WIDTH-savebutton->w-10,Kos_SCREEN_HEIGHT-savebutton->h*4-40,savebutton,NULL);
            Kos_BlitToScreen(20,Kos_SCREEN_HEIGHT-box->h+20,text,NULL);
            Kos_BlitFPS(10,textcolor);
            Kos_TimeFlipScreen(10);
    }
    /*清理工作*/
    TTF_CloseFont(heiti);
    SDL_FreeSurface(image);
    SDL_FreeSurface(warning);
    SDL_FreeSurface(person);
    SDL_FreeSurface(box);
    SDL_FreeSurface(loadbutton);
    SDL_FreeSurface(savebutton);
    SDL_FreeSurface(systembutton);
    SDL_FreeSurface(skipbutton);
    Kos_Clean_Up();
    return 0;
}
