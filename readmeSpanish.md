
# Tiny Fairchild Channel F
Port del emulador de retroarch FreeChaF (FairChild Channel F) a la placa TTGO VGA32 v1.0, v1.1, v1.2 y v1.4 con ESP32.
<br>
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyFairChild/main/preview/pacman.gif'></center>
He realizado varias modificaciones:
<ul>
 <li>Portado de retroarch a ESP32</li>
 <li>No se usa PSRAM, funcionando en ESP32 de 520 KB de RAM (TTGO VGA32 v1.x)</li> 
 <li>Uso de un sólo core</li>
 <li>OSD de bajos recursos</li>
 <li>Creado proyecto compatible con Arduino IDE y Platform IO</li>
 <li>Se puede usar cualquier pin digital para el audio (SPEAKER_PIN en hardware.h)</li>
 <li>Se puede usar cualquier pin digital para el video (hardware.h)</li>
 <li>Ajuste de pantalla X e Y</li>
 <li>Menú de velocidad de video de emulación, teclado</li>
 <li>Soporte para modo 64 colores y 8 colores.</li>   
 <li>VGA 200x150</li>
 <li>VGA 320x200</li>
 <li>No se requiere la libreria de bitluni completa. He reducido a lo mínimo, ahorrando RAM y FLASH, basado en la librería de Ricardo Massaro</li>
 <li>Soporte para leer cartuchos via WIFI</li>
 <li>Versión precompilada (flash download 3.9.2)</li>
</ul> 


<br><br>
<h1>Versión precompilada</h1>
En la carpeta precompile se encuentra una versión ya compilada para poder ser grabada con el flash download tool 3.9.2. Se trata de una versión con los juegos de demostración en FLASH.<br><br>
<a href='https://github.com/rpsubc8/ESP32TinyFairChild/tree/main/ESP32/precompile'>https://github.com/rpsubc8/ESP32TinyFairChild/tree/main/ESP32/precompile</a>
<br><br>
Debemos de elegir el tipo ESP32:
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyFairChild/main/preview/flash00.gif'></center>
Posteriormente, seleccionaremos los archivos tal y como la captura adjunta, con los mismos valores de offset:
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyFairChild/main/preview/flash01.gif'></center>
Y le daremos a start. Si todo ha sido correcto, sólo tendremos que reiniciar el ESP32.


<br><br>
<h1>Requerimientos</h1>
Se requiere:
 <ul>
  <li>TTGO VGA32 v1.x (1.0, 1.1, 1.2, 1.4) o Single core ESP32</li>
  <li>Visual Studio 1.48.1 PLATFORMIO 2.2.0</li>
  <li>Arduino IDE 1.8.11</li>
 </ul>
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyFairChild/main/preview/ttgovga32v12.jpg'></center>
La imagen adjunta es de mi placa TTGO VGA32 v1.2 sin psram ni módulo de SD.
<br>


<br><br>
<h1>PlatformIO</h1>
Se debe instalar el PLATFORMIO 2.2.0 desde las extensiones del Visual Studio.
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyFairChild/main/preview/previewPlatformIOinstall.gif'></center>
Luego se seleccionará el directorio de trabajo <b>TinyFairChildttgovga32</b>.
Debemos modificar el fichero <b>platformio.ini</b> la opción <b>upload_port</b> para seleccionar el puerto COM donde tenemos nuestra placa TTGO VGA32.
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyFairChild/main/preview/previewPlatformIO.gif'></center>
Luego procederemos a compilar y subir a la placa. No se usa particiones, así que debemos subir todo el binario compilado.
Está todo preparado para no tener que instalar ninguna librería.


<br><br>
<h1>Arduino IDE</h1>
Todo el proyecto es compatible con la estructura de Arduino 1.8.11.
Tan sólo tenemos que abrir el <b>fairChild.ino</b> del directorio <b>fairChild</b>.
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyFairChild/main/preview/previewArduinoIDEpreferences.gif'></center>
Para el modo normal, ya está preparado el proyecto, de forma que no se necesita ninguna librería. 
Debemos desactivar la opción de PSRAM, y en caso de superar 1 MB de binario, seleccionar 4 MB de partición a la hora de subir. Aunque el código no use PSRAM, si la opción está activa y nuestro ESP32 no dispone de ella, se generará una excepción y reinicio del mismo en modo bucle.


