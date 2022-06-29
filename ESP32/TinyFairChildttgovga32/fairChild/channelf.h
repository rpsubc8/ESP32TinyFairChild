#ifndef _CHANNELF_H
 #define _CHANNELF_H

 #include "gbConfig.h"
 #include "gbGlobals.h"
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

//extern int CPU_Ticks_Debt;

//int CHANNELF_loadROM(const char* path, int address);

#ifdef use_lib_wifi
 int CHANNELF_loadROM_mem_wifi(int address);
#endif
int CHANNELF_loadROM_mem(const unsigned char* data, int sz, int address);

void CHANNELF_run(void);

void CHANNELF_init(void);

void CHANNELF_reset(void);

#define TICKS_PER_FRAME 14914

#endif
