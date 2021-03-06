/*头文件声明*/
#include "common.h"
#include "error.h"

SDL_Surface* Kos_SDL_Screen=NULL;//屏幕表面
SDL_Event Kos_SDL_NowEvent;//事件类型
int Kos_SCREEN_WIDTH, Kos_SCREEN_HEIGHT;//窗口长宽
TTF_Font * Kos_Default_Font=NULL;//默认字体
const SDL_Color Kos_ErrorColor={0xFF,0,0};//报错时的字体颜色
int Kos_Fliptime,Kos_FPStime;//刷新时间

/*报错函数*/
void Kos_Error (int errorcode)
{
	if (Kos_Default_Font!=NULL&&errorcode>100&&errorcode<200)//处理严重错误，10秒后自动退出
	{
        SDL_Surface * error;
        char errormessage[50]="Error!";
        error=Kos_Render_UTF8Text(Kos_Default_Font,errormessage,Kos_ErrorColor);
        SDL_FillRect(Kos_SDL_Screen,&(Kos_SDL_Screen->clip_rect),SDL_MapRGB(Kos_SDL_Screen->format,0xFF,0xFF,0xFF));
        Kos_BlitToScreen((Kos_SCREEN_WIDTH-error->w)/2,(Kos_SCREEN_HEIGHT-error->h)/2-error->h-20,error,NULL);
        SDL_FreeSurface(error);
        strcpy (errormessage,"The program will exit after 10s");
        error=Kos_Render_UTF8Text(Kos_Default_Font,errormessage,Kos_ErrorColor);
        Kos_BlitToScreen((Kos_SCREEN_WIDTH-error->w)/2,(Kos_SCREEN_HEIGHT-error->h)/2,error,NULL);
        SDL_FreeSurface(error);
        sprintf (errormessage,"Errorcode:%X",errorcode);
        error=Kos_Render_UTF8Text(Kos_Default_Font,errormessage,Kos_ErrorColor);
        Kos_BlitToScreen((Kos_SCREEN_WIDTH-error->w)/2,(Kos_SCREEN_HEIGHT-error->h)/2+error->h+20,error,NULL);
        SDL_FreeSurface(error);
        Kos_FlipScreen();
        SDL_Delay(10000);
	}
	else if (Kos_Default_Font!=NULL&&errorcode>200)//处理一般错误，提示后任意键结束
	{
        SDL_Surface * error;
        bool quit=false;
        char errormessage[50]="Little Error!";
        error=Kos_Render_UTF8Text(Kos_Default_Font,errormessage,Kos_ErrorColor);
        SDL_FillRect(Kos_SDL_Screen,&(Kos_SDL_Screen->clip_rect),SDL_MapRGB(Kos_SDL_Screen->format,0xFF,0xFF,0xFF));
        Kos_BlitToScreen((Kos_SCREEN_WIDTH-error->w)/2,(Kos_SCREEN_HEIGHT-error->h)/2-error->h-20,error,NULL);
        SDL_FreeSurface(error);
        strcpy (errormessage,"Please enter any key or touch screen to continue");
        error=Kos_Render_UTF8Text(Kos_Default_Font,errormessage,Kos_ErrorColor);
        Kos_BlitToScreen((Kos_SCREEN_WIDTH-error->w)/2,(Kos_SCREEN_HEIGHT-error->h)/2,error,NULL);
        SDL_FreeSurface(error);
        sprintf (errormessage,"Errorcode:%X",errorcode);
        error=Kos_Render_UTF8Text(Kos_Default_Font,errormessage,Kos_ErrorColor);
        Kos_BlitToScreen((Kos_SCREEN_WIDTH-error->w)/2,(Kos_SCREEN_HEIGHT-error->h)/2+error->h+20,error,NULL);
        SDL_FreeSurface(error);
        Kos_FlipScreen();
        while (quit==false)
        {
        while (SDL_PollEvent(&Kos_SDL_NowEvent))
            {
	            if (Kos_SDL_NowEvent.type==SDL_KEYDOWN||Kos_SDL_NowEvent.type==SDL_MOUSEBUTTONDOWN)
	            {
	                quit=true;
	            }
	        }
	    }
	    return;
	}
	Kos_Clean_Up();
	exit (errorcode);
}
/*初始化*/
void Kos_SDL_Init (int Width,int Height,char tittle[])
{
	/*初始化SDL所有子系统*/
	if (SDL_Init(SDL_INIT_EVERYTHING)<0)
       {
        Kos_Error (KOS_ERROR_INIT_SDL);
	}
	/*初始化字体系统*/
	if( TTF_Init() <0)
    {
        Kos_Error (KOS_ERROR_INIT_FONTLIB);
    }
    /*初始化声音系统*/
    if (Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024)<0)
    {
        Kos_Error (KOS_ERROR_INIT_MIXLIB);
    }
    if (Mix_Init(MIX_INIT_MP3)<0)
    {
        Kos_Error (KOS_ERROR_INIT_MIXLIB);
    }
	/*初始化屏幕表面*/
    Kos_SDL_Screen=SDL_SetVideoMode(Width,Height,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
	if (Kos_SDL_Screen==NULL)//抛出错误
	{
        Kos_Error (KOS_ERROR_INIT_SDL);
	}
    SDL_WM_SetCaption(tittle,NULL);
    Kos_SCREEN_WIDTH=Width;
    Kos_SCREEN_HEIGHT=Height;
    Kos_FPStime=Kos_Fliptime=SDL_GetTicks();
}

