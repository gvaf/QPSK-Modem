/* 
   QPSK Modem
   
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



#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE     1000 
#define SAMPLE_RANGE    8000  

short m[BUFFER_SIZE] = {0};           // Initial Message
float s[SAMPLE_RANGE] = {0};          // QPSK modulated signal
short recm[BUFFER_SIZE] = {0};        // Recovered Message

extern void encodeQPSK(short message[], float signal[], int size);
extern void decodeQPSK(float signal[], short message[], int size);

void main(void)
{
    int i;

    // Initialize random number generator
    srand(2008);

    // Generate Random message
    for(i = 0; i < BUFFER_SIZE; ++i)
     {
        m[i] = (short)(rand() % 2);
     }
  
    // encode message
    encodeQPSK(m, s, BUFFER_SIZE);

    // decode s the received message is in recm
    decodeQPSK(s, recm, SAMPLE_RANGE); 

    /*
      If you want to see the constellation diagram go 
      View Menu > Graph  > Constellation and set the
	  x-address the Ik address from qpsk.c
	  y-address the Qk address from qpsk.c
	  x-axis [-2,2]  y-axis[-2,2]
      Constellation Points: 500
    */    

    return;
}

