/*
 * LCD driver for the ILI9225 TFT LCD chips. 
 * 
 * This driver works with OTM2201A, and ILI9926 controller chips.
 * 
 * Feel free to use, change, distribute this code as desired. Use under
 * GPLv3 open-source license.
 * 
 * File:   ILI9225.c
 * Author: tommy
 *
 * Created on 2 July 2019, 7:32 PM
 */


#include <xc.h>
#include "ILI9225.h"



/*
 * Writes a byte to SPI without changing chip select (CSX) state.
 * Called by the write_command() and write_data() functions which
 * control these pins as required.
 * 
 * This will use either a software implementation or the hardware
 * implementation depending on if USE_HW_SPI flag is set in the 
 * header file. (Software SPI is reeeeeally slow. Measured at 
 * 40 kHz clock compared to 2 MHz clock with hardware SPI).
 */
void spi_write(unsigned char data) {
    //TODO: Update these buffer labels according to your device.
    
    //Write data to SSPBUFF
    SPIBUF = data;
    //Wait for transmission to finish
    while(!(SPIIDLE));
}

/*
 * Writes a data byte to the display. Pulls CS low as required.
 */
void lcd_write_data(unsigned char data) {
    //CS LOW
    CSX = 0;
    //DC HIGH
    CMD = 1;
    //Send data to the SPI register
    spi_write(data);
    //CS HIGH
    CSX = 1;
}

/*
 * Writes a command byte to the display
 */
void lcd_write_command(unsigned char data) {
    //Pull the command AND chip select lines LOW
    CMD = 0;
    CSX = 0;
    spi_write(data);
    //Return the control lines to HIGH
    CSX = 1;
}

/*
 * Writes data to a specific register.
 * Accepts a 16-bit register address, and 16-bits of data.
 */
void lcd_write_register(unsigned int reg, unsigned int data) {
    //Write each register byte, and each data byte seperately.
    lcd_write_command(reg >> 8); //regH
    lcd_write_command(reg & 0xFF); //regL
    lcd_write_data(data >> 8); //dataH
    lcd_write_data(data & 0xFF); //dataL
}

/*
 * Swaps two 16-bit integers
 */
void swap_int(int *num1, int *num2) {
    int temp = *num2;
    *num2 = *num1;
    *num1 = temp;
}

/*
 * Swaps two 8-bit integers
 */
void swap_char(char *num1, char *num2) {
    char temp = *num2;
    *num2 = *num1;
    *num1 = temp;
}

/*
 * Delay calcualted on 32MHz clock.
 * Does NOT adjust to clock setting
 */
void delay_ms(double millis) {
    int multiplier = 4;
    double counter = millis;
    while(multiplier--) {
        while(counter--);
        counter = millis;
    }
}

/*
 * A short microsecond delay routine
 * (not measured)
 */
void delay_us(long int cycles) {
    while(cycles--);
}

/*
 * Initialisation routine for the LCD
 * I got this from the one of the ebay sellers which make them.
 * From Open-Smart
 */
void lcd_init() {
    
    //SET control pins for the LCD HIGH (they are active LOW)
    CSX = 1; //CS
    CMD = 0; //Data / command select, the datasheet isn't clear on that.
    RESX = 1; //RESET pin HIGH
    
    //Cycle reset pin
    RESX = 0;
    delay_ms(500);
    RESX = 1;
    delay_ms(500);
    
    lcd_init_command_list();
    
}

/**
 * This is the magic initialisation routine. Supplied by Open-Smart
 * who sell cheap modules on eBay.
 * This routine works with OTM2201A and ILI9925.
 */
