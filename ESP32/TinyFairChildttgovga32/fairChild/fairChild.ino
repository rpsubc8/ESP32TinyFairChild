//Port FreeChaF emulator to TTGO VGA32 by ackerman:
//Author: ackerman
//License: WTFPL
// Load Roms
// VGA MOD360x200, MODE320x200, MODE200x150
// Mode 64 colors RGB 6 bits
// VGA Tiny library bitluni 0.3.3 (Ricardo Massaro) mod convert C
// Arduino compatible ESP32 version 1.0.0, 2.0.0 and 3.3.0
// gbConfig options configuration compile
// Keyboard console
//  0,1,2,3
// Keyboard gamer 1
//  Left,Right,Up,Down   o,p
// Keyboard 2
//  a,d,w,s   c,v
//Support load cart WIFI server web

#include "gbConfig.h"
#include "gbGlobals.h"
#include "PS2Kbd.h"
#include <Arduino.h>
//#ifdef use_lib_audio_tone32
// #include "Tone32.h"
//#else 
 #ifdef use_lib_audio_ticker
  //no se usa  #include <Ticker.h>
 #endif 
//#endif 
#include "fairChild.h"
#include "gbCompileOpt.h"
//#ifdef use_lib_tinybitluni_fast
//#else
// //#include "MartianVGA.h"
// //#include "def/Font.h"
//#endif 
//#include "hardware.h"
#include "driver/timer.h"
#include "soc/timer_group_struct.h"
#include "libretro.h"
#include "video.h"
#include "controller.h"
#include "osd.h"
#include "soc/gpio_struct.h" //Para speaker y teclado rapido
//#include "PS2KeyCode.h"

#ifdef use_lib_wifi
 #include "gbWifi.h"
 #include <WiFi.h>
 //#include <WiFiMulti.h>
 #include <HTTPClient.h>
 #include "gbWifiConfig.h"
 //#include <esp_wifi.h>
 //WiFiMulti wifiMulti;
 HTTPClient http;
 WiFiClient * stream;
 
 unsigned char gb_buffer_wifi[1024]; //128 ficheros * 8
 int gb_size_file_wifi=0; 
 char gb_cadUrl[128]=""; 
#endif

//#include "dataFlash/gbrom.h"
//#include "PS2Boot/PS2KeyCode.h"
#ifdef use_lib_tinybitluni_fast
 #include "vga_6bit.h"
 // VGA output pins
 //#define PIN_RED_LOW    21
 //#define PIN_RED_HIGH   22
 //#define PIN_GREEN_LOW  18
 //#define PIN_GREEN_HIGH 19
 //#define PIN_BLUE_LOW   4
 //#define PIN_BLUE_HIGH  5
 //#define PIN_HSYNC      23
 //#define PIN_VSYNC      15

 #ifdef use_lib_vga8colors
  //DAC 3 bits 8 colores
  // 3 bit pins  
 const unsigned char pin_config[] = {  
  PIN_RED_HIGH,
  PIN_GREEN_HIGH,  
  PIN_BLUE_HIGH,
  255,
  255,
  255,
  PIN_HSYNC,
  PIN_VSYNC
 };
 #else
  //DAC 6 bits 64 colores
  const unsigned char pin_config[] = {
   PIN_RED_LOW,
   PIN_RED_HIGH,
   PIN_GREEN_LOW,
   PIN_GREEN_HIGH,
   PIN_BLUE_LOW,
   PIN_BLUE_HIGH,
   PIN_HSYNC,
   PIN_VSYNC
  };
 #endif 

#endif

#ifdef use_lib_tinybitluni_fast 
 //unsigned char **framebuffer = vga_get_framebuffer();
 //unsigned char **gb_buffer_vga= vga_get_framebuffer();
 unsigned char gb_sync_bits;
#else 
 #ifdef use_lib_bitluni_3bpp
  #ifdef use_lib_bitluni_low_memory
   VGA3BitI vga;
  #else
   VGA3Bit vga;
  #endif 
 #else 
  VGA6Bit vga;
 #endif 
#endif 

//#ifdef use_lib_audio_tone32
//#else
 #ifdef use_lib_audio_ticker
  //no se usa Ticker gb_ticker_callback;
  
  hw_timer_t * gb_timer = NULL;
 #endif 
//#endif

volatile unsigned int gb_pulsos_onda=0;
//volatile unsigned int gb_cont_my_callbackfunc=0;
volatile unsigned char gb_estado_sonido=0;
volatile unsigned char speaker_pin_estado=LOW;

volatile int gb_frecuencia01=0;
volatile int gb_dutty_ch01=0;
volatile int gb_volumen01=0;
volatile int gb_duracion01=0;


unsigned char gb_force_load_cart=0;
unsigned char gb_id_cur_cart=0;

unsigned char gb_cpunoexe=0;
unsigned int gb_cpunoexe_timer_ini;
unsigned int tiempo_ini_cpu,tiempo_fin_cpu;
unsigned int total_tiempo_ms_cpu;
unsigned int tiene_que_tardar;

