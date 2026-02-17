#ifndef _GB_CONFIG_H
 #define _GB_CONFIG_H
 
 //Version detect ESP_ARDUINO 3.3.0 or superior (compiler)
 #define use_lib_esp_arduino_ver_3_3_0_auto
 //Uncomment to force compiler version 3.3.0
 //#define use_lib_esp_arduino_ver_3_3_0_force


 //HARDWARE GPIO BEGIN
 //SOUND GPIO
 #define SPEAKER_PIN 25

 //KEYBOARD GPIO DATA
 #define KEYBOARD_DATA 32
 //KEYBOARD GPIO CLK
 #define KEYBOARD_CLK 33

 //VGA GPIO output pins
 #define PIN_RED_LOW    21
 #define PIN_RED_HIGH   22
 #define PIN_GREEN_LOW  18
 #define PIN_GREEN_HIGH 19
 #define PIN_BLUE_LOW   4
 #define PIN_BLUE_HIGH  5
 #define PIN_HSYNC      23
 #define PIN_VSYNC      15
 //HARDWARE GPIO END


 //Video mode boot (select only one option) 
 #define use_lib_boot_vga_360x200x70hz_bitluni_6bpp
 //#define use_lib_boot_vga_360x200x70hz_bitluni_apll_6bpp
 //#define use_lib_boot_vga_320x200x70hz_bitluni_6bpp
 //#define use_lib_boot_vga_320x200x70hz_fabgl_6bpp
 //#define use_lib_boot_vga_320x200x70hz_bitluni_apll_6bpp
 //#define use_lib_boot_vga_200x150x70hz_bitluni_6bpp
 //#define use_lib_boot_vga_200x150x70hz_bitluni_apll_6bpp

