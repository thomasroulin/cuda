#include "Julia.h"
#include "JuliaMath.h"

#include <iostream>
#include <omp.h>
#include "OmpTools.h"

#include "IndiceTools_CPU.h"
using cpu::IndiceTools;

using std::cout;
using std::endl;

/* ========== DECLARATION ========== */

/* ---------- PUBLIC ---------- */

Julia::Julia(uint width, uint height, float deltaTime, uint n,
		float c1, float c2, const DomaineMath &domaineMath) :
		Animable_I<uchar4>(width, height, "Julia Roulin", domaineMath), variateurAnimation(
				Interval<float>(0, 2 * PI), deltaTime)
{
	// Inputs
	this->n = n;
	this->c1 = c1;
	this->c2 = c2;

	// Tools
	this->t = 0;
	this->parallelPatern = ParallelPatern::OMP_MIXTE;

	// OMP
	cout << "\n[Julia] : OMP : nbThread = " << this->nbThread << endl;
}

Julia::~Julia(void)
{
	// Rien
}

/* ~~~~~~~~~~ OVERRIDES ~~~~~~~~~~ */

void Julia::animationStep()
{
	this->t = variateurAnimation.varierAndGet();
}

/**
 * Override (code naturel omp)
 */
void Julia::processForAutoOMP(uchar4 *ptrTabPixels, uint width,
		uint height, const DomaineMath &domaineMath)
{
	// Set up cuda
	JuliaMath juliaMath(this->n, this->c1, this->c2);

#pragma omp parallel for
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int s = IndiceTools::toS(width, i, j);

			workPixel(&ptrTabPixels[s], i, j, domaineMath, &juliaMath);
		}
	}
}

/**
 * Override (code entrainement cuda)
 */
void Julia::processEntrelacementOMP(uchar4 *ptrTabPixels, uint width,
		uint height, const DomaineMath &domaineMath)
{
	//Set up cuda
	JuliaMath juliaMath(this->n, this->c1, this->c2);

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

			workPixel(&ptrTabPixels[s], i, j, domaineMath, &juliaMath);

			s += NB_THREAD;
		}
	}
}

void Julia::workPixel(uchar4* ptrColorIJ, int i, int j,
		const DomaineMath& domaineMath, JuliaMath* ptrJuliaMath)
{
	double x, y;
	domaineMath.toXY(i, j, &x, &y);

	ptrJuliaMath->colorXY(ptrColorIJ, x, y, t);
}
