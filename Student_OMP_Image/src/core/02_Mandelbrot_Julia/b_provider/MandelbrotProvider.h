#pragma once

#include "Animable_I_CPU.h"
#include "Provider_I_CPU.h"

using namespace cpu;

/* ========== DECLARATION ========== */

// ========== PUBLIC
class MandelbrotProvider: public Provider_I<uchar4>
{
public:

	virtual ~MandelbrotProvider()
	{
		// Nope
	}

	/* ---------- OVERRIDE ---------- */

	Animable_I<uchar4>* createAnimable(void);

	Image_I* createImageGL(void);
};
