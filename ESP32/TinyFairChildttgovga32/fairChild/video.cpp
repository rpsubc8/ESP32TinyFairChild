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
#include "video.h"
#include "gbGlobals.h"
#include "fairChild.h"


static unsigned char gb_color_vga[8]=
{
 0, //0x10 00010000 00 00 00
 63, //0xFD 11111101 11 11 11
 49, //0x53 1010011 10 0x31 110001 11  0xFF 11111111 11
 8, //0x5D 1011101 10 0xCC 11001100 11  0x02 10 10
 23, //0xF3 11110011 11 0x3F 111111 11 0x4B 1001011 10
 42, //0xE0 11100000 11   111111
 46, //0xA6 10100110 10 0xFF 11111111 11 0x91 10010001 10
 58  //0xD0 11010000 11 0xCE 11001110 11  0xFF 1111111 11
};

//**************************************************
void PreparaColorVGA()
{
 #ifdef use_lib_bitluni_fast
  for (unsigned char i=0;i<8;i++)
  {  
   gb_color_vga[i] = gb_color_vga[i] | gb_sync_bits;  
  } 
 #else	
  for (unsigned char i=0;i<8;i++)
  {  
   gb_color_vga[i] = (gb_color_vga[i] & vga.RGBAXMask) | vga.SBits;  
  }
 #endif 
}

//JJ pixel_t VIDEO_Buffer_rgb[8192]; // 128x64 //No lo necesito
//JJ unsigned char VIDEO_Buffer_raw[8192]; // 128x64
unsigned char VIDEO_Buffer_raw[VIDEO_SIZE]; // 128x64
//static const pixel_t colors[8] =
//  {
//	  vRGB(0x10, 0x10, 0x10), //0
//	  vRGB(0xFD, 0xFD, 0xFD), //63
//	  vRGB(0x53, 0x31, 0xFF), //49
//	  vRGB(0x5D, 0xCC, 0x02), //8
//	  vRGB(0xF3, 0x3F, 0x4B),
//	  vRGB(0xE0, 0xE0, 0xE0),
//	  vRGB(0xA6, 0xFF, 0x91),
//	  vRGB(0xD0, 0xCE, 0xFF)
//  };
static const unsigned char palette[16] = {0,1,1,1, 7,2,4,3, 6,2,4,3, 5,2,4,3}; // bk wh wh wh, bl B G R, gr B G R, gy B G R...

unsigned char ARM = 0;
unsigned char X = 0;
unsigned char Y = 0;
unsigned char Color = 2; 


//void jj_fast_putpixel_no_clip(SDL_Surface *auxScreen, int x,int y,unsigned char c)
//inline static void jj_fast_putpixel_no_clip(int x,int y,unsigned char c)
//{
// x= (x<<1)+20;
// y= (y<<1)+10;
// //if ((x<0)||(x>639)||(y<0)||(y>399))
// //if ((x<0)||(x>319)||(y<0)||(y>199))
// // return; 
//// vga.dotFast(x,y,gb_color_vga[c]);
//// vga.dotFast(x+1,y,gb_color_vga[c]);
//// vga.dotFast(x,y+1,gb_color_vga[c]);
//// vga.dotFast(x+1,y+1,gb_color_vga[c]);
// 
// gb_buffer_vga[y][x^2]= gb_color_vga[c];
// gb_buffer_vga[y][(x+1)^2]= gb_color_vga[c];
// gb_buffer_vga[y+1][x^2]= gb_color_vga[c];
// gb_buffer_vga[y+1][(x+1)^2]= gb_color_vga[c];
//}

//void jj_fast_putpixel(SDL_Surface *auxScreen, int x,int y,unsigned char c)
void jj_fast_putpixel(int x,int y,unsigned char c)
{
 //if ((x<0)||(x>319)||(y<0)||(y>199))
 // return;
// vga.dotFast(x,y,gb_color_vga[c]);
 gb_buffer_vga[y][x^2]= gb_color_vga[c];
}

