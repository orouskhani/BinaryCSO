/******************************************/
/***        Author: Pei-Wei Tsai        ***/
/***   E-mail: pwtsai@bit.kuas.edu.tw   ***/
/***         Version: 2.0.0.0           ***/
/***   Released on: November 1, 2009    ***/
/******************************************/

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "CSO_lib.h"
#include "Benchmark.h"
int penaltyCounter = 0;
int i_numBit = 0;
double d_InitLInCSOLib;
double d_InitRInCSOLib;
double Rand() // This subroutine returns a random value in the range [0.0, 1.0].
{
  double d_ret;
  d_ret=((double)random()/(pow(2.0,31.0)-1.0));
  return d_ret;
}

void RandSeq(int i_num,int i_seq[]) // This subroutine returns the random sequence with i_num elements.
{
  int i_tmp[2], i;
  double d_tmp;

  for(i=0;i<i_num;i++)
    i_seq[i]=i;

  for(i=0;i<i_num;i++)
  {
    d_tmp=(Rand()*(double)i_num);
    i_tmp[0]=(int)d_tmp;
    i_tmp[1]=i_seq[i_tmp[0]];
    i_seq[i_tmp[0]]=i_seq[i];
    i_seq[i]=i_tmp[1];
  }
}

void CSO_Initialization(tcat t_cat[],int i_PSize,int i_Dim,double d_InitL,double d_InitR,double d_MaxVel,int i_FN)
{
  int i, j, i_tmp;
  int *i_seq = NULL;
  double d_tmp;
  double *d_copy = NULL;

d_InitLInCSOLib = d_InitL;
d_InitRInCSOLib = d_InitR;

  i_numBit = (double)(log((d_InitR - d_InitL) * pow(10 , 5))) / (double)(log(2)) + 1;

  int i_NTracing;                       // Contains the number of cats to be selected to move in the tracing mode.

  d_tmp=MR*(double)i_PSize;             // MR is defined in the "CSO_lib.h".
  i_NTracing=(int)d_tmp;                // The number of cats to move in the tracing mode.

  d_copy = new double [i_Dim];

  i_seq = new int [i_PSize];


  /* Randomly spread the cats into the solution space - Start */
  for(i=0;i<(i_PSize+1);i++)            // The for-loop for initializing the cats.
  {
    t_cat[i].STFlag=0;                  // Set the Seeking/Tracing flag to be deactivated.
    for(j=0;j<i_Dim;j++)                // The for-loop for initializin the dimensions and the velocities of a cat.
    {
      int* bd_pos = new int[i_numBit];
      for(int k = 0 ; k < i_numBit ; k++){
	bd_pos[k] = random() % 2;
      }

       int dec = 0;
       int numOfInts = 0;
      while(i_numBit - numOfInts - 1 >= 0){
	dec += bd_pos[numOfInts] * pow(2 , i_numBit - numOfInts - 1);
	numOfInts++;
	}

      
      t_cat[i].d_pos[j]= d_InitL + dec * ((double)(d_InitR-d_InitL) / (double)(pow(2 , i_numBit) - 1));  

//((Rand()*(d_InitR-d_InitL))+d_InitL); // Set the coordinate of the cat randomly in the initial range.
      t_cat[i].d_vel[j]=((Rand()*(2.0*d_MaxVel))-d_MaxVel);   // Set the velocity of the cat randomly in the range of the maximum velocity.
    }                                   // End of the for-loop of the dimension setting.
  }                                     // End of the for-loop of the initialization.
  /* Randomly spread the cats into the solution space - End   */

  /* Calculate the randomly generated near best solution's fitness vaule - Start */
  for(j=0;j<i_Dim;j++)
    d_copy[j]=t_cat[i_PSize].d_pos[j];  // Copy the coordinate of the cat for further usage.

  t_cat[i_PSize].val=Benchmark(i_FN,i_Dim,d_copy);  // Calculate the fitness value of the randomly generated near best solution.
  /* Calculate the randomly generated near best solution's fitness vaule - End   */

  /* Pick i_NTracing cats and set their STFlage to be activated - Start */
  RandSeq(i_PSize,i_seq);

  for(j=0;j<i_NTracing;j++)
    t_cat[i_seq[j]].STFlag=1;
  /* Pick i_NTracing cats and set their STFlage to be activated - End   */

  delete [] d_copy;
  delete [] i_seq;
}