void lcd_init_command_list(void)
{
    
    lcd_write_register(ILI9225_POWER_CTRL1, 0x0000); // Set SAP,DSTB,STB
    lcd_write_register(ILI9225_POWER_CTRL2, 0x0000); // Set APON,PON,AON,VCI1EN,VC
    lcd_write_register(ILI9225_POWER_CTRL3, 0x0000); // Set BT,DC1,DC2,DC3
    lcd_write_register(ILI9225_POWER_CTRL4, 0x0000); // Set GVDD
    lcd_write_register(ILI9225_POWER_CTRL5, 0x0000); // Set VCOMH/VCOML voltage
    
    delay_ms(10);
    
    lcd_write_register(ILI9225_POWER_CTRL2, 0x0018); // Set APON,PON,AON,VCI1EN,VC
    lcd_write_register(ILI9225_POWER_CTRL3, 0x6121); // Set BT,DC1,DC2,DC3
    lcd_write_register(ILI9225_POWER_CTRL4, 0x006F); // Set GVDD   /*007F 0088 */
    lcd_write_register(ILI9225_POWER_CTRL5, 0x495F); // Set VCOMH/VCOML voltage
    lcd_write_register(ILI9225_POWER_CTRL1, 0x0800); // Set SAP,DSTB,STB
    
    delay_ms(10);
    

    lcd_write_register(ILI9225_POWER_CTRL2, 0x103B); // Set APON,PON,AON,VCI1EN,VC

    delay_ms(50);


    lcd_write_register(ILI9225_DRIVER_OUTPUT_CTRL, 0x011C); // set the display line number and display direction
    lcd_write_register(ILI9225_LCD_AC_DRIVING_CTRL, 0x0100); // set 1 line inversion
    lcd_write_register(ILI9225_ENTRY_MODE, 0x1030); // set GRAM write direction and BGR=1.
    lcd_write_register(ILI9225_DISP_CTRL1, 0x0000); // Display off
    lcd_write_register(ILI9225_BLANK_PERIOD_CTRL1, 0x0808); // set the back porch and front porch
    lcd_write_register(ILI9225_FRAME_CYCLE_CTRL, 0x1100); // set the clocks number per line
    lcd_write_register(ILI9225_INTERFACE_CTRL, 0x0000); // CPU interface
    lcd_write_register(ILI9225_OSC_CTRL, 0x0D01); // Set Osc  /*0e01*/
    lcd_write_register(ILI9225_VCI_RECYCLING, 0x0020); // Set VCI recycling
    lcd_write_register(ILI9225_RAM_ADDR_SET1, 0x0000); // RAM Address
    lcd_write_register(ILI9225_RAM_ADDR_SET2, 0x0000); // RAM Address

    /* Set GRAM area */
    lcd_write_register(ILI9225_GATE_SCAN_CTRL, 0x0000); 
    lcd_write_register(ILI9225_VERTICAL_SCROLL_CTRL1, 0x00DB); 
    lcd_write_register(ILI9225_VERTICAL_SCROLL_CTRL2, 0x0000); 
    lcd_write_register(ILI9225_VERTICAL_SCROLL_CTRL3, 0x0000); 
    lcd_write_register(ILI9225_PARTIAL_DRIVING_POS1, 0x00DB); 
    lcd_write_register(ILI9225_PARTIAL_DRIVING_POS2, 0x0000); 
    lcd_write_register(ILI9225_HORIZONTAL_WINDOW_ADDR1, 0x00AF); 
    lcd_write_register(ILI9225_HORIZONTAL_WINDOW_ADDR2, 0x0000); 
    lcd_write_register(ILI9225_VERTICAL_WINDOW_ADDR1, 0x00DB); 
    lcd_write_register(ILI9225_VERTICAL_WINDOW_ADDR2, 0x0000); 

    /* Set GAMMA curve */
    lcd_write_register(ILI9225_GAMMA_CTRL1, 0x0000); 
    lcd_write_register(ILI9225_GAMMA_CTRL2, 0x0808); 
    lcd_write_register(ILI9225_GAMMA_CTRL3, 0x080A); 
    lcd_write_register(ILI9225_GAMMA_CTRL4, 0x000A); 
    lcd_write_register(ILI9225_GAMMA_CTRL5, 0x0A08); 
    lcd_write_register(ILI9225_GAMMA_CTRL6, 0x0808); 
    lcd_write_register(ILI9225_GAMMA_CTRL7, 0x0000); 
    lcd_write_register(ILI9225_GAMMA_CTRL8, 0x0A00); 
    lcd_write_register(ILI9225_GAMMA_CTRL9, 0x0710); 
    lcd_write_register(ILI9225_GAMMA_CTRL10, 0x0710); 

    lcd_write_register(ILI9225_DISP_CTRL1, 0x0012); 

    delay_ms(50); 
    
    lcd_write_register(ILI9225_DISP_CTRL1, 0x1017);

    
}

/*
 * Draws a single pixel to the LCD at position X, Y, with 
 * Colour.
 */
void draw_pixel(char x, char y, unsigned int colour) {
    //If we are in landscape view then translate -90 degrees
    if(LANDSCAPE) {
        swap_char(&x, &y);
        y = WIDTH - y;
    }
    
    //Set the x, y position that we want to write to
    set_draw_window(x, y, x+1, y+1);
    lcd_write_data(colour >> 8);
    lcd_write_data(colour & 0xFF);
}

