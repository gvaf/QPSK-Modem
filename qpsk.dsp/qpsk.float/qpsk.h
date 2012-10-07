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
const double Icarrier[] = {
	  1.00000000,
	  0.70710678,
	  0.00000000,
	 -0.70710678,
	 -1.00000000,
	 -0.70710678,
	 -0.00000000,
	  0.70710678
};

/* The Quadrature Channel */
const double Qcarrier[] = {
	  0.00000000,
	  0.70710678,
	  1.00000000,
	  0.70710678,
	  0.00000000,
	 -0.70710678,
	 -1.00000000,
	 -0.70710678
};

/* The RRC filter coefficients */
const double bcoeff[] = {
	  0.00562698,
	  0.00850416,
	  0.01011487,
	  0.00977210,
	  0.00707461,
	  0.00205033,
	 -0.00476327,
	 -0.01232624,
	 -0.01920049,
	 -0.02374301,
	 -0.02436238,
	 -0.01979814,
	 -0.00937519,
	  0.00681383,
	  0.02783585,
	  0.05197481,
	  0.07691812,
	  0.10004835,
	  0.11879747,
	  0.13100849,
	  0.13524648,
	  0.13100849,
	  0.11879747,
	  0.10004835,
	  0.07691812,
	  0.05197481,
	  0.02783585,
	  0.00681383,
	 -0.00937519,
	 -0.01979814,
	 -0.02436238,
	 -0.02374301,
	 -0.01920049,
	 -0.01232624,
	 -0.00476327,
	  0.00205033,
	  0.00707461,
	  0.00977210,
	  0.01011487,
	  0.00850416,
	  0.00562698
};

#endif
