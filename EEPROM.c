////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	C:\Users\Mohammad\Desktop\AVRCLibrary\AVRCLibrary\EEPROM.c
//
// summary:	Eeprom class
////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 *
 * EEPROM.c
 *
 *
 * |_______Avr EEPROM library_______|
 *
 *
 *
 *
 * Created: 2020-08-21 15:33:19
 *
 * Filename: EEPROM.c
 * Controller: Atmega8/16/32/128
 * Oscillator: 1 MHz
 * Author: XploreLabz
 * website: www.xplorelabz.com
 * Reference: Atmega8/16/32 dataSheet for Control register description.
 *
 */

#include <avr/io.h>
#include "Configuration.h"
#include <util/delay.h>

/*
 *
 *	The below value should be set depending on the controller by referring the respective data sheet.
 *
 */

#define MaxEepromSize 1024

/*
 *
 * Description:This function is used to write the data at specified EEPROM_address.
 *		Wait till previous write operation is completed(ie wait till EEWE becomes zero).
 *		Load the eeprom address into EEAR at which the data has to be stored.
 *		Load the data into EEDR which has to be stored in Eeprom.
 *		Set the EEMWE(Eeprom Master Write Enable) and within four clock cycles.
 *		set EEWE(Eeprom Write Enable) to trigger the Eeprom Write Opeartion.
 * I/P Arguments: int,char-->eeprom_address at which eeprom_data is to be written.
 * Return value : none
 *
 */
void EEPROM_WriteByte ( unsigned int eeprom_Address , unsigned char eeprom_Data )
	{
		while ( EECR & ( 1 << EEWE ) ) ;   // Wait for completion of previous write, EEWE will be
		// cleared by hardware once Eeprom write is completed

		EEAR = eeprom_Address ;  //Load the eeprom adddress and data
		EEDR = eeprom_Data ;

		EECR |= ( 1 << EEMWE ) ;    // Write logical one to EEMWE

		EECR |= ( 1 << EEWE ) ;     // Start eeprom write by setting EEWE
	}

/*
 *
 * Description: This function is used to read the data from specified EEPROM_address.
 *		WAit for completion of previous Write operation.
 *		EEWE will be cleared once EEprom write is completed.
 *		Load the eeprom address into EEAR from where the data needs to be read.
 *		Trigger the eeprom read operation by setting EERE(Eeprom Read Enable).
 *		Wait for some time and collect the read data from EEDR.
 * I/P Arguments: int-->eeprom_address from where eeprom_data is to be read.
 * Return value : char-->data read from Eeprom.
 *
 */
unsigned char EEPROM_ReadByte ( unsigned int eeprom_Address )
	{
		while ( EECR & ( 1 << EEWE ) ) ;  //Wait for completion of previous write if any.

		EEAR = eeprom_Address ;    //Load the address from where the datas needs to be read.
		EECR |= ( 1 << EERE ) ;         // start eeprom read by setting EERE

		_delay_ms ( 1 ) ;

		return EEDR ;             // Return data from data register
	}

/*
 *
 * Description:This function is used to write N-bytes of data at specified EEPROM_address.
 *		EEPROM_WriteByte() function is called to write a byte at atime.
 *		Source(RAM) and destination(EEPROM) address are incremented after each write.
 *		NoOfBytes is Decemented each time a byte is written.
 *		Above Operation is carried out till all the bytes are written(NoOfBytes!=0).
 * I/P Arguments:
 *		1- int,-->eeprom_address from where the N-bytes are to be written.
 *		2- char*-->Pointer to the N-bytes of data to be written.
 *		3- char --> Number of bytes to be written
 *
 * Return value : none
 *
 */
void EEPROM_WriteNBytes ( unsigned int EepromAddr , unsigned char *RamAddr , char NoOfBytes )
	{
		while ( NoOfBytes !=  0 )
			{
				EEPROM_WriteByte ( EepromAddr , *RamAddr ) ; //Write a byte from RAM to EEPROM
				EepromAddr++ ;				   //Incerement the Eeprom Address
				RamAddr++ ;				  //Increment the RAM Address
				NoOfBytes-- ;			 //Decrement NoOfBytes after writing each Byte
			}
	}