<br><br>
<h1>Teclado</h1>
El teclado está dividido en 3 partes
<ul>
 <li>Control de Sistema: 0,1,2,3</li>
 <li>Control A: Izquierda, Derecha, Arriba, Abajo, o,p</li>
 <li>Control B: a,d,w,s   c,v</li>
</ul>

<br><br>
<h1>Opciones</h1>
El archivo <b>gbConfig.h</b> se seleccionan las opciones:
<ul>
 <li><b>use_lib_200x150:</b> Se usa modo de vídeo 200x150. Se tiene que elegir sólo un modo de video, o bien 200x150 o 320x200</li>
 <li><b>use_lib_320x200:</b> Se usa modo de vídeo 320x200.</li>
 <li><b>use_lib_vga8colors:</b> Obliga a usar RGB modo de 8 colores (3 pines). Saca 8 colores, frente a los 64 del modo normal (6 pines RRGGBB).</li>
 <li><b>FIX_PERIBOARD_NOT_INITING:</b> En aquellos teclados que necesitan ECO para inicializarse. Sólución de David Crespo Tascón.</li>
 <li><b>use_lib_log_serial:</b> Permite dejar trazas por el puerto serie usb. Si se activa, consume un poco más de RAM, CPU y FLASH.</li>
 <li><b>gb_ms_keyboard:</b> Se debe especificar el número de milisegundos de polling para el teclado.</li>
 <li><b>gb_ms_vga:</b> Se debe especificar el número de milisegundos de polling para el frame VGA.</li>
 <li><b>gb_add_offset_x:</b> Desplazamiento a la derecha del frame en múltiplos de 4 pixels.</li>
 <li><b>gb_add_offset_y:</b> Desplazamiento hacia abajo del frame en pixels.</li>
 <li><b>use_lib_delay_tick_cpu_auto:</b> Si es 1, se autoajusta la velocidad de emulación a 14914 ticks de 20 milis. Si es 0, se espera los milis especificados en use_lib_delay_tick_cpu_micros </li>
 <li><b>use_lib_delay_tick_cpu_micros:</b> Se debe especificar el número de milisegundos a esperar la CPU, mientras que use_lib_delay_tick_cpu_auto sea 0.</li>
 <li><b>use_lib_wifi:</b>Activa la WIFI para poder cargar cartuchos desde un servidor web. Al requerir mucha RAM, se aconseja usar un servidor http, en lugar de https. Se debe introducir el nombre de red y clave en el fichero gbWifiConfig.h</li>
</ul>  


<br><br>
<h1>Tool chf2h</h1>
He creado una herramienta muy básica, para convertir los archivos .chf en .h en modo lista para ser procesados por el emulador. Tan sólo tenemos que dejar los archivos .chf en la carpeta <b>input/cart</b> y ejecutar el archivo <b>chf2h.exe</b>, de forma que se generará una salida en el directorio <b>output/dataFlash</b>. Para pruebas, se ha dejado un archivo en el directorio <b>input/cart</b>, que se recomienda borrar en caso de realizar una nueva lista personalizada. También se recomienda borrar los archivos del directorio <b>fairChild/dataFlash/gbcart.h</b> y <b>fairChild/dataFlash/cart</b> para tener un proyecto limpio.<br><br>
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
Posteriormente debemos copiar el directorio <b>dataFlash</b> en el proyecto <b>TinyFairChildttgovga32\fairChild</b> sobreescribiendo la carpeta dataFlash previa. Se recomienda limpiar el proyecto y volver a compilar.<br>
Esta herramienta es muy simple, y no controla los errores, por lo que se recomienda dejarle los archivos con nombres muy simples y lo más sencillo posible.<br>
El proyecto en PLATFORM.IO está preparado para 1 MB de Flash. Si necesitamos los 4MB de flash, tendremos que modificar la entrada del archivo <b>platformio.ini</b>
<pre>board_build.partitions = huge_app.csv</pre>
En el Arduino IDE, debemos elegir la opción <b>Partition Scheme (Huge APP)</b>.


