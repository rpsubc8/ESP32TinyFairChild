
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
 <li>Project compatible with ESP32 versions 1.0.0, 2.0.0, and 3.3.0 (IDF framework version 5.5). I recommend 2.0.0.</li>
 <li>Created project compatible with Arduino IDE and Platform IO</li>
 <li>Web Editor and ArduinoDroid (6.3.1) compatible project with tool makeandroid.bat and makearduinodroidlinux.sh</li>
 <li>Any digital pin can be used for audio (SPEAKER_PIN in gbConfig.h).</li> 
 <li>Any digital pin can be used for video (gbConfig.h).</li>
 <li>Any digital pin can be used for the CLK (KEYBOARD_CLK) and Data (KEYBOARD_DATA) keyboard (gbConfig.h).</li>
 <li>X and Y screen adjustment</li>
 <li>Emulation video speed menu, keyboard</li>
 <li>Support for 64-color mode and 8-color mode.</li>   
 <li>VGA 200x150</li>
 <li>VGA 320x200</li>
 <li>VGA 360x200</li>
 <li>The complete bitluni library is not required. I have reduced to the minimum, saving RAM and FLASH, based on Ricardo Massaro's library.</li>
 <li>Support for reading cartridges via WIFI</li>
 <li>Precompiled version (flash download 3.9.2) 360x200</li>
</ul> 


<br><br>
<h1>Video modes</h1>
There are seven possible video modes, which are actually divided into three basic modes, with 6 bpp (64 colours):
<ul>
 <li>360x200</li>
 <li>320x200</li>
 <li>200x150</li>
</ul>
By default, it starts at 360x200.<br><br>

|  Key  | Resolution                       |
| ----- | ---------------------------------|
|   0   | 360x200x70Hz bitluni             |
|   1   | 360x200x70Hz bitluni force APLL  |
|   2   | 320x200x70Hz bitluni             |
|   3   | 320x200x70Hz fabgl               |
|   4   | 320x200x70Hz bitluni force APLL  |
|   5   | 200x150x56Hz bitluni             |
|   6   | 200x150x56Hz bitluni force  APLL |

<br>
Video modes can be selected during start-up (500 ms) or restart, with the option to specify another time in the <b>gbConfig.h</b> in section <b>use_lib_boot_time_select_vga</b>, by simply pressing the corresponding key, from '0'to '6'.<br>
The start-up video mode can also be set during compilation, but it is more convenient to change it on the fly from the OSD at any time.<br>
Likewise, for each video mode, there is the option of using Espressif's PLL adjustment function or a custom function, which prevents the ESP32 from freezing. This special video mode has the addition of <b>apll</b>.<br>
Different video settings are also permitted, with fabgl or bitluni modes.


<br><br>
<h1>Precompiled version</h1>
In the precompile folder there is a version already compiled to be saved with the flash download tool 3.9.2. It is a version with 200x150 resolution with the demo games in FLASH.<br><br>
<a href='https://github.com/rpsubc8/ESP32TinyFairChild/tree/main/ESP32/precompile'>https://github.com/rpsubc8/ESP32TinyFairChild/tree/main/ESP32/precompile</a>
<br><br>
We must choose the ESP32 type:
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyFairChild/main/preview/flash00.gif'></center>
Subsequently, select the files as shown in the attached screenshot, with the same offset values:
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyFairChild/main/preview/flash01.gif'></center>
And we will press start. If everything has been correct, we will only have to restart the ESP32.