unsigned int tiempo_ini_vga,tiempo_cur_vga;

unsigned int tiempo_ini_keyboard,tiempo_cur_keyboard;

unsigned char **gb_buffer_vga;
unsigned int **gb_buffer_vga32;

unsigned char gb_delay_tick_cpu_micros= use_lib_delay_tick_cpu_micros;
unsigned char gb_auto_delay_cpu= use_lib_delay_tick_cpu_auto;

unsigned char tiempo_vga= 0;
unsigned int gb_cpu_timer_before=0,gb_cpu_timer_cur=0;
unsigned int jj_ini_cpu,jj_end_cpu,jj_ini_vga,jj_end_vga;
unsigned int gb_max_cpu_ticks,gb_min_cpu_ticks,gb_cur_cpu_ticks;
unsigned int gb_max_vga_ticks,gb_min_vga_ticks,gb_cur_vga_ticks;

unsigned char gb_keyboard_cur_poll_ms= gb_ms_keyboard;
unsigned char gb_vga_cur_poll_ms= gb_ms_vga;

unsigned char gb_use_debug=1;
unsigned char gb_vga_videomode_cur_menu=0; //El que seleccionas en menu OSD
unsigned char gb_pos_x_menu=0;
unsigned char gb_pos_y_menu=0;
unsigned char gb_add_offset_x=0;
unsigned char gb_add_offset_y=0; 
unsigned char gb_offset_video32_x=0; //x offset 32 bits 4 pixels
unsigned char gb_do_action_key_show_osd=0;
unsigned char gb_use_mode_pal=1; //PAL o NTSC
unsigned char gb_use_cpu_delay=1;
unsigned char gb_fps_cur=0;
unsigned char gb_fps_cur_videotask_dump=0;

#ifdef use_lib_vga8colors
 unsigned char gb_vga_8colors=1; //1 8 colores, 0 64 colores
#else
 unsigned char gb_vga_8colors=0;
#endif 

#ifdef use_lib_360x200
 const unsigned int *gb_ptrVideo_cur= VgaMode_vga_mode_360x200;
#else
 #ifdef use_lib_320x200
  const unsigned int *gb_ptrVideo_cur= VgaMode_vga_mode_320x200;
 #else
  #ifdef use_lib_200x150
   const unsigned int *gb_ptrVideo_cur= VgaMode_vga_mode_200x150;
  #endif
 #endif
#endif

#ifdef use_lib_320x240
 //unsigned char gb_vga_display_offset_left=((320-256)/2); //revisar quitar calcula OSDUpdateAnchoAltoVGA
 unsigned short int gb_vga_ancho= 320;
 unsigned short int gb_vga_alto= 240;
 //unsigned short int gb_vga_yOffset= 16;
 //unsigned char gb_vga_alto_caracter= 13;
 //unsigned char gb_vga_emu_xOfs_32= 8; //320-256= 64 div 2 = 32 div 4 = 8
 //unsigned char gb_vga_emu_yOfs= 24; //offset y en 8 bits  240-192=48 div 2 = 24
#else 
 #ifdef use_lib_320x200
  //unsigned char gb_vga_display_offset_left=((320-256)/2);
  unsigned short int gb_vga_ancho= 320;
  unsigned short int gb_vga_alto= 200;  
  //unsigned short int gb_vga_yOffset= 2;
  //unsigned char gb_vga_alto_caracter= 12;
  //unsigned char gb_vga_emu_xOfs_32= 8; //320-256= 64 div 2 = 32 div 4 = 8
  //unsigned char gb_vga_emu_yOfs= 4; //offset y en 8 bits  200-192=8 div 2 = 4
 #else
  #ifdef use_lib_360x200
   //unsigned char gb_vga_display_offset_left=((360-256)/2);
   unsigned short int gb_vga_ancho= 360;
   unsigned short int gb_vga_alto= 200;   
   //unsigned short int gb_vga_yOffset= 2;
   //unsigned char gb_vga_alto_caracter= 12;
   //unsigned char gb_vga_emu_xOfs_32= 13; //offset x en 32 bits 360-256= 104 div 2= 52 div 4 = 13
   //unsigned char gb_vga_emu_yOfs= 4; //offset y en 8 bits  200-192=8 div 2 = 4
  #else
   #ifdef use_lib_200x150
    unsigned short int gb_vga_ancho= 200;
    unsigned short int gb_vga_alto= 150;   
   #endif 
  #endif
 #endif 
#endif


#ifdef use_lib_vga360x200x70hz_bitluni               
 unsigned char gb_vga_videomode_cur= video_mode_360x200x70hz_bitluni; //0
