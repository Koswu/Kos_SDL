Kos_SDL
===========
自用的一个封装于SDL的图形库
-------------------------

Ubuntu32位安装方法：将header中的头文件和Bin/Release下的.a文件，加入编译器搜寻目录，在编译器编译时加入-lKos_SDL -lSDL -lSDL_image -lSDL_ttf参数
<br/>
C4droid安装方法:将header中的头文件放到/data/data/com.n0n3m4.droidc/files/gcc/arm-linux-androideabi/include/下，将C4droid bin中的文件加入/data/data/com.n0n3m4.droidc/files/gcc/arm-linux-androideabi/lib/下，如果安装gcc时选择的是存储卡请放到存储卡相应位置，在C4droid设置中的SDL参数最前面加上-lKos_SDL 
<br/>
PS:使用时请#include \<Kos_SDL.h>