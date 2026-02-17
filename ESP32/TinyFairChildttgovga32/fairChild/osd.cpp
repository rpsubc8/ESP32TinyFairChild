#include "gbConfig.h"
#include "gbGlobals.h"
//#include "hardware.h"
#include "fairChild.h"
#include "osd.h"
//#include "dataFlash/gbcom.h"
//#include "hardware.h"
//#ifdef use_lib_audio_tone32
// #include "Tone32.h"
//#endif
#include "PS2Kbd.h"
#include "gb_sdl_font8x8.h"
#include "video.h"
#include "gbCompileOpt.h"
#ifndef use_lib_wifi
 #ifdef gb_use_lib_compile_arduinodroid
  #include "gbcart.h"
 #else
  #include "dataFlash/gbcart.h"
 #endif 
#endif 
#ifdef use_lib_wifi 
 #include "gbWifiConfig.h"
 #include "gbWifi.h"  
#endif

#include "vga_6bit.h"

//#include "render.h"
//#include "dataFlash/gbsnarare.h"
//#include "cpu.h"
//#include "ports.h"


//#define BLACK   0
//#define BLUE    4
//#define RED     1
//#define MAGENTA 5
//#define GREEN   2
//#define CYAN    6
//#define YELLOW  3
//#define WHITE   15

#ifdef COLOR_3B           //       BGR 
 #define BLACK   0x08      // 0000 1000
 #define BLUE    0x0C      // 0000 1100
 #define RED     0x09      // 0000 1001
 #define MAGENTA 0x0D      // 0000 1101
 #define GREEN   0x0A      // 0000 1010
 #define CYAN    0x0E      // 0000 1110
 #define YELLOW  0x0B      // 0000 1011
 #define WHITE   0x0F      // 0000 1111
#endif


//extern int gb_screen_xIni;
//extern int gb_screen_yIni;
//extern unsigned char gb_cache_zxcolor[8];


unsigned char gb_show_osd_main_menu=0;

//extern SDL_Surface * gb_screen;
//extern SDL_Event gb_event;





//#define max_gb_osd_screen 1
//const char * gb_osd_screen[max_gb_osd_screen]={
// "Pixels Left"//,
// //"Pixels Top",
// //"Color 8",
// //"Mono Blue 8",
// //"Mono Green 8",
// //"Mono Red 8",
// //"Mono Grey 8"
//};

//#define max_gb_osd_screen_values 5
//const char * gb_osd_screen_values[max_gb_osd_screen_values]={
// "0",
// "2",
// "4", 
// "8", 
// "16"
//};


#define max_gb_main_menu 8
#ifdef use_lib_wifi
 const char * gb_main_menu[max_gb_main_menu]={
  "Load CART WIFI",
  "Reset",
  "Delay CPU",
  "Video Options",
  "Keyboard Poll",
  "OSD (performance)",
  "Debug options",
  "Return"
 };
#else
 const char * gb_main_menu[max_gb_main_menu]={
  "Load CART",
  "Reset",
  "Delay CPU",
  "Video Options",
  "Keyboard Poll",
  "OSD (performance)",
  "Debug options",
  "Return"
 };
#endif 

#define max_gb_video_options_menu 4
const char * gb_video_options_menu[max_gb_video_options_menu]={
 "Video mode",
 "Mode PAL/NTSC",
 "Video Poll",
 "Offset X"
};

#define max_gb_video_mode_menu 8
static const char * gb_video_mode_menu[max_gb_video_mode_menu]={
// "0 360x200x70hz bitluni(3bpp)",
// "1 360x200x70hz bitluni apll(3bpp)",
// "2 320x200x70hz bitluni(3bpp)",
// "3 320x200x70hz fabgl(3bpp)",
// "4 320x200x70hz bitluni apll(3bpp)",
// "5 320x240x60hz bitluni(3bpp)",
// "6 320x240x60hz fabgl(3bpp)",
// "7 320x240x60hz bitluni apll(3bpp)",
 "0 360x200x70 bitluni",
 "1 360x200x70 bn apll",
 "2 320x200x70 bitluni",
 "3 320x200x70 fabgl",
 "4 320x200x70 bn apll",
 "5 200x150x56 bitluni", 
 "6 200x150x56 bn apll",
 "Return"
};

#define max_gb_video_palntsc_menu 2
static const char * gb_video_palntsc_menu_en[max_gb_video_palntsc_menu]={
 "PAL (50 fps)",
 "NTSC (60 fps)"
};

//#define max_gb_machine_menu 3
//const char * gb_machine_menu[max_gb_machine_menu]={
// "464",
// "664",
// "6128"
//};


#define max_gb_delay_cpu_menu 11
const char * gb_delay_cpu_menu[max_gb_delay_cpu_menu]={
 "Auto",
 "0",
 "1",
 "2",
 "4",
 "8",
 "16",
 "32",
 "64",
 "128",
 "Return"
};


//#define max_gb_speed_sound_menu 7
//const char * gb_speed_sound_menu[max_gb_speed_sound_menu]={
// "0",
// "1",
// "2",
// "4",
// "8",
// "16",
// "32"
//};

//#define max_gb_value_binary_menu 2
//const char * gb_value_binary_menu[max_gb_value_binary_menu]={
// "0",
// "1"
//};


//#define max_gb_speed_videoaudio_options_menu 2
//const char * gb_speed_videoaudio_options_menu[max_gb_speed_videoaudio_options_menu]={
// "Video poll",
// "Keyboard poll"
//};

#define max_gb_speed_video_poll_menu 6
const char * gb_speed_video_poll_menu[max_gb_speed_video_poll_menu]={
 "16",
 "20",
 "30",
 "40",
 "50",
 "Return"
};

#define  max_gb_ofs_x_video_menu 6
const char * gb_ofs_x_video_menu[max_gb_ofs_x_video_menu]={
 "0",
 "4",
 "8",
 "12",
 "16",
 "Return"
};

#define max_gb_speed_keyboard_poll_menu 6
const char * gb_speed_keyboard_poll_menu[max_gb_speed_keyboard_poll_menu]={
 "10",
 "20",
 "30",
 "40",
 "50",
 "Return"
};

#define max_gb_bool_menu 2
static const char * gb_bool_menu_en[max_gb_bool_menu]={
 "Yes",
 "No"
};



//#define max_gb_speed_menu 5
//const char * gb_speed_menu[max_gb_speed_menu]={
// "Normal",
// "2x",
// "4x",
// "8x",
// "16x"
//};


//#define max_gb_osd_mouse_menu 2
//const char * gb_osd_mouse_menu[max_gb_osd_mouse_menu]={
// "right handed",
// "left handed"
//};

