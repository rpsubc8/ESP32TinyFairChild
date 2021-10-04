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
#include "controller.h"
#include "ports.h"
#include "channelf.h"

#include <stdio.h>

int State[] = {0,0,0};
unsigned char ControllerEnabled = 0;

//JJ #define Console 0
//JJ #define ControlA 1
//JJ #define ControlB 2

static const int ConsolePort = 0;
#define ControlAPort (ControllerSwapped ? 4 : 1)
#define ControlBPort (ControllerSwapped ? 1 : 4)
unsigned char ControllerSwapped = 0;

//JJ void setButton(int control, int button, int pressed)
void setButton(unsigned char control, unsigned char button, unsigned char pressed)
{
 //El 0 es el console
 //El 1 es el ControlA
 //El 1 es el ControlB
   //// Console 
   //0 // TIME
   //1 // MODE
   //2 // HOLD
   //3 // START

   //// Controller
   //0 // Right
   //1 // Left
   //2 // Back
   //3 // Forward
   //4 // rot left
   //5 // rot right
   //6 // pull
   //7 // push   

   if(pressed)
      State[control] |= 1<<button;
   else
      State[control] &= (1<<button)^0xFF;

 //printf("control:%d button:%d pressed:%d\n",control,button,pressed);
 //fflush(stdout);
}

//JJ void CONTROLLER_setInput(int control, int state)
void CONTROLLER_setInput(unsigned char control, int state)
{
 //if(control>=0 && control<=2)
 if (control<=2)
  State[control] = state;
}

void CONTROLLER_swap(void)
{
	ControllerSwapped ^= 1;
}

int CONTROLLER_swapped(void)
{
	return ControllerSwapped;
}

//JJ int CONTROLLER_portRead(int port)
unsigned char CONTROLLER_portRead(unsigned char port)
{
 if(port==ConsolePort)
  return (State[Console]^0xFF) & 0x0F;
 if(ControllerEnabled)
 {
  if(port==ControlAPort)
   return(State[ControlA]^0xFF);
  if(port==ControlBPort)
   return(State[ControlB]^0xFF);
 }
 return 0;
}

//JJ void CONTROLLER_portReceive(int port, unsigned char val)
void CONTROLLER_portReceive(unsigned char port, unsigned char val)
{
	if(port==ConsolePort) // Console
		ControllerEnabled = (val&0x40)==0;
}

/* Console buttons */

int cursorX    = 4; /* initial cursor setting 'Start'  */
int cursorDown = 0;

void CONTROLLER_consoleInput(int action, int pressed)
{
	switch(action)
	{
		case 0:
         if(pressed)
            cursorX--;
         break;
		case 1:
         if(pressed)
            cursorX++;
         break;
		case 2:
			cursorDown = pressed;
			if(cursorX==0)
         {
            if(pressed)
               CHANNELF_reset();
         }
			else
				setButton(0, cursorX-1, pressed);
			break;
	}

	if (cursorX<0)
      cursorX = 4;
	if (cursorX>4)
      cursorX = 0;
}

int CONTROLLER_cursorPos(void)
{
	return cursorX;
}
int CONTROLLER_cursorDown(void)
{
	return cursorDown;
}
