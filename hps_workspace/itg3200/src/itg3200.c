#include "itg3200.h"

uint8_t read_version_itg(void){

	uint8_t version = 0;

	uint8_t cmd_reg_0 = {0};

	if(write_i2c(I2C_2, ADDR_ITG, &cmd_reg_0, 1) != 1)
		return -1;

	if(read_i2c(I2C_2, ADDR_ITG, &version, 1) != 1)
		return -1;

	version = (version & 0x7e);

	version = (version >> 1);

	return version;
}

uint16_t read_temp_itg(void){

	uint8_t reg_addr = {0x1B};
	uint8_t temp_data[2];
	uint16_t temperatur = 0;

	if(write_i2c(I2C_2, ADDR_ITG, &reg_addr, 1) != 1)
		return -1;

	if(read_i2c(I2C_2, ADDR_ITG, temp_data, 2) != 2)
		return -2;

	temperatur = temp_data[0];

	temperatur = (temperatur << 8);

	temperatur = (temperatur | temp_data[1]);

	temperatur = temperatur + 13200;

	return temperatur;

}

