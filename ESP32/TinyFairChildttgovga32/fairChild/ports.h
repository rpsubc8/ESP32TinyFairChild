#ifndef PORTS_H
#define PORTS_H

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

// IO Ports 
//extern unsigned char Ports[64];

//JJ int PORTS_read(int port);
unsigned char PORTS_read(unsigned char port);

//void PORTS_write(int port, unsigned char val);
void PORTS_write(unsigned char port, unsigned char val);

//JJ void PORTS_notify(int port, unsigned char val);
void PORTS_notify(unsigned char port, unsigned char val);

void PORTS_reset(void);

#endif
