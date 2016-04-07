#pragma once

#include <math.h>
#include "MathTools.h"

#include "ColorTools_GPU.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*				Public					*|
 \*-------------------------------------*/

class RipplingMath
{
	/*--------------------------------------*\
	|*		Constructeur		*|
	 \*-------------------------------------*/

public:

	__device__ RipplingMath(uint w)
	{
		this->dim2 = w / 2;
	}

	// constructeur copie: pas besoin car pas attribut ptr

	__device__
	 virtual ~RipplingMath(void)
	{
		// rien
	}

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

public:

	__device__
	void colorIJ(uchar4* ptrColorIJ, int i, int j, float t)
	{
		uchar levelGris;

		f(i, j, t, &levelGris);

		ptrColorIJ->x = levelGris;
		ptrColorIJ->y = levelGris;
		ptrColorIJ->z = levelGris;

		ptrColorIJ->w = 255; //opaque
	}

private:

	__device__
	void f(int i, int j, float t, uchar* ptrlevelGris)
	{
		float valDIJ;
		dij(i, j, &valDIJ);

		*ptrlevelGris = 128 + 127 * cos((valDIJ / 10.0) - (t / 7.0)) / (valDIJ / 10.0 + 1);
	}

	__device__
	void dij(int i, int j, float* ptrResult)
	{
		float fi = (float) i - dim2;
		float fj = (float) j - dim2;

		*ptrResult = sqrt(fi * fi + fj * fj);
	}

	/*--------------------------------------*\
	|*		Attribut			*|
	 \*-------------------------------------*/

private:

// Tools
	double dim2;

};

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
