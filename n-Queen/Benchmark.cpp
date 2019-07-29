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

	
sol Benchmark(int i_fn,int i_dim,double d_pos[])
{
	int i, j;
	double d_tmp[4];	// variables for temporary storage.
	double d_result;	// cotains the result to return to the main program.
	sol result;  
	result.cost = 0;
	result.sortedOrder = new int[i_dim];
	result.hit = new int*[i_dim];
	for( i = 0 ; i < i_dim ; i++){
		result.sortedOrder[i] = 0;
		result.hit[i] = new int[i_dim];
		for( j = 0 ; j < i_dim ; j++)
			result.hit[i][j] = 0;
		
	}
	
	/* initialize the parameters - Start */
	for(i=0;i<4;i++)
		d_tmp[i]=0.0;
	/* initialize the parameters - End   */

	if(i_fn==1)	// n-Queen Function
	{
		double* sortedPosition = new double[i_dim];
		for(i = 0 ; i < i_dim ; i++)
			sortedPosition[i] = d_pos[i];

		double tmp;
		for( i = 0 ; i < i_dim ; i++){
			for( j = i ; j < i_dim ; j++){
				if(sortedPosition[i] > sortedPosition[j]){
					tmp = sortedPosition[i];
					sortedPosition[i] = sortedPosition[j];
					sortedPosition[j] = tmp;
				}	
			}
		}

		double* sortedOrder = new double[i_dim];
		bool* sortedFlags = new bool[i_dim];
		for(i = 0 ; i < i_dim ; i++)
			sortedFlags[i] = true;
		for(i = 0 ; i < i_dim ; i++){
			for(j = 0 ; j < i_dim ; j++){
				if((sortedPosition[i] == d_pos[j]) && sortedFlags[j]){
					sortedOrder[i] = j;			
					sortedFlags[j] = false;		
					break;
				}
			}
		}

		int* d_col = new int[i_dim];
		for(i = 0 ; i < i_dim ; i++){
			d_col[i] = i;
		}
		
		int** hit = new int*[i_dim];
		for(i = 0 ; i < i_dim ; i++)
			hit[i] = new int[i_dim];
		
		int z = 0;

		for(i = 0 ; i < i_dim ; i++){
			for(j = i+1 ; j < i_dim ; j++){
			if(abs(sortedOrder[i] - sortedOrder[j]) == abs(d_col[i] - d_col[j])){
				hit[i][j] = 1;
				hit[j][i] = 1;
				z++;
			}
			}
		}

		d_result = z;
		result.cost = d_result;
		result.hit = new int*[i_dim];
		for(j = 0 ; j < i_dim ; j++)
			result.hit[j] = new int[i_dim];
		result.sortedOrder = new int[i_dim];
		for(i = 0 ; i < i_dim ; i++){
			result.sortedOrder[i] = sortedOrder[i];
		}

		for(i = 0 ; i < i_dim ; i++){
			for(j = 0 ; j < i_dim ; j++ )
				result.hit[i][j] = hit[i][j];
		}

	}
	else if(i_fn==2)	// Rastrigrin Function
	{
	}
	else if(i_fn==3)	// Griewank Function
	{
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

  return result;
}
