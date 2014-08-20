/*
 * ntlc.h
 *
 *  Created on: Jul 29, 2014
 *      Author: martin
 */

#ifndef NTLC_H_
#define NTLC_H_
#include <gcrypt.h>

#define TWO_PI 6.2831853071795864769252866 		//required for calculation of normal distributed variables


static long *Q; 				//generate the global list for the Ring for the modulus
static long *Deg;				//generate the global list for the degree of rings
static long NumberOfRings;			//number of Rings currently used
//static long *Elements;			//generate a list of all Elements used


int Init();
/*Functions to set the maximum value of the ring elements*/

int setQ(long q,long ringIndex);


long getQ(long ringIndex);


int setIndex(long ringIndex);


long getIndex(void);



long mod(long in, long ringIndex);

long modDeg(long in, long index);

/*Functions to set the degree of the ring*/

int setDeg(long deg,long ringIndex);


long getDeg(long ringIndex);





/*generate empty Element*/
long* emptyElement(long index);
int initRandom(void);

long* randElement(long index);

long* randNormElement(long index);

long* add(long* ele1, long* ele2, long index);

long* sub(long* ele1, long* ele2, long index);

void printEle(long* ele ,long index);
long* mult(long* ele1, long* ele2, long index);
void randTest();

/*functions for mpi*/

/*create a new secure number*/
void mpiNew(int,gcry_mpi_t );

void mpiOut2(gcry_mpi_t);
void mpiOut(gcry_mpi_t, size_t);
#endif /* NTLC_H_ */
