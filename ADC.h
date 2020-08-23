////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	C:\Users\Mohammad\Desktop\AVRCLibrary\AVRCLibrary\ADC.h
//
// summary:	Declares the ADC class
////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 *
 * ADC.h
 *
 *
 * |_______Avr ADC library_______|
 *
 *
 *
 *
 * Created: 2020-08-19 23:09:46
 *
 * Filename: ADC.h
 * Controller: Atmega8/16/32/128
 * Oscillator: 1 MHz
 * Author: XploreLabz
 * website: www.xplorelabz.com
 * Reference:Atmega32 dataSheet
 *
 */

#ifndef ADC_H_
#define ADC_H_

/*
 *
 * Description :This function initializes the ADC control registers
 * I/P Arguments: none
 * Return value: none
 *
 */
void ADC_Init ( ) ;

/*
 *
 * Description  :This function does the ADC conversioin for the Selected Channel and returns the converted 10bit result
 * I/P Arguments: char(channel number)
 * Return value : int(10 bit ADC result)
 *
 */
unsigned int ADC_StartConversion ( unsigned char channel ) ;

#endif /* ADC_H_ */

////////////////////////////////////////////////////////////////////////////////////////////////////
// End of C:\Users\Mohammad\Desktop\AVRCLibrary\AVRCLibrary\ADC.h
////////////////////////////////////////////////////////////////////////////////////////////////////