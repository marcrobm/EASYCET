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


//Universal 
void GUI_INIT();
void GUI_Draw();
void GUI_HANDLE();
void GUI_Clear();
char colourindex(char r,char g,char b);
//Buttons
struct Button;
void GUI_DRAW_BUTTONS();
void GUI_ADD_BUTTON (struct Button* IB);

//Labels
struct Label;
void GUI_DRAW_LABELS();
void GUI_ADD_LABEL(struct Label* IB);
void GUI_ADD_LABELV(char* Text,uint16_t posx,uint16_t posy,char BC,char TC,char scaling);
//GUI Creation
void GUI_SELECT_MENUE_VERTICAL(char*ButtonsText[],int ButtonCountIN,void(**calls)(void),uint8_t SCsize);
void GUI_SELECT_MENUE_VERTICAL_XYS(char*ButtonsText[],int ButtonCountIN,void(**calls)(void),uint8_t SCsize,int SX,int SY,int maxbuttonlength);
//Styles

void GUI_STYLE_GRAYSCALE();

struct Button{
    uint16_t posx;
    uint16_t posy;
    char* Text;
    char TextColour;
    char BackColour;
    char SelectColour;
    uint8_t buttonlength;
    uint8_t scaling;
 };
struct Label{
    char* Text;
    uint16_t posx;
    uint16_t posy;
    uint8_t scaling;
    char BackColour;
    char TextColour;
};

struct Image{
    char*data;
    char type;//0 rgb222   |1bpp
    uint16_t resx;
    uint16_t resy;
};

struct GUISC{
//Buttons
struct Button* Buttons;//Buttons
void(**OPTIONSENTER)(void);//Functions to call when Buttons are pressed
int Buttoncount;
int SelectedID;//Currently selected Button
//Labels
struct Label* Labels;//Labels
int LabelCount;
//Images
struct Image* Images;
int ImageCount;
//default values for some functions
uint8_t buttonback;
uint8_t buttonselect;
uint8_t textcol;
uint8_t backcol;
uint8_t LABELTEXT;
uint8_t LABELBACK;
}CGUISC;


