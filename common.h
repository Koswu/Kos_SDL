/*头文件定义*/
#include <stdbool.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

/*全局变量声明*/
extern SDL_Surface* Kos_SDL_Screen;//屏幕表面
extern SDL_Event Kos_SDL_NowEvent;//事件类型
extern int Kos_SCREEN_WIDTH, Kos_SCREEN_HEIGHT;//窗口长宽
extern TTF_Font * Kos_Default_Font=NULL;//默认字体
const SDL_Color Kos_ErrorColor={0xFF,0,0};//报错时的字体颜色
extern int Kos_Fliptime,Kos_FPStime;//刷新时间


/*函数声明*/

/*函数名：Kos_Error
    函数作用：处理遇到的错误，在遇到致命错误时直接退出，遇到严重错误时图形报错后退出，遇到一般错误时图形化报错后任意键继续
    函数参数：int errorcode：错误代码
    函数返回值：无
*/
void Kos_Error (int errorcode);


/*函数名：Kos_SDL_Init
    函数作用：进行SDL的初始化并设置用到的全局变量，如果失败，直接向Kos_Error函数抛出错误
    函数参数：int Width：初始化窗口的宽度，int Height：初始化窗口的高度，char tittle[]：初始化窗口的标题
    函数返回值：无
*/
void Kos_SDL_Init (int Width,int Height,char tittle[]);


/*函数名：Kos_Set_DefaultFont
    函数作用：设置默认的字体全局变量，供图形化报错等功能使用，如果失败，直接向Kos_Error函数抛出错误
    函数参数：char path[]：默认字体路径
    函数返回值：无
*/
void Kos_Set_DefaultFont(char path[]);


/*函数名：Kos_Set_ScreenColor
    函数作用：用指定的颜色将窗口全部覆盖
    函数参数：unsigned short r：指定颜色的红色色值，unsigned short g：指定颜色的绿色色值，unsigned short b：指定颜色的蓝色色值
    函数返回值：无
*/
void Kos_Set_ScreenColor (unsigned short r,unsigned short g,unsigned short b);


/*函数名：Kos_Load_Image
    函数作用：从指定的路径里加载图片文件到一个SDL_Surface变量里，如果失败，直接向Kos_Error函数抛出错误
    函数参数：char path[]：图片文件路径
    函数返回值：一个包含已加载图片的SDL_Surface类型指针
*/
SDL_Surface * Kos_Load_Image(char path[]);


/*函数名：Kos_Load_MP3_Music
    函数作用：从指定的路径里加载MP3音乐文件到一个Mix_Music变量里，如果失败，直接向Kos_Error函数抛出错误
    函数参数：char path[]：音乐文件路径
    函数返回值：一个包含已加载音乐的Mix_Music类型指针
*/
Mix_Music *Kos_Load_MP3_Music (char * path);

/*函数名：Kos_Load_Chunk
    函数作用：从指定的路径里加载WAV音效文件到一个Mix_Chunk变量里，如果失败，直接向Kos_Error函数抛出错误
    函数参数：char path[]：音效文件路径
    函数返回值：一个包含加载音效的Mix_Chunk类型指针
*/
Mix_Chunk * Kos_Load_Chunk (char * path);


/*函数名：Kos_Load_Font
    函数作用：从指定的路径里加载字体文件到一个TTF_Font变量里，如果失败，直接向Kos_Error函数抛出错误
    函数参数：char path[]：字体文件路径，int fontsize：要加载的字体大小
    函数返回值：一个包含加载字体和指定大小的TTF_Font类型指针
*/
TTF_Font * Kos_Load_Font (char path[],int fontsize);


/*函数名：Kos_Render_UTF8Text
    函数作用：渲染指定的UTF8字符串，如果失败，直接向Kos_Error函数抛出错误
    函数参数：TTF_Font * font ：用来渲染的字体指针变量，char text[]：要渲染的字符串，SDL_Color Textcolor：渲染的字体颜色
    函数返回值：一个包含已经渲染字符串的SDL_Surface指针
*/
SDL_Surface * Kos_Render_UTF8Text(TTF_Font * font,char text[],SDL_Color Textcolor);

/*函数名：Kos_Render_ASCIIText
    函数作用：渲染指定的ASCII字符串，如果失败，直接向Kos_Error函数抛出错误
    函数参数：TTF_Font * font ：用来渲染的字体指针变量，char text[]：要渲染的字符串，SDL_Color Textcolor：渲染的字体颜色
    函数返回值：一个包含已经渲染字符串的SDL_Surface指针
*/
SDL_Surface * Kos_Render_ASCIIText(TTF_Font * font,char text[],SDL_Color Textcolor);

/*函数名：Kos_Clean_Up
    函数作用：清理Kos_SDL的全局变量和关闭SDL系统
    函数参数：无
    函数返回值：无
*/
void Kos_Clean_Up (void);


/*函数名：Kos_BlitToScreen
    函数作用：将一个surface的指定部分blit到窗口的surface上，如果失败，直接向Kos_Error函数抛出错误
    函数参数：int x：Blit到的x坐标，int y：Blit到的y坐标，SDL_Surface *source 要blit到窗口的Surface变量指针，SDL_Rect *cli：对精灵图的切割变量指针，如果无需切割，请使用NULL
    函数返回值：无
*/
void Kos_BlitToScreen(int x,int y,SDL_Surface * source,SDL_Rect * cli);


/*函数名：Kos_TimeFlipScreen
    函数作用：按照指定的帧率刷新屏幕，如果时间间隔不够，自动休眠合适的时间，如果失败，直接向Kos_Error函数抛出错误
    函数参数：int frame_per_second：指定的帧率
    函数返回值：无
*/
void Kos_TimeFlipScreen(int frame_per_second);


/*函数名：Kos_FlipScreen
    函数作用：直接刷新屏幕，如果失败，直接向Kos_Error函数抛出错误
    函数参数：无
    函数返回值：无
*/
void Kos_FlipScreen (void);


/*函数名：Kos_BlitFPS
    函数作用：在屏幕的右上角显示打印帧率，如果失败，直接向Kos_Error函数抛出错误
    函数参数：int FPSsize：打印的帧率大小，SDL_Color FPScolor：打印的帧率颜色
    函数返回值：无
*/
void Kos_BlitFPS (int FPSsize,SDL_Color FPScolor);


/*函数名：Kos_PlayMusic
    函数作用：播放指定的音乐，如果失败，直接向Kos_Error函数抛出错误
    函数参数：Mix_Music* music：要播放的音乐的指针，int playcount：播放次数，设置为-1时将一直循环播放
    函数返回值：无
*/
void Kos_PlayMusic (Mix_Music* music,int playcount);


/*函数名：Kos_PlayChunk
    函数作用：播放指定的音效，如果失败，直接向Kos_Error函数抛出错误
    函数参数：Mix_Chunk *chunk：要播放的音效的指针，int playcount：播放次数
    函数返回值：无
*/
void Kos_PlayChunk (Mix_Chunk *chunk,int playcount);
