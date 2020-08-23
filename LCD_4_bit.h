////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	C:\Users\Mohammad\Desktop\AVRCLibrary\AVRCLibrary\LCD_4_bit.h
//
// summary:	Declares the LCD 4 bit class
////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * LCD_4_bit.h
 *
 *
 * |_______AVR LCD library for 4-bit_______|
 *
 *
 *
 *
 * Created: 2020-08-20 14:00:00
 *
 * Filename: lcd_4_bit.h
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
 */

#ifndef LCD_4_BIT_H_
#define LCD_4_BIT_H_

/*
 *
 * Description  :This function is used to initialize the lcd in 4-bit mode
 * Function name: LCD_Init()
 * I/P Arguments: none
 * Return value : none
 *
 */
void LCD_Init ( ) ;

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
void LCD_CmdWrite ( char cmd ) ;

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
void LCD_DataWrite ( char dat ) ;


#endif /* LCD_4_BIT_H_ */

////////////////////////////////////////////////////////////////////////////////////////////////////
// End of C:\Users\Mohammad\Desktop\AVRCLibrary\AVRCLibrary\LCD_4_bit Mode.h
////////////////////////////////////////////////////////////////////////////////////////////////////