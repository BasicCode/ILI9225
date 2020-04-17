# ILI9225 (and OTM2201A) Libraries

This is a simple, cut-down library for the ILI9225 (and OTM2201A) LCD controller chips. Currently contains two versions; one for PIC, and another for STM32 micros. They are designed to be easily adaptable to ther architectures as needed.<br>
These libraries only contain the bare essentials to run the LCD and write some text. It is expected that graphic functions are added seperately.<br>

* This project uses documentation provided by some random eBay seller. License unknown, credited in code.

## Usage
These libraries only provides a few basic functions to get started.<br>
* Modify the ILI9225.h file with your own pin and SPI bus definitions to suit your project.
* Initialise the SPI module on yourself.
* Initialise the LCD:
```
lcd_init();
```
* You're ready to go. It is useful to clear the screen manually with:
```
fill_rectangle(0, 0, WIDTH, HEIGHT, COLOR_BLACK);
```
You can set the display driver to draw to the display in either portrait or landscape orientation by changing the **LANDSCAPE** flag in the header file:
```
#define LANDSCAPE 1 //1 = Landscape, 0 = Portrait
```
<br><br>
Feel free to add functions and modify as required. Licensed under GNUv3.