void CSO_Evaluation(tcat t_cat[],int i_PSize,int i_Dim,bool b_Maximize,int i_FN)
{
  int i, j , k;
  double *d_copy = NULL;

  d_copy = new double [i_Dim];

  for(i=0;i<i_PSize;i++)
  {
    for(j=0;j<i_Dim;j++)
    {
      d_copy[j]=t_cat[i].d_pos[j];
    }
    t_cat[i].val=Benchmark(i_FN,i_Dim,d_copy);  // Calculate the fitness value of the ith cat.

    /* If the current solution is better than the stored one, update the best solution in the memory. - Start */
    if(b_Maximize)  // If the goal is to find the near maximum solution, goes into this part of the program.
    {
      if(t_cat[i_PSize].val<t_cat[i].val)
      {
        t_cat[i_PSize].val=t_cat[i].val;
        for(j=0;j<i_Dim;j++)
        {
          t_cat[i_PSize].d_pos[j]=t_cat[i].d_pos[j];
        }
//        printf("The near best solution is updated!\n");
      }
    }
    else            // If the goal is to find the near minimum solution, goes into this part of the program.
    {
      if(t_cat[i_PSize].val>t_cat[i].val)
      {
        t_cat[i_PSize].val=t_cat[i].val;
        for(j=0;j<i_Dim;j++)
        {
          t_cat[i_PSize].d_pos[j]=t_cat[i].d_pos[j];
        }
//        printf("The near best solution is updated!\n");
      }
    }
    /* If the current solution is better than the stored one, update the best solution in the memory. - End   */
  }
  delete [] d_copy;
}

double sig(double velocity , double max , double min){

	double result = ((double)(max - velocity)) / ((double)(max - min));//(double) 1 / (double)(1 + exp(-1 * velocity));
//	printf("velocity is : %f result is : %f \n" , velocity , result);
	return result;
}

void CSO_Tracing_Mode(tcat t_cat[],int i_tg,int i_PSize,int i_Dim,double d_MaxVel)
{
  int i;
  double d_minus=(0-1.0*d_MaxVel);

  for(i=0;i<i_Dim;i++)
  {
    t_cat[i_tg].d_vel[i]+=(Rand()*C1*(t_cat[i_PSize].d_pos[i]-t_cat[i_tg].d_pos[i])); // Update the velocity of the i_tg cat.

    /* Check if the new velocity is larger/smaller than the limitation - Start */
    if(t_cat[i_tg].d_vel[i]>d_MaxVel)
	t_cat[i_tg].d_vel[i]=d_MaxVel;
    else if(t_cat[i_tg].d_vel[i]<d_minus)
      t_cat[i_tg].d_vel[i]=d_minus;
    /* Check if the new velocity is larger/smaller than the limitation - End   */

	int* rndNumbers = new int[i_numBit];
	for(int j = 0 ; j < i_numBit ; j++){
		double randomNumber = Rand();
//		printf("i is : %d rnd is : %f \n" , i , sig(t_cat[i_tg].d_vel[i]));
		if(randomNumber < sig(t_cat[i_tg].d_vel[i] , d_MaxVel , d_minus))
		    rndNumbers[j] = 1;
		else
		    rndNumbers[j] = 0;
		
	}
	// update position of cats for binary CSO
       int dec = 0;
       int numOfInts = 0;
      while(i_numBit - numOfInts - 1 >= 0){
//	printf("i is %d rnd is : %d \n" , i , rndNumbers[numOfInts]);
	dec += rndNumbers[numOfInts] * pow(2 , i_numBit - numOfInts - 1);
	numOfInts++;
	}
	
      t_cat[i_tg].d_pos[i]= d_InitLInCSOLib + dec * ((double)(d_InitRInCSOLib-d_InitLInCSOLib) / (double)(pow(2 , i_numBit) - 1));  
//	printf("d_pos is : %f \n" , t_cat[i_tg].d_pos[i]);
  }
}