#else
 #ifdef use_lib_vga360x200x70hz_bitluni_apll_fix
  unsigned char gb_vga_videomode_cur= video_mode_360x200x70hz_bitluni_apll_fix; //1
 #else
  #ifdef use_lib_vga320x200x70hz_bitluni
   unsigned char gb_vga_videomode_cur= video_mode_vga320x200x70hz_bitluni; //2
  #else
   #ifdef use_lib_vga320x200x70hz_fabgl
    unsigned char gb_vga_videomode_cur= video_mode_vga320x200x70hz_fabgl; //3
   #else
    #ifdef use_lib_vga320x200x70hz_bitluni_apll_fix
     unsigned char gb_vga_videomode_cur= video_mode_vga320x200x70hz_bitluni_apll_fix; //4
    #else 
     #ifdef use_lib_vga200x150x70hz_bitluni
      unsigned char gb_vga_videomode_cur= video_mode_vga200x150x70hz_bitluni; //5
     #else
      #ifdef use_lib_vga200x150x70hz_bitluni_apll_fix
       unsigned char gb_vga_videomode_cur= video_mode_vga200x150x70hz_bitluni_apll_fix; //6
      #endif      
     #endif
    #endif
   #endif
  #endif
 #endif
#endif 


//Funciones
void Setup(void);
void Poll_Keyboard(void);
void ShowFPSCall(void);

#ifdef use_lib_audio_ticker
 void IRAM_ATTR my_callback_speaker_func(void);
#endif 
//void my_callback_speaker_func(void);
//void SDL_DumpVGA(void);


//****************************
//void SDL_DumpVGA(void)
//{
// #ifdef use_lib_tinybitluni_fast        
//  //framebuffer = vga_get_framebuffer();  
//  for (int y=0;y<10;y++)
//  {
//   for (int x=0;x<10;x++)
//   {
//    //framebuffer[y][x^2] = vga_get_sync_bits() | 255;
//    framebuffer[y][x^2] = gb_sync_bits | 0x3F;
//   }
//  }
//  //vga_swap_buffers();
// #else
//  for (int y=0;y<10;y++)
//  {
//   for (int x=0;x<10;x++)
//   {     
//    #ifdef use_lib_bitluni_3bpp
//     vga.dotFast(x,y,0x07);
//    #else
//     vga.dotFast(x,y,0x3F);
//    #endif 
//   }
//  }
// #endif 
//}


//**************************************************
void ActivarVideoPorTeclas()
{
 unsigned char is8colors= 0;//gb_vga_8colors;
 unsigned char usepllcteforce=0;
 unsigned char usecustompll=0;
 unsigned int p0=0;
 unsigned int p1=0;
 unsigned int p2=0;
 unsigned int p3=0; 

 unsigned int tiempo_ahora;
 unsigned int tiempo_antes;
 unsigned char video=255;
 unsigned char isPressed=0; 

 tiempo_antes= tiempo_ahora= millis();
 while ((tiempo_ahora-tiempo_antes)<use_lib_boot_time_select_vga)
 {
  if (isPressed==1){ break; }

  tiempo_ahora= millis();

  if (checkKey(PS2_KC_0)==1) { video=0; } ; //0
  if (checkKey(PS2_KC_1)==1) { video=1; } ; //1
  if (checkKey(PS2_KC_2)==1) { video=2; } ;
  if (checkKey(PS2_KC_3)==1) { video=3; } ;
  if (checkKey(PS2_KC_4)==1) { video=4; } ;
  if (checkKey(PS2_KC_5)==1) { video=5; } ;
  if (checkKey(PS2_KC_6)==1) { video=6; } ;
  if (checkKey(PS2_KC_7)==1) { video=7; } ;

  if (video!=255)
  {
   isPressed=1;
  }

//  read_keyboard();
//  #ifdef use_lib_keyboard_uart
//   keyboard_uart_poll();
//   ///read_keyboard_uart();
//   do_keyboard_uart();
//  #endif     
 }

 ClearKeyboard();

 if (video!=255)
 {//Cambio modo video
  if (gb_use_debug==1){ Serial.printf("Video mode change\r\n"); }
  switch (video)
  {
   case 0: gb_vga_videomode_cur= 0; is8colors=0; gb_ptrVideo_cur= VgaMode_vga_mode_360x200; usepllcteforce=0; usecustompll=0; break;
   case 1: gb_vga_videomode_cur= 1; is8colors=0; gb_ptrVideo_cur= VgaMode_vga_mode_360x200; usepllcteforce=0; usecustompll=1; break;
   case 2: gb_vga_videomode_cur= 2; is8colors=0; gb_ptrVideo_cur= VgaMode_vga_mode_320x200; usepllcteforce=0; usecustompll=0; break;
   case 3: gb_vga_videomode_cur= 3; is8colors=0; gb_ptrVideo_cur= VgaMode_vga_mode_320x200; usepllcteforce=1; p0=0x00AE; p1=0x00CF; p2=0x0004; p3=0x0005; usecustompll=0; break;
   case 4: gb_vga_videomode_cur= 4; is8colors=0; gb_ptrVideo_cur= VgaMode_vga_mode_320x200; usepllcteforce=0; usecustompll=1; break;
   case 5: gb_vga_videomode_cur= 5; is8colors=0; gb_ptrVideo_cur= VgaMode_vga_mode_200x150; usepllcteforce=0; usecustompll=0; break;
   case 6: gb_vga_videomode_cur= 6; is8colors=0; gb_ptrVideo_cur= VgaMode_vga_mode_200x150; usepllcteforce=0; usecustompll=1; break;
   default: break;
  }
 }//fin video!=255
 if (gb_use_debug==1){ Serial.printf("Video mode set %d\r\n",video); }

 OSDUpdateAnchoAltoVGA(gb_vga_videomode_cur,is8colors);//Set is8colors gb_vga_8colors

 //vga_init(pin_config,VgaMode_vga_mode_320x240,false,0,0,0,0,0,0);
   
 //jj_memset(gb_jj_paleta,0,256); //primero metemos 0 para luego recalcule con los bits de sync

 //vga_init(pin_config64,gb_ptrVideo_cur,false,usepllcteforce,p0,p1,p2,p3,usecustompll,is8colors, gb_vga_videomode_cur);
 //vga_init(pin_config,gb_ptrVideo_cur,false,0,0,0,0,0,0,0,gb_vga_videomode_cur); //Llamada en C
 vga_init(pin_config,gb_ptrVideo_cur,false,usepllcteforce,p0,p1,p2,p3,usecustompll,is8colors, gb_vga_videomode_cur);
 if (gb_use_debug==1) {Serial.printf("vga init\r\n");}


 //PrepareColorsBitluniVGA(); //Llamar despues de tener gb_sync_bits   
 //jj_memset(gb_jj_paleta,gb_color_vga[0],256); //memset(gb_jj_paleta,(0|gb_sync_bits),256); 
 //InicializaScanline();
 //vdp_227_init_struct();

 gb_sync_bits= vga_get_sync_bits();
 gb_buffer_vga = vga_get_framebuffer();
 gb_buffer_vga32=(unsigned int **)gb_buffer_vga;
 if (gb_use_debug==1) { Serial.printf("Fast Tiny Bitluni\r\n"); }
 if (gb_use_debug==1) { Serial.printf("vsync_inv_bit:0x%02X hsync_inv_bit:0x%02X\r\n",vga_get_vsync_inv_bit(),vga_get_hsync_inv_bit()); }
 if (gb_use_debug==1) { Serial.printf("Sync bits:0x%02X\r\n",gb_sync_bits); }
 PreparaColorVGA();
 SDLClear();



 //for (unsigned int y=0;y<gb_vga_alto;y++) //200
 //{
 // for (unsigned int x=0;x<gb_vga_ancho;x++) //320
 // {
 //  gb_buffer_vga[y][x^2]= gb_color_vga[0];
 // }
 //}
}





