#ifndef _GB_CONFIG_H
 #define _GB_CONFIG_H
 

 //Corrige teclados que no se inicializan(solucion dcrespo3D)
 //#define FIX_PERIBOARD_NOT_INITING

 //Audio usar libreria Tone32 (No usar)
 //#define use_lib_audio_tone32
 //#define SPEAKER_CHANNEL 2
 #define use_lib_audio_ticker

 //16 microssegundos espera en cada tick
 #define use_lib_delay_tick_cpu_micros 16

 //Usa la librerua bitluni modificada en C tiny fast
 #define use_lib_bitluni_fast

 
 //Selecionar solo uno (use_lib_200x150 o use_lib_320x200)
 #define use_lib_200x150
 //#define use_lib_320x200

 //Logs
 #define use_lib_log_serial
 

 //No usarlo Pruebas
 //#define use_lib_bitluni_3bpp
 
 //No usarlo Pruebas
 //#define use_lib_bitluni_low_memory
 


 //Read keyboard poll x millis
 #define gb_ms_keyboard 20
 
 //Milisegundos polling vga
 #define gb_ms_vga 20
 
 //Delay millis iteration emulate 
 //No usarlo Pruebas
 //#define gb_delay_emulate_ms 0



 //Desplazamiento X en multiplos de 4 pixels (32 bits)
 //Desplazamiento Y en pixels
 #ifdef use_lib_200x150
  #define gb_add_offset_x 8
  #define gb_add_offset_y 30
 #else
  #define gb_add_offset_x 20 
  #define gb_add_offset_y 40
 #endif
#endif