void CSO_Seeking_Mode(tcat t_cat[],int i_tg,int i_Dim,int i_FN,bool b_Maximize)
{
  int i, j, i_tmp, i_SK, i_ModDm;
  double d_tmp, d_max, d_min;
  double *d_Seeking = NULL;             // The variable to contain the copy of the seeking
  double *d_copy = NULL, *d_cpfns = NULL, *d_stfns = NULL;
  int *i_seq = NULL;

  d_Seeking = new double [(SMP*i_Dim)];// Allocate the memory to generate SMP copies of the current coordinate.

	int* dec_Seeking = new int[(SMP*i_Dim)];
  d_copy = new double [i_Dim];          // Allocate the memory to contain the coordinate, which will be sent to the benchmark function.
  d_cpfns = new double [SMP];           // Allocate the memory to contain the new fitness value.
  d_stfns = new double [SMP];           // Allocate the memory to contain the copied fitness values for sorting.
  i_seq = new int [i_Dim];              // Allocate the memory to contain the random sequence.

  d_tmp=CDC*(double)i_Dim;

  i_ModDm=(int)d_tmp;                   // The number of dimensions to be changed for one candidate.
  int i_ModBt = (int)(CBC * ((double)i_numBit));

  /* Make SMP copies of the current coordinate - Start */
  for(i=0;i<SMP;i++)
    for(j=0;j<i_Dim;j++){
      d_Seeking[((i*i_Dim)+j)]=t_cat[i_tg].d_pos[j];
      dec_Seeking[((i*i_Dim)+j)] = ((double)(t_cat[i_tg].d_pos[j] - d_InitLInCSOLib) * (pow(2 , i_numBit) - 1)) / ((double)(d_InitRInCSOLib - d_InitLInCSOLib));
//	if(dec_Seeking[((i*i_Dim)+j)] == 0)
	//	printf("%f" , (double)t_cat[i_tg].d_pos[j]);
    }
  /* Make SMP copies of the current coordinate - End   */

  if(SPC)                                         // The current coordinate is also considered as a candidate.
  {
    i_SK=(SMP-1);
    d_cpfns[(SMP-1)]=t_cat[i_tg].val;
    d_stfns[(SMP-1)]=d_cpfns[(SMP-1)];
  }
  else                                            // The current coordinate is not considered as a candidate.
    i_SK=SMP;
	
	unsigned long remainder = 0 ;
	unsigned long long total = 0;
	int counter = 0;
	int tempLeng = 100;
	int* tempBinaryArray = new int[tempLeng];
	for(int h = 0 ; h < tempLeng ; h++)
		tempBinaryArray[h] = 0;

  /* Generate the seeking spots as the candidates - Start */
  for(i=0;i<i_SK;i++)                             // The for-loop for creating the seeking spots as the candidates.
  {
    RandSeq(i_Dim,i_seq);
    for(j=0;j<i_ModDm;j++)
    {
	
	int tempNum = dec_Seeking[((i*i_Dim)+i_seq[j])];
	remainder = 0 ;
	total = 0;
	counter = 0;
//	printf("tempNum is  : %d" , tempNum);
	while(tempNum > 0){
		remainder = tempNum%2;
//		printf("counter is : %d tempNum is %d \n" , counter , tempNum);
//		total += remainder * pow( 10 , counter);
		tempBinaryArray[tempLeng - counter - 1] = remainder;
//		printf("after %llu \n" , total);
		counter++;
		tempNum /= 2;
        }
	

	//printf("dec is : %d counter is : %d \n" , dec_Seeking[((i*i_Dim)+i_seq[j])] , counter);
	int* totalArray = new int[tempLeng];
	//	printf("2\n");
//	printf("man raftam \n");
//	printf("dec is : %d \n" , 	dec_Seeking[((i*i_Dim)+i_seq[j])]);
        for(int r = 0 ; r < tempLeng ; r++){
	    totalArray[r] = tempBinaryArray[ r ];
//	    printf("%d" , totalArray[r] );
	}
//	printf("\n");
//	printf("%d \n" , dec_Seeking[((i*i_Dim)+i_seq[j])]);
//	printf("before \n");
        for(int r = counter - 1 ; r >=0 ; r--){
//	    printf("%d" , totalArray[99 - r] );
	}
//	printf("\n");
	
	int rndDimLength = i_ModBt;
	int* rndBits = new int[rndDimLength];
	for(int s = 0 ; s < rndDimLength ; s++){
		rndBits[s] = random() %  i_numBit;
	}

	for(int k = 0 ; k < i_ModBt ; k++){
		if(totalArray[99 - rndBits[k]] == 0)
			totalArray[99 - rndBits[k]] = 1;
		else
			totalArray[99 - rndBits[k]] = 0;
	}
//	printf("after \n");
        for(int r = counter - 1 ; r >=0 ; r--){
//	    printf("%d" , totalArray[99 - r] );
	}
//	printf("\n");
        
	int dec = 0;
       int numOfInts = 0;

      while(i_numBit - numOfInts - 1 >= 0){
	dec += totalArray[99 - numOfInts] * pow(2 , i_numBit - numOfInts - 1);
	numOfInts++;
	}
	dec_Seeking[((i*i_Dim)+i_seq[j])] = dec;
	
	d_Seeking[((i*i_Dim)+i_seq[j])] = d_InitLInCSOLib + dec * ((double)(d_InitRInCSOLib-d_InitLInCSOLib) / (double)(pow(2 , i_numBit) - 1));  	
	if(!((d_Seeking[((i*i_Dim)+j)] <= d_InitRInCSOLib) && (d_Seeking[((i*i_Dim)+j)] >= d_InitLInCSOLib))){
		printf("penalty %d %f \n" , dec , d_Seeking[((i*i_Dim)+i_seq[j])]);
	}
    }
    bool penaltyFlag = false;
    for(j=0;j<i_Dim;j++){
	if(d_Seeking[((i*i_Dim)+j)] <= d_InitRInCSOLib && 
d_Seeking[((i*i_Dim)+j)] >= d_InitLInCSOLib){
		d_copy[j]=d_Seeking[((i*i_Dim)+j)];
		//printf("d_copy[%d] is : %f \n" , j , d_copy[j]);
	}

	else{ 
		d_copy[j]=d_InitLInCSOLib + Rand() * ( d_InitRInCSOLib - d_InitLInCSOLib );  
		penaltyCounter++;       
//		printf("i is : %d j is : %d penalty flag set to true %d \n" , i , j , d_Seeking[((i*i_Dim)+j)]);
		penaltyFlag = true;
	}

    }

    d_cpfns[i]=Benchmark(i_FN,i_Dim,d_copy);      // Calculate the fitness value of the seeking spot.
    if(penaltyFlag)
	d_cpfns[i] += 0.5;
    d_stfns[i]=d_cpfns[i];                        // Copy the fitness value for sorting.
  }                                               // End of the for-loop for creating the seeking spots.
  /* Generate the seeking spots as the candidates - End   */

  /* Calculate the chance to movie to the candidate spots - Start */
  for(i=0;i<SMP;i++)                              // Bubble sort to sort the fitness value of the candidates - Start
  {
    for(j=1;j<SMP;j++)
    {
      if(d_stfns[j]<d_stfns[j-1])                 // The smaller element will be moved to the front of the sequence.
      {
        d_tmp=d_stfns[j-1];
        d_stfns[j-1]=d_stfns[j];
        d_stfns[j]=d_tmp;
      }
    }
  }                                               // Bubble sort to sort the fitness value of the candidates - End
  d_max=d_stfns[(SMP-1)];                         // Record the maximum fitness value of the candidates.
  d_min=d_stfns[0];                               // Record the minimum fitness value of the candidates.

  for(i=0;i<SMP;i++)                              // Calculate the chance of the candidate to be picked.
  {
    if((d_stfns[0]-d_stfns[(SMP-1)])==0.0)        // Check if all the candidates present the same fitness vaule.
      d_stfns[i]=1.0;                             // If the candidates persent the same fitness, set the chance to be "1.0" for all of them since there is no difference to pick any of them.
    else
    {
      if(b_Maximize)                              // If the goal is to find the near maximum solution, FSb=FSmin, otherwise FSb=FSmax.
        d_stfns[i]=(fabs(d_cpfns[i]-d_min)/(d_max-d_min));
      else
        d_stfns[i]=(fabs(d_cpfns[i]-d_max)/(d_max-d_min));
    }
  }
  /* Calculate the chance to movie to the candidate spots - End   */

  /* Pick a candidate spot to move to - Start */
  d_tmp=Rand();                                   // Generate a random number in [0,1].
  for(i=0;i<SMP;i++)
  {
    if(b_Maximize)
    {
      if(d_tmp<=d_stfns[i])
      {
        for(j=0;j<i_Dim;j++)
          t_cat[i_tg].d_pos[j]=d_Seeking[(i*i_Dim)+j];
        break;
      }
    }
    else
    {
      if(d_tmp<=d_stfns[i])
      {
        for(j=0;j<i_Dim;j++){
          t_cat[i_tg].d_pos[j]=d_Seeking[(i*i_Dim)+j];
		//printf("pos is : %f \n" , t_cat[i_tg].d_pos[j]);
	  }
        break;
      }
    }
  }
  /* Pick a candidate spot to move to - End   */
	
//	printf("penalty counter is : %d \n" , penaltyCounter);
  delete [] d_Seeking;
  delete [] d_copy;
  delete [] d_cpfns;
  delete [] d_stfns;
  delete [] i_seq;
}

