////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	C:\Users\Mohammad\Desktop\AVRCLibrary\AVRCLibrary\Keypad.h
//
// summary:	Declares the keypad class
////////////////////////////////////////////////////////////////////////////////////////////////////


/*
 * Keypad.h
 *
 *
 * |_______Avr 4x4 Keypad Library_______|
 *
 *
 *
 *
 * Created: 2020-08-21 07:39:08
 *
 * Filename: keypad.c
 * Controller: Atmega8/16/32/128
 * Oscillator: 1 MHz
 * Author: XploreLabz
 * website: www.xplorelabz.com
 * Reference:Atmega32 dataSheet
 *
 *	Note:
 *
 *		Rows are connected to lower 4-bits of PORTC
 *		Cols are connected to higher 4-bits of PORTC
 *
 */


#ifndef KEYPAD_H_
#define KEYPAD_H_

/*
 *
 * Description  : This function the rows and colums for keypad scan
 *		ROW lines are configured as Output.
 *		Column Lines are configured as Input.
 * I/P Arguments:none
 * Return value : none
 *
 */
void KEYPAD_Init ( ) ;

/*
 *
 * Description  : This function waits till the previous key is released.
 *		All the ROW lines are pulled low.
 *		Column Lines are read to check the key press.
 *		If all the Keys are released then Column lines will remain high(0x0f)
 * I/P Arguments:none
 * Return value : none
 *
 */
void KEYPAD_WaitForKeyRelease ( ) ;

/*
 *
 * Description  : This function waits till a new key is pressed.
 *		All the ROW lines are pulled low.
 *		Column Lines are read to check the key press.
 *		If any Key is pressed then corresponding Column Line goes low.
 *		Wait for Some time and perform the above operation to ensure the True Key Press before decoding the KEY.
 * I/P Arguments:none
 * Return value : none
 *
 */
void KEYPAD_WaitForKeyPress ( ) ;

/*
 *
 * Description  :This function scans all the rows to decode the key pressed.
 *		Each time a ROW line is pulled low to detect the KEY.
 *		Column Lines are read to check the key press.
 *		If any Key is pressed then corresponding Column Line goes low.
 *		Return the ScanCode(Combination of ROW & COL) for decoding the key.
 * I/P Arguments:none
 * Return value : char--> Scancode of the Key Pressed
 *
 */
unsigned char KEYPAD_ScanKey ( ) ;

/*
 *
 * Description:This function waits till a key is pressed and returns its ASCII Value
 *		Wait till the previous key is released..
 *		Wait for the new key press.
 *		Scan all the rows one at a time for the pressed key.
 *		Decode the key pressed depending on ROW-COL combination and returns its ASCII value.
 * I/P Arguments: none
 * Return value : char--> ASCII value of the Key Pressed
 *
 */
unsigned char KEYPAD_GetKey ( ) ;


#endif /* KEYPAD_H_ */

////////////////////////////////////////////////////////////////////////////////////////////////////
// End of C:\Users\Mohammad\Desktop\AVRCLibrary\AVRCLibrary\Keypad.h
////////////////////////////////////////////////////////////////////////////////////////////////////