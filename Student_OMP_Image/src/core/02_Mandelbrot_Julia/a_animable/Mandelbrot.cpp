#include "Mandelbrot.h"
#include "MandelbrotMath.h"

#include <iostream>
#include <omp.h>
#include "OmpTools.h"

#include "IndiceTools_CPU.h"
using cpu::IndiceTools;

using std::cout;
using std::endl;

/* ========== DECLARATION ========== */

/* ---------- PUBLIC ---------- */

Mandelbrot::Mandelbrot(uint width, uint height, float deltaTime, uint n,
		const DomaineMath &domaineMath) :
		Animable_I<uchar4>(width, height, "Mandelbrot Roulin", domaineMath), variateurAnimation(
				Interval<float>(0, 2 * PI), deltaTime)
{
	// Inputs
	this->n = n;

	// Tools
	this->t = 0;
	this->parallelPatern = ParallelPatern::OMP_MIXTE;

	// OMP
	cout << "\n[Mandelbrot] : OMP : nbThread = " << this->nbThread << endl;
}

Mandelbrot::~Mandelbrot(void)
{
	// Rien
}

/* ~~~~~~~~~~ OVERRIDES ~~~~~~~~~~ */

void Mandelbrot::animationStep()
{
	this->t = variateurAnimation.varierAndGet();
}

/**
 * Override (code naturel omp)
 */
void Mandelbrot::processForAutoOMP(uchar4 *ptrTabPixels, uint width,
		uint height, const DomaineMath &domaineMath)
{
	//Set up cuda
	MandelbrotMath mandelbrotMath(this->n);

#pragma omp parallel for
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int s = IndiceTools::toS(width, i, j);

			workPixel(&ptrTabPixels[s], i, j, domaineMath, &mandelbrotMath);
		}
	}
}

/**
 * Override (code entrainement cuda)
 */
void Mandelbrot::processEntrelacementOMP(uchar4 *ptrTabPixels, uint width,
		uint height, const DomaineMath &domaineMath)
{
	// Set up cuda
	MandelbrotMath mandelbrotMath(n);

	const int NB_PIXELS = width * height;

#pragma omp parallel
	{
		const int NB_THREAD = OmpTools::getNbThread();

		const int T_ID = OmpTools::getTid();
		int s = T_ID;

		int i, j;

		while(s < NB_PIXELS)
		{
			IndiceTools::toIJ(s, w, &i, &j);

			workPixel(&ptrTabPixels[s], i, j, domaineMath, &mandelbrotMath);

			s += NB_THREAD;
		}
	}
}

void Mandelbrot::workPixel(uchar4* ptrColorIJ, int i, int j,
		const DomaineMath& domaineMath, MandelbrotMath* ptrMandelbrotMath)
{
	double x, y;
	domaineMath.toXY(i, j, &x, &y);

	ptrMandelbrotMath->colorXY(ptrColorIJ, x, y, t);
}
