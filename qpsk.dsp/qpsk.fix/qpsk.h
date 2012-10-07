/** QPSK Modulation Parameters
	!!! Automatically Generated from gen_qpsk.m matlab file !!!
**/

#ifndef QPSK_PARAMETERS_H
#define QPSK_PARAMETERS_H

#define MESSAGE_LENGTH  3      /* Length of sound in seconds */
#define AUDIO_FS        8000   /* Audio frequency in Hz  */
#define CARRIER_FREQ    1000   /* Carrier frequency in Hz  */
#define SYMBOL_FREQ     500    /* Symbol frequency in Hz  */
#define CUT_OFF_FREQ    500    /* Filter cut off frequency */
#define NUM_TAPS        40     /* Number of Filter TAPS */
#define BUFFER_SIZE     1000   /* The size of the buffer */
#define CARRIER_SIZE    8   /* The size of the carrier for each period*/
#define HALF_BUFF_SIZE  500   /* Half of the message buffer*/
#define NUM_SAMPLES     16   /* The number of samples*/
#define SAMPLE_RANGE    8000   /* The size of modulated signal*/

/* The In-phase channel */
const short Icarrier[] = {
	32767,
	 23170,
	 0,
	 -23170,
	 -32768,
	 -23170,
	 0,
	 23170
};

/* The Quadrature Channel */
const short Qcarrier[] = {
	0,
	23170,
	32767,
	23170,
	0,
	-23170,
	-32768,
	-23170
};

/* The RRC filter coefficients */
const short bcoeff[] = {
	184,
	278,
	331,
	320,
	231,
	67,
	-156,
	-403,
	-629,
	-778,
	-798,
	-648,
	-307,
	223,
	912,
	1703,
	2520,
	3278,
	3892,
	4292,
	4431,
	4292,
	3892,
	3278,
	2520,
	1703,
	912,
	223,
	-307,
	-648,
	-798,
	-778,
	-629,
	-403,
	-156,
	67,
	231,
	320,
	331,
	278,
	184
};

#endif
