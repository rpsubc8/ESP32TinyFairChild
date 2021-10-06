
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
 <li>Soporte para modo 64 colores.</li>   
 <li>VGA 200x150</li>
 <li>VGA 320x200</li>
 <li>No se requiere la libreria de bitluni completa. He reducido a lo mínimo, ahorrando RAM y FLASH, basado en la librería de Ricardo Massaro</li>
</ul> 


<br>
<h1>Requerimientos</h1>
Se requiere:
 <ul>
  <li>TTGO VGA32 v1.x (1.0, 1.1, 1.2, 1.4) o Single core ESP32</li>
  <li>Visual Studio 1.48.1 PLATFORMIO 2.2.0</li>
  <li>Arduino IDE 1.8.11</li>
 </ul>
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyFairChild/main/preview/ttgovga32v12.jpg'></center>
La imagen adjunta es de mi placa TTGO VGA32 v1.2 sin psram.
<br>



<br><br>
<h1>Tool chf2h</h1>
He creado una herramienta muy básica, para convertir los archivos .chf en .h en modo lista para ser procesados por el emulador. Tan sólo tenemos que dejar los archivos .chf en la carpeta <b>input/cart</b> y ejecutar el archivo <b>chf2h.exe</b>, de forma que se generará una salida en el directorio <b>output/dataFlash</b>. Para pruebas, se ha dejado un archivo en el directorio <b>input/cart</b>, que se recomienda borrar en caso de realizar una nueva lista personalizada. También se recomienda borrar los archivos del directorio <b>fairChild/dataFlash/gbcart.h</b> y <b>fairChild/dataFlash/cart</b>para tener un proyecto limpio.<br><br>
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