#define max_gb_reset_menu 3
const char * gb_reset_menu[max_gb_reset_menu]={
 "Soft",
 "Hard",
 "Return"
};


//#define gb_pos_x_menu 0
//#define gb_pos_y_menu 20
#define gb_osd_max_rows 10

void SDLClear()
{
 //for (int y=0; y<(auxSurface->w); y++)
 // for (int x=0; x<(auxSurface->h); x++)
 //  SDLputpixel(auxSurface,x,y,1);
 //for (int y=0; y<200; y++)
 // for (int x=0; x<320; x++)
 unsigned char c= gb_color_vga[0];

 for (int y=0; y<gb_vga_alto; y++) //150
 {
  for (int x=0; x<gb_vga_ancho; x++) //200
  {
   gb_buffer_vga[y][x^2]= c; //jj_fast_putpixel(x,y,0);
   //SDLputpixel(auxSurface,x,y,3); 
  }
 }
}


//********************************************************************************************
void OSDprintTextFPS(char *cad,unsigned char x, unsigned char y, unsigned char color,unsigned char backcolor)
{//Coordenadas en 6x8
 unsigned short int xDest= ((unsigned short int)x)<<3; 
 unsigned short int yDest= ((unsigned short int)y)<<3;
 
 unsigned int auxId;
 unsigned char aux;
 unsigned char auxColor;
 unsigned short int xDest2=0;
 unsigned short int yDest2=0; 
 //unsigned short int x2,y2;
 unsigned char aCol[2]= {gb_color_vga[backcolor],gb_color_vga[color]};
 
 int auxLen= strlen(cad);
 if (auxLen>18)
 {
  auxLen=18;
 }
 
 for (int i=0;i<auxLen;i++)
 {
//  OSDprintChar(cad[i],xDest,yDest,color,backcolor,0,1);
    
   auxId = cad[i] << 3; //x8
   //x2= xDest;
   //y2= yDest;
   for (unsigned char j=0;j<8;j++)
   {
    aux = gb_sdl_font_8x8[auxId + j];
    for (int k=0;k<7;k++)
    {
     auxColor= ((aux>>k) & 0x01);
     xDest2= xDest+j; //xDest2= x2+j;
     yDest2= yDest+k; //yDest2= y2+k;
     //jj_fast_putpixel(surface,xDest,yDest,(auxColor==1)?color:backcolor);
     //gb_buffer_vga[yDest2][xDest2]= (auxColor==1)?color:backcolor;
     //gb_buffer_vga[yDest2][xDest2]= aCol[auxColor];
     gb_buffer_vga[yDest2][xDest2^2]= aCol[auxColor];
    }
   }//fin cuando es normal  
  
  
  yDest-=6;
 } 
}


//*************************************************************************************
void SDLprintCharOSD(char car,int x,int y,unsigned char color,unsigned char backcolor)
{ 
// unsigned char aux = gb_sdl_font_6x8[(car-64)];
 int auxId = car << 3; //*8
 unsigned char aux;
 unsigned char auxColor;
 for (unsigned char j=0;j<8;j++)
 {
  aux = gb_sdl_font_8x8[auxId + j];
  for (int i=0;i<8;i++)
  {
   auxColor= ((aux>>i) & 0x01);
   //SDLputpixel(surface,x+(6-i),y+j,(auxColor==1)?color:backcolor);
   gb_buffer_vga[(y+j)][((x+(6-i))^2)]= gb_color_vga[((auxColor==1)?color:backcolor)];  //jj_fast_putpixel(x+(6-i),y+j,(auxColor==1)?color:backcolor);
  }
 }
}

void SDLprintText(const char *cad,int x, int y, unsigned char color,unsigned char backcolor)
{
//SDL_Surface *surface,
// gb_sdl_font_6x8
 int auxLen= strlen(cad);
 if (auxLen>(osd_maxcadaux-1))
 {
  auxLen=(osd_maxcadaux-1);
 }
 for (int i=0;i<auxLen;i++)
 {
  SDLprintCharOSD(cad[i],x,y,color,backcolor);
  x+=7;
 }
}

void OSDMenuRowsDisplayScroll(const char **ptrValue,unsigned char currentId,unsigned char aMax)
{//Dibuja varias lineas
 //for (int i=0;i<gb_osd_max_rows;i++)
 //{
 // SDLprintText("                           ",gb_pos_x_menu,gb_pos_y_menu+8+(i<<3),0,0);               
 //}
 unsigned char tope=0; 
 char cad[osd_maxcadaux];
 unsigned char cont=0;
 
 for (int i=0;i<gb_osd_max_rows;i++)
 {   
  if (currentId >= aMax)
  {
   break;
  }
  //SDLprintText(gb_osd_sdl_surface,ptrValue[currentId],gb_pos_x_menu,gb_pos_y_menu+8+(i<<3),((i==0)?CYAN:WHITE),((i==0)?BLUE:BLACK),1);
  
  tope= strlen(ptrValue[currentId]);
  for (unsigned char j=0;j<osd_maxcadaux;j++)
  {
   cad[j]= (j<tope) ? ptrValue[currentId][j] : ' ';
  }
  cad[osd_maxcadaux-1]='\0';

  SDLprintText(cad,gb_pos_x_menu,gb_pos_y_menu+8+(i<<3),((i==0)?ID_COLOR_WHITE:ID_COLOR_WHITE),((i==0)?ID_COLOR_VIOLETA:ID_COLOR_BLACK));

  currentId++;
  cont++;
 }

 if (cont<gb_osd_max_rows)
 {
  for (unsigned char i=0;i<osd_maxcadaux;i++)
  {
   cad[i]= ' ';
  }
  cad[osd_maxcadaux-1]='\0';
  for (unsigned char i=cont;i<gb_osd_max_rows;i++)
  {
   SDLprintText(cad,gb_pos_x_menu,gb_pos_y_menu+8+(i<<3),ID_COLOR_WHITE,ID_COLOR_BLACK);
  }
 }
}


