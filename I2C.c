////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	C:\Users\Mohammad\Desktop\AVRCLibrary\AVRCLibrary\I2C.c
//
// summary:	Declares the I2C interface
////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 *
 * I2C.c
 *
 *
 * |_______ Avr I2C  library_______|
 *
 *
 *
 *
 * Created: 2020-08-21 08:55:15
 *
 * Filename: I2C.c
 * Controller: Atmega8/16/32/128
 * Oscillator: 1 MHz
 * Author: XploreLabz
 * website: www.xplorelabz.com
 * Refer Atmega32 for register description.
 *
 */

#include <avr/io.h>
#include "Configuration.h"
#include <util/delay.h>
#include "I2C.h"

/*
 *
 * Description :This function is used to initialize the I2c Module.
 * I/P Arguments: none
 * Return value: none
 *
 */
void I2C_Init ( )
	{
		TWSR = 0x00 ; //set presca1er bits to zero
		TWBR = 0x46 ; //SCL frequency is 100K for XTAL = 7.3728M
		TWCR = 0x04 ; //enab1e TWI module
	}

/*
 *
 * Description  :This function is used to generate I2C Start Condition.
 *		Start Condition: SDA goes low when SCL is High.
 * I/P Arguments: none
 * Return value: none
 *
 */
void I2C_Start ( )
	{
		TWCR = ( ( 1 << TWINT ) | ( 1 << TWSTA ) | ( 1 << TWEN ) ) ;
		while ( ! ( TWCR & ( 1 << TWINT ) ) ) ;
	}

/*
 *
 * Description  :This function is used to generate I2C Stop Condition.
 *		Stop Condition: SDA goes High when SCL is High.
 * I/P Arguments: none
 * Return value: none
 *
 */
void I2C_Stop ( )
	{
		TWCR = ( (1 << TWINT ) | ( 1 << TWEN ) | ( 1 << TWSTO ) ) ;
		_delay_us ( 10 ) ; //wait for a short time
	}

/*
 *
 * Description  :This function is used to send a byte on SDA line using I2C protocol
 *		8bit data is sent bit-by-bit on each clock cycle.
 *		MSB(bit) is sent first and LSB(bit) is sent at last.
 *		Data is sent when SCL is low.
 * I/P Arguments: unsigned char-->8bit data to be sent.
 *		Return value: none
 *
 */
void I2C_Write ( unsigned char dat )
	{
		TWDR = dat ;
		TWCR = ( ( 1 << TWINT ) | ( 1 << TWEN ) ) ;
		while ( ! ( TWCR & ( 1 << TWINT ) ) ) ;
	}

/*
 *
 * Description :This fun is used to receive a byte on SDA line using I2C protocol.
 *		8bit data is received bit-by-bit each clock and finally packed into Byte.
 *		MSB(bit) is received first and LSB(bit) is received at last.
 * I/P Arguments: char: Acknowledgment for the Ninth clock cycle.
 * Return value : Unsigned char(received byte)
 *
 */
unsigned char I2C_Read ( unsigned char ack )
	{
		TWCR = ( ( 1 << TWINT ) | ( 1 << TWEN ) | ( ack << TWEA ) ) ;
		while ( ! ( TWCR & ( 1 << TWINT ) ) ) ;
		return TWDR ;
	}

////////////////////////////////////////////////////////////////////////////////////////////////////
// End of C:\Users\Mohammad\Desktop\AVRCLibrary\AVRCLibrary\I2C.c
////////////////////////////////////////////////////////////////////////////////////////////////////