//Setup principal
void setup()
{ 
 pinMode(SPEAKER_PIN, OUTPUT);
 //REG_WRITE(GPIO_OUT_W1TC_REG , BIT25); //LOW clear
 digitalWrite(SPEAKER_PIN, LOW);
 
 //#ifdef use_lib_audio_tone32
 // ledcSetup(SPEAKER_CHANNEL,8000,8);
 // ledcAttachPin(SPEAKER_PIN,SPEAKER_CHANNEL);
 // ledcWriteTone(SPEAKER_CHANNEL,SPEAKER_CHANNEL);
 //#endif
 //Audio PWM ledcSetup(1,1E5,4);
 //Audio PWM ledcAttachPin(SPEAKER_PIN,1);
 //Audio PWM ledcWriteTone(1,0); 

 #ifdef use_lib_log_serial
  Serial.begin(115200);         
  if (gb_use_debug==1) { Serial.printf("HEAP BEGIN %d\r\n", ESP.getFreeHeap()); }
 #endif
 
 kb_begin();
 if (gb_use_debug==1) { Serial.printf("Keyboard init\r\n"); }

 #ifdef use_lib_tinybitluni_fast  
  //void vga_init(const int *pin_map, const VgaMode &mode, bool double_buffered)
  //vga_init(pin_config,vga_mode_320x240,false);
  //vga_init(pin_config,vga_mode_320x200,false); //funciona
  //vga_init(pin_config,vga_mode_240x240,false); //funciona
  
  //vga_init(pin_config,vga_mode_200x150,false);      

  //vga_init(pin_config,gb_ptrVideo_cur,false,0,0,0,0,0,0,0,gb_vga_videomode_cur); //Llamada en C
  //vga_init(pin_config,gb_ptrVideo_cur,false,0,0,0,0,0,0,0,gb_vga_videomode_cur); //Llamada en C
  ActivarVideoPorTeclas();
  

  //#ifdef use_lib_200x150
  // //vga_init(pin_config,VgaMode_vga_mode_200x150,false); //Llamada en C
  // vga_init(pin_config,VgaMode_vga_mode_200x150,false,0,0,0,0,0,0,0,0); //Llamada en C
  //#else 
  // #ifdef use_lib_320x200
  //  vga_init(pin_config,VgaMode_vga_mode_320x200,false); //Llamada en C   
  // #endif
  //#endif

  //vga_init(pin_config,VgaMode_vga_mode_320x200,false); //Llamada en C

  //Serial.printf("pin_config size:%d\n",sizeof(pin_config));
//  gb_sync_bits= vga_get_sync_bits();
//  gb_buffer_vga = vga_get_framebuffer();
//  gb_buffer_vga32=(unsigned int **)gb_buffer_vga;
//  Serial.printf("Fast Tiny Bitluni\n");
//  Serial.printf("vsync_inv_bit:0x%02X hsync_inv_bit:0x%02X\n",vga_get_vsync_inv_bit(),vga_get_hsync_inv_bit());
//  Serial.printf("Sync bits:0x%02X\n",gb_sync_bits);
//  PreparaColorVGA();
//  SDLClear();
  //En 320x200 sale bits:0x80 y deberia ser 0x40
  //En 320x240 sale bits:0xC0
 #else
  #ifdef use_lib_bitluni_3bpp   
   vga.init(vga.MODE320x200, RED_PIN_3B, GRE_PIN_3B, BLU_PIN_3B, HSYNC_PIN, VSYNC_PIN);        
   vga.fillRect(0,0,320,180,BLACK);
   vga.fillRect(0,0,320,180,BLACK);//fix mode fast video
   #ifdef use_lib_bitluni_low_memory
   #else
    if (gb_use_debug==1) { Serial.printf("RGBMask:%02X Sbits:%2X\r\n",vga.RGBAXMask,vga.SBits); }
   #endif 
  #else
   #define RED_PINS_6B 21, 22
   #define GRE_PINS_6B 18, 19
   #define BLU_PINS_6B  4,  5
   const int redPins[] = {RED_PINS_6B};
   const int grePins[] = {GRE_PINS_6B};
   const int bluPins[] = {BLU_PINS_6B}; 
   //vga.init(vga.MODE320x240, redPins, grePins, bluPins, HSYNC_PIN, VSYNC_PIN);
   //vga.init(vga.MODE320x200, redPins, grePins, bluPins, HSYNC_PIN, VSYNC_PIN);
   vga.init(vga.MODE200x150, redPins, grePins, bluPins, HSYNC_PIN, VSYNC_PIN);   
   //vga.setFont(Font6x8);
   //vga.clear(BLACK);
   //vga.clear(0x00);
   gb_buffer_vga= vga.backBuffer;
   gb_buffer_vga32=(unsigned int **)gb_buffer_vga;
   PreparaColorVGA();
   SDLClear();
   
  
   //vga.fillRect(0,0,320,180,0x00);
   //vga.fillRect(0,0,320,180,0x00);//fix mode fast video  
   //vga.fillRect(0,0,200,150,0x00);
   //vga.fillRect(0,0,200,150,0x00);//fix mode fast video  

   //vga.RGBAXMask,vga.SBits  
   if (gb_use_debug==1) { Serial.printf("RGBMask:%02X Sbits:%2X\r\n",vga.RGBAXMask,vga.SBits); }
   //RGBMask:3F Sbits:C0 320x240
   //RGBMask:3F Sbits:40 320x200
  #endif 
 #endif 
 
 
 #ifdef use_lib_log_serial
  if (gb_use_debug==1) { Serial.printf("VGA %d\r\n", ESP.getFreeHeap()); }
 #endif

 //kb_begin();


 #ifdef use_lib_wifi
  #ifdef use_lib_log_serial
   if (gb_use_debug==1) { Serial.printf("RAM before WIFI %d\r\n",ESP.getFreeHeap()); }
  #endif 
  WiFi.mode(WIFI_STA);
  //esp_wifi_set_ps(WIFI_PS_NONE); //Ahorro energia desactivado
  WiFi.begin(gb_wifi_ssd, gb_wifi_pass);

  for(unsigned char t = 4; t > 0; t--)
  {
   #ifdef use_lib_wifi_debug
    if (gb_use_debug==1) { Serial.printf("WIFI WAIT %d...\r\n", t); }
    Serial.flush();
   #endif
   delay(1000);
  }

  Asignar_WIFI(&http, stream);
  Check_WIFI();
  #ifdef use_lib_wifi_debug
   if (gb_use_debug==1) { Serial.print("IP address:"); }
   if (gb_use_debug==1) { Serial.println(WiFi.localIP()); }
  #endif   
 #endif


 retro_init();

 //#ifdef use_lib_audio_tone32
 //#else
  #ifdef use_lib_audio_ticker
   //no se usa  float auxTimer= (float)1.0/(float)SAMPLE_RATE; 
   //no se usa  gb_ticker_callback.attach(auxTimer,my_callback_speaker_func);  
   
   #ifdef use_lib_esp_arduino_compile_ver_3_3_0
    gb_timer = timerBegin(1000000);
    timerAttachInterrupt(gb_timer, &my_callback_speaker_func);
    timerAlarm(gb_timer, (1000000/SAMPLE_RATE), true, 0); //1.000.000 DIV 16.000
   #else
    gb_timer = timerBegin(0, 80, true); //Timer 0
    timerAttachInterrupt(gb_timer, &my_callback_speaker_func, true);
    timerAlarmWrite(gb_timer, (1000000/SAMPLE_RATE), true); //1.000.000 DIV 16.000 
    timerAlarmEnable(gb_timer);    
   #endif 
   //gb_timer = timerBegin(2, 80, true); //Timer 2
  #endif 
 //#endif 

 
tiempo_ini_vga = tiempo_cur_vga= tiempo_ini_keyboard= tiempo_cur_keyboard= millis(); 

 #ifdef use_lib_log_serial  
  if (gb_use_debug==1) { Serial.printf("END SETUP %d\r\n", ESP.getFreeHeap()); }
 #endif 
}

