
# Tiny Fairchild Channel F
Port of the FreeChaF retroarch emulator (FairChild Channel F) to the TTGO VGA32 v1.0, v1.1, v1.2 and v1.4 board with ESP32.
<br>
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyFairChild/main/preview/pacman.gif'></center>
I have made several modifications:
<ul>
 <li>Ported from retroarch to ESP32</li>
 <li>No PSRAM used, running on ESP32 520 KB RAM (TTGO VGA32 v1.x)</li> 
 <li>Use of a single core</li>
 <li>Low resource OSD</li>
 <li>Created project compatible with Arduino IDE and Platform IO</li>
 <li>Any digital pin can be used for audio (SPEAKER_PIN in hardware.h).</li>
 <li>Any digital pin can be used for video (hardware.h).</li>
 <li>X and Y screen adjustment</li>
 <li>Emulation video speed menu, keyboard</li>
 <li>Support for 64-color mode and 8-color mode.</li>   
 <li>VGA 200x150</li>
 <li>VGA 320x200</li>
 <li>The complete bitluni library is not required. I have reduced to the minimum, saving RAM and FLASH, based on Ricardo Massaro's library.</li>
</ul> 


<br><br>
<h1>Requirements</h1>
Required:
 <ul>
  <li>TTGO VGA32 v1.x (1.0, 1.1, 1.2, 1.4) o Single core ESP32</li>
  <li>Visual Studio 1.48.1 PLATFORMIO 2.2.0</li>
  <li>Arduino IDE 1.8.11</li>
 </ul>
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyFairChild/main/preview/ttgovga32v12.jpg'></center>
The attached image is of my TTGO VGA32 v1.2 board without psram or SD module.
<br>


<br><br>
<h1>PlatformIO</h1>
PLATFORMIO 2.2.0 must be installed from the Visual Studio extensions.
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyFairChild/main/preview/previewPlatformIOinstall.gif'></center>
Then the working directory <b>TinyFairChildttgovga32</b> will be selected.
We must modify the <b>platformio.ini</b> file <b>upload_port</b> option to select the COM port where we have our TTGO VGA32 board.
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyFairChild/main/preview/previewPlatformIO.gif'></center>
Then we will proceed to compile and upload to the board. No partitions are used, so we must upload the entire compiled binary.
It's all set up so we don't have to install any libraries.


<br><br>
<h1>Arduino IDE</h1>
The whole project is compatible with the Arduino 1.8.11 framework.
We just need to open the <b>fairChild.ino</b> in the <b>fairChild</b> directory.
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyFairChild/main/preview/previewArduinoIDEpreferences.gif'></center>
For normal mode, the project is already prepared, so no library is needed. 
We must disable the PSRAM option, and in case of exceeding 1 MB of binary, select 4 MB partition at upload time. Although the code does not use PSRAM, if the option is active and our ESP32 does not have it, an exception will be generated and it will restart in loop mode.


<br><br>
<h1>Keyboard</h1>
The keyboard is divided into 3 parts
<ul>
 <li>System Control: 0,1,2,3</li>
 <li>Control A: Left, Right, Up, Down, o,p</li>
 <li>Control B: a,d,w,s c,v</li>
</ul>


<br><br>
<h1>Options</h1>
The <b>gbConfig.h</b> file options are selected:
<ul>
 <li><b>use_lib_200x150:</b> Video mode 200x150 is used. You have to choose only one video mode, either 200x150 or 320x200.</li>
 <li><b>use_lib_320x200:</b> 320x200 video mode is used.</li>
 <li><b>use_lib_vga8colors:</b> Forces to use RGB 8-color mode (3 pins). Outputs 8 colors, as opposed to 64 in normal mode (6 pins RRGGBB)</li>
 <li><b>FIX_PERIBOARD_NOT_INITING:</b> In those keyboards that need ECO to initialize. Solution by David Crespo Tascón.</li>
 <li><b>use_lib_log_serial:</b> It allows to leave traces through the usb serial port. If enabled, it consumes a little more RAM, CPU and FLASH..</li>
 <li><b>gb_ms_keyboard:</b> The number of polling milliseconds for the keyboard must be specified.</li>
 <li><b>gb_ms_vga:</b> The number of polling milliseconds for the VGA frame must be specified.</li>
 <li><b>gb_add_offset_x:</b> Shift to the right of the frame in multiples of 4 pixels.</li>
 <li><b>gb_add_offset_y:</b> Downward displacement of the frame in pixels.</li>
 <li><b>use_lib_delay_tick_cpu_auto:</b> If 1, the emulation speed is auto-set to 14914 ticks of 20 millis. If 0, it waits for the millis specified in use_lib_delay_tick_cpu_micros.</li>
 <li><b>use_lib_delay_tick_cpu_micros:</b> The number of milliseconds to wait for the CPU while use_lib_delay_tick_cpu_auto is 0 must be specified.</li>
</ul>  

<br><br>
<h1>Tool chf2h</h1>
I have created a very basic tool, to convert .chf files to .h in ready mode to be processed by the emulator. We just have to leave the .chf files in the <b>input/cart</b> folder and run the <b>chf2h.exe</b> file, so that an output will be generated in the <b>output/dataFlash</b> directory. For testing purposes, a file has been left in the <b>input/cart</b> directory, which it is recommended to delete in case of making a new custom list. It is also recommended to delete the files in the <b>fairChild/dataFlash/gbcart.h</b> and <b>fairChild/dataFlash/cart</b> directory to have a clean project.<br><br><br>
<a href='https://github.com/rpsubc8/ESP32TinyFairChild/tree/main/tools'>Tool chf2h</a>
<br><br>
<pre>
 input/
  cart/
   ColorOrgan.chf
 output/
  dataFlash/
   cart/
</pre>
Subsequently we must copy the <b>dataFlash</b> directory into the <b>TinyFairChildttgovga32\fairChild</b> project overwriting the previous dataFlash folder. It is recommended that you clean up the project and recompile.<br>
This tool is very simple, and does not check for errors, so it is recommended to leave the files with very simple names and as simple as possible.
The project in PLATFORM.IO is prepared for 1MB of Flash. If we need the 4MB of flash, we will have to modify the entry in the <b>platformio.ini</b> file.
<pre>board_build.partitions = huge_app.csv</pre>
In the Arduino IDE, we must choose the option <b>Partition Scheme (Huge APP)</b>.