<br><br>
<h1>Requirements</h1>
Required:
 <ul>
  <li>TTGO VGA32 v1.x (1.0, 1.1, 1.2, 1.4) o Single core ESP32</li>
  <li>Visual Studio 1.48.1 PLATFORMIO 2.2.0</li>
  <li>Arduino IDE 1.8.11 ESP32 versions 1.0.0, 2.0.0, and 3.3.0 with IDF version 5.5. I recommend 2.0.</li>
  <li>ArduinoDroid (6.3.1)</li>
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
<h1>ArduinoDroid</h1>
ArduinoDroid will allow us to compile and upload the <b>fairChild</b> project to the ESP32 from a 64-bit Android device, i.e. a mobile phone, tablet or Android box, provided that our device is supported.<br>
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyFairChild/main/preview/previewWin.gif'></center>
If you are using Windows, you must run the script <b>makearduinodroidwin.bat</b> just once, which will leave the entire data structure of the dataFlash directory, as well as the rest of the files, in the directory from which the script is launched.<br>
If we are on an Android device with <b>termux</b> or on Linux, we must run <b>makearduinodroidlinux.sh</b>.
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyFairChild/main/preview/previewTermux.gif'></center>
Essentially, we are left with all the files on a single level, with no subdirectories possible.<br>
The 'notdelete' directory is internal to the script and is used to copy the <b>gbCompileOpt.h</b>.<br>
When finished, we can open the <b>fairChild.ino</b> script itself and recompile it from ArdunoDroid, without anything special. The script has a pause at the beginning, in case we want to stop the script from outside, as well as a stop at the end, to see the results of the process.<br>
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyFairChild/main/preview/previewArduinoDroid.gif'></center>
If we think about it, everything revolves around the <b>gb_use_lib_compile_arduinodroid</b> pragma in the <b>gbCompileOpt.h</b> header, which in normal mode is used with multi-level paths and in ArduinoDroid with the script, in a single level.<br>
This script searches for files by going up levels until it reaches <b>ESP32TinyFairChild/fairChild</b>, so you need to download the entire project with the whole structure:
<pre>
 TinyFairChildttgovga32
  fairChild
   dataFlash
  include
  lib
  test
 tools
  arduinodroid
   fairChild
  cart2h
</pre>
ArduinoDroid (6.3.1) with ESP32 support only works with 64-bit processors.

<br><br>
<h1>Arduino Web Editor</h1>
The makearduinodroidwin.bat script must be run only once. Once completed, it is uploaded to the cloud as any other project, either compressed in a zip file or as individual files.
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyFairChild/main/preview/previewArduinoWebEditor.gif'></center>
It is essentially the same, as the aim is to keep everything on a single directory level. We recommend importing the project compressed in a zip file with normal compression, not maximum, as some cloud web editors do not support zip files 100%.<br>
If all files are uploaded in a zip file, it must not contain any directories, so the <b>notdelete</b> directory should not be included.



