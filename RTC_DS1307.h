////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	C:\Users\Mohammad\Desktop\AVRCLibrary\AVRCLibrary\RTC_DS1307.h
//
// summary:	Declares the RTC ds 1307 class
////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 *
 * RTC_DS1307.h
 *
 *
 * |_______AVR DS1307  library_______|
 *
 *
 *
 *
 * Created: 2020-08-21 15:05:04
 *
 * Filename: RTC_DS1307.h
 * Controller: Atmega8/16/32/128
 * Oscillator: 1 MHz
 * Author: XploreLabz
 * website: www.xplorelabz.com
 *
 */

#ifndef RTC_DS1307_H_
#define RTC_DS1307_H_

/*
 *
 * Description :This function is used to initialize the Ds1307 RTC.
 * Ds1307 IC is enabled by sending the DS1307 id on the I2C bus.
 * After selecting DS1307, write 0x00 into Control register of Ds1307
 * I/P Arguments: none
 * Return value : none
 *
 */
void DS1307_Init ( ) ;

/*
 *
 * Description  :This function is used to set Time(hh,mm,ss) into the Ds1307 RTC.
 *		Ds1307 ic is enabled by sending the DS1307 id on the I2C bus.
 *		After selecting DS1307, select the RAM address 0x00 to point to sec.
 *		Initilze Sec, MIN, Hour one after the other.
 *		Stop the I2c communication.
 * I/P Arguments: char,char,char-->hh,mm,ss to initilize the time into DS1307.
 * Return value : none
 *
 */
void DS1307_SetTime ( unsigned char hh , unsigned char mm , unsigned char ss ) ;

/*
 *
 * Description  :This function is used to set Date(dd,mm,yy) into the Ds1307 RTC.
 *		Ds1307 IC is enabled by sending the DS1307 id on the I2C bus.
 *		After selecting DS1307, select the RAM address 0x04 to point to day.
 *		Initialize Day,Month and Year one after the other.
 *		Stop the I2c communication.
 * I/P Arguments: char,char,char-->day,month,year to initilize the Date into DS1307.
 * Return value : none
 *
 */
void DS1307_SetDate(unsigned char dd , unsigned char mm , unsigned char yy) ;

/*
 *
 * Description  :This function is used to get the Time(hh,mm,ss) from Ds1307 RTC.
 *		Ds1307 IC is enabled by sending the DS1307 id on the I2C bus.
 *		After selecting DS1307, select the RAM address 0x00 to point to sec.
 *		Get Sec, MIN, Hour one after the other.
 *		Stop the I2c communication.
 * I/P Arguments: char *,char *,char *-->pointers to get the hh,mm,ss.
 * Return value : none
 *
 */
void DS1307_GetTime ( unsigned char *h_ptr , unsigned char *m_ptr , unsigned char *s_ptr ) ;

/*
 *
 * Description  :This function is used to get the Date(y,m,d) from Ds1307 RTC.
 *		Ds1307 IC is enabled by sending the DS1307 id on the I2C bus.
 *		After selecting DS1307, select the RAM address 0x00 to point to DAY.
 *		Get Day, Month, Year one after the other.
 *		Stop the I2c communication.
 * I/P Arguments: char *,char *,char *-->pointers to get the y,m,d.
 * Return value : none
 *
 */
void DS1307_GetDate ( unsigned char *d_ptr , unsigned char *m_ptr , unsigned char *y_ptr ) ;

#endif /* RTC_DS1307_H_ */

////////////////////////////////////////////////////////////////////////////////////////////////////
// End of C:\Users\Mohammad\Desktop\AVRCLibrary\AVRCLibrary\RTC_DS1307.h
////////////////////////////////////////////////////////////////////////////////////////////////////