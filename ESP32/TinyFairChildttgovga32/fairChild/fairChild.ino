//Port FreeChaF emulator to TTGO VGA32 by ackerman:
//Author: Ackerman
//License: WTFPL
// Load Roms
// VGA MODE200x150, MODE320x200
// Mode 64 colors RGB 6 bits
// VGA Tiny library bitluni 0.3.3 mod convert C
// gbConfig options configuration compile
// Keyboard console
//  0,1,2,3
// Keyboard gamer 1
//  Left,Right,Up,Down   o,p
// Keyboard 2
//  a,d,w,s   c,v

#include "PS2Kbd.h"
#include <Arduino.h>
#include "gbConfig.h"
#ifdef use_lib_audio_tone32
 #include "Tone32.h"
#else 
 #ifdef use_lib_audio_ticker
  #include <Ticker.h>
 #endif 
#endif 
#include "fairChild.h"
#ifdef use_lib_bitluni_fast
#else
 #include "MartianVGA.h"
 #include "def/Font.h"
#endif 
#include "hardware.h"
#include "driver/timer.h"
#include "soc/timer_group_struct.h"
#include "gbGlobals.h"
#include "libretro.h"
#include "video.h"
#include "controller.h"
#include "osd.h"
#include "PS2KeyCode.h"

