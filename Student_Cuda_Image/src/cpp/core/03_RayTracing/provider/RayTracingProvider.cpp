//#include "RayTracingProvider.h"
//
//#include "RayTracing.h"
//
//#include "MathTools.h"
//
//#include "ImageAnimable_GPU.h"
//using namespace gpu;
//
///**
// * Override
// */
//Animable_I<uchar4>* RayTracingProvider::createAnimable(void)
//{
//	float dt = 2 * PI / 800;
//
//	// Dimension
//	int dw = 16 * 60 * 2;
//	int dh = 16 * 60;
//
//	dim3 dg = dim3(32, 2, 1);
//	dim3 db = dim3(16, 16, 1);
//	Grid grid(dg, db);
//
//	uint nbSphere = 50;
//
//	return new RayTracing(grid, dw, dh, dt, nbSphere);
//}
//
///**
// * Override
// */
//Image_I* RayTracingProvider::createImageGL(void)
//{
//	ColorRGB_01 colorTexte(0, 0, 0); // black
//	return new ImageAnimable_RGBA_uchar4(createAnimable(), colorTexte);
//}
