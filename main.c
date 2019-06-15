#include "GUI.c"
#include "Joystick.h"
void main();
void leave();
void SANF();
float WERT(float Input);
char* Version = "v0.22";
void Imagedraw();
void MEMSCAN();
void main(void){
   GUI_INIT();
   FileBrowser();
   exit(1);
}
void leave(){
    exit(0);
}
float WERT(float Input){
        return(Input);   
        GUI_Clear();
}