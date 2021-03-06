#pragma once

#include "cudaTools.h"
#include "MathTools.h"

#include "Animable_I_GPU.h"
using namespace gpu;

/* ========== DECLARATION =========== */

class Julia: public Animable_I<uchar4>
{
	/* ---------- PUBLIC ---------- */

	/* ~~~~~~~~~~ CONSTRUCTEUR ~~~~~~~~~~ */

public:

	Julia(const Grid& grid, uint width, uint height, float t, uint n, float c1, float c2,
			const DomaineMath &domaineMath);

	virtual ~Julia(void);

	/* ~~~~~~~~~~ Methodes ~~~~~~~~~~ */

	/* ---------- OVERRIDE ANIMABLE_I ---------- */

	/**
	 * Called periodically by the api
	 */

	virtual void process(uchar4* ptrTabPixels, uint width,
			uint height, const DomaineMath &domaineMath);

	/**
	 * Called periodically by the api
	 */

	virtual void animationStep();

	/* ---------- PRIVATE ---------- */

private:

	/* ---------- ATTRIBUTS ---------- */

	// Inputs
	uint n;
	float c1;
	float c2;
	float t;
};
