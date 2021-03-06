/**
  *******************************************************************************************************************
  * @file      	srf08.h
  * @author    	B. Eng. Urban Conrad
  * @version   	V1.0
  * @date      	14.07.2016
  * @copyright 	2009 - 2016 UniBw M - ETTI - Institut 4
  * @brief   	Header functions to control srf08 modul
  *******************************************************************************************************************
  * @par History:
  *  @details V1.0.0 14.07.2016 Urban Conrad
  *           - Initial version
  *******************************************************************************************************************
  */
  
#ifndef ITG3200_H_
#define ITG3200_H_

//	I	N	C	L	U	D	E	S

#include <stdint.h>

#include "i2c.h"

//	D	E	F	I	N	E	S

#define ADDR_ITG	0x69

#define REG_Gyro_SampleRateDivider 0x15
#define REG_Gyro_DLPF              0x16
#define REG_Gyro_IR_CFG            0x17

// FS=11 + low pass bandwidth
#define Gyro_LPFBW_256         0x18 //256Hz isr 8kHz
#define Gyro_LPFBW_188         0x19 //188Hz isr 1kHz
#define Gyro_LPFBW_98          0x1A // 98Hz isr 1kHz
#define Gyro_LPFBW_42          0x1B // 42Hz isr 1kHz
#define Gyro_LPFBW_20          0x1C // 20Hz isr 1kHz
#define Gyro_LPFBW_10          0x1D // 10Hz isr 1kHz
#define Gyro_LPFBW_5           0x1E //  5Hz isr 1kHz

#define Gyro_samples4calibration 16

//	F	U	N	K	T	I	O	N	E	N

/**
 *******************************************************************************************************************
 *
 *	@brief		uint8_t init_itg(void)
 *
 *	@details	Diese Funktion Initialisiert den ITG3200 Moduls
 *
 *	@param		void
 *
 *	@retval		0	Alles Ok
 *				-1	Fehler beim schreiben auf I2C - DLPF
 *				-2	Fehler beim schreiben auf I2C - Divisor
 *				-3	Fehler beim schreiben auf I2C - ISR
 *
 *******************************************************************************************************************/

uint8_t init_itg(void);

/**
 *******************************************************************************************************************
 *
 *	@brief		uint8_t read_version_itg(void)
 *
 *	@details	Diese Funktion liest die Version des ITG3200 Moduls aus
 *
 *	@param		void
 *
 *	@retval		x	Version
 *				-1	Fehler beim schreiben auf I2C
 *				-2	Fehler beim lesen auf I2C
 *
 *******************************************************************************************************************/
 
uint8_t read_version_itg(void);

/**
 *******************************************************************************************************************
 *
 *	@brief		uint16_t read_temp_itg(void)
 *
 *	@details	Diese Funktion liest die Temperatur des ITG3200 Moduls aus
 *
 *	@param		void
 *
 *	@retval		x	Temperatur in 1/10 Grad
 *				-1	Fehler beim schreiben auf I2C
 *				-2	Fehler beim lesen auf I2C
 *
 *******************************************************************************************************************/
 
uint16_t read_temp_itg(void);

/**
 *******************************************************************************************************************
 *
 *	@brief		uint16_t read_gyro_z(void)
 *
 *	@details	Diese Funktion liest die Z Werte des ITG3200 Moduls aus
 *
 *	@param		void
 *
 *	@retval		x	z Wert
 *				-1	Fehler beim schreiben auf I2C
 *				-2	Fehler beim lesen auf I2C
 *
 *******************************************************************************************************************/

int16_t read_gyro_z(void);


#endif /* ITG3200_H_ */
