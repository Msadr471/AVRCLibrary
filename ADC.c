////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	C:\Users\Mohammad\Desktop\AVRCLibrary\AVRCLibrary\ADC.c
//
// summary:	ADC class
////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 *
 * ADC.c
 *
 *
 * |_______Avr ADC library_______|
 *
 *
 *
 *
 * Created: 2020-08-19 23:09:46
 *
 * Filename: ADC.c
 * Controller: Atmega8/16/32/128
 * Oscillator: 1 MHz
 * Author: XploreLabz
 * website: www.xplorelabz.com
 * Reference:Atmega32 dataSheet
 *
 */

#include <avr/io.h>
#include "Configuration.h"
#include <util/delay.h>
#include "ADC.h"

/*
 *
 * Description :This function initializes the ADC control registers
 * I/P Arguments: none
 * Return value: none
 *
 */
void ADC_Init ( )
	{
		ADCSRA =0x81 ; //Enable ADC , sampling freq=osc_freq/2
		ADMUX = 0x00 ; //Result right justified, select channel zero
	}

/*
 *
 * Description  :This function does the ADC conversioin for the Selected Channel and returns the converted 10bit result
 * I/P Arguments: char(channel number)
 * Return value : int(10 bit ADC result)
 *
 */
unsigned int ADC_StartConversion ( unsigned char channel )
	{
		ADMUX = channel ;
		_delay_ms ( 5 ) ;
		ADCSRA = 0xc1 ;
		while ( ( ADCSRA & ( 1 << ADIF ) ) == 0 ) ;
		return ( ADCW ) ;
	}

////////////////////////////////////////////////////////////////////////////////////////////////////
// End of C:\Users\Mohammad\Desktop\AVRCLibrary\AVRCLibrary\ADC.c
////////////////////////////////////////////////////////////////////////////////////////////////////