<br><br>
<h1>Arduino IDE</h1>
The whole project is compatible with the Arduino 1.8.11 framework.
We just need to open the <b>fairChild.ino</b> in the <b>fairChild</b> directory.
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyFairChild/main/preview/previewArduinoIDEpreferences.gif'></center>
For normal mode, the project is already prepared, so no library is required.<br>
We must select the appropriate framework, allowing from version 1.0.0 onwards:
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyFairChild/main/preview/esp32ver110.gif'></center>
However, version 3.3.0 is also permitted with auto-detection or forced detection:
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyFairChild/main/preview/esp32ver330.gif'></center>
We must disable the PSRAM option, and if the binary exceeds 1 MB, select a 4 MB partition when uploading. Even if the code does not use PSRAM, if the option is enabled and our ESP32 does not have it, an exception will be generated and it will restart in loop mode.


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
 <li><b>use_lib_boot_vga_360x200x70hz_bitluni_6bpp:</b> 360x200 70 Hz video mode is used.</li>
 <li><b>use_lib_boot_vga_360x200x70hz_bitluni_apll_6bpp:</b> The 360x200 70 Hz video mode is used, which solves the problem of ESP32 crashing.</li>
 <li><b>use_lib_boot_vga_320x200x70hz_bitluni_6bpp:</b> 320x200 70 Hz video mode is used.</li>
 <li><b>use_lib_boot_vga_320x200x70hz_fabgl_6bpp:</b> 320x200 70 Hz video mode with fabgl settings is used.</li>
 <li><b>use_lib_boot_vga_320x200x70hz_bitluni_apll_6bpp:</b> The 320x200 70 Hz video mode is used, which solves the problem of ESP32 crashing.</li>
 <li><b>use_lib_boot_vga_200x150x70hz_bitluni_6bpp:</b> 200x150 50 Hz video mode is used.</li>
 <li><b>use_lib_boot_vga_200x150x70hz_bitluni_apll_6bpp:</b> The 200x150 50 Hz video mode is used, which solves the problem of ESP32 crashing.</li> 
 <li><b>use_lib_vga8colors:</b> Forces to use RGB 8-color mode (3 pins). Outputs 8 colors, as opposed to 64 in normal mode (6 pins RRGGBB). Best not to use, it is for testing purposes, it is adapted for 6bpp mode.</li>
 <li><b>use_lib_boot_time_select_vga:</b> Milliseconds to read the key that will activate video mode at start-up (0 to 6).</li>
 <li><b>use_lib_log_serial:</b> It allows to leave traces through the usb serial port. If enabled, it consumes a little more RAM, CPU and FLASH..</li>
 <li><b>gb_ms_keyboard:</b> The number of polling milliseconds for the keyboard must be specified.</li>
 <li><b>gb_ms_vga:</b> The number of polling milliseconds for the VGA frame must be specified.</li> 
 <li><b>use_lib_delay_tick_cpu_auto:</b> If 1, the emulation speed is auto-set to 14914 ticks of 20 millis. If 0, it waits for the millis specified in use_lib_delay_tick_cpu_micros.</li>
 <li><b>use_lib_delay_tick_cpu_micros:</b> The number of milliseconds to wait for the CPU while use_lib_delay_tick_cpu_auto is 0 must be specified.</li>
 <li><b>use_lib_wifi:</b> Enable WIFI to be able to load cartridges from a web server. As it requires a lot of RAM, it is advisable to use an http server, instead of https. The network name and password must be entered in the gbWifiConfig.h file. Selecting this option forces the use of 200x150 video mode to save RAM.</li>
 <li><b>use_lib_audio_ticker:</b> Para usar sonido, por defecto el GPIO 25.</li>
 <li><b>use_lib_esp_arduino_ver_3_3_0_auto:</b> Para detectar si tenemos ARDUINO 3.3.0 y Espressif IDF5 5.5,para compilar con dicha versión. Sino usará todo el código de versiones inferiores, como 1.0 o 2.0. </li>
 <li><b>use_lib_esp_arduino_ver_3_3_0_force:</b> Force compilation with ARDUINO 3.3.0 and Espressif IDF5 5.5.</li>
 <li><b>SPEAKER_PIN:</b> GPIO audio.</li>
 <li><b>KEYBOARD_DATA:</b> GPIO data PS/2</li>
 <li><b>KEYBOARD_CLK:</b> GPIO clock PS/2.</li> 
 <li><b>PIN_RED_LOW, PIN_RED_HIGH:</b> GPIO red vga.</li>
 <li><b>PIN_GREEN_LOW, PIN_GREEN_HIGH:</b> GPIO green vga.</li>
 <li><b>PIN_BLUE_LOW, PIN_BLUE_HIGH:</b> GPIO blue vga.</li>
 <li><b>PIN_HSYNC:</b> GPIO horizontal synchronism.</li>
 <li><b>PIN_VSYNC:</b> GPIO vertical synchronism.</li> 
</ul>


<br><br>
<h1>Tool cart2h</h1>
I have created a very basic tool to convert .chf files to .h files in list mode so they can be processed by the emulator. All we have to do is leave the .chf files in the folder. <b>input/cart</b> and run the file <b>cart2h.exe</b>, so that an output will be generated in the directory <b>output/dataFlash</b>. For testing purposes, a file has been left in the <b>input/cart</b> directory. It is recommended that you delete this file if you create a new custom list.
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyFairChild/main/preview/previewWinData2h.gif'></center>
It is also recommended to delete the files from the directory. <b>fairChild/dataFlash/gbcart.h</b> and <b>fairChild/dataFlash/cart</b> to have a clean project.<br><br>
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
Next, copy the <b>dataFlash</b> directory into the <b>TinyFairChildttgovga32\fairChild</b> project, overwriting the previous dataFlash folder. It is recommended to clean the project and recompile.<br>
This tool is very simple and does not check for errors, so it is recommended that you give your files very simple names that are as straightforward as possible.<br>
Since the source code is available, it can be compiled for Linux or Android under Termux. In Termux, we need to install the <b>gcc</b> or <b>clang</b> package and compile:<br>
<pre>
 gcc -s cart2h.cpp -ocart2h.a
