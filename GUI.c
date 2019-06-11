#include "GUI.h"
void GUI_INIT(){
     int i = 0;
     char R,G,B;
     gfx_Begin();//enable 8bpp
     GUI_ACTIVE = true;  
     CGUISC.Buttons = calloc(1,sizeof(struct Button));
     CGUISC.Labels = calloc(1,sizeof(struct Label));
     CGUISC.Buttoncount = 0;
     CGUISC.LabelCount = 0;
     CGUISC.SelectedID = 0;
     gfx_palette[0] = gfx_RGBTo1555(11, 15, 40);//Dark_BLUE
     gfx_palette[1] = gfx_RGBTo1555(38, 9, 17);//Dark_RED
     gfx_palette[3] = gfx_RGBTo1555(25, 25, 25); //Dark Gray
  
     gfx_palette[2] = gfx_RGBTo1555(255,255,255);//WHITE
     gfx_palette[4] = gfx_RGBTo1555(200, 200,200);
     gfx_palette[5] = gfx_RGBTo1555(150, 150, 150);
     gfx_palette[6] = gfx_RGBTo1555(100, 100, 100);
     gfx_palette[7] = gfx_RGBTo1555(50, 50, 50);
     gfx_palette[8] = gfx_RGBTo1555(20,20, 20);
     gfx_palette[9] = gfx_RGBTo1555(0,0, 0);//Black
    for(i=0;i<64;i++){
        //Do not change, ez80 c does not like bitwise operators inside of function arguments
        R = (i & 48 )<<2;
        G = (i & 12 )<<4;
        B = (i & 3 )<<6;
        gfx_palette[192+i] = gfx_RGBTo1555(R,G,B);
    }
     GUI_STYLE_GRAYSCALE();//Default style
}

void GUI_STYLE_GRAYSCALE(){
     CGUISC.backcol = 2;
     CGUISC.textcol = 2;
     CGUISC.buttonback = 7;
     CGUISC.buttonselect = 8;
     CGUISC.LABELTEXT = 9;
     CGUISC.LABELBACK = 2; 
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
void GUI_DRAW_BUTTONS(){
     int i = 0;
    int l = 0;
    int tx = 0;
    int ty = 0;
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
         gfx_SetTextScale(CGUISC.Buttons[i].scaling,CGUISC.Buttons[i].scaling);
         gfx_SetTextFGColor(CGUISC.Buttons[i].TextColour);
         gfx_PrintStringXY( CGUISC.Buttons[i].Text,tx,ty);
    }
}

//Code For Labels
void GUI_DRAW_LABELS(){
    int i = 0;
   for(i = 0;i< CGUISC.LabelCount;i++){ 
         gfx_SetTextFGColor(CGUISC.Labels[i].TextColour);
         gfx_SetTextBGColor(CGUISC.Labels[i].BackColour);
         gfx_SetTextScale(CGUISC.Labels[i].scaling,CGUISC.Labels[i].scaling);
         gfx_PrintStringXY( CGUISC.Labels[i].Text,CGUISC.Labels[i].posx,CGUISC.Labels[i].posy);
   }
}
struct Label TempLabel;
void GUI_ADD_LABEL_S(char* Text,uint16_t posx,uint16_t posy,char scaling){
    TempLabel.Text = Text;
    TempLabel.posx = posx;
    TempLabel.posy = posy;
    TempLabel.scaling = scaling;
    TempLabel.BackColour = CGUISC.LABELBACK;
    TempLabel.TextColour = CGUISC.LABELTEXT;
    GUI_ADD_LABEL(&TempLabel);
}

void GUI_ADD_LABELV(char* Text,uint16_t posx,uint16_t posy,char BC,char TC,char scaling){
    TempLabel.Text = Text;
    TempLabel.posx = posx;
    TempLabel.posy = posy;
    TempLabel.scaling = scaling;
    TempLabel.BackColour = BC;
    TempLabel.TextColour = TC;
    GUI_ADD_LABEL(&TempLabel);
}
void GUI_ADD_LABEL(struct Label* IB){
        if( CGUISC.LabelCount>0){
 CGUISC.Labels = realloc( CGUISC.Labels,sizeof(struct Label)*( CGUISC.LabelCount+1));
    }
 CGUISC.Labels[CGUISC.LabelCount] = *IB;
 CGUISC.LabelCount++;
}