//#include "dataFlash/gbrom.h"
//#include "PS2Boot/PS2KeyCode.h"
#ifdef use_lib_bitluni_fast
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

 static const unsigned char pin_config[] = {
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

#ifdef use_lib_bitluni_fast 
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

#ifdef use_lib_audio_tone32
#else
 #ifdef use_lib_audio_ticker
  Ticker gb_ticker_callback;
 #endif 
#endif

volatile unsigned int gb_pulsos_onda=0;
volatile unsigned int gb_cont_my_callbackfunc=0;
volatile unsigned char gb_estado_sonido=0;
volatile unsigned char speaker_pin_estado=LOW;

volatile int gb_frecuencia01=0;
volatile int gb_dutty_ch01=0;
volatile int gb_volumen01=0;
volatile int gb_duracion01=0;


unsigned char gb_force_load_cart=0;
unsigned char gb_id_cur_cart=0;

unsigned char gb_cpunoexe=0;
int gb_cpunoexe_timer_ini;
unsigned short int tiempo_ini_cpu,tiempo_fin_cpu;
unsigned short int total_tiempo_ms_cpu;
unsigned short int tiene_que_tardar;

unsigned int tiempo_ini_vga,tiempo_cur_vga;

unsigned int tiempo_ini_keyboard,tiempo_cur_keyboard;

unsigned char **gb_buffer_vga;
unsigned int **gb_buffer_vga32;

unsigned char gb_delay_tick_cpu_micros= use_lib_delay_tick_cpu_micros;

unsigned char tiempo_vga= 0;
unsigned int gb_cpu_timer_before=0,gb_cpu_timer_cur=0;
unsigned int jj_ini_cpu,jj_end_cpu,jj_ini_vga,jj_end_vga;
unsigned int gb_max_cpu_ticks,gb_min_cpu_ticks,gb_cur_cpu_ticks;
unsigned int gb_max_vga_ticks,gb_min_vga_ticks,gb_cur_vga_ticks;

unsigned char gb_keyboard_cur_poll_ms= gb_ms_keyboard;
unsigned char gb_vga_cur_poll_ms= gb_ms_vga;

//Funciones
void Setup(void);
void Poll_Keyboard(void);
void my_callback_speaker_func(void);
//void SDL_DumpVGA(void);


//****************************
//void SDL_DumpVGA(void)
//{
// #ifdef use_lib_bitluni_fast        
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



//Setup principal
void setup()
{ 
 pinMode(SPEAKER_PIN, OUTPUT);
 //REG_WRITE(GPIO_OUT_W1TC_REG , BIT25); //LOW clear
 digitalWrite(SPEAKER_PIN, LOW);
 
 #ifdef use_lib_audio_tone32
  ledcSetup(SPEAKER_CHANNEL,8000,8);
  ledcAttachPin(SPEAKER_PIN,SPEAKER_CHANNEL);
  ledcWriteTone(SPEAKER_CHANNEL,SPEAKER_CHANNEL);
 #endif
 //Audio PWM ledcSetup(1,1E5,4);
 //Audio PWM ledcAttachPin(SPEAKER_PIN,1);
 //Audio PWM ledcWriteTone(1,0); 

 #ifdef use_lib_log_serial
  Serial.begin(115200);         
  Serial.printf("HEAP BEGIN %d\n", ESP.getFreeHeap()); 
 #endif
 
 #ifdef use_lib_bitluni_fast  
  //void vga_init(const int *pin_map, const VgaMode &mode, bool double_buffered)
  //vga_init(pin_config,vga_mode_320x240,false);
  //vga_init(pin_config,vga_mode_320x200,false); //funciona
  //vga_init(pin_config,vga_mode_240x240,false); //funciona
  
  //vga_init(pin_config,vga_mode_200x150,false);  
  
  #ifdef use_lib_200x150
   vga_init(pin_config,VgaMode_vga_mode_200x150,false); //Llamada en C
  #else 
   #ifdef use_lib_320x200
    vga_init(pin_config,VgaMode_vga_mode_320x200,false); //Llamada en C   
   #endif
  #endif

  //vga_init(pin_config,VgaMode_vga_mode_320x200,false); //Llamada en C

  //Serial.printf("pin_config size:%d\n",sizeof(pin_config));
  gb_sync_bits= vga_get_sync_bits();
  gb_buffer_vga = vga_get_framebuffer();
  gb_buffer_vga32=(unsigned int **)gb_buffer_vga;
  Serial.printf("Fast Tiny Bitluni\n");
  Serial.printf("vsync_inv_bit:0x%02X hsync_inv_bit:0x%02X\n",vga_get_vsync_inv_bit(),vga_get_hsync_inv_bit());
  Serial.printf("Sync bits:0x%02X\n",gb_sync_bits);
  PreparaColorVGA();
  SDLClear();
  //En 320x200 sale bits:0x80 y deberia ser 0x40
  //En 320x240 sale bits:0xC0
 #else
  #ifdef use_lib_bitluni_3bpp   
   vga.init(vga.MODE320x200, RED_PIN_3B, GRE_PIN_3B, BLU_PIN_3B, HSYNC_PIN, VSYNC_PIN);        
   vga.fillRect(0,0,320,180,BLACK);
   vga.fillRect(0,0,320,180,BLACK);//fix mode fast video
   #ifdef use_lib_bitluni_low_memory
   #else
    Serial.printf("RGBMask:%02X Sbits:%2X\n",vga.RGBAXMask,vga.SBits);   
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
   Serial.printf("RGBMask:%02X Sbits:%2X\n",vga.RGBAXMask,vga.SBits);
   //RGBMask:3F Sbits:C0 320x240
   //RGBMask:3F Sbits:40 320x200
  #endif 
 #endif 
 
 
 #ifdef use_lib_log_serial
  Serial.printf("VGA %d\n", ESP.getFreeHeap()); 
 #endif

 kb_begin();

 retro_init();

 #ifdef use_lib_audio_tone32
 #else
  #ifdef use_lib_audio_ticker
   float auxTimer= (float)1.0/(float)SAMPLE_RATE; 
   gb_ticker_callback.attach(auxTimer,my_callback_speaker_func);  
  #endif 
 #endif 

 
 tiempo_ini_vga = tiempo_cur_vga= tiempo_ini_keyboard= tiempo_cur_keyboard= millis();

 #ifdef use_lib_log_serial  
  Serial.printf("END SETUP %d\n", ESP.getFreeHeap()); 
 #endif 
}

void Poll_Keyboard()
{
 gb_show_osd_main_menu = (!keymap[PS2_KC_F1])&0x01;
 //Consola
 setButton(Console,0,!(keymap[PS2_KC_0])&0x01); //0 TIME
 setButton(Console,1,!(keymap[PS2_KC_1])&0x01); //1 MODE
 setButton(Console,2,!(keymap[PS2_KC_2])&0x01); //2 HOLD
 setButton(Console,3,!(keymap[PS2_KC_3])&0x01); //3 START

 //Mando 1 
 setButton(ControlA,0,!(keymap[KEY_CURSOR_RIGHT])&0x01); //Right 0
 setButton(ControlA,5,!(keymap[KEY_CURSOR_RIGHT])&0x01); //clockwise 
 setButton(ControlA,1,!(keymap[KEY_CURSOR_LEFT])&0x01); //Left 1
 setButton(ControlA,4,!(keymap[KEY_CURSOR_LEFT])&0x01); //counter clockwise
 setButton(ControlA,2,!(keymap[KEY_CURSOR_DOWN])&0x01); //Down Back 2
 setButton(ControlA,3,!(keymap[KEY_CURSOR_UP])&0x01); //Up Forward 3
 setButton(ControlA,6,!(keymap[PS2_KC_O])&0x01); //6 // pull 
 setButton(ControlA,7,!(keymap[PS2_KC_P])&0x01); //7 // push


 //Mando 2
 setButton(ControlB,0,!(keymap[PS2_KC_D])&0x01); //Right 0
 setButton(ControlB,5,!(keymap[PS2_KC_D])&0x01); //clockwise 
 setButton(ControlB,1,!(keymap[PS2_KC_A])&0x01); //Left 1
 setButton(ControlB,4,!(keymap[PS2_KC_A])&0x01); //counter clockwise
 setButton(ControlB,2,!(keymap[PS2_KC_S])&0x01); //Down Back 2
 setButton(ControlB,3,!(keymap[PS2_KC_W])&0x01); //Up Forward 3
 setButton(ControlB,6,!(keymap[PS2_KC_C])&0x01); //6 // pull 
 setButton(ControlB,7,!(keymap[PS2_KC_V])&0x01); //7 // push
}

#ifdef use_lib_audio_ticker
void my_callback_speaker_func()
{ 
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
}
#endif


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

 if (gb_cpunoexe == 0)
 {  
  tiempo_cur_keyboard= millis();  
  if ((tiempo_cur_keyboard-tiempo_ini_keyboard)>= gb_keyboard_cur_poll_ms) //20 ms
  {
   tiempo_ini_keyboard= tiempo_cur_keyboard; 
   Poll_Keyboard();
  }  
  tiempo_ini_cpu= millis();
  jj_ini_cpu = micros();
  retro_run();
  jj_end_cpu = micros();
  tiempo_fin_cpu = millis();
  total_tiempo_ms_cpu=tiempo_fin_cpu-tiempo_ini_cpu;

  gb_cur_cpu_ticks= (jj_end_cpu-jj_ini_cpu);
  if (gb_cur_cpu_ticks>gb_max_cpu_ticks)
   gb_max_cpu_ticks= gb_cur_cpu_ticks;
  if (gb_cur_cpu_ticks<gb_min_cpu_ticks)   
   gb_min_cpu_ticks= gb_cur_cpu_ticks;  
 }

 if (gb_show_osd_main_menu == 1)
 {
  do_tinyOSD();
 }


 if (gb_cpunoexe == 0)
 {
  gb_cpunoexe=1;        
  gb_cpunoexe_timer_ini= millis();
  tiene_que_tardar= 20-total_tiempo_ms_cpu;
  if (tiene_que_tardar>20)
   tiene_que_tardar=0;      
 }
 else
 {
  if ((millis()-gb_cpunoexe_timer_ini)>=tiene_que_tardar)
  {
   gb_cpunoexe=0;      
  }
  gb_cpunoexe=0;
  gb_volumen01=0;
  gb_frecuencia01=0;
  //Audio PWM ledcWriteTone(1,0);
  #ifdef use_lib_audio_tone32
   Tone32_noTone(SPEAKER_PIN, SPEAKER_CHANNEL);
  #endif
 }

 tiempo_cur_vga= millis();
 if ((tiempo_cur_vga-tiempo_ini_vga)>= gb_vga_cur_poll_ms) //20
 {
  tiempo_ini_vga= tiempo_cur_vga;
  jj_ini_vga = micros();
  VIDEO_drawFrame();  
  jj_end_vga = micros();
  tiempo_vga=1;
  gb_cur_vga_ticks= (jj_end_vga-jj_ini_vga);
  if (gb_cur_vga_ticks>gb_max_vga_ticks)
   gb_max_vga_ticks= gb_cur_vga_ticks;
  if (gb_cur_vga_ticks<gb_min_vga_ticks)   
   gb_min_vga_ticks= gb_cur_vga_ticks;  
 }



 gb_cpu_timer_cur= millis();
 if ((gb_cpu_timer_cur-gb_cpu_timer_before)>1000)
 {
  gb_cpu_timer_before= gb_cpu_timer_cur;
  if (tiempo_vga == 1)
  {
   Serial.printf("c:%u m:%u mx:%u vc:%u m:%u mx:%u\n",gb_cur_cpu_ticks,gb_min_cpu_ticks,gb_max_cpu_ticks, gb_cur_vga_ticks,gb_min_vga_ticks,gb_max_vga_ticks);
   //Reseteo VGA
   gb_min_vga_ticks= 1000000;
   gb_max_vga_ticks= 0;
   gb_cur_vga_ticks= 0;   
   tiempo_vga=0;
  }
  else
  {//Imprimo CPU
   Serial.printf("c:%u m:%u mx:%u\n",gb_cur_cpu_ticks,gb_min_cpu_ticks,gb_max_cpu_ticks);
  }

  //Reseteo CPU a 1 segundo
  gb_min_cpu_ticks= 1000000;
  gb_max_cpu_ticks= 0;
  gb_cur_cpu_ticks= 0;   
 }

 //}
}
