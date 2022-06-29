//	This file is part of FreeChaF.
//
//	FreeChaF is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	(at your option) any later version.
//
//	FreeChaF is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with FreeChaF.  If not, see http://www.gnu.org/licenses/

#include "gbConfig.h"
#include "gbGlobals.h"
#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//JJ #include "libretro.h"
#include "channelf.h"
#include "memory.h"
#include "f8.h"
#include "audio.h"
#include "f2102.h"
#include "ports.h"
#include "video.h"
#ifdef use_lib_wifi
 #include "gbWifiConfig.h"
 #include "gbWifi.h"
 #include "osd.h"
#endif

int CPU_Ticks_Debt = 0;

//int CHANNELF_loadROM(const char* path, int address)
//{
//	unsigned char word;
//	FILE *fp;
//	if((fp = fopen(path,"rb"))!=NULL)
//	{
//		while(fread(&word,sizeof(word),1,fp) && address<0x10000)
//		{
//         #ifdef use_lib_minimal_ram
//         #else
//		  Memory[address] = word;
//   		 #endif
//		 address++;
//		}
//		
//		if (address>MEMORY_RAMStart) { MEMORY_RAMStart = address; }
//
//		fclose(fp);
//		return 1;	
//	}
//   return 0;
//}

#ifdef use_lib_wifi
 int CHANNELF_loadROM_mem_wifi(int address)
 {
  int auxFileSize=0;
  int length = 0;  
  if (strcmp(gb_cadUrl,"")==0)
  {
   #ifdef use_lib_wifi_debug
    Serial.printf("cart name empty\n");
   #endif   
   return 1;
  }
  
  #ifdef use_lib_wifi_debug
   Serial.printf("load_cart_WIFI\n");
  #endif
  #ifdef use_lib_wifi_debug
   Serial.printf("Check WIFI\n");
  #endif

  ShowStatusWIFI(1);

  if (Check_WIFI() == false)
  {
   ShowStatusWIFI(0);
   return 1;
  }    

  int leidos=0;
  #ifdef use_lib_wifi_debug
   //Serial.printf("URL:%s\n",cadUrl);
   Serial.printf("URL:%s\n",gb_cadUrl);   
  #endif   
  //Asignar_URL_stream_WIFI(cadUrl);
  Asignar_URL_stream_WIFI(gb_cadUrl);
  auxFileSize= gb_size_file_wifi;

  length = auxFileSize;
  if (length > 0x10000 - address)
  {
   length = 0x10000 - address;
  }

  #ifdef use_lib_wifi_debug
   Serial.printf("Size cart:%d\n",gb_size_file_wifi);
  #endif
  Leer_url_stream_WIFI(&leidos);
  #ifdef use_lib_wifi_debug
   Serial.printf("Leidos:%d\n",leidos); //Leemos 1024 bytes
  #endif

  //He leido 1024 bytes. Lee resto
  int contBuffer=0;
  int cont1024= 0;
  while (contBuffer< auxFileSize)
  {
   if (contBuffer>= length)
   {
    #ifdef use_lib_wifi_debug
     Serial.printf("Limit exced 0x10000\n");
    #endif            
    break;
   }
   //cart[contBuffer]= gb_buffer_wifi[cont1024];
   Memory[(address+contBuffer)] = gb_buffer_wifi[cont1024];
   contBuffer++;

   cont1024++;
   if (cont1024 >= 1024)
   {
    Leer_url_stream_WIFI(&leidos);
    #ifdef use_lib_wifi_debug
     Serial.printf("Leidos:%d\n",leidos);
    #endif 
    cont1024= 0;
   }
  }
  ShowStatusWIFI(0);

  if (address+length>MEMORY_RAMStart) { MEMORY_RAMStart = address+length; }

//	int length = size;
//	if (length > 0x10000 - address)
//	{
//		length = 0x10000 - address;
//	}
//	#ifdef use_lib_minimal_ram
//	#else
// 	 memcpy(Memory + address, data, length);
//	#endif
//		
//	if (address+length>MEMORY_RAMStart) { MEMORY_RAMStart = address+length; }

	return 1;
 }
#endif 

int CHANNELF_loadROM_mem(const unsigned char* data, int size, int address)
{
	int length = size;
	if (length > 0x10000 - address)
	{
		length = 0x10000 - address;
	}
	#ifdef use_lib_minimal_ram
	#else
 	 memcpy(Memory + address, data, length);
	#endif
		
	if (address+length>MEMORY_RAMStart) { MEMORY_RAMStart = address+length; }

	return 1;
}

void CHANNELF_run(void) // run for one frame
{
	int tick  = 0;
	int ticks = CPU_Ticks_Debt;
	unsigned char contCPU=0;
	unsigned int cpu_before,cpu_cur;
	int microsMedido,microsExacto;
	int microsEspera;

    if (gb_auto_delay_cpu==1)
	{//14914 ticks en 20 milis
	 cpu_before= cpu_cur= micros();
	 while(ticks<TICKS_PER_FRAME)
	 {	  
  	  tick = F8_exec(); //El que ejecuta el emulador      
	  ticks+=tick;

	  if ((contCPU & 0x03) == 0)
	  {//Cada 4 iteraciones 00000011
	   cpu_cur= micros();
	   microsMedido= (cpu_cur-cpu_before);
	   microsExacto= ((ticks * 20000)/TICKS_PER_FRAME);
	   //180 micros y mido 30  180-30=60
	   microsEspera= (microsExacto-microsMedido);
	   if ((microsEspera>0)&&(microsEspera<=20000))
	   {
	    delayMicroseconds(microsEspera);
	   }
	  }
	  contCPU++;
	 }
	}
	else
	{
	 while(ticks<TICKS_PER_FRAME)
	 {
  	  tick = F8_exec(); //El que ejecuta el emulador
	  ticks+=tick;		
	  if ((contCPU & 0x03) == 0)
	  {//Cada 4 iteraciones 00000011
	   delayMicroseconds(gb_delay_tick_cpu_micros);	  
	  }
	  contCPU++;
      //if (ticks % 768 == 0)
	  //delayMicroseconds(1000);
	  //AUDIO_tick(tick);
	 }
	}
	CPU_Ticks_Debt = ticks - TICKS_PER_FRAME;
	
  //printf("PC:0x%04X\n",PC0);
  //fflush(stdout);
}

void CHANNELF_init(void)
{
	F8_init();
	CHANNELF_reset();
}

void CHANNELF_reset(void)
{
	CPU_Ticks_Debt = 0;
	MEMORY_reset();
	F2102_reset();
	F8_reset();
	tone = 0; //AUDIO_reset();
	PORTS_reset();
}
