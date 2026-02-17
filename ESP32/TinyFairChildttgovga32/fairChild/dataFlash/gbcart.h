#ifndef _GB_CART_H
 #define _GB_CART_H

 #include "gbCompileDataOpt.h"

 //#include <stddef.h>
 #ifdef gb_use_lib_compile_arduinodroid
  #include "gbCartPacman.h"
  #include "gbCartDemo.h"
  #include "gbCartCctro.h"
  #include "gbCartInvasion.h"
  #include "gbCartTetris.h"
  #include "gbCartGalacticSpaceWars.h"
  #include "gbCartPinball.h"
 #else
  #include "cart/gbCartPacman.h"
  #include "cart/gbCartDemo.h"
  #include "cart/gbCartCctro.h"
  #include "cart/gbCartInvasion.h"
  #include "cart/gbCartTetris.h"
  #include "cart/gbCartGalacticSpaceWars.h"
  #include "cart/gbCartPinball.h"
 #endif
 
 #define max_list_cart 7
 
 //Titulos
 static const char * gb_list_cart_title[max_list_cart]={
  "pacman"
  ,"demo"  
  ,"cctro"
  ,"invasion"
  ,"tetris"
  ,"galactic wars"
  ,"pinball"
 };
 
 //Tamanio en bytes
 static const unsigned short int gb_list_cart_size[max_list_cart]={
  8192
  ,2048  
  ,2048
  ,4096
  ,3583
  ,2048
  ,2048
 };
  
 //Datos
 static const unsigned char * gb_list_cart_data[max_list_cart]={
  gb_cart_pacman_chf  
  ,gb_cart_demo
  ,gb_cart_cctro_bin
  ,gb_cart_invasion_chf
  ,gb_cart_tetris_chf
  ,gb_cart_galacticspacewars_chf
  ,gb_cart_pinball_chf
 };


#endif