#ifdef use_lib_wifi
 void ShowStatusWIFI(unsigned char aState)
 {
  if (aState == 1)
  {
   SDLprintText("WIFI LOAD",8,8,ID_COLOR_BLACK,ID_COLOR_WHITE);   
  }
  else
  {  
   SDLprintText("         ",8,8,ID_COLOR_BLACK,ID_COLOR_BLACK);
  }
 }


 //**********************************************************************************
 void OSDMenuRowsDisplayScrollFromWIFI(unsigned char *ptrBuffer,unsigned char currentId,unsigned char aMax)
 {//Dibuja varias lineas
  unsigned char cont=0;
  char cadName8[10];
  cadName8[8]='\0';
  //for (int i=0;i<gb_osd_max_rows;i++)
  //{
  // SDLprintText("                    ",gb_pos_x_menu,gb_pos_y_menu+8+(i<<3),ID_COLOR_BLACK,ID_COLOR_BLACK);
  //}
 
  for (int i=0;i<gb_osd_max_rows;i++)
  {
   if (currentId >= aMax)
   {
    break;
   }
   memcpy(cadName8, &ptrBuffer[(currentId*8)], 8);
   cadName8[8]='\0';
//   SDLprintText(ptrValue[currentId],gb_pos_x_menu,gb_pos_y_menu+8+(i<<3),((i==0)?ID_COLOR_WHITE:ID_COLOR_WHITE),((i==0)?ID_COLOR_MAGENTA:ID_COLOR_BLACK));
   //SDLprintText((const char*)cadName8,gb_pos_x_menu,gb_pos_y_menu+8+(i<<3),((i==0)?ID_COLOR_WHITE:ID_COLOR_WHITE),((i==0)?ID_COLOR_MAGENTA:ID_COLOR_BLACK));
   SDLprintText((const char*)cadName8,gb_pos_x_menu,gb_pos_y_menu+8+(i<<3),((i==0)?ID_COLOR_WHITE:ID_COLOR_WHITE),((i==0)?ID_COLOR_VIOLETA:ID_COLOR_BLACK));
   currentId++;
   cont++;
  }

  if (cont<gb_osd_max_rows)
  {
   for (unsigned char i=0;i<8;i++)
   {
    cadName8[i]= ' ';
   }
   cadName8[8]='\0';
   for (unsigned char i=cont;i<gb_osd_max_rows;i++)
   {
    SDLprintText(cadName8,gb_pos_x_menu,gb_pos_y_menu+8+(i<<3),ID_COLOR_WHITE,ID_COLOR_BLACK);
   }
  }  
 }

 //**********************************************************************************
 unsigned char ShowTinyMenuFromWIFI(const char *cadTitle,unsigned char *ptrBuffer,unsigned char aMax)
 {
  unsigned char aReturn=0;
  unsigned char salir=0;
  char cad[osd_maxcadaux];
  unsigned char tope=0;  

  ClearKeyboard();
  SDLClear();
  SDLprintText("FreeChaF by ackerman",gb_pos_x_menu,(gb_pos_y_menu-16),ID_COLOR_WHITE,ID_COLOR_BLACK);
  //for (int i=0;i<14;i++)
  //{
  // SDLprintCharOSD(' ',gb_pos_x_menu+(i<<3),gb_pos_y_menu,ID_COLOR_BLACK,ID_COLOR_WHITE);   
  //}
  tope= strlen(cadTitle);
  for (unsigned char i=0;i<osd_maxcadaux;i++)
  {
   cad[i]= (i<tope) ? cadTitle[i]: ' ';
  }
  cad[osd_maxcadaux-1]='\0';
  SDLprintText(cad,gb_pos_x_menu,gb_pos_y_menu,ID_COLOR_BLACK,ID_COLOR_WHITE); //Titulo

  //SDLprintText(cadTitle,gb_pos_x_menu,gb_pos_y_menu,ID_COLOR_BLACK,ID_COLOR_WHITE);
  OSDMenuRowsDisplayScrollFromWIFI(ptrBuffer,0,aMax); 
  while (salir == 0)
  {  
   if (checkAndCleanKey(KEY_CURSOR_LEFT))
   {
    if (aReturn>10) aReturn-=10;
    OSDMenuRowsDisplayScrollFromWIFI(ptrBuffer,aReturn,aMax);
   }
   if (checkAndCleanKey(KEY_CURSOR_RIGHT))
   {
    if (aReturn<(aMax-10)) aReturn+=10;
    OSDMenuRowsDisplayScrollFromWIFI(ptrBuffer,aReturn,aMax);
   }
   if (checkAndCleanKey(KEY_CURSOR_UP))
   {
    if (aReturn>0) aReturn--;
    OSDMenuRowsDisplayScrollFromWIFI(ptrBuffer,aReturn,aMax);
   }
   if (checkAndCleanKey(KEY_CURSOR_DOWN))
   {
    if (aReturn < (aMax-1)) aReturn++;
    OSDMenuRowsDisplayScrollFromWIFI(ptrBuffer,aReturn,aMax);
   } 
   if (checkAndCleanKey(KEY_ENTER))
   {
    salir= 1;
   }
   if (checkAndCleanKey(KEY_ESC))
   {
    salir=1; aReturn= 255;
   }
  }
  gb_show_osd_main_menu= 0;

  ClearKeyboard();
  return aReturn;
 }
#endif