/*
 *
 * Description: This function is used to Read N-bytes of data from specified EEPROM_address.
 *		EEPROM_ReadByte() func is called to read a byte at a time.
 *		Source(RAM) and destination(EEPROM) address are incremented each time.
 *		NoOfBytes is Decemented after a byte is read.
 *		Above Operation is carried out till all the bytes are read(NoOfBytes!=0).
 * I/P Arguments:
 *		1- int,-->eeprom_address from where the N-bytes is to be read.
 *		2- char*-->Pointer into which the N-bytes of data is to be read.
 *		3- char --> Number of bytes to be Read
 *
 * Return value : none
 *
 */
void EEPROM_ReadNBytes ( unsigned int EepromAddr , unsigned char *RamAddr , char NoOfBytes )
	{
		while ( NoOfBytes !=  0 )
			{
				*RamAddr = EEPROM_ReadByte ( EepromAddr ) ;//Read a byte from EEPROM to RAM
					EepromAddr++;				    //Incerement the Eeprom Address
						RamAddr++;			         //Increment the RAM Address
							NoOfBytes--;			  //Decrement NoOfBytes after Reading each Byte
			}
	}

/*
 *
 * Description: This function is used to Write a String at specified EEPROM_address.
 *		EEPROM_WriteByte() function is called to write a byte at a time.
 *		Source(RAM) and destination(EEPOM) address are incremented each time.
 *		Above Operation is carried out till Null char is identified.
 * I/P Arguments:
 *		1- int,-->eeprom_address where the String is to be written.
 *		2- char*-->Pointer to String which has to be written.
 * Return value : none
 *
 *		NOTE: Null char is also written into the eeprom.
 *
 */
void EEPROM_WriteString ( unsigned int eeprom_address , unsigned char * source_address )
	{
		do
			{
				EEPROM_WriteByte ( eeprom_address , *source_address ) ; //Write a byte from RAM to EEPROM
				source_address++ ;									    //Increment the RAM Address
				eeprom_address++ ;									   //Increment the Eeprom Address
			}
				while ( * ( source_address - 1 ) != 0 ) ;
	}

/*
 *
 * Description: This function is used to Read a String from specified EEPROM_address.
 *		EEPROM_ReadByte() function is called to read a byte at a time.
 *		Source(EEPROM) and destination(RAM) address are incremented each time.
 *		Above Operation is carried out till Null char is identified.
 * I/P Arguments:
 *		1- int,-->eeprom_address from where the String is to be read.
 *		2- char*-->Pointer into which the String is to be read.
 * Return value : none
 *
 */
void EEPROM_ReadString ( unsigned int eeprom_address , unsigned char * destination_address )
	{
		char eeprom_data ;
		do
			{
				eeprom_data = EEPROM_ReadByte ( eeprom_address ) ; //Read a byte from EEPROM to RAM
				*destination_address = eeprom_data ;	       //Copy the data into String Buffer
				destination_address++ ;			      //Increment the RAM Address
				eeprom_address++ ;			     //Increment the Eeprom Address
			}
				while ( eeprom_data != 0 ) ;
	}

/*
 *
 * Description: This function is used to erase the entire Eeprom memory.
 *		Eeprom is filled with 0xFF to accomplish the Eeprom Erase.
 *		EEPROM_WriteByte() function is called to write a byte at a time.
 *		Whole memory(0-MaxEepromSize) is traversed and filled with 0xFF.
 * I/P Arguments: none
 * Return value : none
 *
 */
void EEPROM_Erase ( )
	{
		unsigned int eeprom_address ;
		for ( eeprom_address = 0 ; eeprom_address < MaxEepromSize ; eeprom_address++ )
			{
				EEPROM_WriteByte ( eeprom_address , 0xff ) ; // Write Each memory location with OxFF
			}
	}

////////////////////////////////////////////////////////////////////////////////////////////////////
// End of C:\Users\Mohammad\Desktop\AVRCLibrary\AVRCLibrary\EEPROM.c
////////////////////////////////////////////////////////////////////////////////////////////////////