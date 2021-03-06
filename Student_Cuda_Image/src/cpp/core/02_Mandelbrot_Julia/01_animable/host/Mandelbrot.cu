#include <iostream>
#include <assert.h>

#include "Device.h"
#include "Mandelbrot.h"
#include "DomaineMath_GPU.h"

using std::cout;
using std::endl;

/* ========== DECLARATION ========== */

extern __global__ void mandelbrot(uchar4* ptrDevPixels, uint w, uint h, float t, uint n, DomaineMath domaineMath);

/* ---------- PUBLIC ---------- */

Mandelbrot::Mandelbrot(const Grid &grid, uint width, uint height, float t,
		uint n, const DomaineMath &domaineMath) :
		Animable_I<uchar4>(grid, width, height, "Mandelbrot Roulin",
				domaineMath)
{
	// Inputs
	this->n = n;

	// Tools
	this->t = t;
}

Mandelbrot::~Mandelbrot(void)
{
	// Rien
}

/* ~~~~~~~~~~  METHODS  ~~~~~~~~~~ */
/**
 * Override
 * Call periodicly by the API
 *
 * Note : domaineMath pas use car pas zoomable
 */
void Mandelbrot::process(uchar4* ptrDevPixels, uint w, uint h,
		const DomaineMath& domaineMath)
{
	Device::lastCudaError("mandelbrot rgba uchar4 (before)"); // facultatif, for debug only, remove for release

	// start kernel
	mandelbrot<<<dg, db>>>(ptrDevPixels, w, h, t, n, domaineMath);

	Device::lastCudaError("mandelbrot rgba uchar4 (after)"); // facultatif, for debug only, remove for release
}

/* ~~~~~~~~~~ OVERRIDES ~~~~~~~~~~ */

void Mandelbrot::animationStep()
{
	this->t += t;
}

/**
 * Override (code naturel omp)
 */