</pre>
This must be done from the home directory of the Android device, so that if we do it in any other directory, the created <b>cart2h.a</b> will never be able to run, unless the device is rooted.
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyFairChild/main/preview/previewTermuxData2h.gif'></center>
The project in PLATFORM.IO is set up for 1 MB of Flash. If we need 4 MB of Flash, we will have to modify the entry in the <b>platformio.ini</b> file.
<pre>board_build.partitions = huge_app.csv</pre>
In the Arduino IDE, we must select the <b>Partition Scheme (Huge APP)</b> option.



<br><br>
<h1>WIFI support</h1>
A basic WIFI support has been added for TEST, to be able to load the cartridges (chf) from a basic HTML server, without the need of CORS, so the deployment is very fast. Apache Server, NGINX, etc... can be used.<br>
By default, it is left pointing to the project's github pages server. RAM consumption with https is higher than with http:
<pre>
https://rpsubc8.github.io/ESP32TinyFairChild/www/fairchild/output
</pre>

 To activate this mode, you must uncomment the line <b>use_lib_wifi</b> in <b>gbConfig.h</b><br>
 If compilation for WIFI is enabled, the use of 200x150 video mode will be forced due to RAM requirements in https mode. The 320x200 mode with WIFI has worked for me, but the 360x200 mode sometimes ran out of RAM in requests.
 We must configure in the file <b>gbWIFIConfig.h</b> the data:
 <pre>
  #define gb_wifi_ssd "nombreDeNuestraRedWIFIdelRooter"
  #define gb_wifi_pass "passwordDeNuestraRedWIFIdelRooter"

  //#define gb_wifi_url_base_path "http://192.168.0.36/fairchild/output"
  #define gb_wifi_url_base_path "https://rpsubc8.github.io/ESP32TinyFairChild/www/fairchild/output"

  //millisecons delay stream read
  #define gb_wifi_delay_available 0

  #define use_lib_wifi_debug
 </pre>
 
 For the time being, the configuration is set in our <b>gbWIFIConfig.h</b> which we will have to recompile, so that it will only connect to our rooter network. Therefore we must change <b>gb_wifi_ssd</b> and <b>gb_wifi_pass</b>.<br>
 The <b>gb_wifi_url_base_path</b> is the path where our <b>outlist</b> and <b>outdat</b> directories are located, which contain the list of files, as well as the files themselves, so this path will be different if we use a local server.<br><br> 
 The concept is simple, you have:
 <pre>
  outlist --> File with the list of names (length 8) of chf. Limit of 128 files
  outdat  --> The chf files.
 </pre>
 For now, to optimize RAM consumption, we have left an 8:3 name length structure, i.e. 8 name characters and 3 extension characters. I leave some intermediate tools to prepare and make the conversion:<br>
 <pre>
  build.bat --> Launches all bats, processing input to output
  
  data83.bat --> Converts all input files to 8:3 format
  
  list.bat --> Generates the outlist (list of files).
  dsk.exe --> Generates a txt file containing a list of files with name length 8.
  lowercart.bat --> Convert CHF to .chf extensions
 </pre>

 An example of <b>outlist</b>, for example from cart.txt, containing:
 <pre>
 AlienInvBaseballBoogie2 Bowling CheckersColorOrgF8NationFninja  Football
 </pre>
 
 Whenever a file is added, we must regenerate the list with the <b>list.bat</b> or by calling the whole process <b>build.bat</b>.<br>
 
 Inside is the list of files with a maximum length of 8 characters, which is what will be displayed in the cartridge selection menu in the ESP32. These files, for now, are intended for a maximum of 128 entries, which is equivalent to 1024 bytes (128 x 8).<br>
 Each time a request is made to a type, the .TXT file with the list (1024 bytes, 128 names) is loaded. And when it is selected, the request is made to the file in the outdat.<br>
 When a file is selected, it will be loaded in <b>outdat</b> with its path. The files must have the extension in lower case.<br>
 
 If you are using an external WEB server, it is possible that policies may prevent you from making consecutive requests, so it is advisable not to make requests too close together.<br>
 
 To debug the WIFI, uncomment <b>use_lib_wifi_debug</b> in the <b>gbWifiConfig.h</b> file.

