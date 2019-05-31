#include "graphx.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



bool GUI_ACTIVE; 
void GUI_Clear();
void GUI_ADD_BUTTON (struct Button* IB);
void GUI_Draw();
void GUI_INIT();
void GUI_HANDLE();
void GUI_SELECT_MENUE(char*ButtonsText[],int ButtonCountIN,void(**calls)(void),uint8_t SCsize);
struct Button;
struct Button{
    uint16_t posx;
    uint16_t posy;
    char* Text;
    uint16_t TextColour;
    uint16_t BackColour;
    uint16_t SelectColour;
    uint8_t buttonlength;
    uint8_t scaling;
 };
struct Label{
    char* Text;
};



struct GUISC{
struct Button* Buttons;//Buttons
void(**OPTIONSENTER)(void);//Functions to call when Buttons are pressed
int Buttoncount;
int SelectedID;//At start the First Button is selected
int8_t buttonback;
int8_t buttonselect;
int8_t textcol;
int8_t backcol;
}CGUISC;

//                         BACK                            SELECT                   BUTTONBACK                  TEXT  

void GUI_INIT(){
     gfx_Begin();//enable 8bpp
     
     gfx_palette[0] = gfx_RGBTo1555(16, 56, 81);//Background
     gfx_palette[1] = gfx_RGBTo1555(107, 0, 0);//SELECT
     gfx_palette[2] = gfx_RGBTo1555(142, 142, 142);//Hintergrundknopfs
     gfx_palette[3] = gfx_RGBTo1555(209, 209, 209);//TEXT
  
     GUI_ACTIVE = true;  
     CGUISC.backcol = 0;
     CGUISC.textcol = 3;
     CGUISC.buttonback = 2;
     CGUISC.buttonselect = 1;
     CGUISC.Buttons = calloc(1,sizeof(struct Button));
     CGUISC.Buttoncount = 0;
     CGUISC.SelectedID = 0;
}

void GUI_ADD_BUTTON(struct Button* IB){
    if( CGUISC.Buttoncount>0){
 CGUISC.Buttons = realloc( CGUISC.Buttons,sizeof(struct Button)*( CGUISC.Buttoncount+1));
    }
 CGUISC.Buttons[ CGUISC.Buttoncount] = *IB;
 CGUISC.Buttoncount++;
}
void SelectButton(bool direction){
if(direction){
    if( CGUISC.SelectedID <  CGUISC.Buttoncount-1){
       CGUISC.SelectedID ++;
    }else{
         CGUISC.SelectedID = 0;
    }
}else{
if( CGUISC.SelectedID>0){
       CGUISC.SelectedID--;
    }else{
      CGUISC.SelectedID =  CGUISC.Buttoncount-1;
    }
}
GUI_Draw();
}

void GUI_Draw(){
    int i = 0;
    int l = 0;
    int tx = 0;
    int ty = 0;
    gfx_FillScreen(CGUISC.backcol);//Fill Background
    for(i = 0;i< CGUISC.Buttoncount;i++){
        if(i ==  CGUISC.SelectedID){
            gfx_SetColor(CGUISC.Buttons[i].SelectColour);
            gfx_SetTextBGColor(CGUISC.Buttons[i].SelectColour);
            tx = CGUISC.Buttons[i].posx-5*CGUISC.Buttons[i].scaling;
        }else{
            tx =  CGUISC.Buttons[i].posx;
            gfx_SetColor(CGUISC.Buttons[i].BackColour);
            gfx_SetTextBGColor(CGUISC.Buttons[i].BackColour);
        }
        
        ty =  CGUISC.Buttons[i].posy;
        gfx_FillRectangle(tx-5*CGUISC.Buttons[i].scaling, ty-5*CGUISC.Buttons[i].scaling, CGUISC.Buttons[i].buttonlength+3,15*CGUISC.Buttons[i].scaling);
       // Fill(Background,tx-10,ty-10,tx+Buttons[i].buttonlength+3,ty+10); 
       // Foreground = Buttons[i].TextColour;
       // Text_Transparent = true; 
        
         gfx_SetTextFGColor(CGUISC.Buttons[i].TextColour);
         gfx_SetTextScale(CGUISC.Buttons[i].scaling,CGUISC.Buttons[i].scaling);
         gfx_PrintStringXY( CGUISC.Buttons[i].Text,tx,ty);
        //DrawText(Buttons[i].Text,tx,ty);
       // Text_Transparent = false;
    }
}

void GUI_HANDLE(){
   struct GUISC backupSC;
    GUI_Draw();
 while(GUI_ACTIVE){
int keycodeC = os_GetKey();
switch(keycodeC){
      case 10:
        GUI_Clear();
      return;
      case 4:
        SelectButton(true);
      break;
      case 3:
        SelectButton(false);
      break;
      case 5:
        backupSC =  CGUISC;
        //Enter Pressed
         gfx_End();
         (*CGUISC.OPTIONSENTER[CGUISC.SelectedID])();
         GUI_INIT();
         CGUISC =  backupSC;   
         GUI_Draw();
      break;
   }
 }
}
void GUI_Clear(){
    gfx_End();
    free(CGUISC.Buttons);
    GUI_ACTIVE = false;
}



struct Button B_TEMP;
void GUI_SELECT_MENUE(char*ButtonsText[],int ButtonCountIN,void(**calls)(void),uint8_t SCsize){
    int bcounta = 0;
    int i = 0;
    int maxbuttonlength = 0;
    int temp = 0;
    CGUISC.OPTIONSENTER = calls;
  //Initialise GUI  
    GUI_INIT();
 //Determine maximal Button length 
    for(i = 0;i<ButtonCountIN;i++){
        temp = strlen(ButtonsText[i]);     
        if(temp>maxbuttonlength){
            maxbuttonlength = temp;
        }
    }
   
    while(bcounta<ButtonCountIN){
        B_TEMP.posx = 320/2-(maxbuttonlength*9*SCsize)/2;
        B_TEMP.posy =  240/2-(ButtonCountIN*25/2)+20*bcounta*SCsize;
        B_TEMP.Text = ButtonsText[bcounta];
        B_TEMP.BackColour = CGUISC.buttonback;
        B_TEMP.SelectColour = CGUISC.buttonselect;
        B_TEMP.TextColour = CGUISC.textcol;
        B_TEMP.buttonlength = maxbuttonlength*9*SCsize;
        B_TEMP.scaling = SCsize;
         GUI_ADD_BUTTON(&B_TEMP);
         bcounta++;
    }
    GUI_HANDLE();
}