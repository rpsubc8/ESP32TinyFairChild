#ifndef VIDEO_H
 #define VIDEO_H

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


// 128x64
//#define VIDEO_SIZE 8192
//extern unsigned char VIDEO_Buffer_raw[VIDEO_SIZE];
//extern unsigned char ARM;
//extern unsigned char X;
//extern unsigned char Y;
//extern unsigned char Color;

void VIDEO_portReceive(int port, int val);
void PreparaColorVGA(void);

//void jj_fast_putpixel_no_clip(int x,int y,unsigned char c);
void jj_fast_putpixel(int x,int y,unsigned char c);
//void jj_fast_putpixel_no_clip(SDL_Surface *auxScreen, int x,int y,unsigned char c);
//void jj_fast_putpixel(SDL_Surface *auxScreen, int x,int y,unsigned char c);

void VIDEO_drawFrame(void);

#ifdef USE_RGB565
typedef unsigned short pixel_t;
#if defined(ABGR1555)
#define vRGB(r,g,b) ((((b) & 0xf8) << 7) | (((g) & 0xf8) << 2) | (((r) & 0xf8) >> 3))
#else
#define vRGB(r,g,b) ((((r) & 0xf8) << 8) | (((g) & 0xfc) << 3) | (((b) & 0xf8) >> 3))
#endif
#else
typedef unsigned int pixel_t;
#define vRGB(r,g,b) (((r) << 16) | ((g) << 8) | (b))
#endif

//JJ #define BLACK vRGB(0,0,0)
//JJ #define WHITE vRGB(0xff, 0xff, 0xff)
//JJ #define YELLOW vRGB(0xff, 0xff, 0)
//JJ #define GRAY_CC vRGB(0xCC, 0xCC, 0xCC)
//JJ #define GREEN vRGB(0, 0xff, 0)

//JJ extern pixel_t VIDEO_Buffer_rgb[VIDEO_SIZE]; // 128x64 //No lo necesito

#endif
