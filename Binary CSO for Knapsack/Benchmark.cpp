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

			// Knapsack Initialization

int d_rndValues[20];
int d_rndWeights[20];
int LimitedWeights;
double alpha = 10000;
bool isInitialized = false;
void initialBenchmark(){
	if(!isInitialized){
	for(int i = 0 ; i < 20 ; i++){
		d_rndValues[i] = random() % 80 + 10;
		printf("%d " , d_rndValues[i]);
	}
		printf("\n");
	int sum = 0;
	for(int i = 0 ; i < 20 ; i++){
		d_rndWeights[i] = random() % 400 + 100;
		sum += d_rndWeights[i];
		printf("%d " , d_rndWeights[i]);	
	}
	printf("\n");
	LimitedWeights = 0.6 * sum;
	printf("%d \n" , LimitedWeights);
	isInitialized = true;
}
	
}
sol Benchmark(int i_fn,int i_dim,double d_pos[])
{
	int i, j;
	double d_tmp[4];	// variables for temporary storage.
	double d_result;	// cotains the result to return to the main program.
	sol result;  
	result.cost = 0;
	result.sumWX = 0;
	result.sumVX = 0;
	result.values = new int[i_dim];
	result.weights = new int[i_dim];
	for(int i = 0 ; i < i_dim ; i++){
		result.values[i] = 0;
		result.weights[i] = 0;
		
	}
	
	/* initialize the parameters - Start */
	for(i=0;i<4;i++)
		d_tmp[i]=0.0;
	/* initialize the parameters - End   */

	if(i_fn==1)	// Knapsack Function
	{
		for(j=0;j<(i_dim);j++){
      			d_tmp[0]+= d_rndValues[j] * ( 1 - d_pos[j] );
			d_tmp[1] += d_rndWeights[j] * d_pos[j]; 
		}
		double max = (((double)(d_tmp[1]) / (double)(LimitedWeights) - 1 ) > 0) ? (((double)(d_tmp[1]) / (double)(LimitedWeights) - 1 ) > 0) : 0;

		d_result = d_tmp[0] + alpha * max;
		result.cost = d_result;
		result.values = new int[i_dim];
		result.weights = new int[i_dim];
		
		for(int i = 0 ; i < i_dim ; i++){
			result.values[i] = d_rndValues[i];
			result.weights[i] = d_rndWeights[i];
			result.sumVX += d_rndValues[i] * d_pos[i];  			
			result.sumWX += d_rndWeights[i] * d_pos[i];

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