//Maximo 256 elementos
unsigned char ShowTinyMenu(const char *cadTitle,const char **ptrValue,unsigned char idSel, unsigned char aMax)
{
 unsigned char aReturn=0;
 unsigned char salir=0;
 char cad[osd_maxcadaux];
 unsigned char tope=0;

 ClearKeyboard();

 SDLClear();
 SDLprintText("FreeChaF by ackerman",gb_pos_x_menu,(gb_pos_y_menu-16),ID_COLOR_WHITE,ID_COLOR_BLACK);
 //for (int i=0;i<20;i++) 
 //for (int i=0;i<14;i++)
 //{
 // SDLprintCharOSD(' ',(gb_pos_x_menu+i),gb_pos_y_menu,ID_COLOR_BLACK,ID_COLOR_WHITE);
 //}
 //SDLprintText(cadTitle,gb_pos_x_menu,gb_pos_y_menu,ID_COLOR_BLACK,ID_COLOR_WHITE);
 tope= strlen(cadTitle);
 for (unsigned char i=0;i<osd_maxcadaux;i++)
 {
  cad[i]= (i<tope) ? cadTitle[i]: ' ';
 }
 cad[osd_maxcadaux-1]='\0';
 SDLprintText(cad,gb_pos_x_menu,gb_pos_y_menu,ID_COLOR_BLACK,ID_COLOR_WHITE); //Titulo


 OSDMenuRowsDisplayScroll(ptrValue,idSel,aMax);
 aReturn= idSel;
 
 while (salir == 0)
 {
  //SDL_PollEvent(gb_osd_sdl_event);
  //if(SDL_WaitEvent(gb_osd_sdl_event))
  {
   //if(gb_osd_sdl_event->type == SDL_KEYDOWN)
   {
    //switch(gb_osd_sdl_event->key.keysym.sym)
    {
     //case SDLK_UP:
     if (checkAndCleanKey(KEY_CURSOR_LEFT))
     {
      if (aReturn>10) aReturn-=10;
      OSDMenuRowsDisplayScroll(ptrValue,aReturn,aMax);
     }
     if (checkAndCleanKey(KEY_CURSOR_RIGHT))
     {
      if (aReturn<(aMax-10)) aReturn+=10;
      OSDMenuRowsDisplayScroll(ptrValue,aReturn,aMax);
     }

     if (checkAndCleanKey(KEY_CURSOR_UP))
     {
      //vga.setTextColor(WHITE,BLACK);
      //vga.setCursor(gb_pos_x_menu,gb_pos_y_menu+((aReturn+1)<<3));
      //vga.print(ptrValue[aReturn]);
      ////SDLprintText(gb_osd_sdl_surface,ptrValue[aReturn],gb_pos_x_menu,gb_pos_y_menu+((aReturn+1)<<3),WHITE,BLACK,1);
      if (aReturn>0) aReturn--;
      OSDMenuRowsDisplayScroll(ptrValue,aReturn,aMax);
      //vga.setTextColor(CYAN,BLUE);
      //vga.setCursor(gb_pos_x_menu,gb_pos_y_menu+((aReturn+1)<<3));
      //vga.print(ptrValue[aReturn]);
      ////SDLprintText(gb_osd_sdl_surface,ptrValue[aReturn],gb_pos_x_menu,gb_pos_y_menu+((aReturn+1)<<3),CYAN,BLUE,1);
      ////break;
     }
     if (checkAndCleanKey(KEY_CURSOR_DOWN))
     {
     //case SDLK_DOWN: 
      //SDLprintText(gb_osd_sdl_surface,ptrValue[aReturn],gb_pos_x_menu,gb_pos_y_menu+((aReturn+1)<<3),WHITE,BLACK,1);
      //vga.setTextColor(WHITE,BLACK);
      //vga.setCursor(gb_pos_x_menu,gb_pos_y_menu+((aReturn+1)<<3));
      //vga.print(ptrValue[aReturn]);
      if (aReturn < (aMax-1)) aReturn++;
      OSDMenuRowsDisplayScroll(ptrValue,aReturn,aMax);
      //vga.setTextColor(CYAN,BLUE);
      //vga.setCursor(gb_pos_x_menu,gb_pos_y_menu+((aReturn+1)<<3));
      //vga.print(ptrValue[aReturn]);
      ////SDLprintText(gb_osd_sdl_surface,ptrValue[aReturn],gb_pos_x_menu,gb_pos_y_menu+((aReturn+1)<<3),CYAN,BLUE,1);
      ////break;
     }
     if (checkAndCleanKey(KEY_ENTER))
     {
      salir= 1;
     }
     //case SDLK_KP_ENTER: case SDLK_RETURN: salir= 1;break;
     if (checkAndCleanKey(KEY_ESC))
     {
      salir=1; aReturn= 255;    
     }
     //case SDLK_ESCAPE: salir=1; aReturn= 255; break;
     //default: break;
    }
    //SDL_Flip(gb_osd_sdl_surface);
    //SDL_PollEvent(gb_osd_sdl_event);
   }  
  }  
 } 
 gb_show_osd_main_menu= 0;

 ClearKeyboard();

 return aReturn;
}

//Menu SNA
void ShowTinyCartMenu()
{
 unsigned char aSelNum;     
 #ifdef use_lib_wifi 
  //unsigned char aSelType;
  //unsigned char aSelNum;
  unsigned char tope;
  int leidos=0;
  //char cadUrl[256];
  if (Check_WIFI() == true)
  {
   //PreparaURL(cadUrl, "/outlist/cart", "", (char*)"cart", "txt");
   PreparaURL(gb_cadUrl, "/outlist/cart", "", (char*)"cart", "txt");   
   #ifdef use_lib_wifi_debug
    //Serial.printf("URL:%s\n",cadUrl);    
    if (gb_use_debug==1) { Serial.printf("URL:%s\r\n",gb_cadUrl); }
   #endif
   ShowStatusWIFI(1);
   //Asignar_URL_stream_WIFI(cadUrl);
   Asignar_URL_stream_WIFI(gb_cadUrl);
   Leer_url_stream_WIFI(&leidos);
   ShowStatusWIFI(0);
   #ifdef use_lib_wifi_debug
    if (gb_use_debug==1) { Serial.printf("Leidos:%d\r\n",leidos); }
   #endif
   tope = gb_size_file_wifi>>3; //DIV 8
   #ifdef use_lib_wifi_debug
    if (gb_use_debug==1) { Serial.printf("Tope:%d\r\n",tope); }
   #endif
   if (tope<1){
    return;
   }
   if (tope>127)
   {
    tope= 127;
   }
   aSelNum = ShowTinyMenuFromWIFI("Cart WIFI",gb_buffer_wifi,tope);
   if (aSelNum == 255){
    return;
   }
   char cadFile[10];
   for (int i=0;i<8;i++)
   {
    cadFile[i]= gb_buffer_wifi[(aSelNum*8)+i];
    if (cadFile[i] ==' '){
     cadFile[i]='\0';
    }
   }
   cadFile[8]='\0';
   #ifdef use_lib_wifi_debug
    if (gb_use_debug==1) { Serial.printf("Select:%d\r\n",aSelNum); }
   #endif
   //PreparaURL(cadUrl, "/outdat/cart/", "", cadFile,"bin");
   PreparaURL(gb_cadUrl, "/outdat/cart", "", cadFile,"chf");
   #ifdef use_lib_wifi_debug
    //Serial.printf("URL:%s\n",cadUrl);    
    if (gb_use_debug==1) { Serial.printf("URL:%s\r\n",gb_cadUrl); }
   #endif 
   ShowStatusWIFI(1);   
   //WIFI changeSna2FlashFromWIFI(cadUrl,1);
   //strcpy(gb_cadUrl,cadUrl);
   ShowStatusWIFI(0);
  }  
 #else
  aSelNum = ShowTinyMenu("CART",gb_list_cart_title,gb_id_cur_cart,max_list_cart);
 #endif 

 if (aSelNum==255)
 {
  return;
 }

 //gb_cartfilename= (char *)gb_list_rom_title[aSelNum];
 gb_force_load_cart= 1;
 gb_id_cur_cart= aSelNum;
 //running= 0; 
}

//Menu ROM
void ShowTinyMachineMenu()
{
 //unsigned char aSelNum;
 //model = ShowTinyMenu("Machine",gb_machine_menu,max_gb_machine_menu);
 //loadroms2FlashModel();
 //switch (aSelNum)
 //{
 // case 0: model= 0; loadroms2FlashModel(0); break;
 // case 1: model= 1; loadroms2FlashModel(1); break;
 // case 2: model= 2; loadroms2FlashModel(2); break;
 // default: model= 0; loadroms2FlashModel(0); break;
 //}
 //vTaskDelay(2);
 //resetz80();
 //resetcrtc();
 //SDL_Delay(2);
}


