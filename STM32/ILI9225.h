/* 
 * Driver for the ILI9225 intended for PIC18F26K42 but should be transferrable
 * to other models fairly easily.
 * 
 * Works with OTM2201A, and ILI9925 controller chips.
 * 
 * For more details see main description in C file.
 * 
 * File:   ILI9225.h
 * Author: tommy
 *
 * Created on 2 July 2019, 7:33 PM
 */

#ifndef ILI9225_H
#define	ILI9225_H

#ifdef	__cplusplus
extern "C" {
#endif

	//STM32 library for your particular microcontroller
	#include "stm32l4xx_hal.h"

    //Hard-coded dimensions of the display
    #define WIDTH       220
    #define HEIGHT      176
    #define LANDSCAPE   1

    /* ILI9225 LCD Registers */
    #define ILI9225_DRIVER_OUTPUT_CTRL      (0x01u)  // Driver Output Control
    #define ILI9225_LCD_AC_DRIVING_CTRL     (0x02u)  // LCD AC Driving Control
    #define ILI9225_ENTRY_MODE              (0x03u)  // Entry Mode
    #define ILI9225_DISP_CTRL1              (0x07u)  // Display Control 1
    #define ILI9225_BLANK_PERIOD_CTRL1      (0x08u)  // Blank Period Control
    #define ILI9225_FRAME_CYCLE_CTRL        (0x0Bu)  // Frame Cycle Control
    #define ILI9225_INTERFACE_CTRL          (0x0Cu)  // Interface Control
    #define ILI9225_OSC_CTRL                (0x0Fu)  // Osc Control
    #define ILI9225_POWER_CTRL1             (0x10u)  // Power Control 1
    #define ILI9225_POWER_CTRL2             (0x11u)  // Power Control 2
    #define ILI9225_POWER_CTRL3             (0x12u)  // Power Control 3
    #define ILI9225_POWER_CTRL4             (0x13u)  // Power Control 4
    #define ILI9225_POWER_CTRL5             (0x14u)  // Power Control 5
    #define ILI9225_VCI_RECYCLING           (0x15u)  // VCI Recycling
    #define ILI9225_RAM_ADDR_SET1           (0x20u)  // Horizontal GRAM Address Set
    #define ILI9225_RAM_ADDR_SET2           (0x21u)  // Vertical GRAM Address Set
    #define ILI9225_GRAM_DATA_REG           (0x22u)  // GRAM Data Register
    #define ILI9225_GATE_SCAN_CTRL          (0x30u)  // Gate Scan Control Register
    #define ILI9225_VERTICAL_SCROLL_CTRL1   (0x31u)  // Vertical Scroll Control 1 Register
    #define ILI9225_VERTICAL_SCROLL_CTRL2   (0x32u)  // Vertical Scroll Control 2 Register
    #define ILI9225_VERTICAL_SCROLL_CTRL3   (0x33u)  // Vertical Scroll Control 3 Register
    #define ILI9225_PARTIAL_DRIVING_POS1    (0x34u)  // Partial Driving Position 1 Register
    #define ILI9225_PARTIAL_DRIVING_POS2    (0x35u)  // Partial Driving Position 2 Register
    #define ILI9225_HORIZONTAL_WINDOW_ADDR1 (0x36u)  // Horizontal Address Start Position
    #define ILI9225_HORIZONTAL_WINDOW_ADDR2 (0x37u)  // Horizontal Address End Position
    #define ILI9225_VERTICAL_WINDOW_ADDR1   (0x38u)  // Vertical Address Start Position
    #define ILI9225_VERTICAL_WINDOW_ADDR2   (0x39u)  // Vertical Address End Position
    #define ILI9225_GAMMA_CTRL1             (0x50u)  // Gamma Control 1
    #define ILI9225_GAMMA_CTRL2             (0x51u)  // Gamma Control 2
    #define ILI9225_GAMMA_CTRL3             (0x52u)  // Gamma Control 3
    #define ILI9225_GAMMA_CTRL4             (0x53u)  // Gamma Control 4
    #define ILI9225_GAMMA_CTRL5             (0x54u)  // Gamma Control 5
    #define ILI9225_GAMMA_CTRL6             (0x55u)  // Gamma Control 6
    #define ILI9225_GAMMA_CTRL7             (0x56u)  // Gamma Control 7
    #define ILI9225_GAMMA_CTRL8             (0x57u)  // Gamma Control 8
    #define ILI9225_GAMMA_CTRL9             (0x58u)  // Gamma Control 9
    #define ILI9225_GAMMA_CTRL10            (0x59u)  // Gamma Control 10

    #define ILI9225C_INVOFF  0x20
    #define ILI9225C_INVON   0x21

    /* RGB 16-bit color table definition (RG565) */
    #define COLOR_BLACK          0x0000      /*   0,   0,   0 */
    #define COLOR_WHITE          0xFFFF      /* 255, 255, 255 */
    #define COLOR_BLUE           0x001F      /*   0,   0, 255 */
    #define COLOR_GREEN          0x07E0      /*   0, 255,   0 */
    #define COLOR_RED            0xF800      /* 255,   0,   0 */
    #define COLOR_NAVY           0x000F      /*   0,   0, 128 */
    #define COLOR_DARKBLUE       0x0011      /*   0,   0, 139 */
    #define COLOR_DARKGREEN      0x03E0      /*   0, 128,   0 */
    #define COLOR_DARKCYAN       0x03EF      /*   0, 128, 128 */
    #define COLOR_CYAN           0x07FF      /*   0, 255, 255 */
    #define COLOR_TURQUOISE      0x471A      /*  64, 224, 208 */
    #define COLOR_INDIGO         0x4810      /*  75,   0, 130 */
    #define COLOR_DARKRED        0x8000      /* 128,   0,   0 */
    #define COLOR_OLIVE          0x7BE0      /* 128, 128,   0 */
    #define COLOR_GRAY           0x8410      /* 128, 128, 128 */
    #define COLOR_GREY           0x8410      /* 128, 128, 128 */
    #define COLOR_SKYBLUE        0x867D      /* 135, 206, 235 */
    #define COLOR_BLUEVIOLET     0x895C      /* 138,  43, 226 */
    #define COLOR_LIGHTGREEN     0x9772      /* 144, 238, 144 */
    #define COLOR_DARKVIOLET     0x901A      /* 148,   0, 211 */
    #define COLOR_YELLOWGREEN    0x9E66      /* 154, 205,  50 */
    #define COLOR_BROWN          0xA145      /* 165,  42,  42 */
    #define COLOR_DARKGRAY       0x7BEF      /* 128, 128, 128 */
    #define COLOR_DARKGREY       0x7BEF      /* 128, 128, 128 */
    #define COLOR_SIENNA         0xA285      /* 160,  82,  45 */
    #define COLOR_LIGHTBLUE      0xAEDC      /* 172, 216, 230 */
    #define COLOR_GREENYELLOW    0xAFE5      /* 173, 255,  47 */
    #define COLOR_SILVER         0xC618      /* 192, 192, 192 */
    #define COLOR_LIGHTGRAY      0xC618      /* 192, 192, 192 */
    #define COLOR_LIGHTGREY      0xC618      /* 192, 192, 192 */
    #define COLOR_LIGHTCYAN      0xE7FF      /* 224, 255, 255 */
    #define COLOR_VIOLET         0xEC1D      /* 238, 130, 238 */
    #define COLOR_AZUR           0xF7FF      /* 240, 255, 255 */
    #define COLOR_BEIGE          0xF7BB      /* 245, 245, 220 */
    #define COLOR_MAGENTA        0xF81F      /* 255,   0, 255 */
    #define COLOR_TOMATO         0xFB08      /* 255,  99,  71 */
    #define COLOR_GOLD           0xFEA0      /* 255, 215,   0 */
    #define COLOR_ORANGE         0xFD20      /* 255, 165,   0 */
    #define COLOR_SNOW           0xFFDF      /* 255, 250, 250 */
    #define COLOR_YELLOW         0xFFE0      /* 255, 255,   0 */

    //Pin definitions (For PIC18F26K40) - change as required
    //NOTE: on older micros this will just be RC0, RC1, etc.
    //On newer chips we have to use the latch registers.
	#define	CSX_PORT	GPIOC
    #define CSX_PIN		GPIO_PIN_1 //Chip select
	#define RESX_PORT	GPIOC
    #define RESX_PIN	GPIO_PIN_0 //Reset pin
	#define	CMD_PORT	GPIOB
    #define CMD_PIN		GPIO_PIN_0 //Command select
    
    //SPI Bus status register
    //Set this to suit your particular microcontroller
	SPI_HandleTypeDef hspi2;
    
    void spi_write(unsigned char data);
    void lcd_write_command(unsigned char data);
    void lcd_write_data(unsigned char data);
    void lcd_write_register(unsigned int reg, unsigned int data);
    void lcd_init(void);
    void swap_int(int *num1, int *num2);
    void swap_char(char *num1, char *num2);
    void delay_ms(double millis);
    void delay_us(long int cycles);
    void lcd_init_command_list(void);
    void draw_pixel(char x, char y, unsigned int colour);
    void set_draw_window(char row_start, char row_end, char col_start, char col_end);
    void fill_rectangle(char x1, char y1, char x2, char y2, unsigned int colour);
    void draw_char(char x, char y, char c, unsigned int colour, char size);
    void draw_fast_char(char x, char y, char c, unsigned int colour, unsigned int bg_colour);
    void draw_string(char x, char y, unsigned int colour, char size, char *str);
    void draw_fast_string(char x, char y, unsigned int colour, unsigned int bg_colour, char *str);
    void draw_line(char x1, char y1, char x2, char y2, unsigned int colour);
    void draw_bitmap(int x, int y, int scale, const unsigned int *bmp);

#ifdef	__cplusplus
}
#endif

#endif	/* ILI9225_H */

