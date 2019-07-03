/*
 * Test Harness for the ILI9225 LCD driver.
 * 
 * File:   main.c
 * Author: tommy
 *
 * Created on 2 July 2019, 7:32 PM
 */

// PIC18F26K42 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1L
#pragma config FEXTOSC = OFF    // External Oscillator Selection->Oscillator not enabled
#pragma config RSTOSC = HFINTOSC_64MHZ    // Reset Oscillator Selection->HFINTOSC with HFFRQ = 4 MHz and CDIV = 4:1

// CONFIG1H
#pragma config CLKOUTEN = OFF    // Clock out Enable bit->CLKOUT function is disabled
#pragma config PR1WAY = ON    // PRLOCKED One-Way Set Enable bit->PRLOCK bit can be cleared and set only once
#pragma config CSWEN = ON    // Clock Switch Enable bit->Writing to NOSC and NDIV is allowed
#pragma config FCMEN = ON    // Fail-Safe Clock Monitor Enable bit->Fail-Safe Clock Monitor enabled

// CONFIG2L
#pragma config MCLRE = EXTMCLR    // MCLR Enable bit->If LVP = 0, MCLR pin is MCLR; If LVP = 1, RE3 pin function is MCLR 
#pragma config PWRTS = PWRT_OFF    // Power-up timer selection bits->PWRT is disabled
#pragma config MVECEN = OFF    // Multi-vector enable bit->Interrupt contoller does not use vector table to prioritze interrupts
#pragma config IVT1WAY = ON    // IVTLOCK bit One-way set enable bit->IVTLOCK bit can be cleared and set only once
#pragma config LPBOREN = OFF    // Low Power BOR Enable bit->ULPBOR disabled
#pragma config BOREN = SBORDIS    // Brown-out Reset Enable bits->Brown-out Reset enabled , SBOREN bit is ignored

// CONFIG2H
#pragma config BORV = VBOR_2P45    // Brown-out Reset Voltage Selection bits->Brown-out Reset Voltage (VBOR) set to 2.45V
#pragma config ZCD = OFF    // ZCD Disable bit->ZCD disabled. ZCD can be enabled by setting the ZCDSEN bit of ZCDCON
#pragma config PPS1WAY = OFF    // PPSLOCK OFF - can change PPS register at any time
#pragma config STVREN = ON    // Stack Full/Underflow Reset Enable bit->Stack full/underflow will cause Reset
#pragma config DEBUG = OFF    // Debugger Enable bit->Background debugger disabled
#pragma config XINST = OFF    // Extended Instruction Set Enable bit->Extended Instruction Set and Indexed Addressing Mode disabled

// CONFIG3L
#pragma config WDTCPS = WDTCPS_31    // WDT Period selection bits->Divider ratio 1:65536; software control of WDTPS
#pragma config WDTE = OFF    // WDT operating mode->WDT Disabled; SWDTEN is ignored

// CONFIG3H
#pragma config WDTCWS = WDTCWS_7    // WDT Window Select bits->window always open (100%); software control; keyed access not required
#pragma config WDTCCS = SC    // WDT input clock selector->Software Control

// CONFIG4L
#pragma config BBSIZE = BBSIZE_512    // Boot Block Size selection bits->Boot Block size is 512 words
#pragma config BBEN = OFF    // Boot Block enable bit->Boot block disabled
#pragma config SAFEN = OFF    // Storage Area Flash enable bit->SAF disabled
#pragma config WRTAPP = OFF    // Application Block write protection bit->Application Block not write protected

// CONFIG4H
#pragma config WRTB = OFF    // Configuration Register Write Protection bit->Configuration registers (300000-30000Bh) not write-protected
#pragma config WRTC = OFF    // Boot Block Write Protection bit->Boot Block (000000-0007FFh) not write-protected
#pragma config WRTD = OFF    // Data EEPROM Write Protection bit->Data EEPROM not write-protected
#pragma config WRTSAF = OFF    // SAF Write protection bit->SAF not Write Protected
#pragma config LVP = ON    // Low Voltage Programming Enable bit->Low voltage programming enabled. MCLR/VPP pin function is MCLR. MCLRE configuration bit is ignored

// CONFIG5L
#pragma config CP = OFF    // PFM and Data EEPROM Code Protection bit->PFM and Data EEPROM code protection disabled

#include <xc.h>
#include "ILI9225.h"

#define PWR_LED     LATC7

/*
 * Initialise SPI port for the LCD
 */
void initSPI() {
    //Set PPS ports for the SPI1 module
    RC0PPS = 0b11111; //SDO on RC0
    RC1PPS = 0b11110; //SCL on RC1
    //Set SPI baud rate FOSC / 4
    SPI1BAUD = 0x01;
    //Transmit only mode
    SPI1CON2 = 0b00000010;
    //Set the SPI bus to resting positive clock
    SPI1CON1 = 0b00100000;
    //Enable SPI bus
    SPI1CON0 = 0b10000011;
}

void main(void) {
    
    //Set oscillator to 32MHz
    OSCFRQ = 0b00000110;
    //Set Port C to OUTPUT
    TRISC = 0x00;
    ANSELC = 0x00;
    //Set all Port A to OUTPUT
    TRISA = 0x00;
    //Port B has the input buttons on it
    TRISB = 0xFF;
    ANSELB = 0x00;
    
    //Begin SPI
    initSPI();
    
    //Initialise the LCD
    lcd_init();
    //Clear the screen
    fill_rectangle(0, 0, WIDTH, HEIGHT, COLOR_BLACK);
    
    //Power LED to show that we have finished boot
    PWR_LED = 1;
    
    //Test pattern
    while(1) {
        fill_rectangle(0, 0, WIDTH, HEIGHT, COLOR_LIGHTBLUE);
        draw_string(64, 64, COLOR_BLACK, 1, "Hello World\0");
        delay_ms(1000);
        fill_rectangle(0, 0, WIDTH, HEIGHT, COLOR_RED);
        draw_string(64, 64, COLOR_BLACK, 2, "Hello World\0");
        delay_ms(1000);
        fill_rectangle(0, 0, WIDTH, HEIGHT, COLOR_GREEN);
        draw_string(64, 64, COLOR_BLACK, 3, "Hello World\0");
        delay_ms(1000);
    }
    return;
}
