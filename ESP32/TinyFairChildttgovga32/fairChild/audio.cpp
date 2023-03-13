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
#include "audio.h"
#include <stdio.h>
#include <string.h>

//JJ #include "sintable.h"
//#include "hardware.h"
//#ifdef use_lib_audio_tone32
// #include "Tone32.h"
//#endif


//JJ short AUDIO_Buffer[735 * 2];

//unsigned char tone = 0; // current tone
unsigned char gb_tone = 0; // current tone

//JJ static const int samplesPerFrame = 735; // sampleRate / framesPerSecond

//JJ int sampleInCycle = 0; // time since start of tone, resets to 0 after every full cycle
//JJ #define FULL_AMPLITUDE 16384
//JJ short amp = FULL_AMPLITUDE; // tone amplitude (16384 = full)
//JJ static const float decay = 0.998; // multiplier for amp per sample

//JJ short ticks = 0; // unprocessed ticks in 1/100 of tick
//JJ int sample = 0; // current sample buffer position

static inline void CalculaPulsosSonido(int frec)
{ 
 //freq= (gb_volumen01==0)?0:gb_frecuencia01;
 //int auxContOnda;
 if (frec!=0) gb_pulsos_onda= (SAMPLE_RATE/frec)>>1; 
 else gb_pulsos_onda=0;
 gb_cont_my_callbackfunc=0;
 //unsigned char estadoOnda=0;
}


//JJ void AUDIO_portReceive(int port, unsigned char val)
void AUDIO_portReceive(unsigned char port, unsigned char val)
{
	if(port==5)
	{
		// Set Tone, bits 6 & 7: 
		// 0 - Silence
		// 1 - 1000hz
		// 2 - 500hz
		// 3 - 120hz
		
		
		val = (val&0xC0)>>6;
		if(val!=gb_tone)
		{
		 gb_tone = val;
		 //JJ amp = FULL_AMPLITUDE;// No lo necesito
		 //JJ sampleInCycle=0;

  switch (gb_tone)
  {
   case 0: gb_volumen01= gb_frecuencia01=0; break;
   case 1: gb_frecuencia01=1000;gb_volumen01=1; break;
   case 2: gb_frecuencia01=500; gb_volumen01=1;break;                  
   case 3: gb_frecuencia01=120;gb_volumen01=1; break;         
  }
  CalculaPulsosSonido(gb_frecuencia01);

  //#ifdef use_lib_audio_tone32
  // Tone32_noTone(SPEAKER_PIN, SPEAKER_CHANNEL);
  // Tone32_tone(SPEAKER_PIN, gb_frecuencia01, 0, SPEAKER_CHANNEL);
  //#endif
  //tone(25,200);     
  //Audio PWM ledcWriteTone(1,gb_frecuencia01);
  //printf("PORTS_notify %d %d\n",port,(val>>6)&0x03);
  //fflush(stdout);

		 /*switch (tone)
         {
          case 0: gb_volumen01= gb_frecuencia01=0; break;
          case 1: gb_frecuencia01=1000;gb_volumen01=1; break;
          case 2: gb_frecuencia01=500; gb_volumen01=1;break;                  
          case 3: gb_frecuencia01=120;gb_volumen01=1; break;         
         }
         if (tone!=0){
          gb_frecuencia01=500;gb_volumen01=1;
         }
         else{
          gb_frecuencia01=0;gb_volumen01=0;
         }
         */
         
   		 //printf("Vol:%d Freq:%d Tone:%d\n",gb_volumen01,gb_frecuencia01,tone);
		 //fflush(stdout);
        			
		}
	}
}

/*void AUDIO_tick(int dt) // dt = ticks elapsed since last call
{
	// an audio frame lasts ~14914 ticks
	// at 44.1khz, there are 735 samples per frame
	// ~20.29 ticks per sample (14913.15 ticks/frame)
	
	ticks += dt * 100;

	while(ticks>2029)
	{
		ticks-=2029;
		
		AUDIO_Buffer[sample] = 0;
		if(sample<samplesPerFrame) // output sample
		{
			int toneOutput = 0;
			// sintable is a 20Hz tone, we need to speed it up to 1000, 500, 120 or 240 Hz
			switch (tone) {
			case 1:
				toneOutput = 2 * sintable[(sampleInCycle * 50) % SINSAMPLES];
				break;
			case 2:
				toneOutput = 2 * sintable[(sampleInCycle * 25) % SINSAMPLES];
				break;
			case 3:
				toneOutput = sintable[(sampleInCycle * 6) % SINSAMPLES];
				toneOutput += sintable[(sampleInCycle * 12) % SINSAMPLES];
				break;
			}

			int res = (toneOutput * amp) / 100000;
			AUDIO_Buffer[2 * sample] = res;
			AUDIO_Buffer[2 * sample + 1] = res;
		}
		
		//JJ amp *= decay;
		amp *= (short)decay;
		sample++;

		// generate tones //
		sampleInCycle++;
		// All tones are multiples of 20 Hz
		sampleInCycle %= SINSAMPLES;
	}
}
*/

/*void AUDIO_frame(void)
{
	while(sample<samplesPerFrame)
	{
		AUDIO_Buffer[sample]=0;
		sample++;
	}
	// start a new audio frame
	sample = 0;
}
*/

/*
void AUDIO_reset(void)
{
	//JJ memset(AUDIO_Buffer, 0, sizeof(AUDIO_Buffer));

	// reset tone generator
	tone = 0;

	// start a new audio frame
	//JJ sample = 0;
	
	//printf("AUDIO reset\n");
	//fflush(stdout);
}
*/