/*
 * Fills a rectangle with a given colour
 */
void fill_rectangle(char x1, char y1, char x2, char y2, unsigned int colour) {
    //If landscape view then translate everyting -90 degrees
    if(LANDSCAPE) {
        swap_char(&x1, &y1);
        swap_char(&x2, &y2);
        y1 = WIDTH - y1;
        y2 = WIDTH - y2;
        swap_char(&y2, &y1);
    }
    
    //Split the colour int in to two bytes
    unsigned char colour_high = colour >> 8;
    unsigned char colour_low = colour & 0xFF;
    
    //Set the drawing region
    set_draw_window(x1, y1, x2, y2);
    
    //We will do the SPI write manually here for speed
    //( the data sheet says it doesn't matter if CSX changes between 
    // data sections but I don't trust it.)
    //CSX low to begin data
    CSX = 0;
    //Write colour to each pixel
    for(int y = 0; y < y2-y1+1 ; y++) {
        for(int x = 0; x < x2-x1+1; x++) {
            lcd_write_data(colour_high);
            lcd_write_data(colour_low);
        }
    }
    //Return CSX to high
    CSX = 1;
}

/*
 * Sets the X,Y position for following commands on the display.
 * Should only be called within a function that draws something
 * to the display.
 */
void set_draw_window(char x1, char y1, char x2, char y2) {

    lcd_write_register(ILI9225_HORIZONTAL_WINDOW_ADDR1,x2);
    lcd_write_register(ILI9225_HORIZONTAL_WINDOW_ADDR2,x1);

    lcd_write_register(ILI9225_VERTICAL_WINDOW_ADDR1,y2);
    lcd_write_register(ILI9225_VERTICAL_WINDOW_ADDR2,y1);

    lcd_write_register(ILI9225_RAM_ADDR_SET1,x1);
    lcd_write_register(ILI9225_RAM_ADDR_SET2,y1);

    lcd_write_command(0x00);
    lcd_write_command(0x22);
}

/*
 * Draws a single char to the screen.
 * Called by the various string writing functions like print().
 */
void draw_char(char x, char y, char c, unsigned int colour, char size) {
    int i, j;
    char line;
    unsigned int font_index = (c - 32);
    
    //Get the line of pixels from the font file
    for(i=0; i<13; i++ ) {

        line = FontLarge[font_index][12 - i];
        
        //Draw the pixels to screen
        for(j=0; j<8; j++) {
            if(line & (0x01 << j)) {
                if(size == 1) {
                    //If we are just doing the smallest size font then do a single pixel each
                    draw_pixel(x+(8-j), y+i, colour);
                }
                else {
                    // do a small box to represent each pixel
                    fill_rectangle(x+((8-j)*size), y+((i)*size), x+((8-j)*size)+size, y+((i)*size)+size, colour);
                }
            }
        }
    }
}


/*
 * Writes a string to the display as an array of chars at position x, y with 
 * a given colour and size.
 */
void draw_string(char x, char y, unsigned int colour, char size, char *str) {
    
    //Work out the size of each character
    int char_width = size * 9;
    //Iterate through each character in the string
    int counter = 0;
    while(str[counter] != '\0') {
        //Calculate character position
        int char_pos = x + (counter * char_width);
        //Write char to the display
        draw_char(char_pos, y, str[counter], colour, size);
        //Next character
        counter++;
    }
}

/* Draws a bitmap array of colours to the display.
 * First two bytes should be width and height respectively.
 * Subsequent bits are uint16 representations of the pixel colours.
 * 
 * NOTE: This could be made more efficient by not using the fill_rectangle
 * method. But I didn't need the speed, and it simplified the code a lot.
 */
void draw_bitmap(int x, int y, int scale, unsigned int *bmp) {
    
    int width = bmp[0];
    int height = bmp[1];
    unsigned int this_byte;
    int this_x;
    int this_y;

    //Write colour to each pixel
    for(int i = 0; i < height ; i++) {
        for(int j = 0; j < width; j++) {
            this_byte = bmp[(width * i) + j + 2];
            this_x = x + (j * scale);
            this_y = y + (i * scale);
            //Draw the pixel with appropriate scaling
            if(scale > 1)
                fill_rectangle(this_x, this_y, this_x + scale, this_y + scale, this_byte);
            else
                draw_pixel(this_x, this_y, this_byte);
        }
    }
}