/* 
   QPSK Fixed Point
   
   Copyright 2012 George Vafiadis

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/


#include "qpsk.h"

short Ik[HALF_BUFF_SIZE], Qk[HALF_BUFF_SIZE];
short Isam[SAMPLE_RANGE], Qsam[SAMPLE_RANGE];
short Irec[SAMPLE_RANGE], Qrec[SAMPLE_RANGE];
short R_in[NUM_TAPS]; 	/* Input samples R_in[0] most recent, R_in[NUM_TAPS-1]  oldest */

/// Convert to Q15 format
inline short Q15(int a)
{
 if( a >= 0 ) return  (a >> 15) ?  (a >> 15) : a;
 else         return  (-a >> 15) ? -(-a >> 15) : a;
}

void fir_filter (short signal[], int size);

#define multFact  23170       /*   SQRT(2) / 2   in Q15 format */

/* Function "encodeQPSK"    
**  Description:   encode message using QPSDK pi/4 modulation 
**
** INPUT : 
**         message      the input message
**         size         the imput message size
** OUTPUT:
**        signal        the modulation signal
** 
*/
extern void encodeQPSK(short message[], short signal[], int size)
{
 int i, j, halfsize, Sample_Range;
 int oldI, oldQ, newI, newQ;
 int replicate_carrier;
 short tbc1, tbc2, t1, t2;

 halfsize     = size >> 1;
 Sample_Range = NUM_SAMPLES * halfsize;
 
 // Remap to {-1, 1}
 for(i = 0; i < size; ++i)
   message[i] = (message[i] << 1) - 1;
 
 oldI = 1;
 oldQ = 0;

 // Returns the phase shifts for pi/4 DQPSK from the input binary data stream 
 for(i = 0; i < halfsize; ++i)
 {
    tbc1 = message[i * 2];
    tbc2 = message[i * 2 + 1];
    
    newI = Q15( (oldI * tbc1 - oldQ * tbc2) * multFact );
    newQ = Q15( (oldQ * tbc1 + oldI * tbc2) * multFact );
	    
    oldI = newI;
    oldQ = newQ;
    
    Ik[i] = newI;
    Qk[i] = newQ;
  } 

 j = 0;

 for(i = 0; i < Sample_Range; ++i)
  if( i % NUM_SAMPLES == 0 )
   {
     Isam[i] = Ik[j];    
     Qsam[i] = Qk[j];
     j = j + 1;
   }
  else
     Isam[i] = Qsam[i] = 0;
 
 fir_filter( Isam, Sample_Range );
 fir_filter( Qsam, Sample_Range );

 // Upmix with carrier
 for(j = 0; j < Sample_Range; ++j)
 {
   replicate_carrier = j % CARRIER_SIZE;
   t1 = Q15(Isam[j] * Icarrier[replicate_carrier]);
   t2 = Q15(Qsam[j] * Qcarrier[replicate_carrier]);
   signal[j] =  t1 + t2;
 }
}

//_____________________________________________________________________________________________________________________________________________________

/* Function "decodeQPSK"    
**  Description:   decode signal  using QPSDK pi/4 modulation  
**
** INPUT : 
**        signal        the modulation signal (Received)
**        size          signal size
** OUTPUT:
**         message      the transmitted message
** 
*/
extern void decodeQPSK(short signal[], short message[], int size)
{
 int i, j, replicate_carrier;

 for(j = 0; j < size; ++j)
 {
    replicate_carrier = j % CARRIER_SIZE;

    Irec[j] = Q15(signal[j] * Icarrier[replicate_carrier]); 
    Qrec[j] = Q15(signal[j] * Qcarrier[replicate_carrier]);  
 }

 fir_filter(Irec, size);
 fir_filter(Qrec, size);
  
 i = 0;
 for(j = NUM_TAPS; j < size; j +=NUM_SAMPLES )
 {
  Ik[i] = Irec[j];
  Qk[i] = Qrec[j];
  ++i;
 }

 // Loop through and decode the phases  
 for(j = 1; j < HALF_BUFF_SIZE; ++j)
  {
    message[(j << 1) - 2] = (Qk[j] * Qk[j-1] + Ik[j] * Ik[j-1]) > 0;
    message[(j << 1) - 1] = (Ik[j-1] * Qk[j] - Ik[j] * Qk[j-1]) > 0;
  } 
}

//_____________________________________________________________________________________________________________________________________________________


void fir_filter(short signal[], int size)
{
    int acc;
    int prod;
    int i, j;
    
    for(j = 0; j < NUM_TAPS; ++j)
        R_in[j] = 0;

    for(j = 0; j < size; ++j)
      {
	  R_in[0] =  signal[j] ;         		/* Update most recent sample */

	  acc = 0;         
	  
	  for (i = 0; i < NUM_TAPS; i++)        
	  {   
               prod = (int)bcoeff[i] * R_in[i];
               acc += prod;
	  }                   
         
	  signal[j] = acc >> 15;
	  
	  for (i = NUM_TAPS-1; i > 0; i--)         	/* Shift delay samples */
		  R_in[i]=R_in[i-1];
      }
}
