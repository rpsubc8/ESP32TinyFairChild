/*
	This file is part of FreeChaF.

	FreeChaF is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	FreeChaF is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with FreeChaF.  If not, see http://www.gnu.org/licenses/
*/

#include "Arduino.h"
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
#include "channelf_hle.h"

#define TICKS_PER_ROW 18606


void unsupported_hle_function(void)
{
	//Serial.printf(stderr, "Unsupported HLE function: 0x%x\n", PC0);
	Serial.printf("Unsupported HLE function: 0x%x\n", PC0);
/*
	char formatted[1024];
	struct retro_message msg;
	msg.msg    = formatted;
	msg.frames = 600;
	Environ(RETRO_ENVIRONMENT_SET_MESSAGE, &msg);
	Environ(RETRO_ENVIRONMENT_SHUTDOWN, NULL);
*/
}

static void hle_clear_row(int row)
{
	memset(VIDEO_Buffer_raw + (row << 7), hle_state.screen_clear_color, 125);
	VIDEO_Buffer_raw[(row << 7) + 125] = 0;
	VIDEO_Buffer_raw[(row << 7) + 126] = hle_state.screen_clear_pal;
	VIDEO_Buffer_raw[(row << 7) + 127] = 0;
}

static int CHANNELF_HLE(void)
{
	if (hle_state.screen_clear_row)
	{
		hle_clear_row(hle_state.screen_clear_row++);
		if (hle_state.screen_clear_row == 64)
		{
			hle_state.screen_clear_row = 0;
		}
		return TICKS_PER_ROW;
	}
	switch (PC0)
	{
	case 0x0: // init
		memset (R, 0, sizeof(R));
		if (Memory[0x800] == 0x55)
		{
			A = 0x55;
			DC0 = 0x801;
			PC0 = 0x802;
			R[0x3b] = 0x28;
			ISAR = 0x3b;
			return 1459;
		}

		unsupported_hle_function();
		return 14914;
	case 0x8f: // delay
	{
		int ticks = 2563 * R[5];
		R[5] = 0;
		R[6] = 0;
		A = 0xff;
		PC0 = PC1;
		return ticks;
	}
	case 0xd0: // screen clear
	{
		// guesswork
		switch (R[3])
		{
		case 0xc6:
			hle_state.screen_clear_pal = 3;
			hle_state.screen_clear_color = 0;
			break;
		case 0x21:
			hle_state.screen_clear_pal = 0;
			hle_state.screen_clear_color = 0;
			break;
		default:
			unsupported_hle_function ();
			return TICKS_PER_FRAME;
		}

		PC0 = PC1;

		if (hle_state.fast_screen_clear)
		{
			int row;
			for(row=0; row<64; row++)
				hle_clear_row(row);
			return TICKS_PER_FRAME;
		}

		hle_clear_row(0);
		hle_state.screen_clear_row = 1;
		
		return TICKS_PER_ROW;
	}
	default:
		unsupported_hle_function();
		return TICKS_PER_FRAME;
	}
}

void CHANNELF_HLE_run(void) // run for one frame
{
	int tick  = 0;
	int ticks = CPU_Ticks_Debt;

	while(ticks<TICKS_PER_FRAME)
	{
		tick = CHANNELF_HLE();
		ticks+=tick;
		//AUDIO_tick(tick);
	}

	CPU_Ticks_Debt = ticks - TICKS_PER_FRAME;
}
