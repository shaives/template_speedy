#include <stdint.h>

#include "laser_include.h"


int main(void) {

	void *virtual_base;
	volatile uint32_t *hps_laser = NULL;
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

	hps_laser = virtual_base + ( (uint32_t)( ALT_LWFPGASLVS_OFST + LASER_BASE ) & (uint32_t)( HW_REGS_MASK ) );

	initMemory(hps_laser); //Speicher initialisieren

	uint16_t distance[ARRAY_LENGHT];

	while(1){
		doMeasurement(hps_laser, &distance);
		usleep(5*1000*1000);
	}



	if( munmap( virtual_base, HW_REGS_SPAN ) != 0 ) {
		printf( "ERROR: munmap() failed...\n" );
		close( fd );
		return( 1 );
	}

	close( fd );

	return( 0 );

}