void Poll_Keyboard()
{
 gb_show_osd_main_menu = checkKey(PS2_KC_F1);  //(!keymap[PS2_KC_F1])&0x01;
 //Consola
 setButton(Console,0,checkKey(PS2_KC_0) /*!(keymap[PS2_KC_0])&0x01*/); //0 TIME
 setButton(Console,1,checkKey(PS2_KC_1) /*!(keymap[PS2_KC_1])&0x01*/); //1 MODE
 setButton(Console,2,checkKey(PS2_KC_2) /*!(keymap[PS2_KC_2])&0x01*/); //2 HOLD
 setButton(Console,3,checkKey(PS2_KC_3) /*!(keymap[PS2_KC_3])&0x01*/); //3 START

 //Mando 1 
 setButton(ControlA,0,checkKey(KEY_CURSOR_RIGHT) /*!(keymap[KEY_CURSOR_RIGHT])&0x01*/); //Right 0
 setButton(ControlA,5,checkKey(KEY_CURSOR_RIGHT) /*!(keymap[KEY_CURSOR_RIGHT])&0x01*/); //clockwise 
 setButton(ControlA,1,checkKey(KEY_CURSOR_LEFT) /*!(keymap[KEY_CURSOR_LEFT])&0x01*/); //Left 1
 setButton(ControlA,4,checkKey(KEY_CURSOR_LEFT) /*!(keymap[KEY_CURSOR_LEFT])&0x01*/); //counter clockwise
 setButton(ControlA,2,checkKey(KEY_CURSOR_DOWN) /*!(keymap[KEY_CURSOR_DOWN])&0x01*/); //Down Back 2
 setButton(ControlA,3,checkKey(KEY_CURSOR_UP) /*!(keymap[KEY_CURSOR_UP])&0x01*/); //Up Forward 3
 setButton(ControlA,6,checkKey(PS2_KC_O) /*!(keymap[PS2_KC_O])&0x01*/); //6 // pull 
 setButton(ControlA,7,checkKey(PS2_KC_P) /*!(keymap[PS2_KC_P])&0x01*/); //7 // push


 //Mando 2
 setButton(ControlB,0,checkKey(PS2_KC_D) /*!(keymap[PS2_KC_D])&0x01*/); //Right 0
 setButton(ControlB,5,checkKey(PS2_KC_D) /*!(keymap[PS2_KC_D])&0x01*/); //clockwise 
 setButton(ControlB,1,checkKey(PS2_KC_A) /*!(keymap[PS2_KC_A])&0x01*/); //Left 1
 setButton(ControlB,4,checkKey(PS2_KC_A) /*!(keymap[PS2_KC_A])&0x01*/); //counter clockwise
 setButton(ControlB,2,checkKey(PS2_KC_W) /*!(keymap[PS2_KC_S])&0x01*/); //Down Back 2
 setButton(ControlB,3,checkKey(PS2_KC_W) /*!(keymap[PS2_KC_W])&0x01*/); //Up Forward 3
 setButton(ControlB,6,checkKey(PS2_KC_C) /*!(keymap[PS2_KC_C])&0x01*/); //6 // pull 
 setButton(ControlB,7,checkKey(PS2_KC_V) /*!(keymap[PS2_KC_V])&0x01*/); //7 // push
}

