/******************************************/
/***        Author: Yasin Orouskhani        ***/
/***   E-mail: orouskhani@ce.sharif.edu   ***/
/***         Version: 2.0.0.0           ***/
/***   Released on: April 20, 2013    ***/
/******************************************/

/* The "Benchmark.h" and the "Benchmark.cpp" composes a library contains i_FuncNum test functions. */
#include "Benchmark.h"			// Include its header file.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double Benchmark(int i_fn,int i_dim,double d_pos[])
{
	int i, j;
	double d_tmp[4];	// variables for temporary storage.
	double d_result = 0;	// cotains the result to return to the main program.
  
	/* initialize the parameters - Start */
	for(i=0;i<4;i++)
		d_tmp[i]=0.0;
	/* initialize the parameters - End   */

	if(i_fn==1)	// Trid10 Function
	{
		for(i = 0 ; i < i_dim ; i++){
			d_tmp[0] += pow(d_pos[i] - 1 , 2);
		}
		for(i = 1 ; i < i_dim ; i++){
			d_tmp[1] += d_pos[i] * d_pos[i-1];
		}
		d_result = d_tmp[0] - d_tmp[1];
	}
	else if(i_fn==2)	// Zakharov functions
	{
		for(i = 0 ; i < i_dim ; i++){
			d_tmp[0] += pow(d_pos[i] , 2);
		}

		for(i = 0 ; i < i_dim ; i++){
			d_tmp[1] += 0.5 * i * d_pos[i];
		}
		d_result = d_tmp[0] + pow(d_tmp[1] , 2) + pow(d_tmp[1] , 4);

	}
	else if(i_fn==3)	// Powell functions
	{
		for(i = 1 ; i <= ( i_dim / 4 ) ; i++){
			d_tmp[0] = pow(d_pos[4 * i - 3] + 10 * d_pos[ 4 * i - 2] , 2);
			d_tmp[1] = 5 * pow( d_pos[ 4 * i - 1 ] - d_pos[4 * i], 2 );
			d_tmp[2] = pow( d_pos[ 4 * i - 2 ] - d_pos[4 * i - 1 ], 4 );
			d_tmp[3] = 10 * pow( d_pos[ 4 * i - 3 ] - d_pos[4 * i], 4 );
			d_result += d_tmp[0] + d_tmp[1] + d_tmp[2] + d_tmp[3];
		}
	}
/*
	else if(i_fn==4)	// Test Function 4
	{
	}
	else if(i_fn==5)  // Test Function 5
	{
	}
	else // Test Function 6
	{
	}
*/

  return d_result;
}
