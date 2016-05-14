#include "Indice2D.h"
#include "cudaTools.h"

#include <stdio.h>
#include <curand_kernel.h>
#include "ReduceTools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void montecarlo(curandState* ptrTabDevGeneratorGM, int* ptrDevN0,
		int nbFlechettes);
__global__ void setup_kernel_rand(curandState* tabGeneratorThread,
		int deviceId);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static __device__ void reduceIntraThread(int* tabSM, curandState* ptrTabDevGeneratorGM, int nbFlechettes);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * output : void required !!
 */
__global__ void montecarlo(curandState* ptrTabDevGeneratorGM, int* ptrDevN0,
		int nbFlechettes)
{
	extern __shared__ int tabSM[];
	reduceIntraThread(tabSM, ptrTabDevGeneratorGM, nbFlechettes);
	__syncthreads();
	reduceIntraBlock (tabSM);
	reduceInterBlock(tabSM, ptrDevN0);
}

__global__ void setup_kernel_rand(curandState* tabGeneratorThread, int deviceId)
{
	int tid = Indice2D::tid();
	//Customisation du generator: Proposition (au lecteur de faire mieux)
	// Contrainte : Doit etre différent d'un GPU à l'autre
	int deltaSeed = deviceId * INT_MAX;
	int deltaSequence = deviceId * 100;
	int deltaOffset = deviceId * 100;
	int seed = 1234 + deltaSeed;
	int sequenceNumber = tid + deltaSequence;
	int offset = deltaOffset;
	curand_init(seed, sequenceNumber, offset, &tabGeneratorThread[tid]);
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__device__ void reduceIntraThread(int* tabSM, curandState* ptrTabDevGeneratorGM,
		int nbFlechettes)
{
	const int NB_THREAD = Indice2D::nbThread();
	const int TID = Indice2D::tid();
	int s = TID;

	// Global Memory -> Registre
	curandState localState = ptrTabDevGeneratorGM[TID];

	while (s < nbFlechettes)
	{
		//if curand uniform.y < f (curand uniform.x) --> tabSM[TID_LOCAL]++
		tabSM[s] = curand_uniform(&localState);
		s += NB_THREAD;
	}
}

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
