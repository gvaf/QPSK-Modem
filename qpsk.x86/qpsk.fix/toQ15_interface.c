/*
    MEXFUNCTION is a MATLAB/C interface for the convertion function Q15
    By George Vafiadis for University of Bristol
	
  Compile first the module  with 
      >>     mex toQ15_interface.c	.
 There is a wrapper function toQ15(X)  which is a matlab wrapper function around the Q15_interface(X) C function.
*/

#include "mex.h"
#include <stdio.h>
#include <math.h>

void mexFunction ( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] );
short toQ15(double num);
short Q15(int a);

void mexFunction ( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] )
/*
  Purpose:

    MEXFUNCTION is a MATLAB/C interface for the convertion function Q15

  Parameters:

    Input, int NLHS, the number of output arguments.

    Input, mxArray *PLHS[NLHS], pointers to the output arguments.

    Input, int NRHS, the number of input arguments.

    Input, const mxArray *PRHS[NRHS], pointers to the input arguments.
*/
{
  double x;
  int *y_pointer;
  int q15;
  mwSize dim[2] = { 1, 1};
  
  x = mxGetScalar ( prhs[0] );
 
  q15 = toQ15(x);
  
  plhs[0] = mxCreateNumericArray ( 2, dim, mxINT32_CLASS, mxREAL );

  y_pointer = (int *)mxGetPr ( plhs[0] );
  *y_pointer = q15;

  return;
}

short Q15(int a)
{
 if( a >= 0 ) return  (a >> 15) ?  (a >> 15) : a;
 else         return  (-a >> 15) ? -(-a >> 15) : a;
}

short toQ15(double num)
{
 short n;
 int a;

 if( num >= 1.0 ) 
    n = 32767;
 else if( num <= -1 )
    n = -32768;
 else
  {
    a = (int)(num * pow(2.0, 15));

    if( a <= -32768 )
      n = -32768;    
    else if( a >= 32768 )
      n = 32767;
    else
      n = Q15(a);
  }

  return n;
}

