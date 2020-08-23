////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	C:\Users\Mohammad\Desktop\AVRCLibrary\AVRCLibrary\LCD_4_bit.c
//
// summary:	LCD 4 bit class
////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * LCD_4_bit.c
 *
 *
 * |_______AVR LCD library for 4-bit mode_______|
 *
 *
 *
 *
 * Created: 2020-08-20 14:00:00
 *
 * Filename: lcd_4_bit.c
 * Controller: Atmega Family(8,16,32,64,128)
 * Oscillator: 1 MHz
 * Author: XploreLabz
 * website: www.xplorelabz.com
 * Note:
 *
 * Pin connection for LCD display in 4-bit mode.
 * By default the LCD is connected to PORTB.
 * The code can be modified to connect the LCD to any of the PORTs by changing the "#define databus PORTB".
 *
 * io.h contains the defnition of all ports and SFRs delay.h contains the in built delay routines(us and ms routines)
 *
 *
 */

#include <avr/io.h>
#include "Configuration.h"
#include <util/delay.h>
#include "LCD_4_bit.h"

#define databus_direction			DDRB //  LCD data and Control bus Direction Configuration

#define databus						PORTB      //	LCD databus connected to PORTB
#define control_bus					PORTB      //	LCD Control bus connected to PORTB

#define rs							0                // Register select pin connected 1st bit(D0) Control bus
#define rw							1                // Read Write pin connected to 2nd bit(D1) Control bus
#define en							2                // Enable pin connected to 3rd bit(D2) Control bus

/* 16x2 LCD Specification */
#define LCDMaxLines				 2
#define LCDMaxChars				16
#define LineOne					0x80
#define LineTwo					0xc0

#define BlankSpace				' '

/*
 *
 * Description  :This function is used to initialize the lcd in 4-bit mode
 * Function name: LCD_Init()
 * I/P Arguments: none
 * Return value : none
 *
 */
void LCD_Init ( )
	{
		_delay_ms ( 50 ) ;
		databus_direction = 0xff ;  // Configure both databus and controlbus as output
		LCD_CmdWrite ( 0x02 ) ;	       //Initilize the LCD in 4bit Mode
		LCD_CmdWrite ( 0x28 ) ;
		LCD_CmdWrite ( 0x0E ) ;	      // Display ON cursor ON
		LCD_CmdWrite ( 0x01 ) ;	      // Clear the LCD
		LCD_CmdWrite ( 0x80 ) ;	      // Move the Cursor to First line First Position
	}

/*
 *
 * Description  :This function sends a command to LCD in the following steps.
 *
 * 	step1: Send the Higher Nibble of the I/P command to LCD.
 * 	step2: Select the Control Register by making RS low.
 * 	step3: Select Write operation making RW low.
 * 	step4: Send a High-to-Low pulse on Enable PIN with some delay_us.
 * 	step5: Send the Lower Nibble of the I/P command to LCD.
 * 	step6: Select the Control Register by making RS low.
 * 	step7: Select Write operation making RW low.
 * 	step8: Send a High-to-Low pulse on Enable PIN with some delay_us.
 *
 * I/P Arguments: 8-bit command supported by LCD.
 * Return value : none
 *
 */
void LCD_CmdWrite ( char cmd )
	{
		databus = ( cmd & 0xf0 ) ;        // Send the Higher Nibble of the command to LCD
		control_bus &= ~ ( 1 << rs ) ;  // Select the Command Register by pulling RS LOW
		control_bus &= ~ ( 1 << rw ) ;  // Select the Write Operation  by pulling RW LOW
		control_bus |= 1 << en ;     // Send a High-to-Low Pusle at Enable Pin
		_delay_us ( 1 ) ;
		control_bus &= ~ ( 1 << en ) ;

		_delay_us ( 10 ) ;				// wait for some time

		databus = ( ( cmd << 4 ) & 0xf0 ) ;   // Send the Lower Nibble of the command to LCD
		control_bus &= ~ ( 1 << rs ) ;  // Select the Command Register by pulling RS LOW
		control_bus &= ~ ( 1 << rw ) ;  // Select the Write Operation  by pulling RW LOW
		control_bus |= 1 << en ;     // Send a High-to-Low Pusle at Enable Pin
		_delay_us ( 1 ) ;
		control_bus &= ~ ( 1 << en ) ;
		_delay_ms ( 1 ) ;
	}

/*
 *
 * Description:This function sends a character to be displayed on LCD in the following steps.
 *
 *	step1: Send the higher nibble of the character to LCD.
 *	step2: Select the Data Register by making RS high.
 *	step3: Select Write operation making RW low.
 *	step4: Send a High-to-Low pulse on Enable PIN with some delay_us.
 *	step5: wait for some time
 *	step6: Send the lower nibble of the character to LCD.
 *	step7: Select the Data Register by making RS high.
 *	step8: Select Write operation making RW low.
 *	step9: Send a High-to-Low pulse on Enable PIN with some delay_us.
 *
 * Function name: LCD_DataWrite()
 * I/P Arguments: ASCII value of the char to be displayed.
 * Return value : none
 *
 */
void LCD_DataWrite ( char dat )
	{
		databus = ( dat & 0xf0 ) ;	  // Send the Higher Nibble of the Data to LCD
		control_bus |= 1 << rs ;	  // Select the Data Register by pulling RS HIGH
		control_bus &= ~ ( 1 << rw ) ;	  // Select the Write Operation  by pulling RW LOW
		control_bus |= 1 << en ;	  // Send a High-to-Low Pusle at Enable Pin
		_delay_us ( 1 ) ;
		control_bus &= ~ ( 1 << en ) ;
		_delay_us ( 10 ) ;

		databus = ( ( dat << 4 ) & 0xf0 ) ; // Send the Lower Nibble of the Data to LCD
		control_bus |= 1 << rs ;	   // Select the Data Register by pulling RS HIGH
		control_bus &= ~ ( 1 << rw ) ;	   // Select the Write Operation  by pulling RW LOW
		control_bus |= 1 << en ;	   // Send a High-to-Low Pusle at Enable Pin
		_delay_us ( 1 ) ;
		control_bus &= ~ ( 1 << en ) ;
		_delay_ms ( 1 ) ;

	}

////////////////////////////////////////////////////////////////////////////////////////////////////
// End of C:\Users\Mohammad\Desktop\AVRCLibrary\AVRCLibrary\LCD_4_bit Mode.c
////////////////////////////////////////////////////////////////////////////////////////////////////