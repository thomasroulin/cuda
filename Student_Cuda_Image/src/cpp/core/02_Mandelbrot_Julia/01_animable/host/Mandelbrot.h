#pragma once

#include "cudaTools.h"
#include "MathTools.h"

#include "Animable_I_GPU.h"
using namespace gpu;

/* ========== DECLARATION =========== */

class Mandelbrot: public Animable_I<uchar4>
{
	/* ---------- PUBLIC ---------- */

	/* ~~~~~~~~~~ CONSTRUCTEUR ~~~~~~~~~~ */

public:

	Mandelbrot(const Grid& grid, uint width, uint height, float t, uint n,
			const DomaineMath &domaineMath);

	virtual ~Mandelbrot(void);

	/* ~~~~~~~~~~ Methodes ~~~~~~~~~~ */

	/* ---------- OVERRIDE ANIMABLE_I ---------- */

	/**
	 * Called periodically by the api
	 */

	virtual void process(uchar4* ptrTabPixels, uint width, uint height,
			const DomaineMath &domaineMath);

	/**
	 * Called periodically by the api
	 */

	virtual void animationStep();

	/* ---------- PRIVATE ---------- */

private:

	/* ---------- ATTRIBUTS ---------- */

	// Inputs
	uint n;
	float t;
};
