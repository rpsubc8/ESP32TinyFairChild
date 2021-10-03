#ifndef AUDIO_H
#define AUDIO_H

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

//JJ extern short AUDIO_Buffer[735 * 2];
//JJ extern unsigned char tone;
//JJ extern short amp;

//JJ void AUDIO_tick(int ticks);

//JJ void AUDIO_frame(void);

//JJ void AUDIO_reset(void);

//JJ void AUDIO_portReceive(int port, unsigned char val);
void AUDIO_portReceive(unsigned char port, unsigned char val);

#endif
