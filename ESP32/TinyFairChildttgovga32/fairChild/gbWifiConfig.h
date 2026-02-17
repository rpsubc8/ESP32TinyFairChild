#ifndef _GB_WIFI_CONFIG_H
 #define _GB_WIFI_CONFIG_H

 #define gb_wifi_ssd ""
 #define gb_wifi_pass ""

 //#define gb_wifi_url_base_path "http://192.168.0.36/fairchild/output"
 //https requiere mucha RAM. Usar http
 #define gb_wifi_url_base_path "https://rpsubc8.github.io/ESP32TinyFairChild/www/fairchild/output"


 //Delay check wifi connect
 #define gb_wifi_delay_check 500

 //Delay millis asign http and read data
 #define gb_wifi_delay_asign_read 500

 //Delay millis in check available buffer
 #define gb_wifi_delay_check_available 100

 //millisecons delay stream read
 #define gb_wifi_delay_available 0

 
 //#define use_lib_wifi_debug

#endif

