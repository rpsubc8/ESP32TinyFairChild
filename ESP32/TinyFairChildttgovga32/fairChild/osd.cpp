#include "gbConfig.h"
#include "gbGlobals.h"
#include "hardware.h"
#include "fairChild.h"
#include "osd.h"
//#include "dataFlash/gbcom.h"
#include "hardware.h"
//#ifdef use_lib_audio_tone32
// #include "Tone32.h"
//#endif
#include "PS2Kbd.h"
#include "gb_sdl_font8x8.h"
#include "video.h"
#ifndef use_lib_wifi
 #include "dataFlash/gbcart.h"
#endif 
#ifdef use_lib_wifi
 #include "gbWifiConfig.h"
 #include "gbWifi.h" 
#endif

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


#define max_gb_main_menu 7
#ifdef use_lib_wifi
 const char * gb_main_menu[max_gb_main_menu]={
  "Load CART WIFI",
  "Reset",
  "Delay CPU",
  "Video Poll",
  "Keyboard Poll",
  "Exit",
  "Return"
 };
#else
 const char * gb_main_menu[max_gb_main_menu]={
  "Load CART",
  "Reset",
  "Delay CPU",
  "Video Poll",
  "Keyboard Poll",
  "Exit",
  "Return"
 };
#endif 

//#define max_gb_machine_menu 3
//const char * gb_machine_menu[max_gb_machine_menu]={
// "464",
// "664",
// "6128"
//};


#define max_gb_delay_cpu_menu 10
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
 "128"
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

#define max_gb_speed_video_poll_menu 4
const char * gb_speed_video_poll_menu[max_gb_speed_video_poll_menu]={
 "20",
 "30",
 "40",
 "50"
};

