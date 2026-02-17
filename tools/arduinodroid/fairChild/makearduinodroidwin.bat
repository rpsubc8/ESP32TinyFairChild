@echo off
echo Convert ARDUINODROID PROJECT DATA (WIN32)
pause
echo Copy *.cpp (Copiar *.cpp)
copy/Y ..\..\..\TinyFairChildttgovga32\fairChild\*.cpp
echo Copy *.h (Copiar *.h)
copy/Y ..\..\..\TinyFairChildttgovga32\fairChild\*.h
echo Copy fairChild.ino (Copiar fairChild.ino)
copy/Y ..\..\..\TinyFairChildttgovga32\fairChild\fairChild.ino
echo Copy gbcart.h (Copiar gbcart.h)
copy/Y ..\..\..\TinyFairChildttgovga32\fairChild\dataFlash\gbcart.h
echo Copy gbCompileDataOpt.h (Copiar gbCompileDataOpt.h)
copy/Y ..\..\..\TinyFairChildttgovga32\fairChild\dataFlash\gbCompileDataOpt.h
echo Copy Chf (Copiar Chf)
copy/Y ..\..\..\TinyFairChildttgovga32\fairChild\dataFlash\cart\*.h
echo Copy ROMs (Copiar ROMs)
copy/Y ..\..\..\TinyFairChildttgovga32\fairChild\dataFlash\bios\*.h
echo Copy Options ARDUINODROID
copy/Y notdelete\gbCompileOpt.h
pause