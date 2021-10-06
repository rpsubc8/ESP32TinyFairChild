
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
  <li>TTGO VGA32 v1.x (1.0, 1.1, 1.2, 1.4) or Single core ESP32</li>
  <li>Visual Studio 1.48.1 PLATFORMIO 2.2.0</li>
  <li>Arduino IDE 1.8.11</li>
 </ul>
<center><img src='https://raw.githubusercontent.com/rpsubc8/ESP32TinyFairChild/main/preview/ttgovga32v12.jpg'></center>
<br>
