#include "GUI.c"
#include "Joystick.h"
void main();
void leave();
float WERT(float Input);
char* Version = "v0.22";
void Imagedraw();
void main(void){
   char* namE[] = {"Test ","EXIT ","Pallette"};
   void(*OPTIONSENTERR[]) = {Imagedraw,leave,GUI_DRAW_PALLETTE};
   GUI_INIT();
   GUI_SELECT_MENUE_VERTICAL(namE,3,OPTIONSENTERR,3); 
   GUI_ADD_LABEL_S(Version,280,230,1);
   
   GUI_HANDLE();
   exit(1);
}
void Imagedraw(){
    struct Image IMG2;
   /*
    struct Image IMG;
    IMG.data = stickIMG;
    IMG.resx = 300;
    IMG.resy = 154;   
    GUI_DRAW_IMAGE(&IMG,10,10);
    */
    IMG2.data = stickIMG;
    IMG2.resx = 300;
    IMG2.resy = 154;
    IMG2.type = 1;
     GUI_DRAW_IMAGE(&IMG2,0,0);
     while(os_GetKey()!=5);
}
void leave(){
    exit(0);
}
float WERT(float Input){
        return(Input);   
        GUI_Clear();
}
char bitIMG[8] = {
0x38,
0x44,
0x82,
0x82,
0x44,
0x38,
0xFF,
0x00
};