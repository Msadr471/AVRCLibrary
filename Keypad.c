////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	C:\Users\Mohammad\Desktop\AVRCLibrary\AVRCLibrary\Keypad.c
//
// summary:	Keypad class
////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 *
 * Keypad.c
 *
 *
 * |_______Avr 4x4 Keypad Library_______|
 *
 *
 *
 *
 * Created: 2020-08-21 07:34:46
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

#include <avr/io.h>
#include "Configuration.h"
#include <util/delay.h>
#include "keypad.h"

#define RowColDirection		DDRC			//Data Direction Configuration for keypad
#define ROW					PORTC            //Lower four bits of PORTC are used as ROWs
#define COL					PINC            //Higher four bits of PORTC are used as COLs

/*
 *
 * Description  : This function the rows and colums for keypad scan
 *		ROW lines are configured as Output.
 *		Column Lines are configured as Input.
 * I/P Arguments:none
 * Return value : none
 *
 */
void KEYPAD_Init ( )
	{
		RowColDirection = 0xf0 ;   // Configure Row lines as O/P and Column lines as I/P
	}

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
void KEYPAD_WaitForKeyRelease ( )
	{
		unsigned char key ;
		do
			{
				ROW = 0x0f ;         // Pull the ROW lines to low and Column high low.
				key = COL & 0x0f ;   // Read the Columns, to check the key press
			}
				while ( key != 0x0f ) ;   // Wait till the Key is released,
		// If no Key is pressed, Column lines will remain high (0x0f)
	}

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
void KEYPAD_WaitForKeyPress ( )
	{
		unsigned char key ;
		do
			{
				do
					{
						ROW = 0x0f ;	   // Pull the ROW lines to low and Column lines high.
						key = COL & 0x0F ;   // Read the Columns, to check the key press
					}
						while ( key == 0x0f ) ; // Wait till the Key is pressed,
				// if a Key is pressed the corresponding Column line go low

				_delay_ms ( 1 ) ;		  // Wait for some time(debounce Time);

				ROW = 0x0f ;		  // After debounce time, perform the above operation
				key = COL & 0x0F ;	  // to ensure the Key press.

			}
				while ( key == 0x0f ) ;
	}

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
unsigned char KEYPAD_ScanKey ( )
	{

		unsigned char ScanKey = 0xe0 , i , key ;

		for ( i = 0 ; i < 0x04 ; i++ )           // Scan All the 4-Rows for key press
			{
				ROW = ScanKey + 0x0F ;         // Select 1-Row at a time for Scanning the Key
				key = COL & 0x0F ;             // Read the Column, for key press

				if ( key != 0x0F )             // If the KEY press is detected for the selected
					break ;                   // ROW then stop Scanning,

				ScanKey = ( ScanKey << 1 ) + 0x10 ; // Rotate the ScanKey to SCAN the remaining Rows
			}

		key = key + ( ScanKey & 0xf0 );  // Return the row and COL status to decode the key

		return ( key ) ;
	}

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
unsigned char KEYPAD_GetKey ( )
	{
		unsigned char key ;

		KEYPAD_WaitForKeyRelease ( ) ;    // Wait for the previous key release
		_delay_ms ( 1 ) ;

		KEYPAD_WaitForKeyPress ( ) ;      // Wait for the new key press
		key = KEYPAD_ScanKey ( ) ;        // Scan for the key pressed.

		switch ( key )                       // Decode the key
			{
				case 0xe7 : key = '0' ; break ;
				case 0xeb : key = '1' ; break ;
				case 0xed : key = '2' ; break ;
				case 0xee : key = '3' ; break ;
				case 0xd7 : key = '4' ; break ;
				case 0xdb : key = '5' ; break ;
				case 0xdd : key = '6' ; break ;
				case 0xde : key = '7' ; break ;
				case 0xb7 : key = '8' ; break ;
				case 0xbb : key = '9' ; break ;
				case 0xbd : key = 'A' ; break ;
				case 0xbe : key = 'B' ; break ;
				case 0x77 : key = 'C' ; break ;
				case 0x7b : key = 'D' ; break ;
				case 0x7d : key = 'E' ; break ;
				case 0x7e : key = 'F' ; break ;
				default : key = 'z' ;
			}
		return ( key ) ;                      // Return the key
	}

////////////////////////////////////////////////////////////////////////////////////////////////////
// End of C:\Users\Mohammad\Desktop\AVRCLibrary\AVRCLibrary\Keypad.c
////////////////////////////////////////////////////////////////////////////////////////////////////