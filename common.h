/*头文件定义*/
#include <stdbool.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>


/*函数声明*/
TTF_Font * Kos_Load_Font (char path[],int fontsize);
SDL_Surface * Kos_Render_UTF8Text(TTF_Font * font,char text[],SDL_Color Textcolor);
void Kos_CopyToSurface(int x,int y,SDL_Surface * source,SDL_Surface * target,SDL_Rect * cli);
void Kos_Clean_Up (void);
void Kos_BlitToScreen(int x,int y,SDL_Surface * source,SDL_Rect * cli);