/*清理函数*/
void Kos_Clean_Up (void)
{
    TTF_CloseFont(Kos_Default_Font);
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
    TTF_Quit();
}

/*优化加载图片*/
SDL_Surface * Kos_Load_Image(char path[])
{
    SDL_Surface * oldimage=NULL;
    SDL_Surface * newimage=NULL;
    oldimage=IMG_Load(path);
    if (oldimage==NULL)
    {
        Kos_Error (KOS_ERROR_LOADIMG);
	}
    newimage=SDL_DisplayFormatAlpha(oldimage);
    SDL_FreeSurface(oldimage);
    return newimage;
}

/*拷贝至表面*/
void Kos_BlitToScreen(int x,int y,SDL_Surface * source,SDL_Rect * cli)
{
	SDL_Rect location;
	location.x=x;
	location.y=y;
	SDL_BlitSurface(source,cli,Kos_SDL_Screen,&location);
}

/*加载音乐*/
Mix_Music *Kos_Load_MP3_Music (char * path)
{
	Mix_Music* music=NULL;
	music=Mix_LoadMUS (path);
	if (music==NULL)
	{
		Kos_Error(KOS_ERROR_LOADMUSIC);
	}
	return music;
}

/*加载音效*/
Mix_Chunk * Kos_Load_Chunk (char * path)
{
	Mix_Chunk * chunk=NULL;
	chunk=Mix_LoadWAV (path);
	if (path==NULL)
	{
		Kos_Error (KOS_ERROR_LOADCHUNK);
	}
	return chunk;
}

/*设置默认字体*/
void Kos_Set_DefaultFont(char path[])
{
    Kos_Default_Font=Kos_Load_Font(path,20);
}

/*加载字体*/
TTF_Font * Kos_Load_Font (char path[],int fontsize)
{
    TTF_Font * temp;
    temp=TTF_OpenFont(path,fontsize);
    if (temp==NULL)
    {
        Kos_Error(KOS_ERROR_LOADFONT);
    }
    return temp;
}

/*渲染UTF8文字*/
SDL_Surface * Kos_Render_UTF8Text(TTF_Font * font,char text[],SDL_Color Textcolor)
{
    SDL_Surface * textface;
	textface=TTF_RenderUTF8_Solid(font,text,Textcolor);
	if (textface==NULL)
	{
		Kos_Error (KOS_ERROR_RENDERTEXT);
	}
	return textface;
}

/*渲染ASCII文字*/
SDL_Surface * Kos_Render_ASCIIText(TTF_Font * font,char text[],SDL_Color Textcolor)
{
    SDL_Surface * textface;
	textface=TTF_RenderText_Solid(font,text,Textcolor);
	if (textface==NULL)
	{
		Kos_Error (KOS_ERROR_RENDERTEXT);
	}
	return textface;
}

/*设置背景色*/
void Kos_Set_ScreenColor (unsigned short r,unsigned short g,unsigned short b)
{
	SDL_FillRect(Kos_SDL_Screen,&(Kos_SDL_Screen->clip_rect),SDL_MapRGB(Kos_SDL_Screen->format,r,g,b));
}


/*按指定帧率刷新屏幕*/
void Kos_TimeFlipScreen(int frame_per_second)
{
    if ((SDL_GetTicks()-Kos_Fliptime)<(1000/frame_per_second))
    {
        SDL_Delay (1000/frame_per_second-(SDL_GetTicks()-Kos_Fliptime));
    }
    Kos_Fliptime=SDL_GetTicks();
    if (SDL_Flip(Kos_SDL_Screen)<0)
    {
        Kos_Error(KOS_ERROR_FLIPSCREEN);
    }
}

/*刷新屏幕*/
void Kos_FlipScreen (void)
{
    if (SDL_Flip(Kos_SDL_Screen)<0)
    {
        Kos_Error(KOS_ERROR_FLIPSCREEN);
    }
}

/*打印FPS*/
void Kos_BlitFPS (int FPSsize,SDL_Color FPScolor)
{
    char fpschar[10];
    int nowtime=SDL_GetTicks();
    sprintf (fpschar,"FPS:%.2f",1000.0/(nowtime-Kos_FPStime));
    if (Kos_Default_Font==NULL)
    {
        Kos_Error(KOS_ERROR_PRINTFPS);
    }
    SDL_Surface * fpsface=Kos_Render_ASCIIText (Kos_Default_Font,fpschar,FPScolor);
    Kos_BlitToScreen(Kos_SCREEN_WIDTH-fpsface->w,0,fpsface,NULL);
    Kos_FPStime=nowtime;
}

/*播放音乐*/
void Kos_PlayMusic (Mix_Music* music,int playcount)
{
    if (Mix_PlayMusic(music,playcount)<0)
	{
		Kos_Error(KOS_ERROR_PLAYMUSIC);
	}
}


/*播放音效*/
void Kos_PlayChunk (Mix_Chunk *chunk,int playcount)
{
    if (Mix_PlayChannel(-1,chunk,playcount-1)<0)
    {
        Kos_Error(KOS_ERROR_PLAYCHUNK);
    }
}
