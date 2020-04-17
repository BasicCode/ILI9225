# ILI9225 (and OTM2201A) Basic Library for STM32

This is a simple, cut-down library for the ILI9225 (and OTM2201A) LCD controller chips. Tested for use on the STM32L476<br>

* This project uses documentation provided by some random eBay seller. License unknown, credited in code.

## Installation
The PIC communicates with this controller over SPI and should be initialised by the **main()** code outside of the ILI9225.c library (because each PIC is slightly different).<br>
* Set the **SPI_HandleTypeDef** in the ILI9225.h file to suit your particular microcontroller.<br>
* Change the **CSX**, **CMD**, and **RESX** pin and port registers in the ILI9225.h file to match your design.

## Usage
This library only provides a few basic functions to get started. After setting up the SPI module, initialise the LCD controller using:
```
lcd_init();
```
It is then useful to clear the screen manually with:
```
fill_rectangle(0, 0, WIDTH, HEIGHT, COLOR_BLACK);
```
You can set the display driver to draw to the display in either portrait or landscape orientation by changing the **LANDSCAPE** flag in the header file:
```
#define LANDSCAPE 1 //1 = Landscape, 0 = Portrait
```
<br><br>
Feel free to add functions and modify as required. Licensed under GNUv3.