//Menu resetear
void ShowTinyResetMenu()
{
 unsigned char aSelNum;
 aSelNum= ShowTinyMenu("RESET",gb_reset_menu,0,max_gb_reset_menu);   
 //loadroms2FlashModel();
 //resetz80();
 //resetcrtc(); 

 if ((aSelNum==255)||(aSelNum==2))
 {
   return;
 }

 if (aSelNum == 1)
 {
  if (gb_use_debug==1) { Serial.printf("Reset Hard\r\n"); }  
  ESP.restart();
 }
 else
 {
   gb_force_load_cart=1;
   if (gb_use_debug==1) { Serial.printf("Reset Soft\r\n"); }
 } 
}

//Menu TAPE
/*void ShowTinyTAPEMenu()
{
 unsigned char aSelNum;
 aSelNum = ShowTinyMenu("48K TAPE",gb_list_tapes_48k_title,max_list_tape_48);
 load_tape2Flash(aSelNum);
}

//Play sound tape
void ShowTinySelectTAPEMenu()
{
 unsigned char aSelNum;
 aSelNum = ShowTinyMenu("48K TAPE",gb_list_tapes_48k_title,max_list_tape_48);
 Z80EmuSelectTape(aSelNum);
// gb_play_tape_current = aSelNum;
// gb_play_tape_on_now = 1;
}

//Menu SCREEN
void ShowTinySCRMenu()
{
 unsigned char aSelNum;
 aSelNum = ShowTinyMenu("48K SCREEN",gb_list_scr_48k_title,max_list_scr_48);
 load_scr2Flash(aSelNum);     
}
*/

//Menu velocidad emulador
void ShowTinySpeedMenu()
{
 unsigned char aSelNum;
 unsigned char id=0;
 
 if (gb_auto_delay_cpu==1)
 {
  id = 0;
 }
 else
 {
  switch (gb_delay_tick_cpu_micros)
  {
   case 0:  id= 1; break;    
   case 1:  id= 2; break;
   case 2:  id= 3; break;
   case 4:  id= 4; break;
   case 8:  id= 5; break;
   case 16: id= 6; break;
   case 32: id= 7; break;
   case 64: id= 8; break;
   case 128:id= 9; break;
  }
 }

 aSelNum = ShowTinyMenu("DELAY CPU",gb_delay_cpu_menu,id,max_gb_delay_cpu_menu);
 if ((aSelNum == 255)||(aSelNum == 10))
 {
  return;
 }

 if (aSelNum==0)
 {//Auto delay
  gb_auto_delay_cpu=1;
 }
 else
 {
  gb_auto_delay_cpu=0;
  if (aSelNum==1)
  {
   gb_delay_tick_cpu_micros=0;
  }
  else
  {
   gb_delay_tick_cpu_micros = (1<<(aSelNum-2));
  }
 }
}

void ShowTinyKeyboardPollMenu()
{
 unsigned char aSelNum;
 unsigned char id=0;

 switch (gb_keyboard_cur_poll_ms)
 {
  case 10: id= 0; break;
  case 20: id= 1; break;
  case 30: id= 2; break;
  case 40: id= 3; break;
  case 50: id= 4; break;   
 }

 aSelNum = ShowTinyMenu("POLL ms KEYBOARD",gb_speed_keyboard_poll_menu,id,max_gb_speed_keyboard_poll_menu);
 if ((aSelNum==255)||(aSelNum==5))
 {
  return;
 }

 switch (aSelNum)
 {
  case 0: gb_keyboard_cur_poll_ms= 10; break;
  case 1: gb_keyboard_cur_poll_ms= 20; break;
  case 2: gb_keyboard_cur_poll_ms= 30; break;
  case 3: gb_keyboard_cur_poll_ms= 40; break;
  case 4: gb_keyboard_cur_poll_ms= 50; break;
 }
}


//*****************************************************************
void ShowTinyOSDMenu()
{
 unsigned char aSelNum; 
 unsigned char id= (gb_do_action_key_show_osd==1)? 0: 1;

 aSelNum = ShowTinyMenu("  SHOW OSD", gb_bool_menu_en ,id,max_gb_bool_menu);
 if (aSelNum == 255)
 {//Pulsa ESC vuelve a menu anterior Main menu  
  return;
 }

 gb_do_action_key_show_osd= (aSelNum==0)? 1: 0; 
}

//********************************************************************************************
void ShowTinyDebugShowMenu()
{
 unsigned char aSelNum;
 unsigned char pos= (gb_use_debug==1)?0:1;

 aSelNum = ShowTinyMenu("   DEBUG", gb_bool_menu_en ,pos,max_gb_bool_menu);
 if (aSelNum == 255)
 {//Pulsa ESC vuelve a menu anterior Main menu  
  return;
 }

 gb_use_debug= (aSelNum==0)?1:0; 
}

//****************************************************
void ShowTinyVGAPollMenu()
{
 unsigned char aSelNum;
 unsigned char id=0;
 
 switch (gb_vga_cur_poll_ms)
 {  
  case 16: id= 0; break;
  case 20: id= 1; break;
  case 30: id= 2; break;
  case 40: id= 3; break;
  case 50: id= 4; break;
 }

 aSelNum = ShowTinyMenu("Poll ms VGA",gb_speed_video_poll_menu,id,max_gb_speed_video_poll_menu );
 if ((aSelNum==255)||(aSelNum==4))
 {
  return;
 }

 switch (aSelNum)
 {
  case 0: gb_vga_cur_poll_ms= 16; break;
  case 1: gb_vga_cur_poll_ms= 20; break;
  case 2: gb_vga_cur_poll_ms= 30; break;
  case 3: gb_vga_cur_poll_ms= 40; break;
  case 4: gb_vga_cur_poll_ms= 50; break;  
 }
}

//*********************************
void ShowTinyVideoOfsXMenu()
{
 unsigned char aSelNum;
  
 aSelNum = ShowTinyMenu("Offset X",gb_ofs_x_video_menu,gb_offset_video32_x,max_gb_ofs_x_video_menu);
 if ((aSelNum==255)||(aSelNum==5))
 {
  return;
 }

 gb_offset_video32_x= aSelNum;
}

