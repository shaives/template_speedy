/**
  *******************************************************************************************************************
  * @file      	srf08.c
  * @author    	B. Eng. Urban Conrad
  * @version   	V1.0
  * @date      	14.07.2016
  * @copyright 	2009 - 2016 UniBw M - ETTI - Institut 4
  * @brief   	Functions to control SRF08 modul
  *******************************************************************************************************************
  * @par History:
  *  @details V1.0.0 14.07.2016 Urban Conrad
  *           - Initial version
  *******************************************************************************************************************
  */
  
//	I	N	C	L	U	D	E	S

#include "itg3200.h"

//	F	U	N	K	T	I	O	N	E	N

uint8_t read_version_itg(void){

	uint8_t version = 0;

	uint8_t cmd_reg_0 = {0};

	//Befehl auf I2C Bus schreiben
	if(write_i2c(I2C_2, ADDR_ITG, &cmd_reg_0, 1) != 1)
		return -1;

	//Lesen auf I2C Bus
	if(read_i2c(I2C_2, ADDR_ITG, &version, 1) != 1)
		return -2;

	//Maske auf Version legen
	version = (version & 0x7e);

	//Muss um 1 nach rechts geschrieben werden
	version = (version >> 1);

	//Version zurueckgeben
	return version;
}

uint16_t read_temp_itg(void){

	uint8_t reg_addr = {0x1B};
	uint8_t temp_data[2];
	uint16_t temperatur = 0;

	//Befehl auf I2C Bus schreiben
	if(write_i2c(I2C_2, ADDR_ITG, &reg_addr, 1) != 1)
		return -1;

	//Lesen auf I2C Bus
	if(read_i2c(I2C_2, ADDR_ITG, temp_data, 2) != 2)
		return -2;

	//Ersten 8 bit schreiben
	temperatur = temp_data[0];

	//8 bit schieben um 8 nach links
	temperatur = (temperatur << 8);

	//Verodern mit low 8 bit
	temperatur = (temperatur | temp_data[1]);

	//Offset auf Temperatur rechnen
	temperatur = temperatur + 13200;

	//Temperatur zurueckgeben
	return temperatur;

}

