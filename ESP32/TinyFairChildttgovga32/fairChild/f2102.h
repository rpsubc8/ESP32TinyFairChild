#ifndef F2102_H
#define F2102_H

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

//JJ void F2102_portReceive(int port, unsigned char val);
void F2102_portReceive(unsigned char port, unsigned char val);

void F2102_reset(void);

//JJ extern unsigned short f2102_state;
//JJ extern unsigned char f2102_memory[1024];
//JJ extern unsigned short f2102_address;
//JJ extern unsigned char f2102_rw;

#endif
