#ifndef GB_GLOBALS_H
 #define GB_GLOBALS_H

 //#include <SDL/SDL.h>
 
 #define VIDEO_SIZE 8192
 
 //Mandos
 #define Console 0
 #define ControlA 1
 #define ControlB 2
 
 #ifdef use_lib_wifi
  extern unsigned char gb_buffer_wifi[1024]; //128 * 8
  extern int gb_size_file_wifi;
  extern char gb_cadUrl[128];
 #endif 

 extern struct hle_state_s hle_state;
 
 #define MEMORY_SIZE 0x10000
 extern unsigned char Memory[MEMORY_SIZE];
 extern int MEMORY_RAMStart;
 
 #define R_SIZE 64
 extern unsigned char R[R_SIZE]; // 64 byte Scratchpad 


 //BEGIN memory_h
 extern unsigned char A; // Accumulator
 extern unsigned short PC0; // Program Counter
 extern unsigned short PC1; // Program Counter alternate
 extern unsigned short DC0; // Data Counter
 extern unsigned short DC1; // Data Counter alternate
 extern unsigned char ISAR; // Indirect Scratchpad Address Register (6-bit)
 extern unsigned char W; // Status Register (flags)
 //END memory_h

 //BEGIN video_h
 extern unsigned char VIDEO_Buffer_raw[VIDEO_SIZE];
 extern unsigned char ARM;
 extern unsigned char X;
 extern unsigned char Y;
 extern unsigned char Color;
 //END video_h

 //BEGIN channelf_h
 extern int CPU_Ticks_Debt;
 //END channelf_h

 //BEGIN f2102
 extern unsigned short f2102_state;
 extern unsigned char f2102_memory[1024];
 extern unsigned short f2102_address;
 extern unsigned char f2102_rw;
 //END f2102
 
 //BEGIN controller_h
 extern unsigned char ControllerEnabled;
 extern unsigned char ControllerSwapped;
 //END controller_h
 
 //BEGIN ports_h
 extern unsigned char Ports[64];
 //END ports_h

 //extern SDL_Surface *screen;
 
 extern unsigned char tone;
 extern volatile int gb_frecuencia01;
 extern volatile int gb_dutty_ch01;
 extern volatile int gb_volumen01;
 extern volatile int gb_duracion01;

 //#define SAMPLE_RATE 16000 
 //Frecuencia correcta 1500
 #define SAMPLE_RATE 1500
 //#define SAMPLE_RATE 3000
 //#define SAMPLE_RATE 12000 
 //#define SAMPLE_RATE 1000
 //#define SAMPLE_RATE 500
 
 extern volatile unsigned int gb_pulsos_onda;
 extern volatile unsigned int gb_cont_my_callbackfunc; 
 extern volatile unsigned char speaker_pin_estado;

 extern volatile unsigned char keymap[256];
 extern volatile unsigned char oldKeymap[256];


 extern unsigned char gb_show_osd_main_menu;
 extern unsigned char gb_force_load_cart;
 extern unsigned char gb_id_cur_cart;

 extern unsigned char **gb_buffer_vga; //Puntero video 8 bits
 extern unsigned int **gb_buffer_vga32; //Puntero video 32 bits

 extern unsigned char gb_delay_tick_cpu_micros;
 extern unsigned char gb_auto_delay_cpu;

 //fast bitluni
 extern unsigned char gb_sync_bits;



 extern unsigned char gb_keyboard_cur_poll_ms;
 extern unsigned char gb_vga_cur_poll_ms;

#endif

 
