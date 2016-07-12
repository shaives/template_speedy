#include <stdio.h>


#include "i2c.h"
#include "itg3200.h"


int main(int argc, char *argv[]){

	if(init_i2c(I2C_2) != 0){
		printf("Init I2C 100kHz Failed\n");
		return -1;
	} else {
		printf("Init I2C 100kHz successful\n");
	}

	uint8_t version;
	version = read_version_itg();

	printf("Version: %d\n", version);

	uint16_t temp;
	temp = read_temp_itg();

	printf("Temperatur: %d", temp);

	return 0;
	
}
