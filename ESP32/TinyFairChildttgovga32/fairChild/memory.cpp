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

#include <string.h>
#include "memory.h"
#include "gbConfig.h"
#include "gbGlobals.h"
#ifdef use_lib_minimal_ram
 #include "gbRoms131253.h"
 #include "gbRomsl90025.h"
 #include "gbRoms131254.h"
 #include "gbCartDemo.h"
 #include "gbCartPacman.h"
#endif 

int MEMORY_RAMStart;
unsigned char Memory[MEMORY_SIZE];


#ifdef use_lib_minimal_ram
 unsigned char tiny_read_memory(unsigned short int addrMem)
 {
  if (addrMem<0x400) //0 - 1024
   return gb_rom_sl31253_bin[addrMem];
  if (addrMem<0x800) //1024 - 2048
   return gb_rom_sl31254_bin[(addrMem-0x400)];
  if (addrMem<(8192+0x800)) //Pacman
   return gb_cart_pacman_chf[(addrMem-(8192+0x800))];
  return 0;
 }
 
 void tiny_write_memory(unsigned short int addrMem, unsigned char aData)
 {
  //if ((addrMem>=0x800)&&(8192+0x800)) //Pacman
  // return gb_cart_pacman_chf[(addrMem-(8192+0x800))];      
 }
#endif

void MEMORY_reset(void)
{
 //clear memory
 #ifdef use_lib_minimal_ram  
 #else 
  memset (Memory + MEMORY_RAMStart, 0, MEMORY_SIZE - MEMORY_RAMStart);
 #endif 
}