#ifdef use_lib_audio_ticker
//void my_callback_speaker_func()
volatile unsigned char gb_spk_data=0;
volatile unsigned char gb_spk_data_before=0;
volatile unsigned int gb_ch_pos_cur=0;
volatile unsigned int gb_ch_max_dur=0;
volatile unsigned char gb_flipflop_ch=0;
volatile unsigned int fast_speaker_pin= (1<<SPEAKER_PIN);
void IRAM_ATTR my_callback_speaker_func()
{ 
 if (gb_spk_data != gb_spk_data_before)
 {
  //digitalWrite(SPEAKER_PIN, gb_spk_data);
  if (gb_spk_data==0) { GPIO.out_w1tc= fast_speaker_pin; }
  else { GPIO.out_w1ts= fast_speaker_pin; }

  gb_spk_data_before= gb_spk_data;
 }

 if (gb_volumen01!=0)
 {   
  gb_ch_pos_cur++;
  if (gb_ch_pos_cur >= gb_pulsos_onda)
  {//cambio canal 0
   gb_ch_pos_cur= 0;
   gb_flipflop_ch++;
   gb_flipflop_ch= (gb_flipflop_ch & 0x01);
  }
  //gb_spk_data= (gb_volumen01!=0)? gb_flipflop_ch: 0;
  gb_spk_data= gb_flipflop_ch;
 }
 else
 {
  gb_spk_data=0; 
 }

 
/*  
 gb_cont_my_callbackfunc++;
 if (gb_cont_my_callbackfunc>=gb_pulsos_onda)
 {
  gb_cont_my_callbackfunc=0;
  gb_estado_sonido = (~gb_estado_sonido)& 0x1;
  if ((gb_volumen01 == 0)||(gb_frecuencia01==0))
  {     
     digitalWrite(SPEAKER_PIN, LOW);
     //REG_WRITE(GPIO_OUT_W1TC_REG , BIT25); //LOW clear
  }  
  else
  {
   if (speaker_pin_estado != gb_estado_sonido)
   {
    //digitalWrite(SPEAKER_PIN,gb_estado_sonido);
	  //digitalWrite(25,gb_estado_sonido);
	  if (gb_estado_sonido==LOW)
    {
	   //REG_WRITE(GPIO_OUT_W1TC_REG , BIT25); //LOW clear
     digitalWrite(SPEAKER_PIN,LOW);
    }
	  else
    {
	   //REG_WRITE(GPIO_OUT_W1TS_REG , BIT25); //High Set
     digitalWrite(SPEAKER_PIN,HIGH);
    }
    speaker_pin_estado= gb_estado_sonido;   
   }
  }
 }
 */ 
}
#endif




