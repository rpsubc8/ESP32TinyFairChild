
#ifndef VGA_6BIT_H_FILE
#define VGA_6BIT_H_FILE

#include "gbConfig.h"
#ifdef use_lib_tinybitluni_fast

#include <cstdint>

//Modos de video
#define video_mode_360x200x70hz_bitluni 0 
#define video_mode_360x200x70hz_bitluni_apll_fix 1
#define video_mode_vga320x200x70hz_bitluni 2
#define video_mode_vga320x200x70hz_fabgl 3
#define video_mode_vga320x200x70hz_bitluni_apll_fix 4
#define video_mode_vga200x150x70hz_bitluni 5
#define video_mode_vga200x150x70hz_bitluni_apll_fix 6


//JJ class VgaMode;
//JJ extern const VgaMode vga_mode_320x240;
//JJ extern const VgaMode vga_mode_288x240;
//JJ extern const VgaMode vga_mode_240x240;

//JJ aniadido
//JJ extern const VgaMode vga_mode_320x200;
//JJ extern const VgaMode vga_mode_200x150;

//320x200 720x400 31.4Khz 70Hz
const unsigned int VgaMode_vga_mode_320x200[12]={
 8,48,24,320,12,2,35,400,2,12587500,0,1 //funciona con 0,1
};

//320x240 640x480 31.4Khz 60Hz
const unsigned int VgaMode_vga_mode_320x240[12]={ 
 8,48,24,320,11,2,31,480,2,12587500,1,1
 //const Mode VGA::MODE320x240(8, 48, 24, 320, 11, 2, 31, 480, 2, 12587500, 1, 1);
};

//360x200 720x400 31.3Khz 70.4Hz
const unsigned int VgaMode_vga_mode_360x200[12]={ 
 8,54,28,360,11,2,32,400,2,14161000,0,1 //funciona con 0,1 polaridad v y h alreves
 //const Mode VGA::MODE360x200(8, 54, 28, 360, 11, 2, 32, 400, 2, 14161000, 1, 0);
};

//200x150 800x600 56Hz
const unsigned int VgaMode_vga_mode_200x150[12]={
 6,18,32,200, 1,2,22,600,4,9000000, 0,0
};



//extern const int VgaMode_vga_mode_200x150[12];


//JJ void vga_init(const int *vga_pins, const VgaMode &mode = vga_mode_320x240, bool double_buffered = true);
//void vga_init(const unsigned char *vga_pins, const VgaMode &mode = vga_mode_320x240, bool double_buffered = true);

//void vga_init(const unsigned char *pin_map, const int *mode, bool double_buffered);
void vga_init(const unsigned char *pin_map, const unsigned int *mode, bool double_buffered,unsigned char pllcteforce, unsigned int p0,unsigned int p1,unsigned int p2,unsigned int p3,unsigned char pllcustomforce,unsigned char is8colors, unsigned char vga_video_mode_id);

void vga_swap_buffers(bool wait_vsync = true);
void vga_clear_screen(uint8_t color);
unsigned char **vga_get_framebuffer();
unsigned char vga_get_sync_bits();
int vga_get_xres();
int vga_get_yres();

unsigned char vga_get_vsync_inv_bit(void);
unsigned char vga_get_hsync_inv_bit(void);
int vga_get_y_res(void);
void vga_free(unsigned char freeHalf);
void vga_freeGPIO(void);
unsigned int vga_get_pll_cte_p0(void);
unsigned int vga_get_pll_cte_p1(void);
unsigned int vga_get_pll_cte_p2(void);
unsigned int vga_get_pll_cte_p3(void);

void SetVideoInterrupt(unsigned char auxState);
//void WaitVsync(void);
void custom_rtc_clk_apll_enable(bool enable, uint32_t sdm0, uint32_t sdm1, uint32_t sdm2, uint32_t o_div);
void FreeInterrupt(void);

#endif

#endif //VGA_6BIT_H_FILE
