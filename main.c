#include "GUI.c"

void TEST();
void main();
void leave();

void main(void){
   char* namE[] = {"Test ","EXIT ","A "};
   void(*OPTIONSENTERR[]) = {TEST,leave,leave};
   GUI_SELECT_MENUE_VERTICAL(namE,3,OPTIONSENTERR,3); 
   GUI_HANDLE();
   exit(1);
}

void TEST(){
  //Text on Buttons
  char* namE[] = {"Back ","EXIT ","Back ","EXIT ","Back ","EXIT "};
  //Functions to call on Buttonpress
  void(*OPTIONSENTERR[]) = {main,leave,main,leave,main,leave};
  //Create Buttons with Test,Count,Functions, and 2 stands for large menue (can be 1-5)
  GUI_SELECT_MENUE_VERTICAL_XYS(namE,6,OPTIONSENTERR,1,15,15,70);
  GUI_HANDLE();
  }

void leave(){
    exit(0);
}

