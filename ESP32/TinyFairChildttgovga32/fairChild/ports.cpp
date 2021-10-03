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

#include "ports.h"
#include "f2102.h"
#include "audio.h"
#include "video.h"
#include "controller.h"
#include <stdio.h>
#include <string.h>

unsigned char Ports[64];

// Read state of port
//JJ int PORTS_read(int port)
unsigned char PORTS_read(unsigned char port)
{
 return Ports[port] | CONTROLLER_portRead(port); // controllers don't latch?
}

// Write data to port
//JJ void PORTS_write(int port, unsigned char val)
void PORTS_write(unsigned char port, unsigned char val)
{//Solo son 64 puertos
 Ports[port] = val; 
 if (port == 5){
  //printf("PORTS_write %d %d\n",port,val);
  //fflush(stdout);
 }
  
}


//JJ void PORTS_notify(int port, unsigned char val)
void PORTS_notify(unsigned char port, unsigned char val)
{
 Ports[port] = val;
 
/* if (port == 5)
 {  
  switch (((val>>6)&0x03))
  {
   case 0: gb_volumen01= gb_frecuencia01=0; break;
   case 1: gb_frecuencia01=1000;gb_volumen01=1; break;
   case 2: gb_frecuencia01=500; gb_volumen01=1;break;                  
   case 3: gb_frecuencia01=120;gb_volumen01=1; break;         
  }
  CalculaPulsosSonido(gb_frecuencia01);
  //printf("PORTS_notify %d %d\n",port,(val>>6)&0x03);
  //fflush(stdout);  
 }
 else
 {
  //gb_volumen01= gb_frecuencia01=0;
 }
 */

 F2102_portReceive(port, val);
 AUDIO_portReceive(port, val);
 VIDEO_portReceive(port, val);
 CONTROLLER_portReceive(port, val);
}

void PORTS_reset(void)
{
//JJ	int i;
//JJ	for(i=0; i<64; i++)
//JJ		Ports[i] = 0;
 memset(Ports,0,sizeof(Ports));
}