//********************************************************************************************
void OSDUpdateAnchoAltoVGA(unsigned char modeVideo, unsigned char is8colors)
{
 gb_vga_8colors= is8colors;
     
 switch(modeVideo)
 {
  case video_mode_360x200x70hz_bitluni: case video_mode_360x200x70hz_bitluni_apll_fix:
   gb_vga_ancho= 360;
   gb_vga_alto= 200;
   //gb_vga_yOffset= 2;
   //gb_vga_alto_caracter= 12;
   //gb_vga_emu_xOfs_32= 13;  //360-256= 104 div 2= 52 div 4 = 13   
   //gb_vga_emu_yOfs= 4; //offset y en 8 bits  200-192=8 div 2 = 4
   break;
  
  case video_mode_vga320x200x70hz_bitluni: case video_mode_vga320x200x70hz_fabgl: case video_mode_vga320x200x70hz_bitluni_apll_fix:
   gb_vga_ancho= 320;
   gb_vga_alto= 200;       
   //gb_vga_yOffset= 2;
   //gb_vga_alto_caracter= 12;
   //gb_vga_emu_xOfs_32= 8; //320-256= 64 div 2 = 32 div 4 = 8
   //gb_vga_emu_yOfs= 4; //offset y en 8 bits  200-192=8 div 2 = 4
   break;
   
  case video_mode_vga200x150x70hz_bitluni: case video_mode_vga200x150x70hz_bitluni_apll_fix:
   gb_vga_ancho= 200;
   gb_vga_alto= 150; 
   //gb_vga_yOffset= 16;
   //gb_vga_alto_caracter= 13;
   //gb_vga_emu_xOfs_32= 8; //320-256= 64 div 2 = 32 div 4 = 8
   //gb_vga_emu_yOfs= 24; //offset y en 8 bits  240-192=48 div 2 = 24
   break;       
   
  default: break;
 }

 gb_pos_x_menu= (gb_vga_ancho-((osd_maxcadaux-1)<<3))>>1;
 gb_pos_y_menu= (gb_vga_alto-(gb_osd_max_rows<<3))>>1;
 //128x64  en realidad es 104x64
 gb_add_offset_x= ((gb_vga_ancho-104)>>1)>>2; //((gb_vga_ancho-128)>>1)>>2; //Es 104x64
 gb_add_offset_y= (gb_vga_alto-64)>>1;
  
 //gb_vga_display_offset_left=((gb_vga_ancho-256)/2);
 
 
 //0 "360x200 bitluni(3bpp)",
 //1 "360x200 bitluni apll(3bpp)",
 //2 "320x200 bitluni(3bpp)",
 //3 "320x200 fabgl(3bpp)",
 //4 "320x200 bitluni apll(3bpp)",
 //5 "320x240x60hz bitluni(3bpp)",
 //6 "320x240x60hz fabgl(3bpp)",
 //7 "320x240x60hz bitluni apll(3bpp)",
 
 //8 "360x200 bitluni(6bpp)",
 //9 "360x200 bitluni apll(6bpp)",
 //10 "320x200 bitluni(6bpp)",
 //11 "320x200 fabgl(6bpp)",
 //12 "320x200 bitluni apll(6bpp)",
 //13 "320x240x60hz bitluni(6bpp)",
 //14 "320x240x60hz fabgl(6bpp)",
 //15 "320x240x60hz bitluni apll(6bpp)" 
 
 switch (modeVideo)
 {
  case video_mode_360x200x70hz_bitluni: gb_vga_videomode_cur_menu= 0; /*(is8colors==1)?0:8;*/ break;
  case video_mode_360x200x70hz_bitluni_apll_fix: gb_vga_videomode_cur_menu= 1; /*(is8colors==1)?1:9;*/ break;

  case video_mode_vga320x200x70hz_bitluni: gb_vga_videomode_cur_menu= 2; /*(is8colors==1)?2:10;*/ break;
  case video_mode_vga320x200x70hz_fabgl: gb_vga_videomode_cur_menu= 3; /*(is8colors==1)?3:11;*/ break;
  case video_mode_vga320x200x70hz_bitluni_apll_fix: gb_vga_videomode_cur_menu= 4; /*(is8colors==1)?4:12;*/ break;
  
  case video_mode_vga200x150x70hz_bitluni: gb_vga_videomode_cur_menu= 5; /*(is8colors==1)?5:13;*/ break;  
  case video_mode_vga200x150x70hz_bitluni_apll_fix: gb_vga_videomode_cur_menu= 7; /*(is8colors==1)?7:15;*/ break;
  
  default:break;
 }
 
 if (gb_use_debug==1){ Serial.printf("OSDUpdateAnchoAltoVGA mode:%d ancho:%d alto:%d id:%d 8colors:%d\r\n",modeVideo,gb_vga_ancho,gb_vga_alto,gb_vga_videomode_cur_menu,gb_vga_8colors); }
 //fflush(stdout);
}

