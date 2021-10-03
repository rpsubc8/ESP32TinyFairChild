
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
 <li>Se puede usar cualquier pin digital para el audio</li>
 <li>Ajuste de pantalla X</li>
 <li>Menú de velocidad de video de emulación, sonido, teclado</li>
 <li>Soporte para modo 64 colores.</li>   
 <li>VGA 200x150</li>
 <li>VGA 320x200</li>
 <li>No se requiere la libreria de bitluni completa. He reducido a lo mínimo, ahorrando RAM y FLASH, basado en la librería de Ricardo Massaro</li>
</ul> 
