# ILI9225 (and OTM2201A) Basic Library for PIC

This is a simple, cut-down library for the ILI9225 (and OTM2201A) LCD controller chips. Tested for use on the PIC18F26K42, however it is designed
to be easily ported to other models.<br>

* This project uses documentation provided by some random eBay seller. License unknown, credited in cocde.

## Installation
The PIC communicates with this controller over SPI and should be initialised by the **main()** code outside of the ILI9225.c library (because each chip is slightly different).<br>
Set the **SPIBUFF**, and **SPIIDLE** registers in the ILI9225.h file to match your particular setup.

## Usage
This library only provides a few basic functionality. Afeter setting up the SPI module, initialise the LCD controller using:
```
lcd_init();
```
It is then useful to clear the screen manually with:
```
fill_rectangle(0, 0, WIDTH, HEIGHT, COLOR_BLACK);
```
<br><br>
Feel free to add functions and modify as required.