//****************************************************
void ShowTinyVideoModeMenu()
{  
 unsigned char aSelNum;
 unsigned char is8colors=0;
 unsigned char usepllcteforce=0;
 unsigned char usecustompll=0;
 unsigned int p0=0;
 unsigned int p1=0;
 unsigned int p2=0;
 unsigned int p3=0; 

 //static const unsigned char pin_config8[] = {  
 // PIN_RED_HIGH,
 // PIN_GREEN_HIGH,  
 // PIN_BLUE_HIGH,
 // 255,
 // 255,
 // 255,
 // PIN_HSYNC,
 // PIN_VSYNC
 //};  
 //static const unsigned char pin_config64[] = {  
 // PIN_RED_LOW,
 // PIN_RED_HIGH,
 // PIN_GREEN_LOW,
 // PIN_GREEN_HIGH,
 // PIN_BLUE_LOW,
 // PIN_BLUE_HIGH,
 // PIN_HSYNC,
 // PIN_VSYNC
 //};

 aSelNum = ShowTinyMenu(" VIDEO MODE", gb_video_mode_menu, gb_vga_videomode_cur_menu ,max_gb_video_mode_menu);
 
 if ((aSelNum==255)||(aSelNum==7))
 {//Pulsa ESC vuelve a menu anterior principal
  //gb_show_osd_main_menu= 0;
  //gb_id_menu_cur= id_menu_video_options;
  return; 
 }     


 if (gb_use_debug==1){ Serial.printf("video aSelNum:%d\r\n",aSelNum); }
 
 switch (aSelNum)
 {
//  case 0: gb_vga_videomode_cur= 0; is8colors=1; gb_ptrVideo_cur= VgaMode_vga_mode_360x200; usepllcteforce=0; usecustompll=0; break; //360x200x70hz bitluni(3bpp)
//  case 1: gb_vga_videomode_cur= 1; is8colors=1; gb_ptrVideo_cur= VgaMode_vga_mode_360x200; usepllcteforce=0; usecustompll=1; break; //360x200x70hz bitluni apll(3bpp)
//  case 2: gb_vga_videomode_cur= 2; is8colors=1; gb_ptrVideo_cur= VgaMode_vga_mode_320x200; usepllcteforce=0; usecustompll=0; break; //320x200x70hz bitluni(3bpp)
//  case 3: gb_vga_videomode_cur= 3; is8colors=1; gb_ptrVideo_cur= VgaMode_vga_mode_320x200; usepllcteforce=1; p0=0x00AE; p1=0x00CF; p2=0x0004; p3=0x0005; usecustompll=0; break; //320x200x70hz fabgl(3bpp)
//  case 4: gb_vga_videomode_cur= 4; is8colors=1; gb_ptrVideo_cur= VgaMode_vga_mode_320x200; usepllcteforce=0; usecustompll=1; break; //320x200x70hz bitluni apll(3bpp)
//  case 5: gb_vga_videomode_cur= 5; is8colors=1; gb_ptrVideo_cur= VgaMode_vga_mode_320x240; usepllcteforce=0; usecustompll=0; break; //320x240x60hz bitluni(3bpp)
//  case 6: gb_vga_videomode_cur= 6; is8colors=1; gb_ptrVideo_cur= VgaMode_vga_mode_320x240; usepllcteforce=1; p0=0x000A; p1=0x0057; p2=0x0007; p3=0x0007; usecustompll=0; break; //320x240x60hz fabgl(3bpp)
//  case 7: gb_vga_videomode_cur= 7; is8colors=1; gb_ptrVideo_cur= VgaMode_vga_mode_320x240; usepllcteforce=0; usecustompll=1; break; //320x240x60hz bitluni apll(3bpp)

  case 0: gb_vga_videomode_cur= 0; is8colors=0; gb_ptrVideo_cur= VgaMode_vga_mode_360x200; usepllcteforce=0; usecustompll=0; break;
  case 1: gb_vga_videomode_cur= 1; is8colors=0; gb_ptrVideo_cur= VgaMode_vga_mode_360x200; usepllcteforce=0; usecustompll=1; break;
  case 2: gb_vga_videomode_cur= 2; is8colors=0; gb_ptrVideo_cur= VgaMode_vga_mode_320x200; usepllcteforce=0; usecustompll=0; break;
  case 3: gb_vga_videomode_cur= 3; is8colors=0; gb_ptrVideo_cur= VgaMode_vga_mode_320x200; usepllcteforce=1; p0=0x00AE; p1=0x00CF; p2=0x0004; p3=0x0005; usecustompll=0; break;
  case 4: gb_vga_videomode_cur= 4; is8colors=0; gb_ptrVideo_cur= VgaMode_vga_mode_320x200; usepllcteforce=0; usecustompll=1; break;
  case 5: gb_vga_videomode_cur= 5; is8colors=0; gb_ptrVideo_cur= VgaMode_vga_mode_200x150; usepllcteforce=0; usecustompll=0; break;  
  case 6: gb_vga_videomode_cur= 6; is8colors=0; gb_ptrVideo_cur= VgaMode_vga_mode_200x150; usepllcteforce=0; usecustompll=1; break;
  
  default: break;
 } 

 //OSDClearPantallaReal(); //borro primero la pantalla anterior 
 SDLClear();

 OSDUpdateAnchoAltoVGA(gb_vga_videomode_cur, is8colors);


 //Set Modo video BEGIN
 SetVideoInterrupt(0);
 delay(100);

 vga_free(0); //libera la mitad RAM
 delay(100);

 FreeInterrupt();
 delay(100);

 if (gb_use_debug==1){ Serial.printf("Trace - vga_init\r\n"); }
 //vga_init(pin_config,gb_ptrVideo_cur,false,usepllcteforce,p0,p1,p2,p3,usecustompll);
 vga_init(pin_config,gb_ptrVideo_cur,false,usepllcteforce,p0,p1,p2,p3,usecustompll,is8colors, gb_vga_videomode_cur); //vga_init((is8colors==1)?pin_config8:pin_config64,gb_ptrVideo_cur,false,usepllcteforce,p0,p1,p2,p3,usecustompll,is8colors, gb_vga_videomode_cur);
 if (gb_use_debug==1){ Serial.printf("usepllcteforce:%d usecustompll:%d\r\n",usepllcteforce,usecustompll); }
 if (gb_use_debug==1){ Serial.printf("Trace - SetVideoInterrupt\r\n"); }
 //SetVideoInterrupt(1);    

 gb_sync_bits= vga_get_sync_bits();
 gb_buffer_vga = vga_get_framebuffer();
 gb_buffer_vga32=(unsigned int **)gb_buffer_vga;
 PreparaColorVGA(); //Llamar despues de tener gb_sync_bits
 //vdp_RecalculaPaleta();
 SDLClear();

 //Set Modo video END

 //PreparaPaleta(); 
 //gb_id_menu_cur= id_menu_video_mode;
 
 if (gb_use_debug==1) { Serial.printf("Free mem:%d\r\n", ESP.getFreeHeap()); }
}


//********************************************************************************************
void ShowTinyVideoPALNTSCMenu()
{
 unsigned char aSelNum;
 unsigned char idPal= (gb_use_mode_pal==1)? 0: 1;

 aSelNum = ShowTinyMenu("  PAL/NTSC ", gb_video_palntsc_menu_en,idPal,max_gb_video_palntsc_menu);
 
 if (aSelNum==255)
 {//Pulsa ESC vuelve a menu anterior Video Options  
  return; 
 }

 gb_use_mode_pal= (aSelNum==0)? 1:0;
 gb_vga_cur_poll_ms= (gb_use_mode_pal==1)? 20: 16;
 //if (gb_use_debug==1)
 //{ 
 // if (gb_use_mode_pal==1){ Serial.printf("Set mode PAL\r\n"); }
 // else{ Serial.printf("Set mode NTSC\r\2222222n"); }
 //}
 //gb_show_osd_main_menu=0;
}


//********************************************************
void ShowTinyVGAOptions()
{
 unsigned char aSelNum;
 aSelNum = ShowTinyMenu("VIDEO OPTIONS", gb_video_options_menu,0, max_gb_video_options_menu); 
 switch (aSelNum)
 {
  case 0: ShowTinyVideoModeMenu(); break;
  case 1: ShowTinyVideoPALNTSCMenu(); break;
  case 2: ShowTinyVGAPollMenu(); break;
  case 3: ShowTinyVideoOfsXMenu(); break;
 }
}



