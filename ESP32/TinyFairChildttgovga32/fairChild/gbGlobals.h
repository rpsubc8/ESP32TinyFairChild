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
 
 //extern unsigned char tone;
 extern unsigned char gb_tone;
 extern volatile int gb_frecuencia01;
 extern volatile int gb_dutty_ch01;
 extern volatile int gb_volumen01;
 extern volatile int gb_duracion01;

 
 extern volatile unsigned int gb_pulsos_onda;
 //extern volatile unsigned int gb_cont_my_callbackfunc; 
 extern volatile unsigned char speaker_pin_estado;

 //extern volatile unsigned char keymap[256];
 //extern volatile unsigned char oldKeymap[256];


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

 extern unsigned char gb_use_debug;
 extern unsigned char gb_vga_videomode_cur_menu; //El seleccionado en el OSD
 extern unsigned char gb_vga_videomode_cur;
 extern unsigned short int gb_vga_ancho;
 extern unsigned short int gb_vga_alto; 
 extern const unsigned int *gb_ptrVideo_cur;
 extern unsigned char gb_vga_8colors; //1 8 colores, 0 64 colores
 extern const unsigned char pin_config[];
 extern unsigned char gb_pos_x_menu;
 extern unsigned char gb_pos_y_menu;
 extern unsigned char gb_add_offset_x;
 extern unsigned char gb_add_offset_y;
 extern unsigned char gb_offset_video32_x; //x offset 32 bits 4 pixels

 extern unsigned char gb_do_action_key_show_osd;
 extern unsigned char gb_use_mode_pal; //PAL o NTSC
 extern unsigned char gb_use_cpu_delay;
 extern unsigned char gb_color_vga[8];
 extern unsigned char gb_fps_cur;
 extern unsigned char gb_fps_cur_videotask_dump;

#endif

 