//Time to select video mode at startup (ms)
 #define use_lib_boot_time_select_vga 500


 //WIFI para leer juegos.Consume RAM. Fuerza modo de video 200x150
 //Hay que configurar el gbWifiConfig.h
 //#define use_lib_wifi


 //Audio usar libreria Tone32 (No se usa)
 //#define use_lib_audio_tone32
 //#define SPEAKER_CHANNEL 2
 #define use_lib_audio_ticker

 //Frecuencia correcta 1500
 //#define SAMPLE_RATE 1500
 //#define SAMPLE_RATE 3000
 //#define SAMPLE_RATE 12000 
 //#define SAMPLE_RATE 1000
 //#define SAMPLE_RATE 500
 #define SAMPLE_RATE 8000
 //#define SAMPLE_RATE 11025
 //#define SAMPLE_RATE 16000 
 //#define SAMPLE_RATE 22050
 //#define SAMPLE_RATE 44100


 //16 microssegundos espera en cada tick
 #define use_lib_delay_tick_cpu_auto 1
 #define use_lib_delay_tick_cpu_micros 16

 //Usa la libreria bitluni modificada en C tiny fast
 #define use_lib_tinybitluni_fast

 
 //No usarlo Pruebas
 //Video colors (8 colores es DAC 3 bits)
 //#define use_lib_vga8colors

 //Logs
 #define use_lib_log_serial
 

 //No usarlo Pruebas
 //#define use_lib_bitluni_3bpp
 
 //No usarlo Pruebas
 //#define use_lib_bitluni_low_memory
 


 //Read keyboard poll x millis
 #define gb_ms_keyboard 10
 
 //Milisegundos polling vga
 #define gb_ms_vga 20
 
 //Delay millis iteration emulate 
 //No usarlo Pruebas
 //#define gb_delay_emulate_ms 0

 
 //Proyect ArduinoDroid
 //#gb_use_lib_compile_arduinodroid
 


 //Internal (do not modify)
 #ifdef use_lib_wifi
  //force 200x150 MEMORY FREE WIFI
  #undef use_lib_boot_vga_360x200x70hz_bitluni_6bpp
  #undef use_lib_boot_vga_360x200x70hz_bitluni_apll_6bpp
  #undef use_lib_boot_vga_320x200x70hz_bitluni_6bpp
  #undef use_lib_boot_vga_320x200x70hz_fabgl_6bpp
  #undef use_lib_boot_vga_320x200x70hz_bitluni_apll_6bpp
  #define use_lib_boot_vga_200x150x70hz_bitluni_6bpp
  #undef use_lib_boot_vga_200x150x70hz_bitluni_apll_6bpp  
 #endif


 //Internal (do not modify)
 #ifdef use_lib_boot_vga_360x200x70hz_bitluni_3bpp
  #define use_lib_vga8colors
  #define use_lib_vga360x200x70hz_bitluni
 #else
  #ifdef use_lib_boot_vga_360x200x70hz_bitluni_apll_3bpp
   #define use_lib_vga8colors
   #define use_lib_vga360x200x70hz_bitluni_apll_fix
  #else
   #ifdef use_lib_boot_vga_320x200x70hz_bitluni_3bpp
    #define use_lib_vga8colors
    #define use_lib_vga320x200x70hz_bitluni
   #else
    #ifdef use_lib_boot_vga_320x200x70hz_fabgl_3bpp
     #define use_lib_vga8colors
     #define use_lib_vga320x200x70hz_fabgl
    #else
     #ifdef use_lib_boot_vga_320x200x70hz_bitluni_apll_3bpp
      #define use_lib_vga8colors
      #define use_lib_vga320x200x70hz_bitluni_apll_fix
     #else
      #ifdef use_lib_boot_vga_320x240x60hz_bitluni_3bpp
       #define use_lib_vga8colors
       #define use_lib_vga320x240x60hz_bitluni
      #else
       #ifdef use_lib_boot_vga_200x150x70hz_fabgl_3bpp
        #define use_lib_vga8colors
        #define use_lib_vga200x150x70hz_fabgl
       #else
        #ifdef use_lib_boot_vga_200x150x70hz_bitluni_apll_3bpp
         #define use_lib_vga8colors
         #define use_lib_vga200x150x70hz_bitluni_apll_fix
         #else
          #ifdef use_lib_boot_vga_360x200x70hz_bitluni_6bpp           
           #define use_lib_vga360x200x70hz_bitluni
          #else 
           #ifdef use_lib_boot_vga_360x200x70hz_bitluni_apll_6bpp
            #define use_lib_vga360x200x70hz_bitluni_apll_fix
           #else
            #ifdef use_lib_boot_vga_320x200x70hz_bitluni_6bpp
             #define use_lib_vga320x200x70hz_bitluni
            #else
             #ifdef use_lib_boot_vga_320x200x70hz_fabgl_6bpp
              #define use_lib_vga320x200x70hz_fabgl
             #else
              #ifdef use_lib_boot_vga_320x200x70hz_bitluni_apll_6bpp
               #define use_lib_vga320x200x70hz_bitluni_apll_fix
              #else
               #ifdef use_lib_boot_vga_200x150x70hz_bitluni_6bpp
                #define use_lib_vga200x150x70hz_bitluni
               #else
                #ifdef use_lib_boot_vga_200x150x70hz_bitluni_6bpp
                 #define use_lib_vga320x240x60hz_fabgl
                #else
                 #ifdef use_lib_boot_vga_200x150x70hz_bitluni_apll_6bpp
                  #define use_lib_vga320x240x60hz_bitluni_apll_fix
                 #endif
                #endif 
               #endif 
              #endif
             #endif 
            #endif
           #endif
          #endif
        #endif
       #endif 
      #endif 
     #endif
    #endif
   #endif
  #endif
 #endif


 #if defined(use_lib_vga360x200x70hz_bitluni) || defined(use_lib_vga360x200x70hz_bitluni_apll_fix)
  #define use_lib_360x200
 #else
  #if defined(use_lib_vga320x200x70hz_bitluni) || defined(use_lib_vga320x200x70hz_fabgl) || defined(use_lib_vga320x200x70hz_bitluni_apll_fix)
   #define use_lib_320x200
  #else
   #if defined(use_lib_vga200x150x70hz_bitluni) || defined(use_lib_vga200x150x70hz_fabgl) || defined(use_lib_vga200x150x70hz_bitluni_apll_fix)
    #define use_lib_200x150
   #endif
  #endif
 #endif






 #ifdef use_lib_esp_arduino_ver_3_3_0_auto
  #if defined __has_include
   #if __has_include("esp_arduino_version.h")
    //version 2.0.0 or sup, posible 3.3.0
    #include <esp_arduino_version.h> //ESP3-3-0-IDF5-5
    #if ESP_ARDUINO_VERSION >= ESP_ARDUINO_VERSION_VAL(3, 3, 0)
     #define use_lib_esp_arduino_compile_ver_3_3_0
    #else
     #define use_lib_esp_arduino_compile_ver_1_0_0
    #endif    
   #else
    #define use_lib_esp_arduino_compile_ver_1_0_0
   #endif 
  #else
   #define use_lib_esp_arduino_compile_ver_1_0_0
  #endif  
 #else
  #define use_lib_esp_arduino_compile_ver_1_0_0
 #endif

 #ifdef use_lib_esp_arduino_ver_3_3_0_force
  #undef use_lib_esp_arduino_compile_ver_1_0_0
  #ifndef use_lib_esp_arduino_compile_ver_3_3_0  
   #define use_lib_esp_arduino_compile_ver_3_3_0
  #endif 
 #endif


#endif