void ShowFPSCall()
{
 //Serial.printf("FPS %d\r\n",gb_fps_cur);
 //gb_fps_cur=0;

 //Serial.printf("FPS %d(c:%d m:%d mx:%d ex:%d) vdp:(c:%d m:%d mx:%d) bg:%d sp:%d rd:%d Vtask:%d\r\n",gb_fps_cur, gb_cpu_current,gb_cpu_min,gb_cpu_max,gb_cpu_frame_prev_exced,gb_vdp_frame_cur, gb_vdp_min, gb_vdp_max, gb_background_time_cur, gb_sprite_time_cur, gb_render_time_cur,gb_fps_cur_videotask_dump);
 char cadFPS[60]=""; 
 unsigned short int posX= ((gb_vga_ancho==320)||(gb_vga_ancho==360))? 34: 21;
 unsigned short int posY= (gb_vga_alto==200)? 24: 17;
 unsigned char colorVerde= 3;
 unsigned char colorBlanco= 1;
 unsigned short int aux_cpu_only= gb_cur_cpu_ticks; //(gb_cpu_time_med-gb_vga_dump_time_dur);
 unsigned short int aux_cpu_min_only= gb_min_cpu_ticks; //(gb_cpu_time_min-gb_vga_dump_time_dur);
 unsigned short int aux_cpu_max_only= gb_max_cpu_ticks; //(gb_cpu_time_max-gb_vga_dump_time_dur);
 unsigned char fpsNoDelay= (aux_cpu_only==0)? 0: (1000000/aux_cpu_only);
 unsigned int tiempoPAL_NTSC= (gb_use_mode_pal==1) ? 20000: 16666;
 unsigned short int idle= (gb_use_cpu_delay==1)? (tiempoPAL_NTSC-aux_cpu_only): 0; 

 //sprintf(cadFPS,"C:%05d M:%05d MX:%05d I:%05d",aux_cpu_only, aux_cpu_min_only, aux_cpu_max_only,idle); 
 //cadFPS[32]='\0';
 sprintf(cadFPS,"C:%05d M:%05d ",aux_cpu_only, aux_cpu_min_only);
 cadFPS[17]='\0';
 OSDprintTextFPS(cadFPS,posX,posY,colorBlanco,colorVerde); 
 posX++;
 sprintf(cadFPS,"MX:%05d I:%05d",aux_cpu_max_only,idle); 
 cadFPS[17]='\0';
 OSDprintTextFPS(cadFPS,posX,posY,colorBlanco,colorVerde);
 posX++;

 
 //sprintf(cadFPS,"FPS:%03d FND:%03d V:%05d F:%03d   ", gb_fps_med, fpsNoDelay, gb_vga_dump_time_dur, gb_video_fps_cur);
 
 //sprintf(cadFPS,"FPS:%03d FND:%03d V:%05d F:%03d   ", gb_fps_cur, fpsNoDelay, (unsigned short int)gb_vdp_frame_cur, gb_fps_cur_videotask_dump);
 sprintf(cadFPS,"FPS:%03d FND:%03d ", gb_fps_cur, fpsNoDelay);
 cadFPS[17]='\0'; 
 OSDprintTextFPS(cadFPS,posX,posY,colorBlanco,colorVerde);  
 posX++; 

 sprintf(cadFPS,"V:%05d F:%03d   ", gb_cur_vga_ticks, gb_fps_cur_videotask_dump);
 cadFPS[17]='\0';
 OSDprintTextFPS(cadFPS,posX,posY,colorBlanco,colorVerde);
}






