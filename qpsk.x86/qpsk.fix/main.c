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
#include <time.h>

#define BUFFER_SIZE     1000 
#define SAMPLE_RANGE    8000  

extern void encodeQPSK(short message[], short signal[], int size);
extern void decodeQPSK(short signal[], short message[], int size);

int main(int argc, char *argv[])
{   
    short m[BUFFER_SIZE] = {0};
    short recm[BUFFER_SIZE] = {0};
    short s[SAMPLE_RANGE] = {0};
    int i;

    srand((unsigned int)time(0));

    printf("Original Message:\n");

    for(i = 0; i < BUFFER_SIZE; ++i)
     {
        m[i] = rand() % 2;
        printf("%d " , m[i]);
     }
    printf("\n");
  
    encodeQPSK(m, s, BUFFER_SIZE);

    decodeQPSK(s, recm, SAMPLE_RANGE); 

    printf("\n"); 

    printf("Demodulated Message:\n");

    for(i = 0; i < BUFFER_SIZE; ++i)
       printf("%d " , recm[i]);

    printf("\n");  

    return 0;
}
