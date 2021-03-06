#include "Slice.h"

#include "Device.h"
#include <iostream>

using std::cout;
using std::endl;

extern __global__ void slice(float* ptrDevPi, int nbSlice);

Slice::Slice(int nbSlice) :
		nbSlice(nbSlice)
{
	this->sizeOctetPi = sizeof(float);

	// MM
	{
		// MM (malloc Device)
		{
			HANDLE_ERROR(cudaMalloc(&ptrDevPi, sizeOctetPi));
		}

		// MM (memset Device)
		{
			HANDLE_ERROR(cudaMemset(ptrDevPi, 0, sizeOctetPi));
		}

		// MM (copy Host->Device)
		{
			// Nope
		}

		Device::lastCudaError("Slice MM (end allocation)"); // temp debug
	}

	{
		this->dg = dim3(16, 2, 1);
		this->db = dim3(256, 1, 1); // contrainte, produit des 3 = 2^n

		Device::gridHeuristic(dg, db);
	}

	this->sizeOctetSM = db.x * db.y * db.z * sizeof(float);
	// assert contrainte
}

Slice::~Slice(void)
{
	//MM (device free)
	{
		HANDLE_ERROR(cudaFree(ptrDevPi));

		Device::lastCudaError("Slice MM (end deallocation)"); // temp debug
	}
}

void Slice::run()
{
	Device::lastCudaError("Slice (before)"); // temp debug
	slice<<<dg,db, sizeOctetSM>>>(ptrDevPi, nbSlice); // assynchrone
	Device::lastCudaError("Slice (after)"); // temp debug

//	Device::synchronize(); // Temp, only for printf in  GPU
	{
		HANDLE_ERROR(
				cudaMemcpy(&pi, ptrDevPi, sizeOctetPi, cudaMemcpyDeviceToHost)); // barriere synchronisation implicite
	}

	pi /= nbSlice;
}

float Slice::getPi()
{
	return this->pi;
}
