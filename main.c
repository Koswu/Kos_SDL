/*头文件声明*/
#include "common.h"
#include "error.h"

/*全局变量*/
static bool IS_INIT_FONT=false;//字体加载状态
SDL_Surface* Kos_SDL_Screen=NULL;//屏幕表面
SDL_Event Kos_SDL_NowEvent;//事件类型
int Kos_SCREEN_WIDTH=0, Kos_SCREEN_WIDTH=0;
/*报错函数*/
void Error (int errorcode)
{
	if (IS_INIT_FONT)
	{
// do Foo
	}
	Clean_Up();
	exit (errorcode);
}
/*初始化*/
void Kos_SDL_Init (int Width,int Height)
{
	/*初始化SDL所有子系统*/
	if (SDL_Init(SDL_INIT_EVERYTHING)<0)
	{
		Error (ERROR_INIT_SDL);
	}
	/*初始化字体系统*/
	if( TTF_Init() <0)
    {
    	Error (ERROR_INIT_FONTLIB);
    }
    /*初始化声音系统*/
    if (Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024)<0)
    {
    	Error (ERROR_INIT_MIXLIB);
    }
    if (Mix_Init(MIX_INIT_MP3)<0)
    {
    	Error (ERROR_INIT_MIXLIB);
    }
	/*初始化屏幕表面*/
	Kos_SDL_Screen=SDL_SetVideoMode(Width,Height,SDL_ANYFORMAT,SDL_HWSURFACE|SDL_DOUBLEBUF);
	if (Kos_SDL_Screen==NULL)
	{
		exit (ERROR_INIT_SDL);
	}
	Kos_SCREEN_WIDTH=Width;
	Kos_SCREEN_WIDTH=Height;
}
/*清理函数*/
void Clean_UP ()
{
    Mix_CloseAudio();
	Mix_Quit();
	SDL_Quit();
	TTF_Quit();
}
