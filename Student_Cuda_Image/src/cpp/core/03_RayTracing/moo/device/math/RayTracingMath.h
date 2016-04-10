#pragma once

#include <math.h>
#include "MathTools.h"

#include "Calibreur_GPU.h"
#include "ColorTools_GPU.h"
using namespace gpu;

/* ========== DECLARATION ========== */

class RayTracingMath
{
	/* ---------- PUBLIC ---------- */

public:
	/* ---------- CONSTRUCTEUR ---------- */

	__device__ RayTracingMath()
	{
		// Nope
	}

	__device__
	virtual ~RayTracingMath()
	{
		// Nope
	}

	/* ---------- METHODES ---------- */

	__device__
	void colorXY(uchar4 *ptrColor, float x, float y, float t)
	{
		//f(x, y, t, &ptrColor);
		ptrColor->x = 0;
		ptrColor->y = 50;
		ptrColor->z = 120;
		ptrColor->w = 0;
	}

private:

	__device__
	void f(float x, float y, float t, uchar4* ptrColor)
	{
	}

	/* ---------- ATTRIBUTS ---------- */
};