/*
void VIDEO_drawFrame(void)
{//795 807 micros rutina casi original con fast bitluni
 //Queda en 726 micros con fast bitluni
 int row;
 int col;
 unsigned char color;
 unsigned char pal;
 unsigned int auxRow=0;
 for(row=0; row<64; row++)
 {  
  pal = ((VIDEO_Buffer_raw[(auxRow+125)]&2)>>1) | (VIDEO_Buffer_raw[(auxRow+126)]&3);
  pal = (pal<<2) & 0xC;  
  for(col=0; col<128; col++)
  {
   color = (VIDEO_Buffer_raw[(auxRow+col)]) & 0x3;
   color = palette[pal|color]&0x7;
   gb_buffer_vga[row][col^2]= gb_color_vga[color];
  }
  auxRow+= 128;
 }
}
*/


//Fast 32 bits DMA
void VIDEO_drawFrame(void)
{//385 micros con fast bitluni
 unsigned int a0,a1,a2,a3;
 unsigned int a32;
 //unsigned int *ptr32;
 unsigned int auxCol;
 unsigned int auxRow=0;
 unsigned int row;
 unsigned int col;
 unsigned int color;
 unsigned int pal;	

 
	for(row=0; row<64; row++)
	{
		// The last three columns in the video buffer are special.
		// 127 - unknown
		// 126 - bit 1 = palette bit 1
		// 125 - bit 1 = palette bit 0 (or with 126 bit 0)
		// (palette is shifted by two and added to 'color'
		//  to find palette index which holds the color's index)
		
		pal = ((VIDEO_Buffer_raw[(auxRow+125)]&2)>>1) | (VIDEO_Buffer_raw[(auxRow+126)]&3);
		pal = (pal<<2) & 0xC;
		
		//JJ for(col=0; col<128; col++)
		//for(col=0; col<126; col++)		
		//ptr32= (unsigned int *)gb_buffer_vga[row];		
		//ptr32= gb_buffer_vga32[row];		
		auxCol=0;		
		//for(col=0; col<32; col++) //128 DIV 4
		for(col=0; col<26; col++) //104 DIV 4
		{
			//color = (VIDEO_Buffer_raw[(row<<7)+col]) & 0x3;
			//color = palette[pal|color]&0x7;
			//gb_buffer_vga[row][col^2]= gb_color_vga[color];

    a0= (VIDEO_Buffer_raw[auxRow+auxCol]) & 0x3;
	a0 = palette[pal|a0];//&0x7;

    a1= (VIDEO_Buffer_raw[auxRow+auxCol+1]) & 0x3;
	a1 = palette[pal|a1];//&0x7;

	a2= (VIDEO_Buffer_raw[auxRow+auxCol+2]) & 0x3;
	a2 = palette[pal|a2];//&0x7;

	a3= (VIDEO_Buffer_raw[auxRow+auxCol+3]) & 0x3;
	a3 = palette[pal|a3];//&0x7;	
	
	auxCol+=4;

    a32= (gb_color_vga[a2]) | (gb_color_vga[a3]<<8) | (gb_color_vga[a0]<<16) | (gb_color_vga[a1]<<24);
	//ptr32[col]= a32;
	gb_buffer_vga32[(row+gb_add_offset_y)][(col+gb_add_offset_x)]= a32;

			//jj_fast_putpixel_no_clip(col,row,color);
			//JJ VIDEO_Buffer_rgb[(row<<7)+col] = colors[palette[pal|color]&0x7]; //No lo necesito
		}

		auxRow+= 128;
	}

}


void VIDEO_portReceive(int port, int val)
{
	switch(port)
	{
		case 0: // ARM 
			val &= 0x60;
			if(val==0x40 && ARM==0x60) // Strobed
			{
				// Write to display buffer
				VIDEO_Buffer_raw[(Y<<7)+X] = Color;
			}
			ARM = val;
		break;

		case 1: // Set Color (bits 6 and 7) 
			Color = ((val ^ 0xFF)>>6)&3;
			break;
		case 4: // X coordinate, inverted (bits 0-6)
			X = (val ^ 0xFF) & 0x7F;
			break;
		case 5: // Y coordinate, inverted (bits 0-5)
			Y = (val ^ 0xFF) & 0x3F;
			break;
	}
}
