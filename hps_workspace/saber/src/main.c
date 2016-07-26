/*
 * main.c
 *
 *  Created on: 30.06.2016
 *      Author: Urban
 */

#include "motor_modul_mm.h"



int main() {

	void *virtual_base;
	volatile uint32_t *hps_saber = NULL;
	int fd;

	if(init_i2c(I2C_1) != 0){
		printf("Init I2C 100kHz Failed\n");
		return -1;
	} else {
		printf("Init I2C 100kHz successful\n");
	}

	if(init_i2c(I2C_2) != 0){
		printf("Init I2C 100kHz Failed\n");
		return -1;
	} else {
		printf("Init I2C 100kHz successful\n");
	}

	init_itg();

	if( ( fd = open( "/dev/mem", ( O_RDWR | O_SYNC ) ) ) == -1 ) {
		printf( "ERROR: could not open \"/dev/mem\"...\n" );
		return( 1 );
	}

	virtual_base = mmap( NULL, HW_REGS_SPAN, ( PROT_READ | PROT_WRITE ), MAP_SHARED, fd, HW_REGS_BASE );

	if( virtual_base == MAP_FAILED ) {
		printf( "ERROR: mmap() failed...\n" );
		close( fd );
		return( 1 );
	}

	hps_saber = virtual_base + ( (uint32_t)( ALT_LWFPGASLVS_OFST + MOTOR_MODUL_BASE ) & (uint32_t)( HW_REGS_MASK ) );

	usleep(10*1000*1000);

	drive(hps_saber, 125, 600);

	usleep(2000*1000);

	drive_turn_w_offset(hps_saber, 60, 90);

	usleep(2000*1000);

	drive_turn_w_offset(hps_saber, 60, -180);

	usleep(2000*1000);

	drive_curve_steps(hps_saber, 180, 130, 600, 5);

	if( munmap( virtual_base, HW_REGS_SPAN ) != 0 ) {
		printf( "ERROR: munmap() failed...\n" );
		close( fd );
		return( 1 );
	}

	close( fd );

	return( 0 );
}
