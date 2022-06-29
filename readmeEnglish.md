
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
 <li>Precompiled version (flash download 3.9.2) 200x150</li>
</ul> 


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
 <li><b>use_lib_wifi:</b> Enable WIFI to be able to load cartridges from a web server. As it requires a lot of RAM, it is advisable to use an http server, instead of https. The network name and password must be entered in the gbWifiConfig.h file.</li>
</ul> 
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



<br><br>
<h1>WIFI support</h1>
A basic WIFI support has been added for TEST, to be able to load the cartridges (chf) from a basic HTML server, without the need of CORS, so the deployment is very fast. Apache Server, NGINX, etc... can be used.<br>
By default, it is left pointing to the project's github pages server. RAM consumption with https is higher than with http:
<pre>
https://rpsubc8.github.io/ESP32TinyFairChild/www/fairchild/output
</pre>

 To activate this mode, you must uncomment the line <b>use_lib_wifi</b> in <b>gbConfig.h</b><br>
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

