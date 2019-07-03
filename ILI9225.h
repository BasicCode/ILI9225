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

    #define WIDTH       176
    #define HEIGHT      220

    /* Font files. Thanks Adafruit!
     * We (might) have to split out fonts in to two or more
     * arrays. Most devices have a limit of one RAM bank per
     * which is probably 256 bytes.
     */
    const char Font1[] = {
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x5F, 0x00, 0x00,
    0x00, 0x07, 0x00, 0x07, 0x00,
    0x14, 0x7F, 0x14, 0x7F, 0x14,
    0x24, 0x2A, 0x7F, 0x2A, 0x12,
    0x23, 0x13, 0x08, 0x64, 0x62,
    0x36, 0x49, 0x56, 0x20, 0x50,
    0x00, 0x08, 0x07, 0x03, 0x00,
    0x00, 0x1C, 0x22, 0x41, 0x00,
    0x00, 0x41, 0x22, 0x1C, 0x00,
    0x2A, 0x1C, 0x7F, 0x1C, 0x2A,
    0x08, 0x08, 0x3E, 0x08, 0x08,
    0x00, 0x80, 0x70, 0x30, 0x00,
    0x08, 0x08, 0x08, 0x08, 0x08,
    0x00, 0x00, 0x60, 0x60, 0x00,
    0x20, 0x10, 0x08, 0x04, 0x02,
    0x3E, 0x51, 0x49, 0x45, 0x3E,
    0x00, 0x42, 0x7F, 0x40, 0x00,
    0x72, 0x49, 0x49, 0x49, 0x46,
    0x21, 0x41, 0x49, 0x4D, 0x33,
    0x18, 0x14, 0x12, 0x7F, 0x10,
    0x27, 0x45, 0x45, 0x45, 0x39,
    0x3C, 0x4A, 0x49, 0x49, 0x31,
    0x41, 0x21, 0x11, 0x09, 0x07,
    0x36, 0x49, 0x49, 0x49, 0x36,
    0x46, 0x49, 0x49, 0x29, 0x1E,
    0x00, 0x00, 0x14, 0x00, 0x00,
    0x00, 0x40, 0x34, 0x00, 0x00,
    0x00, 0x08, 0x14, 0x22, 0x41,
    0x14, 0x14, 0x14, 0x14, 0x14,
    0x00, 0x41, 0x22, 0x14, 0x08,
    0x02, 0x01, 0x59, 0x09, 0x06,
    0x3E, 0x41, 0x5D, 0x59, 0x4E,
    0x7C, 0x12, 0x11, 0x12, 0x7C,
    0x7F, 0x49, 0x49, 0x49, 0x36,
    0x3E, 0x41, 0x41, 0x41, 0x22,
    0x7F, 0x41, 0x41, 0x41, 0x3E,
    0x7F, 0x49, 0x49, 0x49, 0x41,
    0x7F, 0x09, 0x09, 0x09, 0x01,
    0x3E, 0x41, 0x41, 0x51, 0x73,
    0x7F, 0x08, 0x08, 0x08, 0x7F,
    0x00, 0x41, 0x7F, 0x41, 0x00,
    0x20, 0x40, 0x41, 0x3F, 0x01,
    0x7F, 0x08, 0x14, 0x22, 0x41,
    0x7F, 0x40, 0x40, 0x40, 0x40,
    0x7F, 0x02, 0x1C, 0x02, 0x7F,
    0x7F, 0x04, 0x08, 0x10, 0x7F,
    0x3E, 0x41, 0x41, 0x41, 0x3E,
    0x7F, 0x09, 0x09, 0x09, 0x06,
    0x3E, 0x41, 0x51, 0x21, 0x5E,
    0x7F, 0x09, 0x19, 0x29, 0x46
    };
    const char Font2[] = {
    0x26, 0x49, 0x49, 0x49, 0x32,
    0x03, 0x01, 0x7F, 0x01, 0x03,
    0x3F, 0x40, 0x40, 0x40, 0x3F,
    0x1F, 0x20, 0x40, 0x20, 0x1F,
    0x3F, 0x40, 0x38, 0x40, 0x3F,
    0x63, 0x14, 0x08, 0x14, 0x63,
    0x03, 0x04, 0x78, 0x04, 0x03,
    0x61, 0x59, 0x49, 0x4D, 0x43,
    0x00, 0x7F, 0x41, 0x41, 0x41,
    0x02, 0x04, 0x08, 0x10, 0x20,
    0x00, 0x41, 0x41, 0x41, 0x7F,
    0x04, 0x02, 0x01, 0x02, 0x04,
    0x40, 0x40, 0x40, 0x40, 0x40,
    0x00, 0x03, 0x07, 0x08, 0x00,
    0x20, 0x54, 0x54, 0x78, 0x40,
    0x7F, 0x28, 0x44, 0x44, 0x38,
    0x38, 0x44, 0x44, 0x44, 0x28,
    0x38, 0x44, 0x44, 0x28, 0x7F,
    0x38, 0x54, 0x54, 0x54, 0x18,
    0x00, 0x08, 0x7E, 0x09, 0x02,
    0x18, 0xA4, 0xA4, 0x9C, 0x78,
    0x7F, 0x08, 0x04, 0x04, 0x78,
    0x00, 0x44, 0x7D, 0x40, 0x00,
    0x20, 0x40, 0x40, 0x3D, 0x00,
    0x7F, 0x10, 0x28, 0x44, 0x00,
    0x00, 0x41, 0x7F, 0x40, 0x00,
    0x7C, 0x04, 0x78, 0x04, 0x78,
    0x7C, 0x08, 0x04, 0x04, 0x78,
    0x38, 0x44, 0x44, 0x44, 0x38,
    0xFC, 0x18, 0x24, 0x24, 0x18,
    0x18, 0x24, 0x24, 0x18, 0xFC,
    0x7C, 0x08, 0x04, 0x04, 0x08,
    0x48, 0x54, 0x54, 0x54, 0x24,
    0x04, 0x04, 0x3F, 0x44, 0x24,
    0x3C, 0x40, 0x40, 0x20, 0x7C,
    0x1C, 0x20, 0x40, 0x20, 0x1C,
    0x3C, 0x40, 0x30, 0x40, 0x3C,
    0x44, 0x28, 0x10, 0x28, 0x44,
    0x4C, 0x90, 0x90, 0x90, 0x7C,
    0x44, 0x64, 0x54, 0x4C, 0x44,
    0x00, 0x08, 0x36, 0x41, 0x00,
    0xFF, 0x3E, 0x1C, 0x08, 0x00,
    0x11, 0x33, 0x77, 0x33, 0x11,
    0x24, 0x66, 0xE7, 0x66, 0x24
    };

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
    #define CSX     LATC3 //Chip select
    #define RESX    LATC4 //Reset pin
    #define CMD     LATC2 //Command select
    //Software SPI pins if required
    #define SDO     LATC0
    #define SCK     LATC1

    //Use hardware SPI, will just big bang it through if false
    #define USE_HW_SPI  1
    
    //SPI Bus status register and transmission buffer
    //Set these to suit your particular microcontroller
    #define SPIBUF  SPI1TXB
    #define SPIIDLE SPI1STATUS & 0x20
    
    void spi_write(unsigned char data);
    void lcd_write_command(unsigned char data);
    void lcd_write_data(unsigned char data);
    void lcd_write_register(unsigned int reg, unsigned int data);
    void lcd_init(void);
    void delay_ms(double millis);
    void delay_us(long int cycles);
    void lcd_init_command_list(void);
    void draw_pixel(char x, char y, unsigned int colour);
    void set_draw_window(char row_start, char row_end, char col_start, char col_end);
    void fill_rectangle(char x1, char y1, char x2, char y2, unsigned int colour);
    void draw_char(char x, char y, char c, unsigned int colour, char size);
    void draw_string(char x, char y, unsigned int colour, char size, char *str);
    void draw_line(char x1, char y1, char x2, char y2, unsigned int colour);
    void draw_bitmap(int x, int y, int scale, unsigned int *bmp);

#ifdef	__cplusplus
}
#endif

#endif	/* ILI9225_H */