<br><br>
<h1>Soporte WIFI</h1>
Se ha añadido para TEST un soporte básico de WIFI, para poder cargar los cartuchos (chf) desde un servidor básico HTML, sin necesidad de CORS, por lo que el despliegue es muy rápido. Se puede usar un Servidor Apache, NGINX, etc...<br>
Por defecto, se ha dejado apuntando al servidor pages de github del proyecto. El consumo de RAM con https es mayor que con http:
<pre>
https://rpsubc8.github.io/ESP32TinyFairChild/www/fairchild/output
</pre>

 Para activar este modo, se debe descomentar la línea <b>use_lib_wifi</b> en el <b>gbConfig.h</b><br>
 Debemos configurar en el archivo <b>gbWIFIConfig.h</b> los datos:
 <pre>
  #define gb_wifi_ssd "nombreDeNuestraRedWIFIdelRooter"
  #define gb_wifi_pass "passwordDeNuestraRedWIFIdelRooter"

  //#define gb_wifi_url_base_path "http://192.168.0.36/fairchild/output"
  #define gb_wifi_url_base_path "https://rpsubc8.github.io/ESP32TinyFairChild/www/fairchild/output"

  //millisecons delay stream read
  #define gb_wifi_delay_available 0

  #define use_lib_wifi_debug
 </pre>
 
 Por ahora, la configuración está fijada en nuestro <b>gbWIFIConfig.h</b> que tendremos que recompilar, de manera, que sólo se conectará a nuestra red del rooter. Por tanto debemos de cambiar <b>gb_wifi_ssd</b> y <b>gb_wifi_pass</b>.<br>
 El <b>gb_wifi_url_base_path</b> es la ruta en donde se encuentran nuestros directorios <b>outlist</b> y <b>outdat</b>, que contienen el listado de archivos, así como los mismos, por lo que dicho path será diferente si usamos un servidor local.<br><br>
 El concepto es simple, se dispone de:
 <pre>
  outlist --> Fichero con la lista de nombres (longitud 8) de chf. Límite de 128 ficheros
  outdat  --> Los ficheros chf.
 </pre>
 Por ahora, para optimizar el consumo de RAM, se ha dejado una estructura de longitud de nombres 8:3, es decir, 8 caracteres de nombre y 3 de extensión. Dejo unas tools intermedias para preparar y hacer la conversión:<br>
 <pre>
  build.bat --> Lanza todos los bats, procesando input en output
  
  data83.bat --> Convierte todos los archivos input a formato 8:3
  
  list.bat --> Genera los outlist (lista de archivos).
  dsk.exe --> Genera un txt que dentro contiene la lista de archivos con longitud de nombre 8.
  lowercart.bat --> Convierte las extensiones CHF a .chf
 </pre>

 Un ejemplo de <b>outlist</b>, por ejemplo de cart.txt, que contiene:
 <pre>
 AlienInvBaseballBoogie2 Bowling CheckersColorOrgF8NationFninja  Football
 </pre>
 
 Siempre que se añada un fichero, debemos de regenerar la lista con el <b>list.bat</b> o bien llamando a todo el proceso <b>build.bat</b>.<br>
 
 Dentro esta la lista de archivos con longitud máxima de 8 caracteres, que es la que se mostrará en el menu de selección de cartucho en el ESP32. Estos archivos, por ahora están pensados para un máximo de 128 entradas, que equivale a 1024 bytes (128 x 8).<br>
 Cada vez que se hace una petición a un tipo, se carga el fichero .TXT con la lista (1024 bytes, 128 nombres). Y cuando se selecciona, se hace la petición al fichero que se encuentra en el outdat.<br>
 Cuando se seleccione un archivo, se procederá a cargarlo en <b>outdat</b> con su ruta. Los archivos tienen que tener la extensión en minúsculas.<br>
 
 Si se usa un servidor externo WEB, es posible, que por políticas impida realizar peticiones seguidas, así que es recomendable no hacer peticiones muy seguidas.<br>
 
 Para depurar la WIFI, se debe descomentar <b>use_lib_wifi_debug</b> en el fichero <b>gbWifiConfig.h</b>