//Ajustar pantalla
//void ShowTinyScreenAdjustMenu()
//{
// unsigned char aSelNum, auxCol; 
// aSelNum= ShowTinyMenu("Screen Adjust",gb_osd_screen,max_gb_osd_screen);
// auxCol= ShowTinyMenu("Pixels",gb_osd_screen_values,max_gb_osd_screen_values);
// auxCol = auxCol<<1; //x2
 //gb_screen_xOffset = auxCol; 
 /*switch (aSelNum)
 {
  case 2:
   //OSD_PreparaPaleta8Colores();
   OSD_PreparaPaleta64para8Colores();
   memcpy(gb_cache_zxcolor,gb_const_colornormal8,8);
   #ifdef use_lib_use_bright
    memcpy(gb_cache_zxcolor_bright,gb_const_colornormal8_bright,8);
   #endif
   SDL_SetPalette(gb_osd_sdl_surface, SDL_LOGPAL|SDL_PHYSPAL, gb_osd_sdl_palette, 0, 256);
   return;
   break;
  case 3:
   OSD_PreparaPaleta64para8Colores();
   memcpy(gb_cache_zxcolor,gb_const_monoBlue8,8);
   #ifdef use_lib_use_bright
    memcpy(gb_cache_zxcolor_bright,gb_const_monoBlue8_bright,8);
   #endif 
   SDL_SetPalette(gb_osd_sdl_surface, SDL_LOGPAL|SDL_PHYSPAL, gb_osd_sdl_palette, 0, 256);
   //for (int k=0;k<256;k++)
   // printf("%d %d %d\n",gb_osd_sdl_palette[k].r,gb_osd_sdl_palette[k].g,gb_osd_sdl_palette[k].b);
   //for (int k=0;k<8;k++)
   // printf("%d ",gb_cache_zxcolor[k]);
   //printf("\n");    
   return;
   break;
  case 4:
   OSD_PreparaPaleta64para8Colores();   
   memcpy(gb_cache_zxcolor,gb_const_monoGreen8,8);
   #ifdef use_lib_use_bright
    memcpy(gb_cache_zxcolor_bright,gb_const_monoGreen8_bright,8);
   #endif 
   SDL_SetPalette(gb_osd_sdl_surface, SDL_LOGPAL|SDL_PHYSPAL, gb_osd_sdl_palette, 0, 256);
   return;
   break;
  case 5:
   OSD_PreparaPaleta64para8Colores();   
   memcpy(gb_cache_zxcolor,gb_const_monoRed8,8);
   #ifdef use_lib_use_bright
    memcpy(gb_cache_zxcolor_bright,gb_const_monoRed8_bright,8);
   #endif 
   SDL_SetPalette(gb_osd_sdl_surface, SDL_LOGPAL|SDL_PHYSPAL, gb_osd_sdl_palette, 0, 256);
   return;
  case 6:
   OSD_PreparaPaleta64para8Colores();   
   memcpy(gb_cache_zxcolor,gb_const_grey8,8);
   #ifdef use_lib_use_bright
    memcpy(gb_cache_zxcolor_bright,gb_const_grey8_bright,8);
   #endif 
   SDL_SetPalette(gb_osd_sdl_surface, SDL_LOGPAL|SDL_PHYSPAL, gb_osd_sdl_palette, 0, 256);
   return;
   break;          
 }
 auxCol= ShowTinyMenu("Cols or pixels",gb_osd_screen_values,max_gb_osd_screen_values);
 switch (aSelNum)
 {
  case 0: gb_screen_xIni = -(auxCol<<3); break;
  case 1: gb_screen_yIni = (auxCol<=3)? (-auxCol):(-3); break;  
  default: break;
 }
 */
//}

//void ShowTinyCOMMenu()
//{
// unsigned char aSelNum;     
// aSelNum = ShowTinyMenu("COM",gb_list_com_title,max_list_com);
//
// //gb_cartfilename= (char *)gb_list_rom_title[aSelNum];
// gb_force_load_com= 1;
// gb_id_cur_com= aSelNum;
// //running= 0;
//}

//void ShowTinyMouseMenu()
//{
// #ifdef use_lib_amx_mouse    
//  unsigned char aSelNum;
//  aSelNum = ShowTinyMenu("Mouse Buttons",gb_osd_mouse_menu,max_gb_osd_mouse_menu); 
//  switch (aSelNum)
//  {
//   case 0: gb_force_left_handed= 0; break; //diestro
//   case 1: gb_force_left_handed= 1; break; //zurdo
//   default: break;
//  }
// #endif
// vTaskDelay(2);
//}


//*******************************************
void SDLActivarOSDMainMenu()
{     
 gb_show_osd_main_menu= 1;   
}



//Very small tiny osd
void do_tinyOSD() 
{
 int auxVol;
 int auxFrec;  
 unsigned char aSelNum;
 if (checkAndCleanKey(KEY_F1))
 {
  gb_show_osd_main_menu= 1;
  #ifdef use_lib_sound_ay8912  
   gb_silence_all_channels = 1;
  #endif    
  return;
 }

 if (gb_show_osd_main_menu == 1)
 {
  ClearKeyboard();

  auxVol= gb_volumen01;
  auxFrec= gb_frecuencia01;
  gb_volumen01= gb_frecuencia01=0;
  //Audio PWM ledcWriteTone(1,0);
  //#ifdef use_lib_audio_tone32
  // Tone32_noTone(SPEAKER_PIN, SPEAKER_CHANNEL);
  //#endif

  aSelNum = ShowTinyMenu("MAIN MENU",gb_main_menu,0,max_gb_main_menu);
  switch (aSelNum)
  {
   case 0:
    ShowTinyCartMenu();
    gb_show_osd_main_menu=0;
    break;
   case 1:
    ShowTinyResetMenu();
    gb_show_osd_main_menu=0;
    break;
   case 2: ShowTinySpeedMenu();
    gb_show_osd_main_menu=0;
    break;
   case 3: ShowTinyVGAOptions();
    gb_show_osd_main_menu=0;
    break;
   case 4: ShowTinyKeyboardPollMenu();
    gb_show_osd_main_menu=0;
    break;
   case 5: ShowTinyOSDMenu();
    gb_show_osd_main_menu=0;
    break;   
   case 6: ShowTinyDebugShowMenu();
    gb_show_osd_main_menu=0;
    break;
   default: break;
  }


  ClearKeyboard();

  gb_volumen01= auxVol;
  gb_frecuencia01= auxFrec;  
  //Audio PWM ledcWriteTone(1,auxFrec);
  //#ifdef use_lib_audio_tone32
  // Tone32_tone(SPEAKER_PIN, gb_frecuencia01, 0, SPEAKER_CHANNEL);
  //#endif  
  
 }

 SDLClear();
 
 #ifdef use_lib_sound_ay8912
  gb_silence_all_channels = 0;
 #endif 
}

