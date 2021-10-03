#ifndef GB_GLOBALS_H
 #define GB_GLOBALS_H

 //#include <SDL/SDL.h>
 
 #define VIDEO_SIZE 8192
 
 //Mandos
 #define Console 0
 #define ControlA 1
 #define ControlB 2
 
 extern struct hle_state_s hle_state;
 
 
 #define MEMORY_SIZE 0x10000
 extern unsigned char Memory[MEMORY_SIZE];
 extern int MEMORY_RAMStart;
 
 #define R_SIZE 64
 extern unsigned char R[R_SIZE]; // 64 byte Scratchpad 

 //BEGIN f2102
 extern unsigned short f2102_state;
 extern unsigned char f2102_memory[1024];
 extern unsigned short f2102_address;
 extern unsigned char f2102_rw;
 //END f2102
 
 
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

 //fast bitluni
 extern unsigned char gb_sync_bits;



 extern unsigned char gb_keyboard_cur_poll_ms;
 extern unsigned char gb_vga_cur_poll_ms;

#endif

 
