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
#include "gbConfig.h"
#include "gbGlobals.h"
#include "f2102.h"
#include "ports.h"


unsigned short f2102_state = 0;
unsigned char f2102_memory[1024];
unsigned short f2102_address = 0;
unsigned char f2102_rw = 0;

//JJ void F2102_portReceive(int port, unsigned char val)
void F2102_portReceive(unsigned char port, unsigned char val)
{
	switch(port)
	{
		case 0x20:
		case 0x24:
			f2102_state = (f2102_state & 0xFF) | (val<<8);

			f2102_rw = val & 1; //read/write bit = val bit 0

			f2102_address = f2102_address & 0x3F3; // clear address bits 2, 3
			f2102_address = f2102_address | (val & 0x04); // address bit 2 = val bit 2
			f2102_address = f2102_address | ((val & 0x02)<<2); // address bit 3 = val bit 1

			if(f2102_rw==0) // read/write bit = 0-read, 1-write
			{
				// read - output bit in state bit 15 (port 24 bit 7)
				f2102_state = (f2102_state & 0x7FFF) | (f2102_memory[f2102_address]<<15);
			}
			else
			{
				// write
				f2102_memory[f2102_address] = (val>>3) & 1; // data = val bit 3
			}
		break;
		
		case 0x21:
		case 0x25:
			f2102_state = (f2102_state & 0xFF00) | (val);
			
			f2102_address = f2102_address & 0x0C; // clear all, save bits 2, 3
			// set bits 9,8,7 to val bits 7,6,5
			f2102_address = f2102_address | ((val & 0xE0)<<2);
			// set bits 6,5,4 to val bits 3,2,1
			f2102_address = f2102_address | ((val & 0x0E)<<3);
			// set bit 1 to val bit 4
			f2102_address = f2102_address | ((val&0x10)>>3);
			// set bit 0 to val bit 0
			f2102_address = f2102_address | (val & 1);
		break;
	}
	
	//poll
	PORTS_write(0x24, f2102_state>>8);
	PORTS_write(0x25, f2102_state & 0xFF);
}

void F2102_reset(void)
{
 f2102_state = 0;
 f2102_address = 0;
 memset (f2102_memory, 0, sizeof(f2102_memory));
}
