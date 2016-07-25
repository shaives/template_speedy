/*
 * main.c
 *
 *  Created on: 30.06.2016
 *      Author: Urban
 */

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <soc_cv_av/socal/socal.h>
#include <soc_cv_av/socal/hps.h>

#include "hps_0.h"
#include "hwlib.h"
#include "motor_modul_mm.h"

#define HW_REGS_BASE 	( ALT_STM_OFST )
#define HW_REGS_SPAN 	( 0x04000000 )
#define HW_REGS_MASK 	( HW_REGS_SPAN - 1 )


int main() {

	void *virtual_base;
	volatile uint32_t *hps_saber = NULL;
	int fd;


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

	drive(hps_saber, 50, 600);


	if( munmap( virtual_base, HW_REGS_SPAN ) != 0 ) {
		printf( "ERROR: munmap() failed...\n" );
		close( fd );
		return( 1 );
	}

	close( fd );

	return( 0 );
}
