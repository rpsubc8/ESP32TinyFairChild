#ifndef OSDFILE_H
 #define OSDFILE_H
 
 #define osd_maxcadaux 21

 //Colores Indices en Fairchild
 #define ID_COLOR_BLACK 0 //Negro
 #define ID_COLOR_WHITE 1 //Blanco
 #define ID_COLOR_VIOLETA 2 //Violeta

 void changeSna2Flash(unsigned char id);
 void do_tinyOSD(void);
 //void SDLAssignSDLSurfaceOSD(SDL_Surface *surface,SDL_Event * ptrEvent);
 void SDLActivarOSDMainMenu();
 void SDLOSDClear(void);
 //SDL_Surface * SDLOSDGetSurface();
 void SDLEsperaTeclado(void);
 void SDLClear(void);
 void ShowStatusWIFI(unsigned char aState);
 void OSDUpdateAnchoAltoVGA(unsigned char modeVideo, unsigned char is8colors);
 void OSDprintTextFPS(char *cad,unsigned char x, unsigned char y, unsigned char color,unsigned char backcolor);
#endif