void GUI_DRAW_PALLETTE(){
   int x = 0;
   int y = 0;
   GUI_INIT();
   gfx_FillScreen(254);
   for(x=0;x<16;x++){
       for(y=0;y<16;y++){ 
           gfx_SetColor(colourindex(x*15,y*15,128));
           gfx_FillRectangle(10+x*5,10+y*5,10,10);
       }
   }
   for(x=0;x<16;x++){
       for(y=0;y<16;y++){ 
           gfx_SetColor(colourindex(128,x*15,y*15));
           gfx_FillRectangle(100+x*5,10+y*5,10,10);
       }
   }
 for(x=0;x<16;x++){
       for(y=0;y<16;y++){ 
           gfx_SetColor(colourindex(x*15,128,y*15));
           gfx_FillRectangle(10+x*5,100+y*5,10,10);
       }
   }

   while(os_GetKey()!=5);
}
char colourindex(char r,char g,char b){
return( ((r & 224) >> 0) + ((b & 192) >> 3) + ((g & 224) >> 5) );
}




void GUI_Draw(){
    int i = 0;
    gfx_FillScreen(CGUISC.backcol);//Fill Background
    GUI_DRAW_BUTTONS();
    GUI_DRAW_LABELS();
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
         //gfx_End();
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
    free(CGUISC.Labels);
    GUI_ACTIVE = false;
}


struct Button B_TEMP;
void GUI_SELECT_MENUE_VERTICAL_XYS(char*ButtonsText[],int ButtonCountIN,void(**calls)(void),uint8_t SCsize,int SX,int SY,int maxbuttonlength){
    
    int bcounta = 0;
    int i = 0;
    int temp = 0;
    CGUISC.OPTIONSENTER = calls; 
    while(bcounta<ButtonCountIN){
        B_TEMP.posx = SX;
        B_TEMP.posy =  SY+20*bcounta*SCsize;
        B_TEMP.Text = ButtonsText[bcounta];
        B_TEMP.BackColour = CGUISC.buttonback;
        B_TEMP.SelectColour = CGUISC.buttonselect;
        B_TEMP.TextColour = CGUISC.textcol;
        B_TEMP.buttonlength = maxbuttonlength*9*SCsize;
        B_TEMP.scaling = SCsize;
         GUI_ADD_BUTTON(&B_TEMP);
         bcounta++;
    }
}
void GUI_SELECT_MENUE_VERTICAL(char*ButtonsText[],int ButtonCountIN,void(**calls)(void),uint8_t SCsize){
    int maxbuttonlength = 0;
    int i = 0;
    int temp = 0;
  //Determine Maximum Button Length
    for(i = 0;i<ButtonCountIN;i++){
        temp = strlen(ButtonsText[i]);     
        if(temp>maxbuttonlength){
            maxbuttonlength = temp;
        }
    }
   GUI_SELECT_MENUE_VERTICAL_XYS(ButtonsText,ButtonCountIN,calls,SCsize,(320/2-(maxbuttonlength*9*SCsize)/2),(240/2-(ButtonCountIN*25/2)),maxbuttonlength);     
}

void GUI_DRAW_IMAGE(struct Image* IM,uint16_t x,uint16_t y){
int rowy;
int starta;
int desta;
uint16_t size;
char* dat;
uint16_t re;
int X;
int Y;
switch(IM->type){
    case 0:
 size = IM->resx;
 dat = IM->data;
 re = IM->resy;
for(rowy = 0;rowy<re;rowy++){
   starta = (int)dat + rowy*IM->resx;//pixel* in picture
   desta  = (int)gfx_vram + (rowy+x)*320 +y;//pixel* in vram
   memcpy((void*)desta ,(void*)starta,size);
}
break;
case 1:
for(X=0;X<IM->resx;X++){
 for(Y=0;Y<IM->resy;Y++){
    starta = Y*IM->resx + X;//index of color bit in data
    rowy = (int)(starta/8);
    desta  = starta % 8 ; //bit of byte 
   if((IM->data[rowy] << desta) & 128  ){
    gfx_vram[320*Y+X] = 255;
   }else{
    gfx_vram[320*Y+X] = 192;
   }
}   
}
break;
}
}