void CSO_Movement(tcat t_cat[],int i_PSize,int i_Dim,bool b_Maximize,int i_FN,double d_MaxVel)
{
  int i_NTracing;                       // Contains the number of cats to be selected to move in the tracing mode.
  double d_tmp;
  int i, *i_seq;

  d_tmp=MR*(double)i_PSize;             // MR is defined in the "CSO_lib.h".
  i_NTracing=(int)d_tmp;                // The number of cats to move in the tracing mode.

  i_seq= new int [i_PSize];             // Allocate a memory space to contain the series number of the cats.

  for(i=0;i<i_PSize;i++)                // All the cats should take turns to move according to their STFlags.
  {
    if(t_cat[i].STFlag)                 // This cat should go into the Tracing mode.
      CSO_Tracing_Mode(t_cat,i,i_PSize,i_Dim,d_MaxVel);
    else                                // This cat should go into the Seeking mode.
      CSO_Seeking_Mode(t_cat,i,i_Dim,i_FN,b_Maximize);

    t_cat[i].STFlag=0;                  // Set the STFlags of all the cats to be deactivated.
  }

  /* Pick i_NTracing cats and set their STFlage to be activated - Start */
  RandSeq(i_PSize,i_seq);

  for(i=0;i<i_NTracing;i++)
    t_cat[i_seq[i]].STFlag=1;
  /* Pick i_NTracing cats and set their STFlage to be activated - End    */

  delete [] i_seq;
}
