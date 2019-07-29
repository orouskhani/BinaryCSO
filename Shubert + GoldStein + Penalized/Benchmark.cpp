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

double u(double xi , double a , double k , double m){
	if (xi > a){
		return k * pow((xi - a) , m);
	}
	if(xi < -1 * a){
		return k * pow((-1 * xi - a) , m);
	}
	return 0;
}

double yi(double xi){
	return 1 + ((double)1 / (double)4) * (xi + 1);
}
double Benchmark(int i_fn,int i_dim,double d_pos[])
{
	int i, j;
	double d_tmp[4];	// variables for temporary storage.
	double d_result = 0;	// cotains the result to return to the main program.
  
	/* initialize the parameters - Start */
	for(i=0;i<4;i++)
		d_tmp[i]=0.0;
	/* initialize the parameters - End   */

	if(i_fn==1)	// Shubert Function
	{
		for(i = 0 ; i < i_dim ; i++ )
			d_tmp[0] += (i+1)* cos((i+2) * d_pos[0] + (i+1));
		for(i = 0 ; i < i_dim ; i++ )
			d_tmp[1] += (i+1)* cos((i+2) * d_pos[1] + (i+1));

		d_result = d_tmp[0] * d_tmp[1];


	}
	else if(i_fn==2)	// GoldStein functions
	{
		d_tmp[0] = 1 + (pow(d_pos[0] + d_pos[1] + 1 , 2)) * (19 - 14 * d_pos[0] + 3 * pow(d_pos[0] , 2 ) - 14 * d_pos[1] + 6 * d_pos[0] * d_pos[1] + 3 * pow(d_pos[1] , 2));
		d_tmp[1] = 30 + (pow(2 * d_pos[0] - 3 * d_pos[1] , 2)) * (18 - 32 * d_pos[0] + 12 * pow(d_pos[0] , 2 ) + 48 * d_pos[1] - 36 * d_pos[0] * d_pos[1] + 27 * pow(d_pos[1] , 2));
		d_result = d_tmp[0] * d_tmp[1];
	}
	else if(i_fn==3)	// Penalized functions
	{
		d_tmp[0] = 10 * pow(sin(d_PIE * yi(d_pos[0])) , 2);
		for(i = 0 ; i < i_dim - 1 ; i++){
			d_tmp[1] += pow(yi(d_pos[i]) - 1 , 2) * (1 + 10 * pow(sin(d_PIE * d_pos[i+1]) , 2)) + pow( yi(d_pos[i_dim - 1] - 1), 2);
		}
		for(i = 0 ; i < i_dim ; i++){
			d_tmp[2] += u(d_pos[i] , 10 , 100 , 4);
		}
		d_result = ((double) d_PIE) / ((double)i_dim) * (d_tmp[0] + d_tmp[1] ) + d_tmp[2]; 
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
