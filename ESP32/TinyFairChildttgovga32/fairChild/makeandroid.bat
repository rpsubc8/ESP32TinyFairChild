@echo off
echo Convert ANDROID PROJECT DATA (WIN32)
echo Delete dataFlash (Borrar dataFlash)
pause

echo Process gbcart.h (Procesar gbcart.h)
fart dataFlash\gbcart.h "cart/gbCart" "gbCart"
ping -n 2 127.0.0.1>nul

echo Copy gbcart.h (Copiar gbcart.h)
copy/Y dataFlash\gbcart.h
ping -n 2 127.0.0.1>nul

echo Copy cart (Copiar cart)
copy/Y dataFlash\cart\*.h
ping -n 2 127.0.0.1>nul

echo Copy bios (Copiar bios)
copy/Y dataFlash\bios\*.h
ping -n 2 127.0.0.1>nul

echo Process libretro.cpp (Procesar libretro.cpp)
fart libretro.cpp "dataFlash/gbcart.h" "gbcart.h"
ping -n 2 127.0.0.1>nul
fart libretro.cpp "dataFlash/bios/gbRoms" "gbRoms"
ping -n 2 127.0.0.1>nul

echo Process osd.cpp (Procesar osd.cpp)
fart osd.cpp "dataFlash/gbcart.h" "gbcart.h"
ping -n 2 127.0.0.1>nul

echo Delete dataFlash (Borrar dataFlash)
rmdir /S /Q dataFlash

pause