/*
 * ntlc.c
 *
 *  Created on: Jul 29, 2014
 *      Author: martin
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <gcrypt.h>
#include "ntlc.h"


/*Functions to setup the ring*/
int Init(void)
{	//chekc is needed
	if (!gcry_check_version (NULL))
	{
	printf ("test\n");
	printf ("libgcrypt version mismatch\n ");
	}

	/* ... If required, other initialization goes here. */
	/* Tell Libgcrypt that initialization has completed. */
	gcry_control (GCRYCTL_INITIALIZATION_FINISHED, 0);

	return 0;
}
int setQ(long q,long ringIndex)
{
	if((ringIndex+1)>getIndex())							//check if the ring array already has this element
	{
		setIndex(ringIndex);
		if(NULL==(Q = realloc(Q,(getIndex()+1)*sizeof(long))) )
		{
			printf("not enough memory to generate Ring\n");				//if not enough memory is available prompt error
			return -1;
		}
	}
	Q[ringIndex]=q;										//assign a value for the Ring
	return 0;
}

long getQ(long ringIndex)
{
	return Q[ringIndex];
}

int setIndex(long ringIndex)
{
	NumberOfRings=ringIndex;
	return 0;
}

long getIndex(void)
{
	return NumberOfRings;
}

int setDeg(long deg,long ringIndex)
{
	if((ringIndex+1)>getIndex())											//check if the ring array already has this element
	{
		setIndex(ringIndex);
		if(NULL==(Deg = realloc(Deg,(getIndex()+1)*sizeof(long))))
			{
				printf("not enough memory to generate Ring\n");				//if not enough memory is available prompt error
				return -1;
			};

	}
	Deg[ringIndex]=deg;														//assign a value for the Ring
	return 0;
}

long getDeg(long ringIndex)
{
	return Deg[ringIndex];
}


long mod(long in, long ringIndex)
{
	return in%Q[ringIndex];
}

long modDeg(long in, long index)
{
	return in%Deg[index];
}



/*generate empty Element*/
long* emptyElement(long index)
{
	long *elem;
	int i=0;
	if( NULL ==(elem = malloc(getDeg(index)*sizeof(long))) )					//allocate required memory for the ring
			{printf("not enough memory to generate Ring\n");				//if not enough memory is available prompt error
			return (long*) -1;
			}
	for(i=0;i<getDeg(index);i++)												//generate a random number for every parameter
		{
			elem[i]=0;
		}
	return elem;
}

//function to initiate randomness
int initRandom(void)
{
	srand (time(NULL));
	return 0;
}

//returns a random element
long* randElement(long index)
{
	long *elem;
	int i=0;
	if( NULL ==(elem = malloc(getDeg(index)*sizeof(long))) )					//allocate required memory for the ring
				{printf("not enough memory to generate Ring\n");				//if not enough memory is available prompt error
				return (long*) -1;
				}
	for(i=0;i<getDeg(index);i++)												//generate a random number for every parameter
	{
		elem[i]=mod(rand(),index);
	}

return elem;
}

long* randNormElement(long index)
{
	long *elem;
	int i=0;
	float u,v,test; 																	//variables needed to generate normal distribution
	if( NULL ==(elem = malloc(getDeg(index)*sizeof(long))) )					//allocate required memory for the ring
				{printf("not enough memory to generate Ring\n");				//if not enough memory is available prompt error
				return (long*) -1;
				}
	for(i=0;i<getDeg(index);i++)												//generate a random number for every parameter
	{
		u=(float)rand()/RAND_MAX;
		v=(float)rand()/RAND_MAX;
		test=(sqrt(-2*log(u))*cos(TWO_PI*v));

		test=round(test*getQ(index)+0.5);													//discretesize values
		elem[i]=mod(test+getQ(index)*3,index);											//adding 3 times the modulus to the number to make sure that it isnt negative
	}

return elem;
}
void randTest()
{
	int array[20];
	int i=0;
	for(i=0;i<20;i++)
		array[i]=0;


float u,v,test;
	for(i=0;i<10000;i++)												//generate a random number for every parameter
		{
			u=(float)rand()/RAND_MAX;
			v=(float)rand()/RAND_MAX;
			test=(sqrt(-2*log(u))*cos(TWO_PI*v));
			if(test>2||test<-2){
				i--;
				continue;
			}

			test=round(test*7+0.5);													//discretesize values
			array[(int)(test-1)]++;
		}
for(i=0;i<20;i++)
	printf("%d: %d\n",i,array[i]);
}
/*operators*/
long* add(long* ele1, long* ele2, long index)
{
	int i=0;
	long *ele3=emptyElement(index);
	for(i=0;i<getDeg(index);i++)
		{
			ele3[i]=mod(ele1[i]+ele2[i],index);
		}
	return ele3;
}

long* sub(long* ele1, long* ele2, long index)
{
	int i=0;
	long *ele3=emptyElement(index);
	for(i=0;i<getDeg(index);i++)
		{
			ele3[i]=mod(ele1[i]-ele2[i]+getQ(index),index);
		}
	return ele3;
}

long* mult(long* ele1, long* ele2, long index)
{
	int i,m,pow;
	long *ele3=emptyElement(index);
		for(i=0;i<getDeg(index);i++)						//current power of ele 1
		{
			for(m=0;m<getDeg(index);m++)					//current power of ele 2
			{	pow=modDeg(i+m,index);							//calculate the new power of the product
				ele3[pow]=mod(ele3[pow]+ele1[i]*ele2[m],index);
			}
		}
	return ele3;
}


/*misc functions*/
void printEle(long* ele ,long index)
{
int i=0;
for (i=0;i<getDeg(index);i++)
	{
	printf("%d ",ele[i]);
	}
}
