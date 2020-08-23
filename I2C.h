////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	C:\Users\Mohammad\Desktop\AVRCLibrary\AVRCLibrary\I2C.h
//
// summary:	Declares the I2C interface
////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 *
 * I2C.h
 *
 *
 * |_______ Avr I2C  library_______|
 *
 *
 *
 *
 * Created: 2020-08-21 08:55:15
 *
 * Filename: I2C.h
 * Controller: Atmega8/16/32/128
 * Oscillator: 1 MHz
 * Author: XploreLabz
 * website: www.xplorelabz.com
 * Refer Atmega32 for register description.
 *
 */

#ifndef I2C_H_
#define I2C_H_

/*
 *
 * Description :This function is used to initialize the I2c Module.
 * I/P Arguments: none
 * Return value: none
 *
 */
void I2C_Init ( ) ;

/*
 *
 * Description  :This function is used to generate I2C Start Condition.
 *		Start Condition: SDA goes low when SCL is High.
 * I/P Arguments: none
 * Return value: none
 *
 */
void I2C_Start ( ) ;

/*
 *
 * Description  :This function is used to generate I2C Stop Condition.
 *		Stop Condition: SDA goes High when SCL is High.
 * I/P Arguments: none
 * Return value: none
 *
 */
void I2C_Stop ( ) ;

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
void I2C_Write ( unsigned char dat ) ;

/*
 *
 * Description :This fun is used to receive a byte on SDA line using I2C protocol.
 *		8bit data is received bit-by-bit each clock and finally packed into Byte.
 *		MSB(bit) is received first and LSB(bit) is received at last.
 * I/P Arguments: char: Acknowledgment for the Ninth clock cycle.
 * Return value : Unsigned char(received byte)
 *
 */
unsigned char I2C_Read ( unsigned char ack ) ;

#endif /* I2C_H_ */

////////////////////////////////////////////////////////////////////////////////////////////////////
// End of C:\Users\Mohammad\Desktop\AVRCLibrary\AVRCLibrary\I2C.h
////////////////////////////////////////////////////////////////////////////////////////////////////