#define max_gb_speed_keyboard_poll_menu 5
const char * gb_speed_keyboard_poll_menu[max_gb_speed_keyboard_poll_menu]={
 "10",
 "20",
 "30",
 "40",
 "50"
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

#define max_gb_reset_menu 2
const char * gb_reset_menu[max_gb_reset_menu]={
 "Soft",
 "Hard"
};


#define gb_pos_x_menu 40
#define gb_pos_y_menu 20
#define gb_osd_max_rows 10

void SDLClear()
{
 //for (int y=0; y<(auxSurface->w); y++)
 // for (int x=0; x<(auxSurface->h); x++)
 //  SDLputpixel(auxSurface,x,y,1);
 //for (int y=0; y<200; y++)
 // for (int x=0; x<320; x++)   
 for (int y=0; y<150; y++)
  for (int x=0; x<200; x++)    
   jj_fast_putpixel(x,y,0);
   //SDLputpixel(auxSurface,x,y,3); 
}

//*************************************************************************************
void SDLprintCharOSD(char car,int x,int y,unsigned char color,unsigned char backcolor)
{ 
// unsigned char aux = gb_sdl_font_6x8[(car-64)];
 int auxId = car << 3; //*8
 unsigned char aux;
 unsigned char auxBit,auxColor;
 for (unsigned char j=0;j<8;j++)
 {
  aux = gb_sdl_font_8x8[auxId + j];
  for (int i=0;i<8;i++)
  {
   auxColor= ((aux>>i) & 0x01);
   //SDLputpixel(surface,x+(6-i),y+j,(auxColor==1)?color:backcolor);
   jj_fast_putpixel(x+(6-i),y+j,(auxColor==1)?color:backcolor);
  }
 }
}

void SDLprintText(const char *cad,int x, int y, unsigned char color,unsigned char backcolor)
{
//SDL_Surface *surface,
// gb_sdl_font_6x8
 int auxLen= strlen(cad);
 if (auxLen>50)
  auxLen=50;
 for (int i=0;i<auxLen;i++)
 {
  SDLprintCharOSD(cad[i],x,y,color,backcolor);
  x+=7;
 }
}

void OSDMenuRowsDisplayScroll(const char **ptrValue,unsigned char currentId,unsigned char aMax)
{//Dibuja varias lineas
 for (int i=0;i<gb_osd_max_rows;i++)
  SDLprintText("                    ",gb_pos_x_menu,gb_pos_y_menu+8+(i<<3),0,0);
 
 for (int i=0;i<gb_osd_max_rows;i++)
 {
  if (currentId >= aMax)
   break;
  //SDLprintText(gb_osd_sdl_surface,ptrValue[currentId],gb_pos_x_menu,gb_pos_y_menu+8+(i<<3),((i==0)?CYAN:WHITE),((i==0)?BLUE:BLACK),1);
  SDLprintText(ptrValue[currentId],gb_pos_x_menu,gb_pos_y_menu+8+(i<<3),((i==0)?ID_COLOR_WHITE:ID_COLOR_WHITE),((i==0)?ID_COLOR_VIOLETA:ID_COLOR_BLACK));
  currentId++;
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
  char cadName8[10];
  cadName8[8]='\0';
  for (int i=0;i<gb_osd_max_rows;i++)
  {
   SDLprintText("                    ",gb_pos_x_menu,gb_pos_y_menu+8+(i<<3),ID_COLOR_BLACK,ID_COLOR_BLACK);
  }
 
  for (int i=0;i<gb_osd_max_rows;i++)
  {
   if (currentId >= aMax)
    break;
   memcpy(cadName8, &ptrBuffer[(currentId*8)], 8);
   cadName8[8]='\0';
//   SDLprintText(ptrValue[currentId],gb_pos_x_menu,gb_pos_y_menu+8+(i<<3),((i==0)?ID_COLOR_WHITE:ID_COLOR_WHITE),((i==0)?ID_COLOR_MAGENTA:ID_COLOR_BLACK));
   //SDLprintText((const char*)cadName8,gb_pos_x_menu,gb_pos_y_menu+8+(i<<3),((i==0)?ID_COLOR_WHITE:ID_COLOR_WHITE),((i==0)?ID_COLOR_MAGENTA:ID_COLOR_BLACK));
   SDLprintText((const char*)cadName8,gb_pos_x_menu,gb_pos_y_menu+8+(i<<3),((i==0)?ID_COLOR_WHITE:ID_COLOR_WHITE),((i==0)?ID_COLOR_VIOLETA:ID_COLOR_BLACK));
   currentId++;
  }     
 }

 //**********************************************************************************
 unsigned char ShowTinyMenuFromWIFI(const char *cadTitle,unsigned char *ptrBuffer,unsigned char aMax)
 {
  unsigned char aReturn=0;
  unsigned char salir=0;

  SDLClear();
  SDLprintText("FreeChaF by Ackerman",gb_pos_x_menu-(4<<3),gb_pos_y_menu-16,ID_COLOR_WHITE,ID_COLOR_BLACK);
  for (int i=0;i<14;i++)
  {
   SDLprintCharOSD(' ',gb_pos_x_menu+(i<<3),gb_pos_y_menu,ID_COLOR_BLACK,ID_COLOR_WHITE);   
  }
  SDLprintText(cadTitle,gb_pos_x_menu,gb_pos_y_menu,ID_COLOR_BLACK,ID_COLOR_WHITE);
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
  return aReturn;
 }
#endif


//Maximo 256 elementos
unsigned char ShowTinyMenu(const char *cadTitle,const char **ptrValue,unsigned char aMax)
{
 unsigned char aReturn=0;
 unsigned char salir=0;
 SDLClear();
 SDLprintText("FreeChaF by Ackerman",gb_pos_x_menu-(4<<3),gb_pos_y_menu-16,ID_COLOR_WHITE,ID_COLOR_BLACK);
 //for (int i=0;i<20;i++) 
 for (int i=0;i<14;i++)
 {
  SDLprintCharOSD(' ',gb_pos_x_menu+(i<<3),gb_pos_y_menu,ID_COLOR_BLACK,ID_COLOR_WHITE);
 }
 SDLprintText(cadTitle,gb_pos_x_menu,gb_pos_y_menu,ID_COLOR_BLACK,ID_COLOR_WHITE);

 OSDMenuRowsDisplayScroll(ptrValue,0,aMax);
 
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
    Serial.printf("URL:%s\n",gb_cadUrl);    
   #endif
   ShowStatusWIFI(1);
   //Asignar_URL_stream_WIFI(cadUrl);
   Asignar_URL_stream_WIFI(gb_cadUrl);
   Leer_url_stream_WIFI(&leidos);
   ShowStatusWIFI(0);
   #ifdef use_lib_wifi_debug
    Serial.printf("Leidos:%d\n",leidos);
   #endif
   tope = gb_size_file_wifi>>3; //DIV 8
   #ifdef use_lib_wifi_debug
    Serial.printf("Tope:%d\n",tope);
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
    Serial.printf("Select:%d\n",aSelNum);
   #endif
   //PreparaURL(cadUrl, "/outdat/cart/", "", cadFile,"bin");
   PreparaURL(gb_cadUrl, "/outdat/cart", "", cadFile,"chf");
   #ifdef use_lib_wifi_debug
    //Serial.printf("URL:%s\n",cadUrl);    
    Serial.printf("URL:%s\n",gb_cadUrl);    
   #endif 
   ShowStatusWIFI(1);   
   //WIFI changeSna2FlashFromWIFI(cadUrl,1);
   //strcpy(gb_cadUrl,cadUrl);
   ShowStatusWIFI(0);
  }
 #else
  aSelNum = ShowTinyMenu("Cart",gb_list_cart_title,max_list_cart);
 #endif 

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
 aSelNum= ShowTinyMenu("Reset",gb_reset_menu,max_gb_reset_menu);   
 //loadroms2FlashModel();
 //resetz80();
 //resetcrtc(); 
 if (aSelNum == 1)
 {
  ESP.restart();
 }
 else
 {
   gb_force_load_cart=1;
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
 aSelNum = ShowTinyMenu("Delay CPU",gb_delay_cpu_menu,max_gb_delay_cpu_menu);
 if (aSelNum == 255)
  return;
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
 aSelNum = ShowTinyMenu("Poll ms Keyboard",gb_speed_keyboard_poll_menu,max_gb_speed_keyboard_poll_menu);
 switch (aSelNum)
 {
  case 0: gb_keyboard_cur_poll_ms= 10; break;
  case 1: gb_keyboard_cur_poll_ms= 20; break;
  case 2: gb_keyboard_cur_poll_ms= 30; break;
  case 3: gb_keyboard_cur_poll_ms= 40; break;
  case 4: gb_keyboard_cur_poll_ms= 50; break;
 }
}

void ShowTinyVGAPollMenu()
{
 unsigned char aSelNum;
 aSelNum = ShowTinyMenu("Poll ms VGA",gb_speed_video_poll_menu,max_gb_speed_video_poll_menu );
 switch (aSelNum)
 {
  case 0: gb_vga_cur_poll_ms= 20; break;
  case 1: gb_vga_cur_poll_ms= 30; break;
  case 2: gb_vga_cur_poll_ms= 40; break;
  case 3: gb_vga_cur_poll_ms= 50; break;  
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
  auxVol= gb_volumen01;
  auxFrec= gb_frecuencia01;
  gb_volumen01= gb_frecuencia01=0;
  //Audio PWM ledcWriteTone(1,0);
  //#ifdef use_lib_audio_tone32
  // Tone32_noTone(SPEAKER_PIN, SPEAKER_CHANNEL);
  //#endif

  aSelNum = ShowTinyMenu("MAIN MENU",gb_main_menu,max_gb_main_menu);
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
   case 3: ShowTinyVGAPollMenu();
    gb_show_osd_main_menu=0;
    break;
   case 4: ShowTinyKeyboardPollMenu();
    gb_show_osd_main_menu=0;
    break;
   default: break;
  }

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

