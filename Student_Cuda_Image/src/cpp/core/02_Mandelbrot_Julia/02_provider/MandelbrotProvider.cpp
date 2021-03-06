#include "MandelbrotProvider.h"
#include "MathTools.h"
#include "Grid.h"
#include "../01_animable/host/Mandelbrot.h"

using namespace gpu;

/* ========== DECLARATION =========== */

/* ---------- IMPORTED ---------- */

/* ---------- PUBLIC ---------- */

/* ---------- PRIVATE ---------- */

/* ========== IMPLEMENTATION ========== */

/* ---------- PUBLIC ---------- */

/* ---------- OVERLOADS ---------- */

/**
 * Override
 */
Animable_I<uchar4>* MandelbrotProvider::createAnimable(void)
{
	int n = 102;
	DomaineMath domaineMath = DomaineMath(-2.1, -1.3, 0.8, 1.3);

//	int n = 102;
//	DomaineMath domaineMath = DomaineMath(-1.3968, -0.03362, -1.3578, 0.0013973);

	float dt = 0.0f;

	//Dims
	int dw = 16 * 80;
	int dh = 16 * 60;

	dim3 dg = dim3(32, 2, 1);
	dim3 db = dim3(32, 32, 1);
	Grid grid(dg, db);

	return new Mandelbrot(grid, dw, dh, dt, n, domaineMath);
}

/**
 * Override
 */
Image_I* MandelbrotProvider::createImageGL(void)
{
	ColorRGB_01 textColor(0, 0, 0); // black
	return new ImageAnimable_RGBA_uchar4(createAnimable(), textColor);
}

/* ---------- PRIVATE ---------- */
