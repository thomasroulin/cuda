#pragma once

#include <math.h>
#include "MathTools.h"

#include "Calibreur_CPU.h"
#include "ColorTools_CPU.h"
using namespace cpu;

/* ========== DECLARATION ========== */

class JuliaMath
{
	/* ---------- PUBLIC ---------- */

public:
	/* ---------- CONSTRUCTEUR ---------- */

	JuliaMath(uint n, float c1, float c2) :
			calibreur(Interval<float>(0.0, n), Interval<float>(0.0, 1.0))
	{
		this->n = n;
		this->c1 = c1;
		this->c2 = c2;
	}

	virtual ~JuliaMath()
	{
		// rien
	}

	/* ---------- METHODES ---------- */

	void colorXY(uchar4 *ptrColor, float x, float y, float t)
	{
		float k = getK(x, y);

		if(k > n)
		{
			ptrColor->x = 0;
			ptrColor->y = 0;
			ptrColor->z = 0;
		}else
		{
			float hue = k;
			calibreur.calibrer(hue);
			ColorTools::HSB_TO_RVB(hue, ptrColor);
		}

		ptrColor->w = 255;
	}

private:

	bool isDivergent(float z)
	{
		return z > 2.0 ? true : false;
	}

	int getK(float x, float y)
	{
		float zr = x;
		float zi = y;
		float old_zr;

		int k = 0;
		while(k <= this->n)
		{
			if(isDivergent(norm(zr, zi)))
				return k;

			old_zr = zr;
			zr = pow(zr, 2) - pow(zi, 2) + this->c1;
			zi = 2 * old_zr * zi + this->c2;

			k++;
		}

		return k;
	}

	float norm(float a, float b)
	{
		return sqrt(pow(a, 2) + pow(b, 2));
	}

	/* ---------- ATTRIBUTS ---------- */

	// Input
	uint n;
	float c1;
	float c2;

	// Tools
	Calibreur<float> calibreur;
};
