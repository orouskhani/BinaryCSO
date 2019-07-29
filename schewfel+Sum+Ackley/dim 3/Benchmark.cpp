/******************************************/
/***        Author: Pei-Wei Tsai        ***/
/***   E-mail: pwtsai@bit.kuas.edu.tw   ***/
/***         Version: 2.0.0.0           ***/
/***   Released on: November 1, 2009    ***/
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

	if(i_fn==1)	// schwefel Function
	{
		for(j=0;j<i_dim-1;j++){
			d_result += (-1*d_pos[j]*sin(sqrt(abs(d_pos[j]))));
		}
	}
	else if(i_fn==2)	// Sum of different power functions
	{
		for(j=0;j<i_dim;j++)
		{
			d_result += pow(abs(d_pos[j]),j+1);
		}
	}
	else if(i_fn==3)	// Ackley functions
	{
		for(j=0;j<i_dim;j++)
		{
			d_tmp[0] += pow(d_pos[j],2);
			d_tmp[1] += cos(d_PII*d_pos[j]);
		}
		d_tmp[0] = d_tmp[0]/i_dim;
		d_tmp[0] = -1 * 0.2 * sqrt(d_tmp[0]);
		
		d_tmp[1] = d_tmp[1]/i_dim;

	
		d_result= -1 * 20 * exp(d_tmp[0]) - exp(d_tmp[1]) + 20 + exp(1);
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