//Loop main
void loop() 
{ 
 //SDL_DumpVGA();
 //while (!done)
 //{
 
 if (gb_force_load_cart==1)
 {
  gb_force_load_cart=0;
  retro_init();
 }     

 //BEGIN one frame 20 ms  
 if (gb_cpunoexe == 0)
 {    
  tiempo_cur_keyboard= millis();  
  if ((tiempo_cur_keyboard-tiempo_ini_keyboard)< gb_keyboard_cur_poll_ms) //20 ms
  {
  }
  else
  {
   tiempo_ini_keyboard= tiempo_cur_keyboard; 
   Poll_Keyboard();
  }  
  //tiempo_ini_cpu= millis();
  jj_ini_cpu = micros();
  tiempo_ini_cpu= jj_ini_cpu;
  //gb_volumen01= gb_frecuencia01=0;  //Silencio PWM Audio
  retro_run();
  gb_fps_cur_videotask_dump++;
  jj_end_cpu = micros();
  //tiempo_fin_cpu = millis();
  tiempo_fin_cpu= jj_end_cpu;
  total_tiempo_ms_cpu=tiempo_fin_cpu-tiempo_ini_cpu; //microseconds no miliseconds

  gb_cur_cpu_ticks= (jj_end_cpu-jj_ini_cpu);
  if (gb_cur_cpu_ticks>gb_max_cpu_ticks)
  {
   gb_max_cpu_ticks= gb_cur_cpu_ticks;
  }
  if (gb_cur_cpu_ticks<gb_min_cpu_ticks)
  {
   gb_min_cpu_ticks= gb_cur_cpu_ticks;
  }
 }
 //END one frame 20 ms  

 if (gb_show_osd_main_menu == 1)
 {
  do_tinyOSD();
 }
 

 if (gb_cpunoexe == 0)
 {
  gb_cpunoexe=1;        
  gb_cpunoexe_timer_ini= micros(); //gb_cpunoexe_timer_ini= millis();  
  tiene_que_tardar= (gb_use_mode_pal==1)? (20000-total_tiempo_ms_cpu) : (16666-total_tiempo_ms_cpu);
  if (tiene_que_tardar> ((gb_use_mode_pal==1)?20000:16666))
  {
   tiene_que_tardar=0;
  }
 }
 else
 {
  //if ((millis()-gb_cpunoexe_timer_ini) < tiene_que_tardar)
  if ((micros()-gb_cpunoexe_timer_ini) < tiene_que_tardar)
  {
  }
  else
  {
   gb_cpunoexe=0;
  }
  gb_cpunoexe=0;
  gb_volumen01= gb_frecuencia01=0;  //Silencio PWM Audio
  //Audio PWM ledcWriteTone(1,0);
  //#ifdef use_lib_audio_tone32
  // Tone32_noTone(SPEAKER_PIN, SPEAKER_CHANNEL);
  //#endif
 }

 tiempo_cur_vga= millis();
 if ((tiempo_cur_vga-tiempo_ini_vga) < gb_vga_cur_poll_ms) //20 
 {
 }
 else
 {
  tiempo_ini_vga= tiempo_cur_vga;
  jj_ini_vga = micros();
  VIDEO_drawFrame();  
  jj_end_vga = micros();
  tiempo_vga=1;
  gb_cur_vga_ticks= (jj_end_vga-jj_ini_vga);
  if (gb_cur_vga_ticks>gb_max_vga_ticks)
  {
   gb_max_vga_ticks= gb_cur_vga_ticks;
  }
  if (gb_cur_vga_ticks<gb_min_vga_ticks)   
  {
   gb_min_vga_ticks= gb_cur_vga_ticks;  
  }

  gb_fps_cur++;
 }
  

 gb_cpu_timer_cur= millis();
 if ((gb_cpu_timer_cur-gb_cpu_timer_before)<1000)
 {   
 }
 else
 {
  gb_cpu_timer_before= gb_cpu_timer_cur;
  if (tiempo_vga == 1)
  {
   //Serial.printf("c:%u m:%u mx:%u vc:%u m:%u mx:%u\n",gb_cur_cpu_ticks,gb_min_cpu_ticks,gb_max_cpu_ticks, gb_cur_vga_ticks,gb_min_vga_ticks,gb_max_vga_ticks);

   if (gb_do_action_key_show_osd==1)
   {
    ShowFPSCall();
   }      

   //Reseteo VGA   
   gb_min_vga_ticks= 1000000;
   gb_max_vga_ticks= 0;
   gb_cur_vga_ticks= 0;   
   tiempo_vga=0;
   gb_fps_cur=0;
   gb_fps_cur_videotask_dump=0;
  }
  else
  {//Imprimo CPU
   //Serial.printf("c:%u m:%u mx:%u\n",gb_cur_cpu_ticks,gb_min_cpu_ticks,gb_max_cpu_ticks);
  }

  //Reseteo CPU a 1 segundo
  gb_min_cpu_ticks= 1000000;
  gb_max_cpu_ticks= 0;
  gb_cur_cpu_ticks= 0;
  gb_fps_cur=0;
  gb_fps_cur_videotask_dump=0;
 }

 //}
}
